
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <time.h>

struct person  
{ 
    int id; 
    char username[256]; 
    char password[256]; 
}; 
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
void newUser(){
    

    char user[256],pass[256];
    srand(time(0));
    system("clear");
    printf("Register : \n");
    printf("Username:");
    fgets(user,256,stdin);
    printf("Password:");
    fgets(pass,256,stdin);
    int r = rand()%10;

    struct person input;
    input.id = r;
    strcpy(input.username,user);
    strcpy(input.password,pass);
    FILE *outfile; 
      
    // open file for writing 
    outfile = fopen ("person.dat", "a"); 
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    } 
    fwrite (&input, sizeof(struct person), 1, outfile); 
      
    if(fwrite != 0)  
        printf("contents to file written successfully !\n"); 
    fclose (outfile); 
}
int oldUser(char testuser[20]){
  FILE *infile; 
    struct person input1; 
    // Open person.dat for reading 
    infile = fopen ("person.dat", "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
      
    // read file contents till end of file 
    while(fread(&input1, sizeof(struct person), 1, infile)) 
        {
          if( strncmp(testuser,input1.username,7)==0){
               return input1.id; 
          }

        }
  
    // close file 
    fclose (infile); 
    return -1;
}

int passCheck(int id, char testpass[256]){
  FILE *infile; 
    struct person input1; 
      // Open person.dat for reading 
    infile = fopen ("person.dat", "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
      
    // read file contents till end of file 
    while(fread(&input1, sizeof(struct person), 1, infile)) 
        {
          if( input1.id == id && strncmp(testpass,input1.password,strlen(testpass))==0){
                fclose (infile);
               return 1; 
          }

        }
  
    // close file 
    fclose (infile); 
    return 0;
}


int main(int argc, char *argv[])
{
     char command[50],mes[256];
     int ans , choice;
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256],username[256],password[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;



     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     

     if (newsockfd < 0) 
          error("ERROR on accept");
     L: system("clear");
     printf("Connection Established\n");
     
     printf("Authenticating Client\n");
      
     n = write(newsockfd,"Username: ",strlen("Username: "));  
        if (n < 0) error("ERROR writing to socket");
        
        read(newsockfd, username, 255);  
        
        n = write(newsockfd,"Password: ",strlen("Password: "));  
        if (n < 0) error("ERROR writing to socket");
        read(newsockfd, password, 255);  
     int o = passCheck(oldUser(username),password);
     
    printf("Authentication Successfull\n\n\n");
    goto S;



 S:  
    n = write(newsockfd,"Enter your choice : \n1.MKD\n2.CWD\n3.RMD\n4.PWD\n5.STOR\n6.LIST\n7.RETR\n8.ABORT\n9.QUIT\n",strlen("Enter your choice : \n1.MKD\n2.CWD\n3.RMD\n4.PWD\n5.STOR\n6.LIST\n7.RETR\n8.ABORT\n9.QUIT\n"));         //Ask for choice    
     if (n < 0) error("ERROR writing to socket");
     choice = NULL;
     read(newsockfd, &choice, sizeof(int));					//Read choice
     
     printf("Client - Choice is : %d\n" , choice);	
     
     char filename[256],dest_file[256];
      switch(choice)
     {
     	case 1:
            n = write(newsockfd,"MKD\n",strlen("MKD\n"));         //Ask for choice    
            if (n < 0) error("ERROR writing to socket");
            bzero(filename,255);
    
            read(newsockfd, filename, 255);
            sprintf(command,"mkdir %s >> log.txt",filename);
            int m = system(command);

            if (m == 0){
                
                sprintf(mes,"200: Directory %s created Successfully\n", filename);
                n = write(newsockfd,mes,strlen(mes));         //Ask for choice    
                if (n < 0) error("ERROR writing to socket");
            }
            else {
                sprintf(mes,"504: Command not implemented for that parameter.\n");
                n = write(newsockfd,mes,strlen(mes));         //Ask for choice    
                if (n < 0) error("ERROR writing to socket");   
            }
            break;
     	case 2:
     		n = write(newsockfd,"CWD\n",strlen("CWD\n"));         //Ask for choice    
            if (n < 0) error("ERROR writing to socket");
             
            bzero(filename,256);
            read(newsockfd, filename, 255);
            printf("%s\n",filename );
            
            sprintf(command,"cd %s ",filename);
            m = system(command);
            
            break;
     	case 3:
                bzero(filename,256);                      
        
     		    n = write(newsockfd,"RMD\n",strlen("RMD\n"));         //Ask for choice    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd, filename, 255);
                sprintf(command,"rm -r %s >> log.txt",filename);
                 m = system(command);
         		if (m == 0){
                    
                    sprintf(mes,"200: Directory %s removed Successfully\n", filename);
                    n = write(newsockfd,mes,strlen(mes));         //Ask for choice    
                    if (n < 0) error("ERROR writing to socket");
                }
                else {
                    sprintf(mes,"504: Command not implemented for that parameter.\n");
                    n = write(newsockfd,mes,strlen(mes));         //Ask for choice    
                    if (n < 0) error("ERROR writing to socket");   
                }

            break;
     	case 4:
                n = write(newsockfd,"PWD\n",strlen("PWD\n"));         //Ask for choice    
                if (n < 0) error("ERROR writing to socket");
                 system("pwd >> command.txt ");
                 printf("2\n");
                
         		break;
     	case 5 :
                bzero(filename,256);

                n = write(newsockfd,"STOR\n",strlen("STOR\n"));         //Ask for choice    
                if (n < 0) error("ERROR writing to socket");
                int ch = 0;
                n = read(newsockfd,filename,255);                //Read Server String
                if (n < 0) 
                   error("ERROR reading from socket");
                printf("%s\n",filename );
                sprintf(dest_file,"dest_%s",filename);
                
                FILE *fp;
                    fp = fopen(dest_file,"a");            
                    int words;
                read(newsockfd, &words, sizeof(int));
                //printf("Passed integer is : %d\n" , words);      //Ignore , Line for Testing
                while(ch != words)
                   {
                     read(newsockfd , buffer , 512); 
                    printf("%s\n",buffer );
                    fprintf(fp , " %s" , buffer);   
                 //printf(" %s %d "  , buffer , ch); //Line for Testing , Ignore
                 ch++;
               }
         

                

            break;
        case 6: //              system("rm list.txt");
                system("ls -l >> list.txt");
                sleep(0.8);
               n = write(newsockfd,"LIST\n",strlen("LIST\n"));         //Ask for choice    
               if (n < 0) error("ERROR writing to socket");
                        
                break;
        case 7: 
                bzero(buffer,255);
                n = write(newsockfd,"RETR\n",strlen("RETR\n"));         //Ask for choice    
                if (n < 0) error("ERROR writing to socket");
            F:  n = read(newsockfd,filename,255);                //Read Server String
                if (n < 0) 
                   error("ERROR reading from socket");
                
                sprintf(command,"find %s ",filename);
                m = system(command);
                if(m == 0)
                {
                    n = write(newsockfd,"proceed\n",strlen("proceed\n"));         //Ask for choice    
                    if (n < 0) error("ERROR writing to socket");

                
                }
                else if(m != 0)
                {
                    n = write(newsockfd,"504: Command not implemented for that parameter.\n",strlen("504: Command not implemented for that parameter.\n"));         //Ask for choice    
                    if (n < 0) error("ERROR writing to socket");
                    goto F;
                
                }
                
                FILE *f;
                words = 0;
                char c;
                    
                 f=fopen(filename,"r");
                while((c=getc(f))!=EOF)         //Counting No of words in the file
                {   
                    fscanf(f , "%s" , buffer);
                    if(isspace(c)||c=='\t')
                    words++;    
                }
                write(sockfd, &words, sizeof(int));
                    rewind(f);
                  
                 
                char chh ;
                while(chh != EOF)
                {
                   
                   fscanf(f , "%s" , buffer);
                   //printf("%s\n" , buffer);  //Ignore
                   write(newsockfd,buffer,512);
                   chh = fgetc(f);
                }
             
                n = write(newsockfd,"200: File Sent Successfully.\n",strlen("200: File Sent Successfully.\n"));         //Ask for choice    
                if (n < 0) error("ERROR writing to socket");
          
                break;
        case 8:
                bzero(username,256);
                bzero(password,256);
                goto L;
                break;

        case 9:
 		         goto Q;
     		     break;
    }
     
    // write(newsockfd , &ans , sizeof(int));
     if(choice != 9)
     {
            choice = NULL;
            goto S;
     }
    
   Q:  close(newsockfd);
     close(sockfd);
     return 0; 
}



