/*Programa: <Trabajo Obligatorio ESTRUCTURA DE DATOS>
Autor: <Michael Schossow> Fecha: <15.08.2022> */

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
#define MAX 24

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

/* Variables globales */
typedef Pregunta *pNodo;             //instancia de la estructura, puntero al primer elemento de la lista
typedef Pregunta *Lista;              //lista


/* Imprime el menu principal. Devuelve un 'char' que sea usado para un caso 'switch'*/ 
int mainmenu();

/* Imprime el menu secundario (Añadir, eliminar o ver pretuntas), devuele un 'char' para un caso switch */
int submenu();

/* Función que pide al usuario que introduzca un número que se devuelve */
int getIntegerFromUser();

/* Inserta un elemento nuevo al final de la lista enlazada.*/
void insertar(Lista *lista, char pregunta[length_pregunta], int letras, int nr, int rA, int rB, int rC, int rD, int iter);

/* Quita un elemento de la lista elegido por la variable 'Pregunta numPregunta'. */
void eliminar(Lista *lista, int num);

/*Función devuelve cantidad de elementos que hay en la lista enlazada, '0' si está vacia*/
int listSize(Lista lista);

/*renumera las preguntas de 1 hasta el final de la lista - Struct variable numPregunta*/
void renumerarPreguntas(Lista *lista);

/* Imprime la lista en pantalla */
void printPreguntas(Lista lista);

/* Copia todas las lineas del fichero a la lista enlazada, si el fichero no es vacio. */
void copyFileToList(Lista *lista, const char *nombre_fichero);

/* copia todos los elementos de la variable 'Pregunta texto' al fichero */
void copyListToFile(const char *nombre_fichero, Lista *lista);

/* agregar , print e ileminar preguntas de la lista. Mantiene un submemú para realizarlo */
void manejarPreguntas(Lista *lista, const char *nombre_fichero);



/* */
void iniciarEncuesta(Lista *lista){

    // Checken , ob fragen gespeichert sind.
       // Wenn keine Fragen gespeichert sind, den user auffordern, welche anzulegen. 
       //Auf das submenu 2 verweisen.

    // Fragen, wieviel Fragen die Umfrage haben soll
        // Tsten, das es weniger sind als fragen die gespeichert sind. 

    // Neue liste erstellen mit Zufallszahlen     int aleartoria()  gib zufällig eine zurück
    //Vielleicht in eine liste packen, wenn Zahlen doppelt, noch einmal bis array voll ?????
    // wird wohl recursive


    //Benutzer fragen, wie oft er die Umfrage wiederholen möchte

    

    //  Umfrage starten
    // Usted ha elegido 6 preguntas aleatorias de 42 total. La encuesta se va a realizar x veces.
        //Estos datos son correctso (Sí/NO)
    // EStá seguro que Usted quiere empezar la encuesta. (Sí/No)


                // if iteracion == 1    ++  funcion die den wert iteration um 1 erhöht

    // 1. Pregunta                  -> 2. PRegunta           -> 3. Pregunta
        //(a) Mala
        //(b) Normal
        //(c) Buena
        //(d) Excelente

    //Estadistica ->file : resultado_encuesta. Vielleicht noch ne nummer Iteration davor
    // Iter: Resp. A = 66%, Resp. B = 33%, Resp. C = 0%, Resp. D = 0%



}



/*******************************************************************************/
/**********************           main - function          *********************/
/*******************************************************************************/
int main(){
    /* Creamos instancias de Lista */
    Lista lista1 = NULL;           // lista1 contiene todas las preguntas
    //Lista lista2 = NULL;           // lista2 contiene una seleción aleatoria de preguntas
    const char *fichero = "fichero3.txt";           //fichero que guarda todas las preguntas
    copyFileToList(&lista1, fichero);              //Actualiza la lista enlazada con datos en fichero si existen
    
    bool loop = True; //Valor para determinar el loop.
    while(loop==True){
        switch(mainmenu()){
            case 1:
                    printf("*** Iniciar Encuesta ***\n"); 
                    break;
            case 2:  
                    manejarPreguntas(&lista1, fichero);
                    break;
            case 3:
                    printf("Fichero con resultados de las STATS\n");
                    break;
            case 4:
                    printf("\n*********************************************************\n"
                            "*******************  FIN DEL PROGRAMA  ******************\n"
                            "*********************************************************\n");
                    loop = False;
                    break;
            default:
                    printf("\n*********************************************\n"
                            "\tINPUT VALUE ERROR!\n"
                            "Elige un número de 1 a 4 por favor.\n"
                            "*********************************************\n");
                    break;   
        }
    }
}




int mainmenu(){
    int num;      
    printf("\n*********************************************************\n");
    printf("*************  Encuesta - menú principal  ***************\n\n");
    printf("(1) Iniciar encusta\n");
    printf("(2) Agregar preguntas al fichero de preguntas\n");
    printf("(3) Visualizar el fichero con los últimos resultados\n");
    printf("(4) Salir\n");
    printf("\n\tElige un número [1-4]: ");
    do{
        num = getIntegerFromUser();  
        if(num<0 || num >4){           //limitar de número 1 a 4
            printf("\n\tERROR al introduzir número!\n"
                    "\tPor favor, eliga un número de 1 a 4: ");
        }
    }while(num < 0 || num > 4);
    printf("\n\n");
    return num;
}




int submenu(){
    int num;
    printf("\n\t********  Submenú  ********\n\n");
    printf("\t(1) Agregar preguntas\n");
    printf("\t(2) Eliminar preguntas\n");
    printf("\t(3) Imprimir Preguntas\n");
    printf("\t(4) Volver al menú principal\n");
    printf("\n\tElige un número [1-4]: ");
    do{
        num = getIntegerFromUser();
        if(num<0 || num >4){
            printf("\n\tERROR al introduzir número!\n"
                    "\tPor favor, eliga un número de 1 a 4: ");
        }
    }while(num < 0 || num > 4);
    printf("\n\n");
    return num;
}




/* Función que pide al usuario que introduzca un número que se devuelve */
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




/* Inserta un elemento nuevo al final de la lista enlazada.*/
void insertar(Lista *lista, char pregunta[length_pregunta], int letras, int nr, int rA, int rB, int rC, int rD, int iter){
    pNodo new, actual;                 //Crear un nodo nuevo
    new = malloc(sizeof(Pregunta));    //Reservar memoria en el tamaño del dato 'Pregunta'
    if(new == NULL){                   //Comprobar si la memoria apunta a '0', entonces no hay espacio y suelta error
        printf("ERROR, no assignmend new Element to RAM!\n");
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





/* Quita un elemento de la lista elegido por la variable 'Pregunta numPregunta'. */
void eliminar(Lista *lista, int num){
    pNodo first, previous;
    first = *lista;
    previous = NULL;
    while(first && first->numPregunta < num){
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




/*Función devuelve cantidad de elementos que hay en la lista enlazada, '0' si está vacia*/
int listSize(Lista lista){
    int counter = 0;          //variable que cuenta los bucles
    while(lista != NULL){     //recorre la lista hasta el final
        lista = lista->next;
        counter++;
    }
    return counter;
}




/*renumera las preguntas de 1 hasta el final de la lista - Struct variable numPregunta*/
void renumerarPreguntas(Lista *lista){
    pNodo first, previous;
    first = *lista;
    previous = NULL;
    int counter = 1;
    while(first){
        previous = first;
        previous->numPregunta = counter;
        first = first->next;
        counter++;
    }
}




void printPreguntas(Lista lista){
    printf("****************** Lista de Preguntas  ********************\n\n");
    if(listSize(lista) == 0){                
        printf("\tNo hay preguntas añadidas a la lista aún!\n"
                "\tElige número 1 en el menú para añadir preguntas.\n");
        printf("\n***********************************************************\n");
    } else {
        while(lista != NULL){
            printf("%d. %s\n", lista->numPregunta, lista->texto);
            lista = lista->next;
        }
    }
    printf("\n***********************************************************\n\n");
}





/* Copia todas las lineas del fichero a la lista enlazada, si el fichero no es vacio. */
/* Si hay datos guardados de la última sesión, lo volvemos a agregar a la lista */
void copyFileToList(Lista *lista, const char *nombre_fichero){
    char texto[length_pregunta];
    int tamano;           //variable para el tamaño (longitud) de la pregunta
    int nr_pregunta = 1;     //Inicializamos los números con 1
    FILE *fichero = fopen(nombre_fichero, "a+");    // a+ en vez de 'r' por si el archivo no existe aún
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
            insertar(lista, texto, tamano, nr_pregunta, 0, 0, 0, 0, 1);
            nr_pregunta++;                  //incrementa el número de las preguntas
        }
    } 
    fclose(fichero);
    renumerarPreguntas(lista);   //renumera la variable 'numPregunta' de 1 hasta final por si estan mal numerados anteriormente
}





/* copia todos los elementos de la variable 'Pregunta texto' al fichero */
void copyListToFile(const char *nombre_fichero, Lista *lista){
        char pregunta[length_pregunta];    //Este array va a ser nuestra pregunta que se pasa al fichero
        //Abrimos el fichero con 'w' para cambiarlo a la longitud '0'.
        //Quiere decir, que vamos a borrar el contenido del fichero
        FILE *fichero = fopen(nombre_fichero, "w");
        if(!fichero){
            printf( "\tProblemas al abrir el fichero!\n"
                    "\tEl problema puede tener varios motivos.\n"
                    "\tComprueban sus derechos de escribir en la carpeta!\n" );
        }
        // antes de pasar los datos de la lista al fichero, renumbramos las preguntas por ser caso.
        renumerarPreguntas(lista);   //renumera la variable 'numPregunta' de 1 hasta final por si estan mal numerados anteriormente

        pNodo first, previous;
        first = *lista;
        previous = NULL;
        while(first){               //Iteramos sobre la lista
            previous = first;
            strcpy(pregunta, previous->texto);
            fputs(pregunta, fichero);  //Añade la pregunta al fichero
            fputs("\n", fichero);      //Añade 'salto linea' a la pregunta    
            first = first->next;
        }
        fclose(fichero);
}    





/* agregar , print e ileminar preguntas de la lista. Mantiene un submemú para realizarlo */
void manejarPreguntas(Lista *lista, const char *nombre_fichero){
    bool loop = True; //Valor para determinar el loop.
    while(loop==True){
        switch(submenu()){
            case 1:
                    /* En un bucle se pregunta al usuario si quiere agregar otra pregunta a la encuesta.
                    El bucle se termina con la tecla 'q'. Se inserta cada pregunta en la lista y al final se 
                    usa la funcion copyListToFile() para actualizar el fichero.*/ 
                    printf("\n*********************************************\n"
                            "***********   Agregar preguntas  ************\n\n");
                    char question[length_pregunta];       //Inizialisación de la variable 'question'
                    int len, i;
                    while(1){
                        printf("\tIntroduzca una pregunta [quit='q']:\n");
                        fgets(question, length_pregunta, stdin);
                        len = strlen(question);    // lo anotamos para luego pasarlo a la función 'insertar()'
                        for(i = 0;i<MAX; i++){     //fgets adjunta al final un newline '\n' que vamos a quitar con este bucle
                            if(question[i] == '\n'){
                                question[i] = '\0';
                            }
                        }
                        if((question[0] == 'q' || question[0] == 'Q') && (len == 2)){  //terminamos el bucle
                            break;
                        }
                        insertar(lista, question, len, 0, 0, 0, 0, 0, 1);       //insertamos cada pregunta en la lista, por defecto valores con 0 y 1.
                    }
                    copyListToFile(nombre_fichero, lista);    //pasamos la lista que ha sido actualizada al fichero.
                    break;
            case 2:
                    /* Se pide al usuario elegir un número de una pregunta para eliminarlo para luego eliminarlo
                    en la lista enlazada. El próximo paso, se actualiza el fichero con la lista actúal */
                    printf("\n*********************************************\n"
                            "***********   Eliminar preguntas  ***********\n\n");
                    printPreguntas(*lista);
                    printf("Introduzca el número de la pregunta que desa eliminar: ");
                    int numeroPregunta;
                    int listsize;
                    numeroPregunta = getIntegerFromUser();
                    listsize = listSize(*lista);
                    if(numeroPregunta>=0 && numeroPregunta<=listsize){  //comprueba si el numero introducido está dentro del limite
                        eliminar(lista, numeroPregunta);
                        renumerarPreguntas(lista);
                        copyListToFile(nombre_fichero, lista);
                    }else{
                        printf("\n\tNúmero no existe en la lista!\n");
                    } 
                    break;
            case 3:  
                    /*Imprime los números de las preguntas con la pregunta correspondiente. */
                    printPreguntas(*lista); 
                    break;
            case 4:
                    loop = False;
                    break;
            default:
                    printf("\n*********************************************\n"
                            "\tINPUT VALUE ERROR!\n"
                            "Elige un numero del menú de 1 a 4 por favor.\n"
                            "*********************************************\n");
                    break;
            
        }
    }
}
