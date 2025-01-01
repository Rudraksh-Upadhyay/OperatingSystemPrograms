#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<time.h>


#define BUFFER_SIZE 5

sem_t mutex, full, empty;

int buffer[BUFFER_SIZE];
int in=0;   //produce index
int out=0; //consume index

void *producer(void *arg){
    int item;
    for(int i=0; i<10; i++){     //producing 10 times
        item = rand() % 100;    //generate number withing 100

        sem_wait(&empty);       //empty hone ka wait krna hai....wait krega if buffer is full
        sem_wait(&mutex);       //entering critical section

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        printf("\nproducer produced %d\n", item);

        sem_post(&mutex);   //exiting critical section
        sem_post(&full);    //signal dega ki...kuch hai apke buffer mei...means..produce hua hai



    }

    pthread_exit(NULL);
}



void *consumer(void *arg){
    int item;
    for(int i=0; i<10; i++){  //consume 10 times

        sem_wait(&full);    //wait krenge ki..buffer mei kuch ho...agar...buffer empty hai woh waiting  
        sem_wait(&mutex);   //critical section

        item = buffer[out];

        out = (out+1) % BUFFER_SIZE;

        printf("\nConsumer consumed %d\n", item);

        sem_post(&empty);
        sem_post(&mutex);
    }

    pthread_exit(NULL);
}

int main(){

    pthread_t prod, cons;

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);  // means no item filled/produced yet
    sem_init(&empty, 0, BUFFER_SIZE);// meand puura buffer hai woh..empty hai

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);


    //wait krenge for producer and consumer to finish

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    //destroy sems

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
 
}