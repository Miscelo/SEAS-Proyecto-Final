/****************************** Trabajo obligatorio - CURSO Programación C - SEAS **************************************
*  Ejercicio: Crear un programa que elige preguntas aleatoriamente de un fichero y lo seleccióna *
*             para hacer una encuensta. 
*             - La respuesta de cada pregunta podrán tener sólo uno de entre cuatro valores predefinidos.
*             - El sistema deberá realizar un número indeterminado de repeticiones de la encusta.
*             - El usuario puede añadir preguntas al fichero.
*             - Estadisticas de la encuesta y que el resultado ganador se guarda en otro fichero.
************************************************************************************************************************
*/  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define length_pregunta 100


typedef enum{False, True} bool;     //Definición de un tipo de dato bool para mejorar la legibilidad del código.

typedef struct _Pregunta_ {         //Definición de la estructura del tipo 'Non type'
    char texto[length_pregunta];    //se almacena la pregunta
    int tamano;                     //se almacena tamaño de la pregunta
    int numPregunta;                //se almacena el number de la pregunta
    int respA;                      // número de veces que el usuario ha elegido la respusta
    int respB;
    int respC;
    int respD;
    int iteraciones;                //número de veces que se ha ejecutado la encusta
    struct _Pregunta_ *next;
} Pregunta;

Pregunta *first = NULL;             //instancia de la estructura, puntero al primer elemento de la lista
Pregunta *list = NULL;              //lista






char menu(){
     char c;
    printf("\n**********************  Encuesta - Menu  *************************\n\n");
    printf("(1) Iniciar encusta\n");
    printf("(2) Agregar preguntas al fichero de preguntas\n");
    printf("(3) Visualizar el fichero con los últimos resultados\n");
    printf("(4) Salir\n");
    printf("\tElige un número [1-4]: ");
    do{
        fflush(stdin);
        c = getchar();
    }while(c<'0'||c>'5');
    printf("\n\n");
    return c;
}



/* Lee el archivo de texto que incluye las preguntas*/
void readPreguntas(){

}


/* Añade una pregunta nueva al archivo de texto de preguntas */
void writePreguntas(){

}


/* */
void writeStatistics(){

}



/* Añade un elemento en la pila */
void insertar(char pregunta[length_pregunta], int letras, int nr, int rA, int rB, int rC, int rD, int iter){
    Pregunta *new = malloc(sizeof(Pregunta));
    if(new == NULL){
        printf("ERROR, no se podía asignar espacio en la memoría RAM!\n");
    }
    strcpy(new->texto, pregunta);
    new->next = NULL;
    new->tamano =  letras;  //????
    new->numPregunta = nr;
    new->respA = rA;
    new->respB = rB;
    new->respC = rC;
    new->respD = rD;
    new->iteraciones =  iter;
    new->next = NULL;
    if(first == NULL){              //Añade primer elemento a la lista si no existe aún.
        first = new;
        list = new;
    } else  {                      //Añade un elemento a la lista si ya contiene mínimo un Elemento.
    
        list = first;
        while(list!=NULL){
            if(list->next == NULL){
                list->next = new;
                break;
            } else{
                list = list->next;
            }
        }

    }
}



/* Retira un elemento de la pila */
void pop(){

}


void printList(){
    list = first;
    while(list!=NULL){
        printf("%s\n", list->texto);
        list = list->next;
    }
}


int main(){
    insertar("Que tal la atención?", 22, 1, 30, 25, 24, 21, 1);
    insertar("Que le ha aparecido la materia estudiado?", 41, 2, 40, 30, 22, 8, 1);
    printList();

    return EXIT_SUCCESS;
}




/*
Al seleccionar la opción de “Iniciar encuesta” el procedimiento será:

    1. Cargar la encuesta en una lista enlazada, cada pregunta será un nodo de la lista.

    2. Preguntar al usuario por el número de preguntas que formaran la encuesta definitiva que haremos al usuario.

    3. Cargar una nueva lista seleccionando de la lista anterior de modo aleatorio el número de preguntas (nodos) indicado en el apartado anterior.

    4. Preguntar al usuario el número de veces que se debe de repetir la encuesta.

    5. Ejecutar la encuesta tantas veces como se haya indicado almacenando los resultados en el lugar adecuado para mostrar posteriormente la estadística.

    6. Una vez finalizada la encuesta mostrar los resultados y cargar el fichero con los mismos.

Al seleccionar la opción de “Agregar preguntas al fichero de preguntas” simplemente se agregaran preguntas al fichero original. A la entrega del trabajo deben existir preguntas almacenadas en la encuesta.´
Por último, al seleccionar la opción 3, simplemente se mostrará el fichero resultado_encuesta donde aparecerán las preguntas y las estadísticas de la última encuesta realizada.
*/