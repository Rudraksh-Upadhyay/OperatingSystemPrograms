#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define philo_num 5

sem_t forks[5];
sem_t mutex; // prevent deadlock by limiting the number of philosopher that can pick the fork

void* philosopher(void* philo){
    int id = *(int*)philo;

    while(1){
        printf("Philosopher %d is thinking\n", id);
        sleep(1);


        sem_wait(&mutex); //decrease the number of philosopher allowed to pick forks

        sem_wait(&forks[id]); //pick left fork
        sem_wait(&forks[(id+1) % 5]); // pick right fork

        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        //puting down forks
        sem_post(&forks[(id+1) % 5]);
        sem_post(&forks[id]);

        sem_post(&mutex);
    }
    return NULL;
}

int main(){
    pthread_t threads[5];
    int philosopher_ids[5];

    sem_init(&mutex, 0, 4);

    for(int i=0 ; i < 5; i++){
        sem_init(&forks[i], 0, 1); // each fork is available
    }

    //create philo thread
    for(int i=0 ; i<5; i++){
        philosopher_ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for(int i=0; i<5; i++){
        pthread_join(threads[i], NULL);
    }

    //destory semaphores
    sem_destroy(&mutex);
    for(int i=0; i<5; i++){
        sem_destroy(&forks[i]);
    }

    return 0;
}