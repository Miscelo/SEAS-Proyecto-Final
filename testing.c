#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20



typedef enum{false, true} bool;


int getIntegerFromUser(){
    char buffer[1024];
    char *p;
    long numero_long;
    int  numero_int;
    //Uso de fgets para evitar overflow
    fflush(stdin);
    fgets(buffer, sizeof buffer, stdin);          //guarda una linea de flujo de dato
    if(strchr(buffer, '\n') == NULL){             //Comprueba que toda la linea està leida y el 'buffer' no se ha quedado pequeño
        printf("ERROR! El numero introducido es demasiado largo!\n");
        exit(EXIT_FAILURE);
    }
    numero_long = strtol(buffer, &p, 10);    // cambiar una cadena a un número entero del tipo 'long'
    if(p == buffer){
        printf("\n\tERROR, no es un número!\n"
                "\tIntroduzca un número: ");
        getIntegerFromUser();   //Funcion se llama recursivo si la entrada no era un número
    }
    numero_int = (int)numero_long;       //cambiar número entero del tipo long a número entero
    return numero_int;
}




void dynArray(){
    int sizeOfList = 20;
    printf("Wie lang soll das Array sein: ");
    int arraylength = getIntegerFromUser();
    
    // MAX 20
    int *random_numbers = malloc(sizeof(int)*arraylength);
    if(random_numbers == NULL){
        printf("No hayu space\n");
        exit(1);
    }
    memset(random_numbers, 0, sizeof(int) * arraylength);  // inizalizar array con '0'
    srand(clock());
    for(int i=0;i<arraylength;i++){
        int temp = rand()%sizeOfList+1;
        bool exists = false;
        for(int j=0;j<i;++j){
            if(*(random_numbers+j) == temp){
                exists = true;
                break;
            }
        }
        if(!exists){
            *(random_numbers+i) = temp;
            printf("%d,", *(random_numbers+i));
        }
        else{
            --i;  //si ya existe , contamos el bucle una para atras
        }
    }
}






int main(){
    
    dynArray();
   

    return 0;
}