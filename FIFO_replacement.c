#include<stdio.h>
#include<conio.h>

int main(){

    int noOfFrames, noOfPages;
    printf("\n\t\t FIFO REPLACEMENT\n");

    printf("\nEnter the number of frames->");
    scanf("%d",&noOfFrames);

    printf("\nEnter the number of pages->");
    scanf("%d", &noOfPages);

    //=============================//
    //input page numbers

    int ref[50], frm[50];   
    //ref -> page no sequence
    //frm -> frames jisme page number settle honge

    printf("\nEnter the Page no sequence");
    for(int i=0; i<noOfPages; i++){
        scanf("%d",&ref[i]);
    }
    printf("\nThe given pages are:");
    for(int i=0;i<noOfPages; i++){
        printf("\n%4d", ref[i]);
    }

    //--------------------------------//
    for(int i=1; i<=noOfFrames; i++){
        frm[i] = -1;
    }
    
    //----------replacement logic----------//

    int pageFault = 0;
    int victim = -1;

    for(int i=0; i<noOfPages; i++){
        int flag = 0;
        printf("\npage number->%d", ref[i]);

        for(int j=0 ; j<noOfFrames; j++){
            if(ref[i] == frm[i]){
                flag = 1;
                break;
            }
        }

        if(flag == 0){
            pageFault++;
            victim++;
            victim = victim % noOfFrames;

            frm[victim] = ref[i];

            for(int j=0; j<noOfFrames; j++){
                printf("\t%4d", frm[j]);
            }
        }
    }

    printf("\n\n No.of pages faults ....%d", pageFault);
    return 0;

}
