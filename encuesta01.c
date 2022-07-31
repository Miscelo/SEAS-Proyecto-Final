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
} Pregunta;

// ??????
typedef struct _Stack_ {
    struct Pregunta *pregunta;
    struct _Stack_ *next;
} Stack;




void menu(){
    printf("(1) Iniciar encusta\n");
    printf("(2) Agregar preguntas al fichero de preguntas\n");
    printf("(3) Visualizar el fichero con los últimos resultados\n");
    printf("(4) Salir\n");
}



/* Lee el archivo de texto que incluye las preguntas*/
void readPreguntas(){

}


/* Añade una pregunta nueva al archivo de texto de preguntas */
void writePreguntas(){

}


/* Añade un elemento en la pila */
void push(){

}

/* Retira un elemento de la pila */
void pop(){

}





int main(){


    return EXIT_SUCCESS;
}