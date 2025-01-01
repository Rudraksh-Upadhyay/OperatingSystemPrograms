#include<stdio.h>

typedef struct {
    int id;
    int arrival;
    int burst;
    int completiontime;
    int waiting;
    int turnaroundtime;
}Process;


// SORTING BY ARRIVAL TIME AND BY BURST TIME IF ARRIVAL TIME ARE EQUAL
void sortProcess(Process p[], int n){
    for(int i=0 ; i<n-1; i++){
        for(int j=0; j<n-1-i; j++){

            if((p[j].arrival > p[j+1].arrival) || (p[j].arrival == p[j+1].arrival && p[j].burst > p[j+1].burst)){
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int findNextProcess(Process p[], int n, int currentTime){
    int minBurst = __INT_MAX__;
    int shortest = -1;

    for(int i=0; i<n; i++){
        if(p[i].arrival <= currentTime && p[i].completiontime == 0){
            if(p[i].burst < minBurst){
                minBurst = p[i].burst;
                shortest = i;
            }
        }
    }

    return shortest;
}

int main(){
    int n;
    printf("Enter the number of processes->");
    scanf("%d", &n);

    Process p[n];
    printf("\nEnter the arrival time and burst time of each process\n");
    for(int i=0; i<n; i++){
        p[i].id = i+1;
        printf("process %d\n",p[i].id);
        printf("arrival->");
        scanf("%d", &p[i].arrival);
        printf("burst->");
        scanf("%d", &p[i].burst);
        p[i].completiontime =0;
    }

    //sorting process by arrival time and by burst tiem
    sortProcess(p, n);

    int currentTime =0, completed = 0;
    float total_waiting_time =0, total_turnaround_time =0;

    while(completed < n){
        int index = findNextProcess(p, n, currentTime);


        if(index != -1){
            //agar process 0 time mei arrive nahi hoga toh yeh kaam ak yega
            //agar parocess 1 unit time mei ayega toh...current time p.arrival ho ajyega
            //magar iska koi use nahi...kyuki..hum arrvial time 0 se hi start krenge so chill
            currentTime = (currentTime < p[index].arrival) ? p[index].arrival : currentTime;
            
            p[index].completiontime = currentTime + p[index].burst;
            p[index].turnaroundtime = p[index].completiontime - p[index].arrival;
            p[index].waiting = p[index].turnaroundtime - p[index].burst;


            total_waiting_time += p[index].waiting;
            total_turnaround_time += p[index].turnaroundtime;

            currentTime += p[index].burst;
            completed++;
        }
        else{
            currentTime++;
        }
    }

    printf("\nprocess id \t arrival \t burst \t completion \t waiting \t turnaround\n");
    for(int i=0; i<n; i++){
        printf("%d \t\t %d \t\t %d \t\t %d \t\t %d \t\t %d \n",
        p[i].id, p[i].arrival, p[i].burst, p[i].completiontime, p[i].waiting
        ,p[i].turnaroundtime);
    }


    printf("average waiting time->%f\n",(total_waiting_time/n));
    printf("avarage turn around time->%f\n", (total_turnaround_time)/n);


    return 0;
}
