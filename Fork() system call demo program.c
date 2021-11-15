#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int global=0;

int main()
{  int value=10;
   int status=2;

    pid_t i = fork();
   
    if(i<0) 
      { printf("Error\n");
        exit(0);
      }

    if(i==0) 
             {  global=1; value = 2; printf("child:%d %d\n",global,value);
                sleep(20);
                //execlp("/bin/ls","ls","-l",NULL);
                execlp("./sum","sum",NULL);
                //printf("exec failed\n");
                
                printf("Child completed\n");
             }
    else 
      {  wait(&status);
         sleep(10);
         printf("parent:%d %d %d\n",global,value,status);
      }

}
