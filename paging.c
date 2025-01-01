#include<stdio.h>
int main(){

    int memorySize, pageSize, noOfProcesses, TotalPages, remainingPages;
    int s[10], frameNo[10][20];

    printf("\nEnter the memory size->");
    scanf("%d", &memorySize);

    printf("\nEnter the page size->");
    scanf("%d", &pageSize);

    TotalPages = memorySize / pageSize;
    printf("\nNumber of pages available-> %d", TotalPages);

    //--------------------------------------------------------//

    printf("\nEnter the number of processes->");
    scanf("%d", &noOfProcesses);

    remainingPages = TotalPages;

    for(int i=1; i<=noOfProcesses; i++){
        printf("\nEnter the no. of pages required   for p%d", i);
        scanf("%d", &s[i]);

        if(s[i] > remainingPages){
            printf("\nMemory is full");
            break;
        }

        remainingPages -= s[i];

        printf("\nEnter the page-table for p%d", i);

        for(int j=0; j<s[i]; j++){
            scanf("%d", &frameNo[i][j]);
        }
    }

    //-----------------------------------------------------//

    int x,y,offset;
    int physicalAddress;

    printf("\nEnter the logical address to find physical address");
    printf("\nEnter process no, page no, offset");
    scanf("%d %d %d", &x,&y,&offset);

    if( x>noOfProcesses || y>s[x] || offset > pageSize){
        printf("\nInvalid process");
    }
    else{
        physicalAddress = frameNo[x][y] * pageSize + offset;
        printf("The physical address->%d", physicalAddress);
    }

}