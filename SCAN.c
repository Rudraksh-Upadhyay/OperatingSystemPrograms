// SCAN DISK SCHEDULLING ALGORITHM //

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_TRACKS 20

int main(){
    int tracks[MAX_TRACKS], head, num_tracks, total_movement=0;

    //input the number of tracks to be traversed
    printf("\nEnter the number of tracks to be traversed: ");
    scanf("%d", &num_tracks);

    //input the initial position of head
    printf("\nEnter the position of head: ");
    scanf("%d", &head);

    //input the track position
    printf("\nEnter the track positions->");
    for(int i=0; i<num_tracks; i++){
        scanf("%d", &tracks[i]);
    }

    // adding head and 0 
    tracks[num_tracks] = head;
    tracks[num_tracks+1] = 0;

    //sorting
    for(int i=0; i<num_tracks+2; i++){
        for(int j=i+1; j<num_tracks+2; j++){
            if(tracks[i] > tracks[j]){
                int temp = tracks[i];
                tracks[i] = tracks[j];
                tracks[j] = temp;
            }
        }
    }

    //finding index of head
    int head_position;
    for(int i=0; i<num_tracks; i++){
        if(tracks[i] == head){
            head_position = i;
        }
    }

    //----------------MOVEMENT LOGIC---------------------------//

    //from head to 0
    for(int i=head_position; i >= 0; i--){
        if(i == head_position){
            printf("\nMoving towards 0\n");
            continue;
        }
        total_movement += abs(tracks[i] - tracks[i+1]);
        printf("\nMOving to track: %d", tracks[i]);
    }

    // frmo head to right
    for(int i=head_position+1; i< num_tracks+2; i++){
        if(i==head_position+1){
            total_movement += abs(tracks[i] - tracks[0]);
            printf("\nMoving towards right\n");
            printf("\nMoving to track: %d", tracks[i]);
            continue;
        }
        total_movement += abs(tracks[i] - tracks[i-1]);
        printf("\nMoving to track: %d", tracks[i]);
    }

    printf("\ntotal number of movements: %d\n", total_movement);
    printf("\n avaerage of total movement->%d", (total_movement/(num_tracks-1)));

    return 0;

}