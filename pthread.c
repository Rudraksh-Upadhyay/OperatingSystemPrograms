#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* workfunc(void* arg){
    long * myID = (long*) arg;
    printf("I am a thread %ld\n", *myID);
    return NULL;
}

int main(){

    pthread_t tid0;
    pthread_t tid1;
    pthread_t tid2;

    pthread_t * pthreads[] = {&tid0, &tid1, &tid2};

    // pthread_create(&tid0, NULL, workfunc, (void*)&tid0);
    for(int i =0; i<3; i++){
        pthread_create(&pthreads[i], NULL, workfunc, (void*) pthreads[i]);
    }


    pthread_exit(NULL);
    return 0;
}