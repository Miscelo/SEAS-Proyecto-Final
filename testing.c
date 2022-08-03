#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define length_pregunta 100


typedef enum{False, True} bool; 


char menu(){
     char c[length_pregunta];

    printf("\n*********************************************************\n");
    printf("******************  Encuesta - Menu  ********************\n\n");
    printf("(1) Iniciar encusta\n");
    printf("(2) Agregar preguntas al fichero de preguntas\n");
    printf("(3) Visualizar el fichero con los últimos resultados\n");
    printf("(4) Salir\n");
    printf("\n\tElige un número [1-4]: ");
    do{
        fflush(stdin);
        fgets(c, length_pregunta, stdin);
    }while(c[0]<'0'||c[0]>'4');
    printf("\n\n");
    return c[0];
}


int main(){
    bool loop = True; //Valor para determinar el loop.
    while(loop==True){
        switch(menu()){
            case '1':
                    printf("*** Iniciar Encuesta ***\n");
                    char name[30];
                    fgets(name, 30, stdin);
                    printf("%s\n", name); 
                    break;
            case '2':
                    printf("Agreegar preguntas\n");
                    
                    break;
            case '3':
                    printf("Fichero con resultados de las STATS\n");
                    break;
            case '4':
                    printf("\n*********************************************************\n"
                            "\t\t\tFIN DEL PROGRAMA\n"
                            "*********************************************************\n");
                    loop = False;
                    break;
            default:
                    printf("\n*********************************************\n"
                            "\tINPUT VALUE ERROR!\n"
                            "Elige un numero del menú de 1 a 5 por favor.\n"
                            "*********************************************\n");
                    break;
            
        }
    }
    






    return 0;
}