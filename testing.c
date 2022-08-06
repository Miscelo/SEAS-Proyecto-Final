#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int main(){
    char mystring[MAX];
    while(1){
        fgets(mystring, MAX, stdin);
        
        for(int i = 0;i<MAX; i++){
            if(mystring[i] == '\n'){
                mystring[i] = '\0';
            }
        }
        
        
        
        if((mystring[0] == 'q' || mystring[0]== 'Q') && (strlen(mystring) == 1)){
            break;
        } else {
            printf("String is: %s und länge ist %d\n", mystring, (int)strlen(mystring));
        }
    }


    return 0;
}