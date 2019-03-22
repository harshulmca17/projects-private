#include<iostream>
 #include<stdio.h>
#include<stdlib.h>
//#include<conio.h>
using namespace std;

int main(){
	cout<<system("rm  Harshul >> command.txt");

	FILE *fp;
	char s;
	
	if(fp=fopen("text.txt","r"))
	{
		do
		{
			s=getc(fp);
			cout<<s;
		}while(s!=EOF);
		fclose(fp);
		
	}
//	getch();
}