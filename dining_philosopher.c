//DINING PHILOSOPHER

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (philo_num + 4) % N
#define RIGHT (philo_num + 1) % N


//GLOBAL VARABLES

int state[N];
int philo[] = {0, 1, 2, 3, 4};

sem_t mutex; //semaphore mutex
sem_t S[N]; //semaphores


void test(int philo_num){
    if(state[philo_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
        
        state[philo_num] = EATING;

        sleep(2);

        printf("Philosopher %d takes fork %d and %d\n", philo_num+1, LEFT+1, philo_num + 1);
        printf("philosopher %d is EATING\n", philo_num + 1);

        sem_post(&S[philo_num]);
    }
}



void take_fork(int philo_num){

    sem_wait(&mutex);

    state[philo_num] = HUNGRY;

    printf("Philosopher %d is Hungry\n", philo_num + 1);

    //eat agar LEFT RIGHT eating nahi kr rhe hai toh=>
    // agar LEFT RIGHT nhai khaa rhe toh -> philo_num EATING STATE MEI AA JAYEGA
    test(philo_num);

    sem_post(&mutex);

    //agar fork take nahi kr paye toh
    //agar take kr liye hai...and eating ho gaya...toh...semaphore 0 kr denge
    sem_wait(&S[philo_num]);

    sleep(1);

}

void put_fork(int philo_num){
    sem_wait(&mutex);

    state[philo_num] = THINKING;

    printf("Philosopher %d putting fork %d and %d\n", philo_num+1, LEFT + 1, philo_num+1);
    printf("Philosopher %d is THINKING\n", philo_num+1);

    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}

//phlisopher function
void* philosopher(void* philo){
    while(1){
        int* i=philo;

        sleep(1); //THINKING STATE

        take_fork(*i);

        sleep(0); //EATING STATE

        put_fork(*i); //PUT DOWN FORKS

    }
}


int main(){

    // int i;
    
    pthread_t thread_id[N];

    //initialize krenge semaphores ko
    sem_init(&mutex, 0, 1);

    for(int i =0; i< N; i++){
        sem_init(&S[i], 0, 0);
    }

    for(int i =0 ; i<N; i++){
        pthread_create(&thread_id[i], NULL, philosopher, &philo[i]);
        printf("Philosopher %d is thinking\n", i+1); //philo[i] + 1 bhi likh sakte ho
    }

    for(int i =0 ; i<N; i++){
        pthread_join(thread_id[i], NULL);
    }


    return 0;
}