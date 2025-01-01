#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int main(){

    char dirname[100];
    DIR *dirp;           //directory steam ko represent krta hai...pointer to an open directory
                        //when you open a directory using "opendir", it returns pointer of type 
                        //'DIR*'. You use it to read entries from the directory

    struct dirent *entry; //gets the individual entries in the directory

    printf("\nEnter the directory name->\n");
    scanf("%s", dirname);


    //open the directory
    if((dirp = opendir(dirname)) == NULL){
        printf("\nThe directory doesnt exist\n");
        exit(1);
    }

    //read and print

    while((entry = readdir(dirp)) != NULL){
        printf("%s\n", entry->d_name);
    }


    //close directory
    closedir(dirp);


    return 0;
}