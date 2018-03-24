#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <errno.h>


//int argc,char* argv[]
int main()
{
    unsigned long Num_of_cmd=0, Cmd_length=0;
    char buf[BUFSIZ];
    char *temp;
    char *arr[510];
    char *ptr;
    int i;
    
    temp=(char*)malloc(510*sizeof(char));
    if(temp == NULL)
    {
        printf("ERR\n");
        exit(1);
    }

	printf("%s@%s>",getpwuid(geteuid())->pw_name,getcwd(buf, sizeof(buf)));
    fgets(temp,sizeof(temp),stdin);
    
    while(strcmp(temp,"done\n"))
    {
        Num_of_cmd++;
        ptr=strtok(temp," \n");
        Cmd_length += (strlen(ptr));

        i=0;
        while(ptr != NULL)
        {
            arr[i]=ptr;
            ptr=strtok(NULL," \n");
            i++;  
        }
                
        arr[i]=NULL;
        pid_t t;       
        t=fork();
        if(t==-1)
        {
            printf("ERR\n");
            exit(1);
        }        
        if(t==0)
	    {
		    if(execvp(arr[0],arr)!=0);
                printf("%s: command not found\n",arr[0]);
            exit(0);
	    }
        else	
	    {
            wait(NULL);
        }



        printf("%s@%s>",getpwuid(geteuid())->pw_name,getcwd(buf, sizeof(buf)));
        fgets(temp,sizeof(temp),stdin); 
    }
   
    printf("Num of cmd: %lu\n",Num_of_cmd);
    printf("Cmd length: %lu\n",Cmd_length);
    printf("bye !\n");
    free(ptr);

return 0;
}
