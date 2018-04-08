/****************************
*   UserName:    roimd      *
*   Name:   Roi Madmon      *
*   ID:     203485164       *
*   Exercise 1              *
****************************/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <errno.h>
#define BUFLEN 4096



//The function counts how many arguments were entered from the writing line
int NumberOfWards(char *word, char *x)
{
   int n, count=0;
    n=strlen(word);
    for(int i=0;i<n;i++)
    {
        if(word[i]=='\"')
        {
            if(count==1)
                count--;
            else
               count++;
        }        
    }
    if(count>0)
        return 0;
	int numword = 0;
	char *ptr;
	ptr = strtok(word,x);
	while(ptr != NULL)
	{
        numword++;
		ptr = strtok(NULL,x);
	}
    return numword;
}


/*-------------------------------------------------------------------------------*/
//The function inserts the entered arguments into an array
void EnterWordToArray(char** arr,char *word,char *x)
{
    char *ptr;
    int i = 0,j=0;
    ptr = strtok(word,x);
	while(ptr != NULL)
	{ 
         j=strlen(ptr);
         arr[i]=(char*)malloc(j*sizeof(char));
		 strcpy(arr[i],ptr);
         i++;
         ptr = strtok(NULL,x);
    }
}


/*-------------------------------------------------------------------------------*/
//The function frees the array
void freearr(char** arr,int num_word)
{
    for(int j=0;j<num_word;j++)
        free(arr[j]);
    free(arr);
}


/*-------------------------------------------------------------------------------*/
int main()
{

    struct passwd pw ,*pwp;
    char buf1[BUFLEN];
    setpwent();
    getpwent_r(&pw,buf1,BUFLEN,&pwp);
    


   unsigned long Num_of_cmd=0, Cmd_length=0;
    char buf[BUFSIZ];
    char temp[510];
    char tempsize[510],tempApostropy[510];
    char **arr;
    int j;
   

	printf("%s@%s>",pwp->pw_name,getcwd(buf, sizeof(buf)));
    fgets(temp,sizeof(temp),stdin);
    
    
    while(strcmp(temp,"done\n"))
    {

        strcpy(tempsize,temp);
        strcpy(tempApostropy,temp);
        j=NumberOfWards(tempsize," \"\n");
        arr=(char**)malloc((j+1)*sizeof(char*));
        if(arr == NULL)
        {
            printf("ERR\n");
            exit(1);
        }
        arr[j]=NULL;
            
        EnterWordToArray(arr,temp," \"\n");
        
        if(arr[0]!=NULL && !strcmp(arr[0],"cd"))
        {
            if(arr[1]!=NULL)
                chdir(arr[1]);         
        }
        else if(arr[0]!=NULL)
        {
            Num_of_cmd++;
            if(arr[0]!=NULL)
            Cmd_length = Cmd_length + strlen(arr[0]); 
            pid_t t;       
            t=fork();
            if(t==-1)
            {
                printf("ERR\n");
                exit(1);
            }        
            else if(t==0)
	        {
		        if(execvp(arr[0],arr)!=0);
                    printf("%s: command not found\n",arr[0]);
                exit(0);
	        }
            else	
	        {
                wait(NULL);
            }
        }
    
	printf("%s@%s>",pwp->pw_name,getcwd(buf, sizeof(buf)));
    fgets(temp,sizeof(temp),stdin);
    }
    freearr(arr,j);
    printf("Num of cmd: %lu\n",Num_of_cmd);
    printf("Cmd length: %lu\n",Cmd_length);
    printf("Bye !\n");
    

return 0;
}

