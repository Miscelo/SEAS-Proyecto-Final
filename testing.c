#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#define MAX 20

typedef enum{false, true} bool;





    

int main(){
    int a = 42;
    int b = 30;
    char str[64];
    sprintf(str, "%d", a);

    printf("string: %s", str);

    sprintf(str, "%d", b);

    printf("string: %s", str);

    return 0;
}