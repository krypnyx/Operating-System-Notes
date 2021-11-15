#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<pthread.h>
#include <stdlib.h>

int sum;
void sig_handler(int signo)
{  
  if (signo == SIGTERM)
    { printf("SIGTERM Interrupt\n");}
  else if(signo == SIGINT)
     {printf("SIGINT interrupt\n");}
  
   
  
}

void *threadhandle(void *param)
{
  int i, upper = atoi(param),y;

  sum = 0;printf("entered\n");

  for (i = 1; i <= upper; i++)
    { sum += i;sleep(1);}

  //sleep(20);
  //pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t tid; 
    pthread_attr_t attr; 

    signal(SIGTERM,sig_handler);
    signal(SIGINT,sig_handler);
    signal(SIGFPE,sig_handler);

    pthread_attr_init(&attr);

    pthread_create(&tid,&attr,threadhandle,argv[1]);

    sleep(5);

    kill(getpid(),SIGINT);
    kill(getpid(),SIGTERM);
    
    pthread_kill(tid,SIGTERM);

    pthread_join(tid,NULL);

    

    printf("%d Handled\n",sum);

}





