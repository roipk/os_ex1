#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

//int argc,char* argv[]
int main()
{
    
    char buf[BUFSIZ];
    char temp[510];
	printf("%s@%s>",getpwuid(geteuid())->pw_name,getcwd(buf, sizeof(buf)));
    fgets(temp,sizeof(temp),stdin);   
    while(strcmp(temp,"done\n"))
    {
        printf("%s@%s>",getpwuid(geteuid())->pw_name,getcwd(buf, sizeof(buf)));
        fgets(temp,sizeof(temp),stdin); 
    }
    printf("Num of cmd: \n");
    printf("Cmd length: \n");
    printf("bye !\n");

return 0;
}
