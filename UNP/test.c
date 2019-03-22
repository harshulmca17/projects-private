 #include<stdio.h>
#include<stdlib.h>
//using namespace std;

void main(){
	system("ls -l >> command.txt");

	FILE *fp;
	char s;
	
	if(fp=fopen("command.txt","r"))
	{
		do
		{
			s=getc(fp);
			printf("%c",s);
		}while(s!=EOF);
		fclose(fp);
		
	}

	if(fp=fopen("command.txt","w"))
	{
		do
		{
			putc(' ',fp);
		}while(s!=EOF);
		fclose(fp);
		
	}
}