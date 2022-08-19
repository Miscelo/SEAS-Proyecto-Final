/*Programa: <Trabajo ESTRUCTURA DE DATOS>
Autor: <Michael Schossow> Fecha: <16.08.2022> */

/****************************** Generador de una encuesta **************************************
*  Ejercicio: Crear un programa que elige preguntas aleatoriamente de un fichero y lo seleccióna *
*             para hacer una encuensta. 
*             - La respuesta de cada pregunta podrán tener sólo uno de entre cuatro valores predefinidos.
*             - El sistema deberá realizar un número indeterminado de repeticiones de la encusta.
*             - El usuario puede añadir preguntas al fichero.
*             - Estadisticas de la encuesta y que el resultado ganador se guarda en otro fichero.
************************************************************************************************
*/  


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define length_pregunta 160         //Longitud máxima que puede tener una pregunta
#define MAX 24                      

typedef enum{False, True} bool;     //Definición de un tipo de dato bool para mejorar la legibilidad del código.

typedef struct _Pregunta_ {         //Definición de la estructura del tipo 'Non type'
    char texto[length_pregunta];    //se almacena la pregunta
    int tamano;                     //almacena tamaño de la pregunta
    int numPregunta;                //almacena el número de la pregunta
    int respA;                      // número de veces que el usuario ha elegido la respusta
    int respB;
    int respC;
    int respD;
    int iteraciones;                //número de veces que se ha ejecutado la encusta
    struct _Pregunta_ *next;
} Pregunta;

typedef Pregunta *pNodo;             //instancia de la estructura, puntero al primer elemento de la lista
typedef Pregunta *Lista;             //crea instancia de la estructura, puntero a lista


/* Imprime el menú principal. Devuelve un integer que sea usado para el caso 'switch' en la función main() */ 
int mainmenu();

/* Imprime el submenú. Devuelve un integer que sea usado para el caso 'switch' en la función 'manejarPreguntas()'*/ 
int submenu();

/* Imprime otro submenú. El usuario elige entre (a) mala, (b) normal, (c) buena y (d) excelente. */
char submenu2();

/* Función que pide al usuario que introduzca un número captando errores y lo devuelve de forma integer. */
int getIntegerFromUser();

/* Inserta un elemento nuevo al final de una lista enlazada.*/
void insertar(Lista *lista, char pregunta[length_pregunta], int letras, int nr, 
                int rA, int rB, int rC, int rD, int iter);

/* Quita un elemento de la lista, elegido por la variable 'Pregunta numPregunta'. */
void eliminar(Lista *lista, int num);

/* Se elimina la lista, quiere decir todos sus entradas usando la función 'eliminar()'*/
void borrarLista(Lista *lista);

/* Función devuelve cantidad de elementos que hay en la lista enlazada, '0' si está vacia*/
int listSize(Lista lista);

/* Renumera las preguntas de 1 hasta el final de la lista -> cambia Struct variable 'numPregunta'. */
void renumerarPreguntas(Lista *lista);

/* Imprime las preguntas y su número en pantalla. */
void printPreguntas(Lista lista);

/* Copia todas las lineas del fichero a la lista enlazada, dado que el fichero no está vacio. */
void copyFileToList(Lista *lista, const char *fichero1);

/* Copia todos los elementos de la variable 'Pregunta texto' (que son las preguntas) al fichero. */
void copyListToFile(const char *fichero1, Lista *lista);

/* Agregar, imprimir e ileminar preguntas de la lista. Mantiene un submemú para realizarlo */
void manejarPreguntas(Lista *lista, const char *fichero1);

/*  Primero elige un usuario, cuantas preguntas se lleva a la encuesta. Creamos un array dinámico que contiene
    en el primer elemento su longitud y despues siguen los números, teniendo cada uno un valor dentro del rango de la lista.
    El usuario tiene la opción de elegir las preguntas o que sean aleatoriamente elegido. 
    Este array tiene en favor que no hace falta barajar el fichero principal y se consigue el mismo efecto de aleatoria. */
int *crearArrayDinamico(Lista *lista_preguntas);

/* Se crea una nueva lista de preguntas. Las preguntas en esta lista serán seleccionado
   con los números que pasamos con el array dinámico a esta función. */
void crearListaEncuesta(Lista *lista_preguntas, Lista *lista_encuesta, int *random_array);

/* En este bucle, los encuestados responden a las preguntas y se pasa sus entradas a una lista.
   Está función se va a usar en la función 'iniciarEncuesta()'*/
void encuesta(Lista *lista_encuesta, int repeticiones);

/* Despues de que el usuario ha terminado responder a la encusta, se imprime el resultado de forma
   PREGUNTA X: Respuesta A 60% Respuesta B 30% Respuesta C 3% Respuesta D 2%,
   y se generarán dos ficheros con resultados de la encusta.*/
void statistics(Lista *lista, const char *nombre_fichero2, const char *nombre_fichero3);

/* En esta función se va a realizar la encuesta para los usuarios y la estadística. Se generarán dos 
   ficheros que reflejan los resultados de las encuestas.*/
void iniciarEncuesta(Lista *lista_preguntas, Lista *lista_encuesta, const char *fichero1,
                        const char *fichero2, const char *fichero3);

/* Función pasa el fichero que contiene la encusta y la estádistica a la pantalla (stdout). */
void printResumenEncuesta(const char *nombre_fichero3);




/****************************************************************************************************/
/**********************                       main - function                   *********************/
/****************************************************************************************************/
/*                                                                                                  */
/*        Main function contiene el menú princial que dejá eligir el usuario.                       */
int main(){
    /* Creamos instancias de 'Lista' */
    Lista lista1 = NULL;                                // lista1 contendrá todas las preguntas
    Lista lista2 = NULL;                                // lista2 contendrá una seleción aleatoria de preguntas
    const char *fichero1 = "fichero.txt";               //fichero que guarda todas las preguntas
    const char *fichero2 = "de_solucion";               //fichero que guarda pregunta con mejor resultado.
    const char *fichero3 = "resultado_encuesta";        //fichero que guarde encuesta con resultado estadístico.
   
    copyFileToList(&lista1, fichero1);                   //Actualiza la lista enlazada con datos en fichero si existen
    
    bool loop = True; //Valor para determinar el loop.
    while(loop==True){
        switch(mainmenu()){
            case 1:
                    iniciarEncuesta(&lista1, &lista2, fichero1, fichero2, fichero3);
                    break;
            case 2:  
                    manejarPreguntas(&lista1, fichero1);
                    break;
            case 3:
                    printResumenEncuesta(fichero3);
                    break;
            case 4:
                    printf("\n********************************************************************************\n"
                             "********************            FIN DEL PROGRAMA            ********************\n"
                             "********************************************************************************\n");
                    loop = False;
                    break;
            default:
                    printf("\n********************************************************************************\n"
                            "\t\t%cINPUT VALUE ERROR!\n"
                            "\tElige un n%cmero de 1 a 4 por favor.\n"
                            "********************************************************************************\n", 173,  163);
                    break;   
        }
    }
}



/* Imprime el menú principal. Devuelve un integer que sea usado para el caso 'switch' en la función main() */ 
int mainmenu(){
    int num;      
    printf("\n********************************************************************************\n");
    printf("************************    Encuesta - men%c principal   ************************\n\n", 163);
    printf("(1) Iniciar encuesta\n");
    printf("(2) Agregar preguntas al fichero de preguntas\n");
    printf("(3) Visualizar el fichero con los %cltimos resultados\n", 163);
    printf("(4) Salir\n");
    printf("\n\tElige un n%cmero [1-4]: ", 163);
    do{
        num = getIntegerFromUser();  
        if(num<0 || num >4){           //limitar al usuario introducir números 1 a 4
            printf("\n\tERROR al introducir n%cmero!\n"
                    "\tPor favor, elija un n%cmero de 1 a 4: ", 163);
        }
    }while(num < 0 || num > 4);
    printf("\n\n");
    return num;
}



/* Imprime el submenú. Devuelve un integer que sea usado para el caso 'switch' en la función 'manejarPreguntas()' */ 
int submenu(){
    int num;
    printf("\n\t********  Submen%c  ********\n\n", 163);
    printf("\t(1) Agregar preguntas\n");
    printf("\t(2) Eliminar preguntas\n");
    printf("\t(3) Imprimir Preguntas\n");
    printf("\t(4) Volver al men%c principal\n", 163);
    printf("\n\tElige un n%cmero [1-4]: ", 163);
    do{
        num = getIntegerFromUser();        //limitar al usuario introducir números 1 a 4
        if(num<0 || num >4){
            printf("\n\t¡ERROR al introducir el n%cmero!\n"
                    "\tPor favor, elija un n%cmero de 1 a 4: ", 163, 163);
        }
    }while(num < 0 || num > 4);
    printf("\n\n");
    return num;
}



/* Imprime otro submenú. El usuario elige entre (a) mala, (b) normal, (c) buena y (d) excelente. */
char submenu2(){
    char abcd[MAX];
    int len;
    printf("\t(a) Mala\n");
    printf("\t(b) Normal\n");
    printf("\t(c) Buena\n");
    printf("\t(d) Excelente\n");
    do{
        printf("\n\tIntroduzca: ");
        fflush(stdin);
        fgets(abcd, MAX, stdin);
        len = strlen(abcd);
        if((abcd[0]=='a'|| abcd[0]=='b' || abcd[0]=='c' || abcd[0]=='d') && len==2){
            break;
        } else {
            printf("\nPor favor, ¡elige entre [a/b/c/d]!\n", 173);
        }
    }while(1);
    return abcd[0];
}



/* Función que pide al usuario que introduzca un número que se devuelve */
int getIntegerFromUser(){
    char buffer[1024];
    char *p;
    long numero_long;
    int  numero_int;
    //Uso de fgets para evitar overflow
    fflush(stdin);
    fgets(buffer, sizeof(buffer), stdin);          //guarda una linea de flujo de dato
    if(strchr(buffer, '\n') == NULL){             //Comprueba que toda la linea està leida y el 'buffer' no se ha quedado pequeño
        printf("ERROR! El n%cmero introducido es demasiado largo!\n", 163);
        exit(EXIT_FAILURE);
    }
    numero_long = strtol(buffer, &p, 10);    // cambiar una cadena a un número entero del tipo 'long'
    if(p == buffer){
        printf("\n\tERROR, no es un n%cmero!\n"
                "\tIntroduzca un n%cmero: ", 163, 163);
        getIntegerFromUser();   //Funcion se llama recursivo si la entrada no era un número
    }
    numero_int = (int)numero_long;       //cambiar número entero del tipo long a número entero
    return numero_int;
}




/* Inserta un elemento nuevo al final de la lista enlazada.*/
void insertar(Lista *lista, char pregunta[length_pregunta], int letras, int nr, int rA, int rB, int rC, int rD, int iter){
    pNodo new, actual;                 //Crear un nodo nuevo
    new = malloc(sizeof(Pregunta));    //Reservar memoria en el tamaño del dato 'Pregunta'
    if(new == NULL){                   //Comprobar si la memoria apunta a '0', entonces no hay espacio y suelta error
        printf("ERROR, no se puede asignar espacio en la memoria!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new->texto, pregunta);      //pasamos las variables al elemento nuevo creado (new)
    new->tamano = letras;
    new->numPregunta = nr;
    new->respA = rA;
    new->respB = rB;
    new->respC = rC;
    new->respD = rD;
    new->iteraciones = iter;
    if(*lista == NULL){                
        new->next = *lista;
        *lista = new;
    } else {
        actual = *lista;
        while(actual->next!=NULL){
            actual = actual->next;
        }
        new->next = actual->next;
        actual->next = new;
    }
}



/* Quita un elemento de la lista, elegido por la variable 'Pregunta numPregunta'. */
void eliminar(Lista *lista, int num){
    pNodo first, previous;
    first = *lista;
    previous = NULL;
    while(first && first->numPregunta < num){   //iteración de la lista hasta llegar al número dado
        previous = first;
        first = first->next;
        }
        if(!first || first->numPregunta != num){
            return;     //Return para salir de la función si el número no existe
        }else{
            if(!previous){
                *lista = first->next;
            }else{
                previous->next = first->next;
            }
        free(first);
        }
}



/* Eliminamos la lista con todos sus entradas usando la función 'eliminar()'*/
void borrarLista(Lista *lista) {
    renumerarPreguntas(lista);  //Renumeramos las preguntas en la lista 'numPregunta'
    int listsize = listSize(*lista);
    for(int i=listsize; i>=0; --i){    //bucle elimina cada entrada en la lista linea por linea
        eliminar(lista, i);
    }
    lista = NULL;    //finalmente, la lista apunta a cero
}



/* Función devuelve cantidad de elementos que hay en la lista enlazada, '0' si está vacia. */
int listSize(Lista lista){
    int counter = 0;          //variable que cuenta los bucles
    while(lista != NULL){     //recorre la lista hasta el final
        lista = lista->next;
        counter++;
    }
    return counter;
}




/* Renumera las preguntas de 1 hasta el final de la lista - Struct variable numPregunta*/
void renumerarPreguntas(Lista *lista){
    pNodo first = *lista;
    int counter = 1;   //empezamos la renumeración con el valor 1  
    while(first){
        first->numPregunta = counter;
        first = first->next;
        counter++;
    }
}



/* Imprime las preguntas y su número en pantalla (stdin). */
void printPreguntas(Lista lista){
    printf("\n\n******************  Lista de Preguntas  ********************\n\n");
    if(listSize(lista) == 0){                
        printf("\tNo hay preguntas a%cadidas a la lista a%cn!\n"
                "\tElige n%cmero 1 en el men%c para a%cadir preguntas.\n", 164, 163, 163, 163, 164);
        printf("\n************************************************************\n");
    } else {
        while(lista != NULL){   //Iteración sobre la lista
            printf("%d. %s\n", lista->numPregunta, lista->texto);
            lista = lista->next;
        }
    }
    printf("\n************************************************************\n\n");
}



/* Copia todas las lineas del fichero a la lista enlazada, si el fichero no es vacio. */
void copyFileToList(Lista *lista, const char *fichero1){
    char texto[length_pregunta];
    int tamano;           //variable para el tamaño (longitud) de la pregunta
    int nr_pregunta = 1;     //Inicializamos los números con 1
    FILE *fichero = fopen(fichero1, "a+");    // a+ en vez de 'r' por si el archivo no existe aún
    if(fichero == NULL){
        printf( "\tProblemas al leer el fichero!\n");
        exit(1);
    }
    //Comprobamos si el fichero contiene datos
    fseek(fichero, 0, SEEK_END);       //cambia la posición en el fichero al final
    if(ftell(fichero) != 0){           //ftell devuelve posición actual y si es mayor que '0', entonces contiene datos.
        fseek(fichero, 0, SEEK_SET);        //cambia de vuelta al principio del fichero
        while(fgets(texto, sizeof(texto), fichero) != NULL){     //lee linea por linea del fichero con fgets
            char *p = strchr(texto, '\n');  // encuenta '\n' al final de la pregunta 
            if (p != NULL) *p = '\0';       // elimina '\n'
            tamano = strlen(texto);     //Tamaño de la pregunta
            insertar(lista, texto, tamano, nr_pregunta, 0, 0, 0, 0, 0);
            nr_pregunta++;                  //incrementa el número de las preguntas
        }
    } 
    fclose(fichero);
    renumerarPreguntas(lista);   //renumera la variable 'numPregunta' de 1 hasta final por si estan mal numerados anteriormente
}



/* Copia todos los elementos de la variable 'Pregunta texto' (que son las preguntas) al fichero. */
void copyListToFile(const char *fichero1, Lista *lista){
        //Creamos un array en que se guarda la pregunta de un elemento para pasarla en un bucle al fichero
        char pregunta[length_pregunta];    
        FILE *fichero = fopen(fichero1, "w");   //El contenido con opción 'w' se sobreescribe
        if(!fichero){
            printf( "\tProblemas al abrir el fichero!\n"
                    "\tEl problema puede tener varios motivos.\n"
                    "\tCompruebe sus derechos al escribir en la carpeta!\n" );
        }
        //Antes de pasar los datos de la lista al fichero, renumbramos las preguntas por ser caso que no esten bien númerados.
        renumerarPreguntas(lista);   //Renumera la variable 'numPregunta' de la lista de 1 hasta final.

        pNodo first;
        first = *lista;
        while(first){               //Iteramos sobre la lista
            strcpy(pregunta, first->texto);
            fputs(pregunta, fichero);  //Añade la pregunta al fichero
            fputs("\n", fichero);      //Añade 'salto linea' al final de la pregunta    
            first = first->next;
        }
        fclose(fichero);
}    



/* Agregar, imprimir e ileminar preguntas de la lista. Mantiene un submemú para realizarlo */
void manejarPreguntas(Lista *lista, const char *fichero1){
    bool loop = True; //Valor para determinar el loop.
    while(loop==True){
        switch(submenu()){
            case 1:
                    /* En un bucle se pregunta al usuario si quiere agregar otra pregunta a la encuesta.
                    El bucle se termina con la tecla 'q'. Se inserta cada pregunta en la lista y al final se 
                    usa la funcion copyListToFile() para actualizar el fichero.*/ 
                    printf("\n************************************************************\n"
                             "******************    Agregar preguntas   ******************\n\n");
                    char question[length_pregunta];       //Inizialisación de la variable 'question'
                    int len, i;
                    while(1){
                        printf("\tIntroduzca una pregunta [quit='q']:\n");
                        fgets(question, length_pregunta, stdin);
                        len = strlen(question);    // lo anotamos para luego pasarlo a la función 'insertar()'.
                        for(i = 0;i<MAX; i++){     //fgets adjunta al final un newline '\n' que vamos a quitar con este bucle.
                            if(question[i] == '\n'){
                                question[i] = '\0';   //sustituimos '\n' por '\0'.
                            }
                        }
                        if((question[0] == 'q' || question[0] == 'Q') && (len == 2)){  //terminamos el bucle con 'q' o 'Q'
                            break;
                        }
                        if(question[0] != '\0'){	 //evita que se guarda una linea vacia tecleando 2 veces 'Return'.
						    insertar(lista, question, len, 0, 0, 0, 0, 0, 0);       //insertamos cada pregunta en la lista, por defecto valores con 0.
						}
                    }
                    copyListToFile(fichero1, lista);    //pasamos la lista que ha sido actualizada al fichero.
                    break;
            case 2:
                    /* Se pide al usuario elegir un número de una pregunta para eliminarlo para luego eliminarlo
                    en la lista enlazada. El próximo paso, se actualiza el fichero con la lista actúal */
                    printf("\n************************************************************\n"
                             "******************   Eliminar preguntas   ******************\n\n");
                    printPreguntas(*lista);  //imprimimos la lista de preguntas para que el usuario puede elegir
                    printf("Introduzca el n%cmero de la pregunta que desea eliminar: ", 163);
                    int numeroPregunta;
                    int listsize;
                    numeroPregunta = getIntegerFromUser();
                    listsize = listSize(*lista);
                    if(numeroPregunta>=0 && numeroPregunta<=listsize){  //comprueba si el numero introducido está dentro del limite
                        eliminar(lista, numeroPregunta);
                        renumerarPreguntas(lista);
                        copyListToFile(fichero1, lista);
                    }else{
                        printf("\n\t%cEl n%cmero no existe en la lista!\n", 173, 163);
                    } 
                    break;
            case 3:  
                    /*Imprime los números de las preguntas con la pregunta correspondiente. */
                    printPreguntas(*lista); 
                    break;
            case 4:
                    loop = False;  //Volvemos al menú principal
                    break;
            default:
                    printf("\n*********************************************\n"
                            "\tINPUT VALUE ERROR!\n"
                            "Elija un n%cmero del men%c de 1 a 4 por favor.\n"
                            "*********************************************\n",163, 163);
                    break;
            
        }
    }
}



/*  Primero elige un usuario cuantas preguntas se lleva a la encuesta. Creamos un array dinámico que contiene
    en el primer elemento su longitud y despues números en un rango de la longitud de la lista.
    El usuario tiene la opción de elegir las prguntas o que sean aleatoriamente elegido. 
    Este array tiene en favor que no hace falta barrajar el fichero principal y tenemos el mismo efecto. */
int *crearArrayDinamico(Lista *lista_preguntas){
    int sizeOfList = listSize(*lista_preguntas);
    int arraylength;
    char encuestaAleatoria[MAX];
    while(1){    // Loop para asegurar valor intruducido por el usuario
        printf("\t%cCu%cntas preguntas desea para la encuesta?\n"
                "\t(m%cximo %d preguntas): ", 168, 160, 160, sizeOfList);
        arraylength = getIntegerFromUser();
        if(arraylength<=sizeOfList){   //comprobamos si el valor introducido no sea mas que las preguntas guradadas
            break;
        }else{
            printf("\n\tError, s%clamente hay %d preguntas guardadas!\n\n", 162,  sizeOfList);
        }
    }

    arraylength+=1; //añadimos una entrada al array, para guarar la longitud del array, que sea la primera entrada
    
    int *dinamic_array = malloc(sizeof(int)*arraylength); //se crea un array dinámico
    if(dinamic_array == NULL){                            //comprobamos que no apunta a '0'
        printf("Error, No se puede asignar espacio en la memoria.\n");
        exit(EXIT_FAILURE);
    }
    memset(dinamic_array, 0, sizeof(int) * arraylength);  // inizalizar array con '0'
    *dinamic_array = arraylength; //en la primera entrada del array guardamos su longitud total.

    printf("\n\t%cDesea que las preguntas sean elegidas de forma aleatoria?\n"
            "\t\t[S%c='S'/No='N']: ", 168, 161);
    bool loop = True;
    while(loop == True){
        fgets(encuestaAleatoria, MAX, stdin);
        if((encuestaAleatoria[0] == 'S' || encuestaAleatoria[0] == 's')){  //terminamos el bucle
            srand(clock());     //usamos la función srand en combinación con la hora para crear un número aleatorio
            /* En este bucle loop asignamos un valor aleatorio en nuestro array
            dinámico con un máximo del tamaño como preguntas en la lista*/
            for(int i=1;i<arraylength;i++){    //comenzamos por 1, la primera entrada es la longitud
                int temp = rand()%sizeOfList+1;   //rand() devuelve un número aleatorio desde 1 hasta tamaño lista
                bool exists = False;
                for(int j=1;j<i;++j){  //vamos a comprobar si el valor ya existe en el array
                    if(*(dinamic_array+j) == temp){
                        exists = True;
                        break;
                    }
                }
                if(!exists){
                    *(dinamic_array+i) = temp;      //asignamos el valor aleatorio a nuestra entrada del array
                }
                else{
                    --i;  //si ya existe , descontamos del bucle uno y lo intentamos de nuevo
                }
            }
            loop = False; 
        } else if ((encuestaAleatoria[0] == 'N' || encuestaAleatoria[0] == 'n')){  //terminamos el bucle con 'n' o 'N'
            printPreguntas(*lista_preguntas);
            printf("\nIntroduzca %d n%cmeros de las preguntas que desea usar para la encuesta.\n", arraylength-1, 163);
            for(int i=1;i<arraylength;i++){
                *(dinamic_array+i) = getIntegerFromUser();       
            }
            loop = False;
        }else{
            printf("\n\t%cInputError! Por favor, introduzca S o N: ", 173);
        }
    }

    return dinamic_array;          //devolvemos el array creado
}



/* Se crea una nueva lista de preguntas. Las preguntas en esta lista serán seleccionado
   con los números que pasamos usando el array dinámico a esta función. */
void crearListaEncuesta(Lista *lista_preguntas, Lista *lista_encuesta, int *random_array){
    int arraylength = *random_array;
    //Ahora creamos una lista con preguntas aleatorias usando nuestro array
    for(int k = 1; k<arraylength; k++){  //iteramos por el array
        pNodo first = *lista_preguntas; 
        while(first){                     //iteramos sobre la lista
            if(first->numPregunta == *(random_array+k)){  //comprobamos si el número de la pregunta es igual al número aleatorio del array
                int len = strlen(first->texto);
                insertar(lista_encuesta, first->texto, len, first->numPregunta,0,0,0,0,0);
            }
            first = first->next;
        }
    }
}



/* En este bucle, los encuestados responden a las preguntas y se pasa sus entradas a una lista.
   Está función se va a usar en la función 'iniciarEncuesta()'*/
void encuesta(Lista *lista_encuesta, int repeticiones){
    printf("\n\n********************************************************************************\n");
    printf("*******************               Encuesta                  ********************\n");
    printf("********************************************************************************\n");
    renumerarPreguntas(lista_encuesta);  
    int c = 1;
    while(c<=repeticiones){
        printf("\n\n-----------------------------    Encuestado %d    -------------------------------\n\n", c);
        pNodo first;
        first = *lista_encuesta;
        while(first != NULL){
            printf("%d. %s\n\n", first->numPregunta, first->texto);
            //El usuario elige entre a,b,c,d. Según su elección aumentamos la variable por 1
            switch(submenu2()){
                case 'a':
                            first->respA+=1;
                            break;
                        
                case 'b':
                            first->respB+=1;
                            break;
                case 'c':
                            first->respC+=1;
                            break;
                case 'd':
                            first->respD+=1;
                            break;
            }
            first->iteraciones+=1;
            first = first->next;
        }
        c++;
    }
}



/* Despues de que el usuario ha terminado responder a la encuesta, se imprime el resultado de forma
   PREGUNTA X: Respuesta A 60% Respuesta B 30% Respuesta C 3% Respuesta D 2%,
   y se generarán dos ficheros con resultados de la encusta.*/
void statistics(Lista *lista, const char *nombre_fichero2, const char *nombre_fichero3){
    int numbers[4];    //Generamos un array que usamos mas tarde para conseguir un valor máximo.
    /* Creamos algunos string que pasaremos a los ficheros. */
    char mala[] = {" (a) Mala"};    
    char normal[] ={" (b) Normal"};
    char buena[] = {" (c) Buena"};
    char excelente[] = {" (d) Excelente"};
    int maximum = 0;
    
    /* En este fichero aparecerán las preguntas realizadas junto con las respuestas
       que más porcentaje obtuvieron para cada una de ellas*/
    FILE *fichero2 = fopen(nombre_fichero2, "w");
    if(!fichero2){
            printf( "\n\t%cProblemas al abrir el fichero!\n"
                    "\tEl problema puede tener varios motivos.\n"
                    "\t%cCompruebe sus derechos al escribir en la carpeta!\n", 173, 173 );
    }

    /* En este fichero aparecerán las preguntas y las estadísticas de la última encuesta realizada */
    FILE *fichero3 = fopen(nombre_fichero3, "w");
    if(!fichero3){
            printf( "\n\t%cProblemas al abrir el fichero!\n"
                    "\tEl problema puede tener varios motivos.\n"
                    "\t%cCompruebe sus derechos al escribir en la carpeta!\n", 173, 173 );
    }
    renumerarPreguntas(lista);
    printf("\n\n********************************************************************************\n");
    printf("***************            Estad%cstica de la encuesta          *****************\n\n", 161);
    int numPregunta, rA, rB, rC, rD;  // en estas variables se guardaran los porcentajes de la respuesta elegida
    pNodo first;
    first = *lista;
    while(first != NULL){
            numPregunta = first->numPregunta;
            double total = first->respA + first->respB + first->respC + first->respD;
            numbers[0] = first->respA;
            numbers[1] = first->respB;
            numbers[2] = first->respC;
            numbers[3] = first->respD;
            rA = (int)(((double)first->respA * 100) / total); //cambiar a porcentaje
            rB = (int)(((double)first->respB * 100) / total);
            rC = (int)(((double)first->respC * 100) / total);
            rD = (int)(((double)first->respD * 100) / total);
            // : Resp. A = 66%,  Resp. B = 33%,  Resp. C = 0%, Resp. D = 0%
            printf("Pregunta %d: Respuesta A %d%%,  Respuesta B %d%%,  Respuesta C %d%%,  "
                "Respuesta D %d%%\n", numPregunta, rA, rB, rC, rD);

            /* Hacemos un simple bucle por el array para reconocer su valor máximo*/
            for(int i = 0;i<4;i++){
                if(numbers[i]>maximum){
                    maximum = numbers[i];
                }        
            }

            /* Definimos la longitud del string ' (d) excelente'->14 Entradas +1 */
            int len = strlen(first->texto) + 15 ;
            char line[len];
            //Comprobamos quien tiene el valor máximo y lo pasamos al fichero2 
            // Si el mismo valor sale dos veces, entonces se agregan las dos preguntas al fichero
            if(first->respA == maximum){
                strcpy(line, first->texto);
                strcat(line, mala);
                fputs(line, fichero2);
                fputs("\n", fichero2);
            } else if(first->respB == maximum){
                strcpy(line, first->texto);
                strcat(line, normal);
                fputs(line, fichero2);
                fputs("\n", fichero2);
            } else if(first->respC == maximum){
                strcpy(line, first->texto);
                strcat(line, buena);
                fputs(line, fichero2);
                fputs("\n", fichero2);
            } else if(first->respD == maximum){
                strcpy(line, first->texto);
                strcat(line, excelente);
                fputs(line, fichero2);
                fputs("\n", fichero2);
            }

            /* Aquí pasamos la encuesta entera al fichero3*/
            char str[64];    //creamos un string para pasar los valores integer en adelante
            sprintf(str, "%d", numPregunta);      //cambiar de integer a string, añadimos el número de la pregunta
            strcpy(line, str);                    //lo copiamos a nuestro array que luego pasamos al fichero
            strcat(line, ". ");                   //Añadimos un '. ' despues del número de la pregunta
            strcat(line, first->texto);           //Ahora añadimos la pregunta
            fputs(line, fichero3);                //lo pasamos al fichero                  
            fputs("\n", fichero3);
            /* Se pasan nuestros variables string que hemos creado al principio de la función.
               mala, normal, buena, excelente al fichero */
            fputs(mala, fichero3);                
            fputs("\n", fichero3);

            fputs(normal, fichero3);
            fputs("\n", fichero3);
            fputs(buena, fichero3);
            fputs("\n", fichero3);

            fputs(excelente, fichero3);
            fputs("\n", fichero3);
            fputs("*******************************************************\n", fichero3);
            /* La última linea que queda por añadir son los resultados estadísticos 
               que viene ahora. Con sprintf()  lo cambiamos de integer a string. */
            fputs("Resp. A = ", fichero3);
            sprintf(str, "%d", rA);
            fputs(str, fichero3);
            fputs(", Resp. B = ", fichero3);
            sprintf(str, "%d", rB);
            fputs(str, fichero3);
            fputs(", Resp. C = ", fichero3);
            sprintf(str, "%d", rC);
            fputs(str, fichero3);
            fputs(", Resp. D = ", fichero3);
            sprintf(str, "%d", rD);
            fputs(str, fichero3);
            fputs("\n\n\n", fichero3);
            first = first->next;    // pasamos en el bucle un elemento 
    }
    fclose(fichero2);
    fclose(fichero3);
    printf("\n");
}



/* En esta función se va a realizar la encuesta para los usuarios y estadística. Se generarán dos 
   ficheros que reflejan nuestros resultados de las encuestas.*/
void iniciarEncuesta(Lista *lista_preguntas, Lista *lista_encuesta, const char *fichero1,
                        const char *fichero2, const char *fichero3){
    int *dynArray;   
    int repeticiones;
    int cantidad_preguntas;
    char empezarEncuesta[MAX];   //variable para devolver un 'S' o 'N' para comenzar la encuesta
    int sizeOfList = listSize(*lista_preguntas);
    //Antes de empezar, nos aseguramos que existen preguntas para la encuesta
    if(sizeOfList == 0){      
        printf("\n\n\t*********************************************************\n");
        printf("\t\t%cAtenci%cn!, No hay preguntas a%cadidas para la encuesta.\n"
                "\t\tPor favor, vaya al men%c principal y elija la tecla 2.\n"
                "\t\t- Agregar preguntas al fichero de preguntas. Gracias\n", 173, 162, 164, 163);
        printf("\t*********************************************************\n");
    } else {
        /*recibimos una array con las números de las preguntas que usamos en la encuesta.*/
        dynArray = crearArrayDinamico(lista_preguntas);
        /*Crea una lista que guarda las preguntas que usaremos para la encusta. */
        crearListaEncuesta(lista_preguntas, lista_encuesta, dynArray);

        
        printf("\n\t%cCu%cntas veces se debe repetir la encuesta?: ", 168,  160);
        repeticiones = getIntegerFromUser();

        cantidad_preguntas = *dynArray - 1;
        printf("\n********************************************************************************\n");
        printf("*******            La encuesta contiene %d preguntas                    ********\n"
               "*******            y se repitir%c %d veces!                              ********\n", cantidad_preguntas, 160, repeticiones);
        printf("********************************************************************************\n");


        printf("\n\t%cEst%c seguro que quiere comenzar la encuesta?\n"
                "\t\t[S%c='S'/No='N']: ", 168, 160, 161);
        bool loop = True;
        while(loop == True){
            fgets(empezarEncuesta, MAX, stdin);
            if((empezarEncuesta[0] == 'S' || empezarEncuesta[0] == 's')){  //terminamos el bucle
                loop = False;                
            }else if((empezarEncuesta[0] == 'N' || empezarEncuesta[0] == 'n')){  //terminamos el bucle
                borrarLista(lista_encuesta);   //Antes de salir liberamos la memoria
                borrarLista(lista_preguntas);
                printf("\n*********************************************************\n");
                printf("\tFin del programa - Hasta la pr%cxima", 162);
                printf("\n*********************************************************\n\n");
                exit(1);    
            }else{
                printf("\n\tInputError! Por favor, introduzca S o N: ");
            }
        }
        
        /***** Empezamos con nuestra encuesta ******/            
        encuesta(lista_encuesta, repeticiones);  
        /***** Creamos nuestros ficheros con los resultados de la encuesta ******/
        statistics(lista_encuesta, fichero2, fichero3);

        borrarLista(lista_encuesta);   //Cómo último, dejamos la lista vacía para realizar otro sin salir del programa.
    }
}



/* Función pasa el fichero que contiene la encusta y la estádistica a la pantalla (stdout). */
void printResumenEncuesta(const char *nombre_fichero3){
    printf("\n********************************************************************************\n");
    printf("**************************    Los %cltimos resultados    ************************\n\n", 163);
    FILE *resultado = fopen(nombre_fichero3, "r");
    if(!resultado){
        printf("\t%cEl fichero se genera terminando una encuesta!\n" 
                "\t%cProblemas al abrir el fichero!\n"
                "\tEl problema puede tener varios motivos.\n"
                "\t%cCompruebe sus derechos al escribir en la carpeta!\n", 173, 173, 173);
    } else {
		char letra;
		while((letra = fgetc(resultado)) != EOF){      //busca cada carácter char hasta termine el fichero
			printf("%c", letra);
		}
	}
    fclose(resultado);
}

