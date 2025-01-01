#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N 5

pthread_mutex_t forks[N];

void *philosopher(void *args){
    int id = *(int*)args;
    int left = id;
    int right = (id+1)%N;


    while(1){
        printf("Philosopher %d is thinking\n", id);
        sleep(2);

        printf("Philosopher %d is hungry\n",id);

        //picking left fork
        pthread_mutex_lock(&forks[left]);
        printf("Philosopher %d is picking left fork\n",id);

        //picking right fork
        pthread_mutex_lock(&forks[right]);
        printf("Philosopher %d is picking right fork\n",id);



        //eating...
        printf("Philosopher %d is eating...\n",id);
        sleep(2);


        printf("Philosopher %d is done Eating.\n",id);

        //droping left fork
        pthread_mutex_unlock(&forks[left]);
        printf("Philosoper %d is putting left fork\n",id);

        //putting right fork
        pthread_mutex_unlock(&forks[right]);
        printf("Philosopher %d is putting right fork\n",id);
    }

    pthread_exit(NULL);
}



int main(){

    pthread_t threads[N];  //array holding philosophers

    int ids[N];

    for(int i=0; i<N; i++){
        ids[i] = i;
        pthread_mutex_init(&forks[i], NULL);
        pthread_create(&threads[i],NULL, philosopher, &ids[i]);

    }

    for(int i=0; i<N; i++){
        pthread_join(threads[i],NULL);
        pthread_mutex_destroy(&forks[i]);
    }


    return 0;
}