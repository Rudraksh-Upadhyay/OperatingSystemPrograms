#include<stdio.h>

int main(){
    // 5 processes hai -> p0, p1, p2, p3, p4;
    int n = 5; //proceses
    int m = 3; //resources

    int allocation[5][3] = {
        {0, 1, 0}, //p0
        {2, 0, 0}, //p1
        {3, 0, 2}, //p2
        {2, 1, 1}, //p3
        {0, 0, 2}  //p4
    };

    int max_need[5][3] = {
        {7,5,3}, //p0
        {3,2,2}, //p1
        {9,0,2}, //p2 
        {2,2,2}, //p3
        {4,3,3}  //p4
    };

    int available[3] = {3,3,2}; //available resources


//---------------------------------------//
    int f[n], ans[n], index = 0;

    for(int k =0; k<n; k++){
        f[k] = 0;    //none of the processe is done with its job yet
    }

    int need[n][m];  //actual need of resources kya hai har process ki
    for(int i=0; i<n; i++){
        for(int j=0; j<m;j++){
            need[i][j] = max_need[i][j] - allocation[i][j];
        }
    }

    //-------------------------------//

    for(int k=0; k<n; k++){
        for (int i=0; i<n;i++){
            if(f[i] == 0){
                int flag =0;

                for(int j=0; j<m; j++){
                    if(need[i][j] > available[j]){
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0){
                    ans[index++] = i;
                    for(int k=0; k<m;k++){
                        available[k] += allocation[i][k];
                    }
                    f[i] = 1;  //setting process as done
                }
            }
        }
    }

    //-------------------------------------------//
    int flag = 1;
    for(int i=0; i< n; i++){
        if(f[i] == 0){
            flag =0;  //if not done...then...NOT SAFE
            printf("NOT SAFE");
            break;

        }
    }
    if(flag == 1){
        printf("safe sequence->\n");
        for(int i=0; i<n; i++){
            printf("p%d->", ans[i]);
        }
    }
    return 0;

}