
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<ctype.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int m,sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    FILE *fp;
    char s;
    char buffer[256],command[50],filename[256];
    if (argc < 3)
    {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    int num1 ;
    int num2 ;
    int ans;
    int choice;
    int option;
    L:system("clear");
    printf("Connection Established\n");

    
    
    bzero(buffer,256);                     
    n = read(sockfd,buffer,255);                //Read Server String
    if (n < 0) 
         error("ERROR reading from socket");
    printf("asas\n" );
    printf("Server - %s\n",buffer);
    
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) error("ERROR writing to socket");
        
    bzero(buffer,256);                     
    n = read(sockfd,buffer,255);                //Read Server String
    if (n < 0) 
         error("ERROR reading from socket");
    printf("Server - %s\n",buffer);
    
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) error("ERROR writing to socket");
    

    system("clear");
      
    printf("Authentication Granted\n225: Data connection open; no transfer in progress.\n");
    goto S;


  S:choice = NULL;
    bzero(buffer,255);                      
    n = read(sockfd,buffer,255);      
    if (n < 0) 
         error("ERROR reading from socket");
    
    printf("\n\n\nServer - %s\n",buffer);
    scanf("%d" , &choice);                      //Enter choice
    write(sockfd, &choice, sizeof(int));                //Send choice to Server
    printf("Choice selected is %d\n", choice );
    bzero(buffer,256);                      
    n = read(sockfd,buffer,255);                //Read Server String
    if (n < 0) 
         error("ERROR reading from socket");
    
    if (choice == 1)
    {   
        bzero(filename,256);                      
    
        int mkd = strncmp("MKD",buffer,3);
        if(mkd == 0){

        printf("Enter File Name: ");
        scanf("%s",&filename);
 //       fgets(filename,255,stdin);
        n = write(sockfd,filename,strlen(filename));
        if (n < 0) error("ERROR writing to socket");

        bzero(buffer,256);                      
        n = read(sockfd,buffer,255);                //Read Server String
        if (n < 0) 
            error("ERROR reading from socket");
        printf("%s\n", buffer );
    }
    
    }
    else if (choice == 2)
    {
        
        bzero(filename,256);                      
        int mkd = strncmp("CWD",buffer,3);
        bzero(buffer,256);                      
        if(mkd == 0){

        printf("Enter Absolute Path: ");
        scanf("%s",&filename);
        sprintf(command,"cd %s ",filename);
            m = system(command);
        n = write(sockfd,filename,strlen(filename));
        if (n < 0) error("ERROR writing to socket");

        }
       /* code */
        printf("Directory Reached.\n");
    }
    else if (choice == 3)
    {
        bzero(filename,256);                      
        int rmd = strncmp("RMD",buffer,3);
        if(rmd == 0){

            printf("Enter File Name: ");
            scanf("%s",&filename);
     //       fgets(filename,255,stdin);
            n = write(sockfd,filename,strlen(filename));
            if (n < 0) error("ERROR writing to socket");

        bzero(buffer,256);                      
        n = read(sockfd,buffer,255);                //Read Server String
        if (n < 0) 
            error("ERROR reading from socket");
        printf("%s\n", buffer );

        }    /* code */
    }
    else if (choice == 4)
    {
        int rmd = strncmp("PWD",buffer,3);
        if(rmd == 0){
        if(fp=fopen("command.txt","r"))
        {
            s = 0;
            while(s!=EOF){
                s=getc(fp);
                printf("%c", s);
            }
            
        }
        fclose(fp);
        
        system("rm command.txt");
        
      }  
    }
    else if (choice == 5)
    {       
         int rmd = strncmp("STOR",buffer,4);
         if(rmd == 0)
         {
           

                FILE *f;
    
                int words = 0;
                char c;
              F:  printf("Enter File Name: \n");
                scanf("%s",&filename);
                
                sprintf(command,"find %s ",filename);
                int m = system(command);
                if(m != 0)
                {
                    printf("File Not Found. Try Again\n");
                    goto F;
                }

            n = write(sockfd,filename,strlen(filename));
            if (n < 0) error("ERROR writing to socket");
            bzero(buffer,256);                      
        
                f=fopen(filename,"r");
                while((c=getc(f))!=EOF)         //Counting No of words in the file
                {   
                    fscanf(f , "%s" , buffer);
                    if(isspace(c)||c=='\t')
                    words++;    
                }
                write(sockfd, &words, sizeof(int));
                    rewind(f);
                  
                char ch ;
                   while(ch != EOF)
                  {
                    
                    fscanf(f , "%s" , buffer);
                    write(sockfd,buffer,512);
                    ch = fgetc(f);
                  }
                printf("The file was sent successfully");
    


            
        }
    }
    else if (choice == 6)
    {
        int list = strncmp("LIST",buffer,4);
        if(list == 0){
            
            if(fp=fopen("list.txt","r"))
            {
                s = 0;
                while(s!=EOF){
            
                    s=getc(fp);
                    printf("%c", s);
                }
            
            }
            fclose(fp);
        
        system("rm list.txt");
      } 
    }
    else if(choice == 7)
    {
        int rmd = strncmp("RETR",buffer,4);
         if(rmd == 0)
         {
          G:bzero(filename,256);
            printf("Enter File Name: \n");
            scanf("%s",&filename);
            n = write(sockfd,filename,strlen(filename));
            if (n < 0) error("ERROR writing to socket");
            bzero(buffer,256);
            n = read(sockfd,buffer,255);                //Read Server String
            if (n < 0) 
                error("ERROR reading from socket");
            int k = strncmp("504: Command not implemented for that parameter.",buffer,strlen("504: Command not implemented for that parameter."));
            if( k == 0)
            {
                printf("%s\n",buffer );
                goto G;
            }    
                FILE *fp;
                int ch=0;
                fp = fopen("recieved_file.txt","a");            
                int words;
                read(sockfd, &words, sizeof(int));
                //printf("Passed integer is : %d\n" , words);      //Ignore , Line for Testing
                while(ch != words)
                   {
                     read(sockfd , buffer , 512); 
                    printf("%s\n",buffer );
                    fprintf(fp , " %s" , buffer);   
                 printf(" %s %d "  , buffer , ch); //Line for Testing , Ignore
                 ch++;
               }
         

            bzero(buffer,256);                      
            n = read(sockfd,buffer,255);                //Read Server String
            if (n < 0) 
                error("ERROR reading from socket");
            printf("\n\n\nServer - %s\n",buffer);
        }
    }

	else if (choice == 8)
	{   
       goto L;
    }
    if(choice == 9){
        goto Q;
    }
    if(choice != 9)
    {       
            goto S;
     }
    	
Q:  printf("You chose to exit, Thank You so much.\n");
     	
       
   
    
    close(sockfd);
    return 0;
}



