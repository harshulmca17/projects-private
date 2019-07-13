#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <mutex>
#include <queue>
#include <stack>
#include <chrono>
#include <condition_variable>

struct sleepQueue           //  sleepQueue is used to keep track of allocated 
{                           //  buffer along with their process(thread)
    int block;
    std::thread::id p_id;
}obj;


using namespace std;
    
enum field {locked=1,unlocked=2,valid=3,not_valid=4,delay=5 }; //status field

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

  
struct BUFFER {   //
                  // book specified buffer header structure   
    int block_num;
    int device_num;
    int hash_Q;
    enum field status;


    struct BUFFER* previous_hash_buffer;
    struct BUFFER* next_hash_buffer;
    
    struct BUFFER* previous_free_buffer;
    struct BUFFER* next_free_buffer;
     
}; 

condition_variable convar;  // to make a thread sleep and wake perticular thread from sleep
    
int number = 4;
struct BUFFER* FREE = NULL;
struct BUFFER* BUFFER_POOL[4];


std::mutex mu;              // to ensure concurrency and consistency in buffer pool
queue<sleepQueue> waitingQ; 
stack <int> async_write;    

//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: hash_calculate
    purpose: to calculate hash for required buffer and
             linked to its respective buffer pool

*/
int hash_calcuate (int block,int n){

        int hash_queue = block%n;
        return hash_queue;
}  


//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: insert_free_list_head
    purpose: to handle delay write case and append same buffer
             to the head of free list
*/

void insert_free_list_head(struct BUFFER** free_head,struct BUFFER** head_ref , int new_data) { 
    struct BUFFER* temp = *head_ref;
    while(  temp->next_hash_buffer != NULL )
     {      
        //printf("%d--\n",temp->block_num);
        if(temp->block_num == new_data)
        {   
            break;
        }
        temp = temp->next_hash_buffer;

     }   
     //printf("%d2\n",temp->block_num);
     temp->status = unlocked;
    
    struct BUFFER* last = *free_head; /* used in step 5*/
    //  new_node->block_num = new_data; 
    
    temp->next_free_buffer = (*free_head);
    (*free_head)= temp; 
  //new_node->next_free_buffer = NULL; 
       //printf("%d3\n",temp->block_num);

        

        temp->previous_free_buffer = NULL; 
//        *free_head = temp; 
  //      return; 
    return; 
}


//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: insert_free_list_end
    purpose: to linked newly freed buffer into free list but in the end

*/

void insert_free_list_end(struct BUFFER** free_head,struct BUFFER** head_ref , int new_data) { 
    struct BUFFER* temp = *head_ref;
    while(  temp->next_hash_buffer != NULL )
     {      
        //printf("%d--\n",temp->block_num);
        if(temp->block_num == new_data)
        {   
            break;
        }
        temp = temp->next_hash_buffer;

     }   
     //printf("%d2\n",temp->block_num);
     temp->status = unlocked;
    
    struct BUFFER* last = *free_head; /* used in step 5*/
    //  new_node->block_num = new_data; 
    
    temp->next_free_buffer = NULL; 
  //new_node->next_free_buffer = NULL; 
       //printf("%d3\n",temp->block_num);

    if (*free_head == NULL) { 
        

        temp->previous_free_buffer = NULL; 
        *free_head = temp; 
        return; 
    } 
    while (last->next_free_buffer != NULL) 
        last = last->next_free_buffer; 
  
    last->next_free_buffer = temp; 
    temp->previous_free_buffer = last;
    return; 
}



//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: insert_hash_queue_end
    purpose: to link new buffer into its respective 
             buffer hash queue 

*/


void insert_hash_queue_end(struct BUFFER** head_ref, int new_data) { 
    /* 1. allocate node */
    struct BUFFER* new_node = (struct BUFFER*)malloc(sizeof(struct BUFFER)); 
  
    struct BUFFER* last = *head_ref; /* used in step 5*/
  
    new_node->block_num = new_data; 
    new_node->status = locked;
    new_node->next_hash_buffer = NULL; 
  
    if (*head_ref == NULL) { 
        new_node->previous_hash_buffer = NULL; 
        *head_ref = new_node; 
        return; 
    } 
  
    while (last->next_hash_buffer != NULL) 
        last = last->next_hash_buffer; 
  
    last->next_hash_buffer = new_node; 
    
    new_node->previous_hash_buffer = last;

    return; 
} 


//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: find_buffer
    purpose: to search for a perticular buffer into a
             perticular hash queue

*/

struct BUFFER* find_buffer(struct BUFFER* node,int n){
    struct BUFFER* last; 
    //printf("\nBUFFER BLOCK %d : ",n); 
    while (node != NULL) { 
        if(node->block_num == n){
            return node;
        } 
        node = node->next_hash_buffer; 
    } 
    return NULL;    
}


//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: remove_free_list_buffer
    purpose: to required buffer from free list

*/

void remove_free_list_buffer(struct BUFFER** free_head,int n){
    struct BUFFER* last = NULL;
    struct BUFFER* node = *free_head ;

    if((*free_head)->next_free_buffer == NULL){
        (*free_head) = NULL;
    }

    else if(node->block_num == n){
        struct BUFFER* result = NULL;
        struct BUFFER* temp = (*free_head)->next_free_buffer;
        (*free_head)->next_free_buffer->previous_free_buffer = NULL;
        (*free_head)->next_free_buffer = NULL;
    
    
        result = (*free_head);
        *free_head = temp;

    }

    //printf("\nBUFFER BLOCK %d : ",n); 
    while (node->next_free_buffer != NULL) { 
        if(node->block_num == n){
            node->previous_free_buffer->next_free_buffer = node->next_free_buffer;
            node->next_free_buffer->previous_free_buffer = node->previous_free_buffer;
            node->next_free_buffer = NULL;
            node->previous_free_buffer = NULL;
            //delet(node);
            break;
        }
        node = node->next_free_buffer; 
    } 
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: print_buffer
    purpose: to print buffer pool at perticular instance

*/
  
void print_buffer(struct BUFFER* node,int n){
    struct BUFFER* last; 
    printf("\nBUFFER BLOCK %d : ",n); 
    while (node != NULL) { 
        printf(" %d ", node->block_num); 
        node = node->next_hash_buffer; 
    } 
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: print_free_list
    purpose: to print free list along with newly freed buffer

*/
void print_free_list(struct BUFFER* node){
    struct BUFFER* last; 
    printf("\nFREE BUFFER BLOCK : "); 
    while (node != NULL) { 
        printf(" %d ", node->block_num); 
        node = node->next_free_buffer; 
    } 
} 


//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: get_free_buffer
    purpose: to extract first free buffer from 
             free list

*/
struct BUFFER* get_free_buffer(struct BUFFER** head){   
        
    struct BUFFER* result = NULL;
    if( (*head) == NULL){
        return NULL;
    }
    if ((*head)->next_free_buffer == NULL)
    {
        result = (*head);
        (*head) = NULL;
    }
    else{
        struct BUFFER* temp = (*head)->next_free_buffer;
        (*head)->next_free_buffer->previous_free_buffer = NULL;
        (*head)->next_free_buffer = NULL;
        result = (*head);
        *head = temp;
        
    }
    
        return result;
}



//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: remove_hash_queue_buffer
    purpose: to remove a perticular buffer from buffer pool 

*/

void remove_hash_queue_buffer(struct BUFFER** head,int n){   
    
    struct BUFFER* temp = *head;
    while(temp->next_hash_buffer != NULL){
        if(temp->block_num == n)
            break;
        temp = temp->next_hash_buffer;
    }

    if(temp->previous_hash_buffer == NULL){
        (*head) = temp->next_hash_buffer;
        temp->next_hash_buffer->previous_hash_buffer = NULL;
        temp->next_hash_buffer = NULL;
    }
    else if(temp->next_hash_buffer == NULL){
        
        temp->previous_hash_buffer->next_hash_buffer = NULL;
        temp->previous_hash_buffer = NULL;
    }
    else{
        temp->next_hash_buffer->previous_hash_buffer = temp->previous_hash_buffer;
        temp->previous_hash_buffer->next_hash_buffer = temp->next_hash_buffer;
    }

}


//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: free_list_empty
    purpose: to check weather free list is empty or not

*/
bool free_list_empty(struct BUFFER** head){ 
    if( (*head) == NULL){
        return true;
    }
    return false;
}  



//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: brleas
    purpose: to free allocated buffer and wake 
             sleeping processes

*/
void brleas(){
        std::unique_lock<std::mutex> lock(mu);
    std::thread::id this_id = std::this_thread::get_id();
    //cout<<buffer_need;
    sleepQueue obj;
    while(!waitingQ.empty()){
        obj = waitingQ.front();
        waitingQ.pop();
    //    cout<<obj.block<<" : "<<obj.p_id<<"\n";
            struct BUFFER* temp = find_buffer(BUFFER_POOL[hash_calcuate(obj.block,number)],obj.block);
            if(temp == NULL){
                    //perror("Buffer Error Doesn't exist");
            }
            else{
                temp->status = unlocked;
                insert_free_list_end(&FREE,&BUFFER_POOL[hash_calcuate(obj.block,number)], obj.block);
                convar.notify_all();
            }   
            break;
        
    }    
}



//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: getblk
    purpose: to allocate free buffer to process(thread)
             according to the 5 scenarios

*/
void getblk(){
    
    std::thread::id this_id = std::this_thread::get_id();
    {
        std::unique_lock<std::mutex> lock(mu);
    
    
    int buffer_need;
        cout<<"\n\nEnter buffer number:";
        cin>>buffer_need;
            
F:  struct BUFFER* temp = find_buffer(BUFFER_POOL[hash_calcuate(buffer_need,number)],buffer_need);
    if(temp == NULL){
        
        if(free_list_empty(&FREE)){
            cout<<"\nScenario 4\n";
            cout<<this_id;
            cout<<"\nProcess with pid:"<<this_id<<" state changed to sleep. \n";
            cout<<"\n\n-----------------------------------------------------------------------------------------------------------------------";

           G: convar.wait(lock);
                if(free_list_empty(&FREE))
                    goto G;
                goto F;
        }
        else{
            while(1){
           A: struct BUFFER* free_buffer = get_free_buffer(&FREE);
            //printf("%d\n", free_buffer->block_num );
            if(free_buffer->status == delay){
                printf("\nScenario 3\n");
                
                printf("\nBUFFER %d status is set to delay write.\n",free_buffer->block_num);
                

                async_write.push(free_buffer->block_num);
                //insert_free_list_end(&FREE,&BUFFER_POOL[hash_calcuate(free_buffer->block_num,number)], free_buffer->block_num);        
            }
            else if(free_buffer->status == unlocked){
                printf("\nScenario 2\n");
                cout<<this_id;
                free_buffer->status= locked;
            
                remove_hash_queue_buffer(&BUFFER_POOL[hash_calcuate(free_buffer->block_num,number)],free_buffer->block_num);
                insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(buffer_need,number)], buffer_need);
                      

                cout<<"\n\n-----------------------------------------------------------------------------------------------------------------------";
                sleepQueue obj;
                obj.block = buffer_need;
                obj.p_id = this_id;
                waitingQ.push(obj);
                break;  
            }
        }
                while(!async_write.empty()){
                    int temp = async_write.top();
                    async_write.pop();
                    insert_free_list_head(&FREE,&BUFFER_POOL[hash_calcuate(temp,number)], temp);
                }
        }


        
            

    }
    else{
        
        if(temp->status == unlocked){
        
            printf("\nScenario 1\n");
            cout<<this_id;
            temp->status = locked;
            remove_free_list_buffer(&FREE,buffer_need);              
            cout<<"\n\n-----------------------------------------------------------------------------------------------------------------------";
            
            sleepQueue obj;
            obj.block = temp->block_num;
            obj.p_id = this_id;
            waitingQ.push(obj);
        }

        else if(temp->status == locked)
        {
            cout<<"\nScenario 5\n";
            cout<<this_id;
            cout<<"\nProcess with pid:"<<this_id<<" state changed to sleep. \n";
            cout<<"-----------------------------------------------------------------------------------------------------------------------";

         H: convar.wait(lock);
            if(temp->status == locked)
                goto H;
            goto F;       
        }
        else{
            goto A;
        }
    }
    }
    mu.unlock();
    cout<<"\n\n\n";    
    for (int i = 0; i < number; ++i)
     {
         print_buffer(BUFFER_POOL[i],i);
     } 
    print_free_list(FREE); 
    cout<<"\n\n";
        ////// BRELEASE()
     srand (time(NULL));
     this_thread::sleep_for(chrono::seconds(5));
     brleas();
}



//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    name: main
    purpose: to create a parent thread and execute and run child threads

*/
int main() 
{ 

    int num_p;
    cout<<"Enter no. of processes: \n";
    cin>>num_p;    
    for (int i = 0; i < number; ++i)
    {
        BUFFER_POOL[i] = NULL;
    }
    thread t[num_p];
 //   t = new thread[num_p];


    /*
    initializing buffer pool according to text book
    */
    
    insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(28,number)], 28);
    insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(4,number)], 4);
    insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(64,number)], 64);
    insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(17,number)], 17);
    insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(5,number)], 5);
    insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(97,number)],97);
    insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(98,number)], 98);
    insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(50,number)], 50);
    insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(10,number)], 10);
    insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(3,number)], 3);
    insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(35,number)], 35);
    insert_hash_queue_end(&BUFFER_POOL[hash_calcuate(99,number)], 99);
    


    insert_free_list_end(&FREE,&BUFFER_POOL[hash_calcuate(3,number)], 3);
    insert_free_list_end(&FREE,&BUFFER_POOL[hash_calcuate(5,number)], 5);
    insert_free_list_end(&FREE,&BUFFER_POOL[hash_calcuate(4,number)], 4);
    insert_free_list_end(&FREE,&BUFFER_POOL[hash_calcuate(28,number)], 28);
    insert_free_list_end(&FREE,&BUFFER_POOL[hash_calcuate(97,number)], 97);
    insert_free_list_end(&FREE,&BUFFER_POOL[hash_calcuate(10,number)], 10);
    
    
    FREE->status = delay;
    FREE->next_free_buffer->status = delay;
    
    
    for (int i = 0; i < number; ++i)
     {
         print_buffer(BUFFER_POOL[i],i);
     } 
    print_free_list(FREE); 
    srand(time(NULL));


    for (int i = 0; i < num_p; ++i)
    {                                                   // thread decleration
                                                        //  and execution of 
        t[i]=std::thread(getblk);                       //  getblk 
        std::thread::id id = std::this_thread::get_id();
        
    }
    
    for (int i = 0; i < num_p; ++i)
    {                                           // parent thread has to wait for every child thread to
        t[i].join();                            //  finish
    }


   cout<<"\nAll process executed successfully.";
    return 0; 
} 
