#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20



typedef enum{false, true} bool;





char submenu2(){
    char abcd[MAX];
    int len;
    printf("\t(a) Mala\n");
    printf("\t(b) Normal\n");
    printf("\t(c) Buena\n");
    printf("\t(d) Excelente\n");
    while(1){
        printf("\n\tEliga: ");
        fflush(stdin);
        fgets(abcd, 24, stdin);
        len = strlen(abcd);
        if((abcd[0]=='a'|| abcd[0]=='b' || abcd[0]=='c' || abcd[0]=='d') && len==2){
            break;
        } else {
            printf("¡Por favor, introduzca a, b, c, d!: ");
        }
    };
    return abcd[0];
}





int main(){
    while(1){
        printf("Buchstabe: %c\n", submenu2());
    }
    

    return 0;
}