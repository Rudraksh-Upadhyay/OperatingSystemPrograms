#include<stdio.h>

typedef struct 
{
    int pid;
    int arrival;
    int burst;
    int completion;
    int waiting;
    int turnaround;
    int remaining;
}Process;

void calculationTimes(Process processes[], int n , int quantum){
    int time = 0;
    int completed = 0;
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    while(completed < n){
        
        for(int i =0; i< n; i++){
            if(processes[i].remaining > 0 && processes[i].arrival <= time){
                if(processes[i].remaining <= quantum){

                    time+=processes[i].remaining;
                    processes[i].remaining =0;
                    processes[i].completion = time;
                    
                    processes[i].turnaround = processes[i].completion - processes[i].arrival;
                    processes[i].waiting = processes[i].turnaround - processes[i].burst;

                    total_waiting_time += processes[i].waiting;
                    total_turnaround_time += processes[i].turnaround;
                    completed++;
                }
                else{
                    time += quantum;
                    processes[i].remaining -= quantum;
                }
            }
        }
    }

    printf("\nPID\t arrival \t burst \t completion\t waiting\t turnaround\n");
    for(int i=0; i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival, processes[i].burst, processes[i].completion, processes[i].waiting, processes[i].turnaround);
    }

    printf("average waiting time->%.2f\n", total_waiting_time/n);
    printf("average turnaround time->%.2f\n", total_turnaround_time/n);
}


int main(){
    int n , quantum;
    printf("Enter the number of processes->");
    scanf("%d",&n);

    Process processes[n];
    for(int i=0; i<n;i++){
        printf("Enter the details of process %d\n", i+1);
        processes[i].pid = i+1;
        printf("arrival time->");
        scanf("%d", &processes[i].arrival);
        printf("burst time->");
        scanf("%d", &processes[i].burst);
        processes[i].remaining = processes[i].burst;  //yeh bhul jaoge
    }

    printf("Enter the quantum time->");
    scanf("%d", &quantum);

    calculationTimes(processes, n, quantum);

    return 0;
}
