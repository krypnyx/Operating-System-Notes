#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<unistd.h>

#define BUFFER_SIZE 15

pthread_t prod,consum;

pthread_mutex_t mutex;

sem_t full, empty;


int buffer[BUFFER_SIZE];


int counter;  

int in,out; 

void insert_item(int item)
{
   if(counter < BUFFER_SIZE)
    {
      buffer[counter] = item;
      printf("Produced item at position %d with value = %d\n",counter,item);
      counter++;
    }
   else printf("Buffer full\n");
}


void remove_item()
{   int item;
   
   if(counter > 0) 
    { item = buffer[counter-1];
      printf("Consumed item at position %d with value = %d\n",counter-1,item);
      counter--;
    }
   else printf("Buffer empty\n");
}


void *producer(void *param) 
{   int item;

    while(1) 
   {
      
      sem_wait(&empty);

      
      pthread_mutex_lock(&mutex);
    
      if(counter%2 == 0) item = 2*counter+1;else item = 2*counter;
      insert_item(item);sleep(1);

      pthread_mutex_unlock(&mutex);
      
      sem_post(&full);
   }
}


void *consumer(void *param) 
{
   int item;
   while(1) 
   {
      sem_wait(&full);

      
      pthread_mutex_lock(&mutex);

      remove_item(&item);sleep(1);

      pthread_mutex_unlock(&mutex);
      
      sem_post(&empty);
   }
}



int main(int argc, char *argv[]) 
{

   int i;

   pthread_mutex_t mutex;
   pthread_mutex_init(&mutex, NULL);

   pthread_attr_t attr;
   pthread_attr_init(&attr);

   
   sem_init(&full, 0, 0);
   sem_init(&empty, 0, BUFFER_SIZE);


   counter = 0;
   

   pthread_create(&prod,&attr,producer,NULL);    

   pthread_create(&consum,&attr,consumer,NULL);
   

   pthread_join(prod,NULL);
   pthread_join(consum,NULL);
    

   return 0;
}
