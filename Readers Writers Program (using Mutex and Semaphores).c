#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<unistd.h>

sem_t wrt,mutex;
int readcnt =0;

int buffer=0;

void * writer(void *p)
{

do {  sleep(4);
    // writer requests for critical section
    sem_wait(&wrt);  
   
    buffer++; printf("Write:%d\n",buffer);
    // performs the write

    // leaves the critical section
    sem_post(&wrt);

} while(1);

}

void * reader(void *p)
{

do {   sleep(1);
    
   // Reader wants to enter the critical section
   sem_wait(&mutex);

   // The number of readers has now increased by 1
   readcnt++;                          

   // there is atleast one reader in the critical section
   // this ensure no writer can enter if there is even one reader
   // thus we give preference to readers here
   if (readcnt==1)     
      sem_wait(&wrt);                    

   // other readers can enter while this current reader is inside 
   // the critical section
   
   
   sem_post(&mutex);                   

    printf("Read:%d by %lu\n",buffer,pthread_self());
   // current reader performs reading here
   sem_wait(&mutex);   // a reader wants to leave

   readcnt--;

   // that is, no reader is left in the critical section,
   if (readcnt == 0) 
       sem_post(&wrt);         // writers can enter

   sem_post(&mutex); // reader leaves

} while(1);

}

int main(int argc,char *argv[])
{    pthread_t rd[3],wr;int i;

     pthread_attr_t attr;

     sem_init(&mutex,0,1);sem_init(&wrt,0,1);
     
     pthread_attr_init(&attr);

     for(i=0;i<3;i++)
      pthread_create(&rd[i],&attr,reader,NULL);
     pthread_create(&wr,&attr,writer,NULL); 
    
     for(i=0;i<3;i++)
      pthread_join(rd[i],NULL);
     pthread_join(wr,NULL);
     //sleep(atoi(argv1]);printf("Exit the program after %d seconds\n",atoi(argv[1]));
     return 0;
}

