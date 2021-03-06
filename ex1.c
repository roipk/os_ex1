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
   // printf("count=%d\n",count);
    if(count>0)
        return -1;
    //printf("in\n");
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




void arguments(char** arr,char *word, int i)
{
    int j=0;  
    char *temp, *ptr;
    temp=(char*)malloc(strlen(word)*sizeof(char));
    strcpy(temp,word);
    ptr= strtok(temp,"\"\0");
    if(!strcmp(ptr,word))
    {
        ptr = strtok(word," \n\0");
	    while(ptr != NULL)
	    { 
            j=strlen(ptr);
            arr[i]=(char*)malloc(j*sizeof(char));
		    strcpy(arr[i],ptr);
            i++;
            ptr = strtok(NULL," \n\0");
        }   

    }
    else
    {
       while(ptr != NULL)
	    { 
            j=strlen(ptr);
            arr[i]=(char*)malloc(j*sizeof(char));
		    strcpy(arr[i],ptr);
            i++;
            ptr = strtok(NULL,"\"\n\0");
        }   
    }
}



/*-------------------------------------------------------------------------------*/
//The function inserts the entered arguments into an array
void EnterWordToArray(char** arr,char *word,char *x)
{
    char *ptr;
    int i = 0,j=0;
    ptr = strtok(word," \n");
	if(ptr != NULL)
	{ 
         j=strlen(ptr);
         arr[i]=(char*)malloc(j*sizeof(char));
		 strcpy(arr[i],ptr);
         i++;   
    }
    ptr = strtok(NULL,"\n");
    if(ptr!= NULL)
        arguments(arr,ptr,i);
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
    char tempSize[510],tempApostropy[510],tempSpace[510];
    char **arr;
    char* ptr;
    int j;
   

	printf("%s@%s>",pwp->pw_name,getcwd(buf, sizeof(buf)));
    fgets(temp,sizeof(temp),stdin);
    
    
    while(strcmp(temp,"done\n"))
    {
        strcpy(tempSpace,temp);
        ptr = strtok(tempSpace," \0");
        strcpy(tempSize,temp);
        strcpy(tempApostropy,temp);
        j=NumberOfWards(tempSize," \"\n");
        if(j!= -1)
            arr=(char**)malloc((j+1)*sizeof(char*));
        else
             arr=(char**)malloc((sizeof(char*)));
        if(arr == NULL)
        {
            printf("ERR\n");
            exit(1);
        }
        if(j!=-1)
        {      
            arr[j]=NULL; 
            if(!strcmp(ptr,"\n") && strlen(temp)>1)
            {
                ptr=strtok(tempApostropy,"\n");
                arr[0]=(char*)malloc(sizeof(char));
                strcpy(arr[0],"");  
            }
            else
                EnterWordToArray(arr,temp," \"\n");
        }
        else
            arr[0]=NULL;
            
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
    freearr(arr,j);
	printf("%s@%s>",pwp->pw_name,getcwd(buf, sizeof(buf)));
    fgets(temp,sizeof(temp),stdin);
    }
    
    printf("Num of cmd: %lu\n",Num_of_cmd);
    printf("Cmd length: %lu\n",Cmd_length);
    printf("Bye !\n");
    

return 0;
}









