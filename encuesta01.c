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

/*********----------**********----------80********----------**********---------*/
/*********----------**********----------100*******----------**********----------**********----------**********--------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define length_pregunta 160
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

char submenu2();

/* Función que pide al usuario que introduzca un número que se devuelve */
int getIntegerFromUser();

/* Inserta un elemento nuevo al final de la lista enlazada.*/
void insertar(Lista *lista, char pregunta[length_pregunta], int letras, int nr, 
                int rA, int rB, int rC, int rD, int iter);

/* Quita un elemento de la lista elegido por la variable 'Pregunta numPregunta'. */
void eliminar(Lista *lista, int num);

void borrarLista(Lista *lista);

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

/*  Primero elige un usuario cuantas preguntas se lleva a la encuesta. Creamos un array dinámico que tiene de primer elemento
    su longitud que ha definido el usuario anteriormente y despues números aleatorias en un rango de la longitud de la lista.*/
int *crearArrayDinamico(Lista *lista_preguntas);

/*  Se crea una nueva lista de preguntas. Las preguntas en esta lista han sido seleccionado
    con el número aleatorio que hemos pasado con el array dinámico a la función.*/
void crearListaAleatoria(Lista *lista_preguntas, Lista *lista_aleatoria, int *random_array);


/*********----------**********----------80********----------**********---------*/

/*********----------**********----------100*******----------**********----------**********----------**********--------*/


/* Encuesta */
void encuesta(Lista *lista_aleatoria, int repeticiones){
    int loopCounter = 1;
    printf("\n*********************************************************\n");
    printf("\n*******************    Encuesta      ********************\n");
    printf("\n*********************************************************\n");
    
    int c = 1;
    while(c<=repeticiones){
        printf("\n\t *** Encuestado %d *** \n", c);
        pNodo first;
        first = *lista_aleatoria;
        while(first != NULL){
            printf("%d. %s\n\n", loopCounter, first->texto);
            switch(submenu2()){
                case 'a':
                            printf("\ta\n");
                            first->respA+=1;
                            break;
                        
                case 'b':
                            printf("\tb\n");
                            first->respB+=1;
                            break;
                case 'c':
                            printf("\tc\n");
                            first->respC+=1;
                            break;
                case 'd':
                            printf("\tc\n");
                            first->respD+=1;
                            break;
            }
            first->iteraciones+=1;
            first = first->next;
            loopCounter++;
        }
        loopCounter = 1;
        c++;
    }
}



/* */
void iniciarEncuesta(Lista *lista_preguntas, Lista *lista_aleatoria, const char *nombre_fichero){
    int *dynArray;
    int repeticiones;
    int cantidad_preguntas;
    char empezarEncuesta[MAX];   //variable para devolver un 'S' o 'N' para comenzar la encuesta
    int sizeOfList = listSize(*lista_preguntas);
    if(sizeOfList == 0){      
        printf("\n*********************************************************\n");
        printf("\tAtención: No hay preguntas añadidas!\n"
                "\tPor favor, vayanse al menú principal y eligan la tecla 2\n"
                "\t- Agregar preguntas al fichero de preguntas. Gracias\n");
        printf("\n*********************************************************\n");
    }
    
    dynArray = crearArrayDinamico(lista_preguntas);
    crearListaAleatoria(lista_preguntas, lista_aleatoria, dynArray);

    
    printf("\n\tCuantos veces se debe repitir\n"
            "\tla la encuesta?: ");
    repeticiones = getIntegerFromUser();

    cantidad_preguntas = *dynArray - 1;
    printf("\n*********************************************************\n");
    printf("\tLa encuesta contiene %d preguntas\n"
            "\ty se repitira %d veces!\n", cantidad_preguntas, repeticiones);
    printf("*********************************************************\n");


    printf("\n\t¿Estas seguro que quiere comenzar la encuesta?\n"
            "\t\t[Si='S'/No='N']: ");
    bool loop = True;
    while(loop == True){
        fgets(empezarEncuesta, MAX, stdin);
        if((empezarEncuesta[0] == 'S' || empezarEncuesta[0] == 's')){  //terminamos el bucle
            loop = False;                
        }else if((empezarEncuesta[0] == 'N' || empezarEncuesta[0] == 'n')){  //terminamos el bucle
            borrarLista(lista_aleatoria);   //Antes de salir liberamos la memoria
            borrarLista(lista_preguntas);
            printf("\n*********************************************************\n");
            printf("\tFin del programa - Hasta la próxima");
            printf("\n*********************************************************\n\n");
            exit(1);    
        }else{
            printf("\n\tInputError! Por favor, introduzca S o N: ");
        }
    }
     
    printf("\n*********************************************************\n");
    printf("\n*******************    Encuesta      ********************\n");
    printf("\n*********************************************************\n");
    
    encuesta(lista_aleatoria, repeticiones);  // Encuesta, bucle por las preguntas

    // func() statistics
    


    printAll(*lista_aleatoria);   // borrar

}



void printAll(Lista lista){
    while(lista != NULL){
            printf("%d. %s, %d, %d, %d, %d, %d, %d\n", lista->numPregunta, lista->texto,
            lista->tamano, lista->respA, lista->respB, lista->respC, lista->respD, lista->iteraciones);
            lista = lista->next;
    }
}






    //Estadistica ->file : resultado_encuesta. Vielleicht noch ne nummer Iteration davor
    // Iter: Resp. A = 66%, Resp. B = 33%, Resp. C = 0%, Resp. D = 0%

    // imprimir resultado de la encuesta

    // vaciar lista aleatoria




/*******************************************************************************/
/**********************           main - function          *********************/
/*******************************************************************************/
int main(){
    /* Creamos instancias de Lista */
    Lista lista1 = NULL;           // lista1 contiene todas las preguntas
    Lista lista2 = NULL;           // lista2 contiene una seleción aleatoria de preguntas
    const char *fichero = "fichero3.txt";           //fichero que guarda todas las preguntas
    copyFileToList(&lista1, fichero);              //Actualiza la lista enlazada con datos en fichero si existen
    
    bool loop = True; //Valor para determinar el loop.
    while(loop==True){
        switch(mainmenu()){
            case 1:
                    iniciarEncuesta(&lista1, &lista2, fichero);
                    break;
            case 2:  
                    manejarPreguntas(&lista1, fichero);
                    break;
            case 3:
                    printf("Fichero con resultados de las STATS\n");
                    char abcd;
                    abcd = submenu2();
                    printf("%c\n", abcd);
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



char submenu2(){
    char abcd[MAX];
    int len;
    printf("\t(a) Mala\n");
    printf("\t(b) Normal\n");
    printf("\t(c) Buena\n");
    printf("\t(d) Excelente\n");
    do{
        printf("\n\tIntrocuzca: ");
        fflush(stdin);
        fgets(abcd, MAX, stdin);
        len = strlen(abcd);
        if((abcd[0]=='a'|| abcd[0]=='b' || abcd[0]=='c' || abcd[0]=='d') && len==2){
            break;
        } else {
            printf("\nPor favor, ¡elige entre [a/b/c/d]!\n");
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


/* Eliminamos la lista con todos sus entradas usando la función 'eliminar()'*/
void borrarLista(Lista *lista) {
    renumerarPreguntas(lista);  //Renumeramos las preguntas en la lista 'numPregunta'
    int listsize = listSize(*lista);
    for(int i=listsize; i>=0; --i){    //bucle elimina cada entrada en la lista linea por linea
        eliminar(lista, i);
    }
    lista = NULL;    //dejamos que la lista apunta a NULL
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
    pNodo first = *lista;
    int counter = 1;
    while(first){
        first->numPregunta = counter;
        first = first->next;
        counter++;
    }
}




void printPreguntas(Lista lista){
    printf("\n\n****************** Lista de Preguntas  ********************\n\n");
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
            insertar(lista, texto, tamano, nr_pregunta, 0, 0, 0, 0, 0);
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
                        insertar(lista, question, len, 0, 0, 0, 0, 0, 0);       //insertamos cada pregunta en la lista, por defecto valores con 0 y 1.
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



/*  Primero elige un usuario cuantas preguntas se lleva a la encuesta. Creamos un array dinámico que tiene de primer elemento
    su longitud que ha definido el usuario anteriormente y despues números aleatorias en un rango de la longitud de la lista.*/
int *crearArrayDinamico(Lista *lista_preguntas){
    int sizeOfList = listSize(*lista_preguntas);
    int arraylength;
    while(1){    // Loop para asegurar valor intruducido por el usuario
        printf("\tCuantos preguntas desea para la encuesta?\n"
                "\t(máximo %d preguntas): ", sizeOfList);
        arraylength = getIntegerFromUser();
        if(arraylength<=sizeOfList){   //comprobamos si el valor introducido no sea mas que las preguntas guradadas
            break;
        }else{
            printf("\n\tError, sólamente hay %d preguntas guardadas!\n\n", sizeOfList);
        }
    }

    arraylength+=1; //añadimos una entrada al array, para guarar la longitud del array, que sea la primera entrada
    
    int *random_array = malloc(sizeof(int)*arraylength); //se crea un array dinámico
    if(random_array == NULL){                            //comprobamos que no apunta a '0'
        printf("Error, No se puede asignar espacio en la memoria\n");
        exit(EXIT_FAILURE);
    }
    memset(random_array, 0, sizeof(int) * arraylength);  // inizalizar array con '0'
    *random_array = arraylength; //en la primera entrada del array guardamos su longitud total.

    srand(clock());     //usamos la función srand en combinación con la hora para crear un número aleatorio
    /* En este bucle loop asignamos un valor aleatorio en nuestro array
     dinámico con un máximo del tamaño como preguntas en la lista*/
    for(int i=1;i<arraylength;i++){    //comenzamos por 1, la primera entrada es la longitud
        int temp = rand()%sizeOfList+1;   //rand() devuelve un número aleatorio desde 1 hasta tamaño lista
        bool exists = False;
        for(int j=1;j<i;++j){  //vamos a comprobar si el valor ya existe en el array
            if(*(random_array+j) == temp){
                exists = True;
                break;
            }
        }
        if(!exists){
            *(random_array+i) = temp;
        }
        else{
            --i;  //si ya existe , descontamos del bucle uno y lo intentamos de nuevo
        }
    }
    return random_array; //devolvemos el array creado
}



/*  Se crea una nueva lista de preguntas. Las preguntas en esta lista han sido seleccionado
    con el número aleatorio que hemos pasado con el array dinámico a la función.*/
void crearListaAleatoria(Lista *lista_preguntas, Lista *lista_aleatoria, int *random_array){
    int arraylength = *random_array;
    //Ahora creamos una lista con preguntas aleatorias usando nuestro array
    for(int k = 1; k<arraylength; k++){  //iteramos por el array
        pNodo first = *lista_preguntas; 
        while(first){                     //iteramos sobre la lista
            if(first->numPregunta == *(random_array+k)){  //comprobamos si el número de la pregunta es igual al número aleatorio del array
                int len = strlen(first->texto);
                insertar(lista_aleatoria, first->texto, len, first->numPregunta,0,0,0,0,0);
            }
            first = first->next;
        }
    }
}



