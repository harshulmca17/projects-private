#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct person  
{ 
    int id; 
    char username[20]; 
    char password[20]; 
}; 
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
void newUser(){
    

    char user[20],pass[20];
    srand(time(0));
    system("clear");
    printf("Register : \n");
    printf("Username:");
    fgets(user,20,stdin);
    printf("Password:");
    fgets(pass,20,stdin);
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
void oldUser(){
  FILE *infile; 
    struct person input1; 
      char testuser[20] = "wert",testpass[20] = "wert";
    // Open person.dat for reading 
    infile = fopen ("person.dat", "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
      
    // read file contents till end of file 
    while(fread(&input1, sizeof(struct person), 1, infile)) 
        printf ("id = %d name = %s - %s \n", input1.id, 
        input1.username, input1.password); 
  
    // close file 
    fclose (infile); 
}

int main(){
  
    newUser();
    oldUser();
     /* If you want to send input to command */
   //  fclose(fp);
  return 0 ;
}