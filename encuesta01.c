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

Pregunta *first = NULL;
Pregunta *list = NULL;




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


/* */
void writeStatistics(){

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