#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void firstFit(int blockSize[], int numberOfBlocks, int processSize[], int numberOfProcesses){

    int allocation[numberOfProcesses]; //array to allocate each process in blocks

    for(int i=0; i<numberOfProcesses; i++){
        allocation[i] = -1;
    }

    //allocate block to each process
    for(int i=0; i<numberOfProcesses ; i++){
        for(int j=0; j<numberOfBlocks; j++){

            if(blockSize[j] >= processSize[i]){

                allocation[i] = j;

                blockSize[j] -= processSize[i];

                break;
            }
        }
    }

    

    //print the allocation results
    printf("\nProcess NO. \t Process size \t block No\n");

    for(int i=0; i<numberOfProcesses; i++){
        printf("%d\t\t",i+1); //process no
        printf("%d \t\t", processSize[i]); //process size
        if(allocation[i] != -1){
            printf("%d", allocation[i] + 1);
        }
        else{
            printf("not allocated");
        }
        printf("\n");
    }


}

int main(){

    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};

    int blockNumber = sizeof(blockSize) / sizeof(blockSize[0]);
    int processNumber  = sizeof(processSize) / sizeof(processSize[0]);

    firstFit(blockSize, blockNumber, processSize, processNumber);

    

    return 0;
}