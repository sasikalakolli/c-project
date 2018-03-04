#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <dirent.h>
int ar[20],k,j=0;
main()
{
	int ch;
	printf("*********MAIN MENU*********\n");
	printf("     SIGN IN\npress 1 to sign in:");
	scanf("%d",&ch);
	if(ch!=1)
	  exit(0);
	printf("***IF THE PASSWORD ENTERED IS WRONG THERE ARE THREE TRALIS ONLY***\n");
	password();   
	while(1)
	{
		
		
		printf("***** MAIN MENU *****\n1.ADD RECORD\n2.VIEW RECORD\n3.DELETE RECORD\n4.EDIT RECORD\n5.exit\n");
		printf("enter your choice :");
		scanf("%d",&ch);
		switch(ch)
		{
		case 1:
			addrecord();
			break;
		case 2:
			viewrecord();
			break;
		case 3:
			deleterecord();
			break;
		case 4:
			editrecord();
			break;
		case 5:
			exit(0);
	    }
    }
    return 0;
}
password()
{
	char password[25], cho;
	int i=0;
    puts("Enter password : ");
    while (1) 
    {
      	 cho = getch();
       if (cho == 13)
         break;
         if (cho == 8)
          {
          	 printf("%c",cho);
             printf(" ");
             printf("%c",cho);
             i--;
//             continue;
	      }
		 password[i++] = cho;
         cho='*';
         printf("%c",cho);
    }
    password[i] = '\0'; 
    printArray(password,i);
    compare();
}
printArray(char * array, int n )
{ 
     int i;
     FILE *fout;
     fout = fopen("pass.txt","w");     
     for (i=0; i<n; i++)
          fprintf(fout,"%c",*(array+i));
     fclose(fout);  
     printf("\n");
}
addrecord()
{
   char sentence[1000],ch;
   FILE *fptr;
   time_t t = time(NULL);
   struct tm* t1 = localtime(&t);
   char filename[16];
   strftime (filename,9,"%d%m%Y",t1);
   strcat(filename,".txt");
   fptr=fopen(filename,"w+");
   if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }
   printf("Enter details into the file:\n");
   do
   {
   gets(sentence);
   fprintf(fptr,"%s", sentence);
   printf("to add another record press enter/to quit press (q)");
   scanf("%c",&ch);
   if(ch=='\n')
   fprintf(fptr,"%c", ch);
   }while(ch=='\n');
   fclose(fptr);
}
showfiles()
{
 	DIR *p;
  	struct dirent *pp;     
  	p = opendir ("./");
  	if (p != NULL)
  	{
   		while ((pp = readdir (p))!=NULL)
		{
      		int length = strlen(pp->d_name);
      		if (strncmp(pp->d_name + length - 4, ".txt", 4) == 0)
			{
       			puts (pp->d_name);
      		}
    	}
    	(void) closedir (p);
  	}
}
viewrecord()
{
	showfiles();
	FILE *fp;
	char fn[10],ch;
	printf("enter the file to view details:");
	scanf("%s",&fn);
	printf("the content in the file:\n");
    fp = fopen(fn, "r");
    ch = getc(fp);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fp);
    }
    fclose(fp);
    printf("\n");
}
deleterecord()
{
	showfiles();
    int s;
    char fn[25];
    printf("Enter the name of file you want to delete:\n");
    scanf("%s",&fn);
    s=remove(fn);
    if(s==0)
	{    
    	printf("%s file deleted successfully\n",fn);
    }    
    else
    {    
        printf("Unable to delete the file\n");
    }
}
editrecord()
{
	showfiles();
    FILE *fp1, *fp2;
    char fn[40];
    char ch;
    int delete_line, temp = 1;
    printf("Enter file name: ");
    scanf("%s", fn);
    fp1 = fopen(fn, "r");
    ch = getc(fp1);
    while(ch!=EOF)
    {
        printf("%c", ch);
        ch=getc(fp1);
    }
    rewind(fp1);
    printf("\nEnter line number of the line to be deleted:");
    scanf("%d",&delete_line);
    fp2=fopen("replace.c", "w");
    ch=getc(fp1);
    while(ch!=EOF)
    {
        ch=getc(fp1);
        if (ch=='\n')
            temp++;
            if (temp!=delete_line)
            {
                putc(ch,fp2);
            }
    }
    fclose(fp1);
    fclose(fp2);
    remove(fn);
    rename("replace.c",fn);
    printf("The contents of file after being modified are as follows:\n");
    fp1=fopen(fn, "r");
    ch=getc(fp1);
    while (ch!=EOF)
    {
        printf("%c",ch);
        ch=getc(fp1);
    }
    fclose(fp1);
}
compare()
{
	 FILE *fp1, *fp2;
   int i=0;
   char ch1[10], ch2[10];
   fp1 = fopen("pass.txt","r");
   fp2 = fopen("password.txt","r");
   for(i=0;i<10;i++)
  {
   ch1[i] = getc(fp1);
   ch2[i] = getc(fp2);
  } 
  for(i=0;i<ch2[i];i++)
  {
      if (ch1[i] != ch2[i])
      {
     	printf("wrong password\n");
     	j++;
		 wrgpasswd(j);
	   }
   }
      fclose(fp1);
      fclose(fp2);
}
wrgpasswd(int j)
{
	while(j!=4)
	{
		printf("the %d trail\n",j);
		password();
	}
	printf("entered password is wrong task is exited");
	exit(0); 
}
