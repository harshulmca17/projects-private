/*Name : Jay Jagtap
3154037
Problem Statement: To implement client-server calculator.
*/

/*
	Server Side
	Please pass port no as command line argument
*/
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     char command[50],mes[255];
     int ans , choice;
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[1024],username[255],password[255];
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
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     
     printf("Connection Established\n");
     printf("Authenticating Client\n");

     n = write(newsockfd,"Username: ",strlen("Username: "));  
     if (n < 0) error("ERROR writing to socket");
     read(newsockfd, username, 255);  
//    printf("%s askjdhjs  2nd%s\n",username,password );
     n = write(newsockfd,"Password: ",strlen("Password: "));  
     if (n < 0) error("ERROR writing to socket");
     read(newsockfd, password, 255); 
     int check1 = strncmp("harshul",username,7);
     int check2 = strncmp("harshul",password,7);
     if( check1 == 0 )
    {
        if (check2 == 0)
        {   


            n = write(newsockfd,"accept",strlen("accept"));  
            if (n < 0) error("ERROR writing to socket");
        }
        else{
            printf("Invalid Client Details\nAborting Connection\n");
            

            n = write(newsockfd,"decline",strlen("decline"));  
            if (n < 0) error("ERROR writing to socket");
            exit(1);

        }
    }
    else{
        printf("Invalid Client Details\nAborting Connection\n");
        n = write(newsockfd,"decline",strlen("decline"));  
        if (n < 0) error("ERROR writing to socket");
     
        exit(1);
    }

     
    printf("Authentication Successfull\n\n\n");
    bzero(username,255);
    read(newsockfd, username, 255);
    goto S;



 S:  n = write(newsockfd,"Enter your choice : \n1.MKD\n2.CWD\n3.RMD\n4.PWD\n5.RMD\n6.List\n7.Exit\n",strlen("Enter your choice : \n1.MKD\n2.CWD\n3.RMD\n4.PWD\n5.RMD\n6.List\n7.Exit\n"));         //Ask for choice    
     if (n < 0) error("ERROR writing to socket");
     read(newsockfd, &choice, sizeof(int));					//Read choice
     printf("Client - Choice is : %d\n" , choice);	
     
     char filename[255];
      switch(choice)
     {
     	case 1:
            n = write(newsockfd,"MKD\n",strlen("MKD\n"));         //Ask for choice    
            if (n < 0) error("ERROR writing to socket");
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
     		printf("CWD\n");
     		break;
     	case 3:
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
            
            
     		break;
     	case 5 :
            break;
        case 6:system("ls -l");
                 n = write(newsockfd,"LIST\n",strlen("LIST\n"));         //Ask for choice    
            if (n < 0) error("ERROR writing to socket");
                break;
        case 7:
 
 		goto Q;
     		break;
     }
     
    // write(newsockfd , &ans , sizeof(int));
     if(choice != 7)
     	goto S;
    
   Q:  close(newsockfd);
     close(sockfd);
     return 0; 
}



/*
Server side terminal:
jj@ubuntu:~/Desktop$ gcc Server.c -o Server
jj@ubuntu:~/Desktop$ ./Server 4562
Client - Number 1 is : 50
Client - Number 2 is : 110
Client - Choice is : 1
Client - Number 1 is : 50
Client - Number 2 is : 60
Client - Choice is : 2
Client - Number 1 is : 4
Client - Number 2 is : 8
Client - Choice is : 3
Client - Number 1 is : 66
Client - Number 2 is : 11
Client - Choice is : 4
Client - Number 1 is : 5
Client - Number 2 is : 7
Client - Choice is : 5
jj@ubuntu:~/Desktop$ 


Client side Terminal:

jj@ubuntu:~/Desktop$ gcc client.c -o client
jj@ubuntu:~/Desktop$ ./client 192.168.244.139 4562
Server - Enter Number 1
50
Server - Enter Number 2
110
Server - Enter your choice : 
1.Addition
2.Subtraction
3.Multiplication
4.Division
5.Exit
1
Server - The answer is : 160
Server - Enter Number 1
50
Server - Enter Number 2
60
Server - Enter your choice : 
1.Addition
2.Subtraction
3.Multiplication
4.Division
5.Exit
2
Server - The answer is : -10
Server - Enter Number 1
4
Server - Enter Number 2
8
Server - Enter your choice : 
1.Addition
2.Subtraction
3.Multiplication
4.Division
5.Exit
3
Server - The answer is : 32
Server - Enter Number 1
66
Server - Enter Number 2
11
Server - Enter your choice : 
1.Addition
2.Subtraction
3.Multiplication
4.Division
5.Exit
4
Server - The answer is : 6
Server - Enter Number 1
5
Server - Enter Number 2
7
Server - Enter your choice : 
1.Addition
2.Subtraction
3.Multiplication
4.Division
5.Exit
5
You chose to exit, Thank You so much.jj@ubuntu:~/Desktop$

*/

