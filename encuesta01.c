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
Pregunta *pNodo = NULL;             //instancia de la estructura, puntero al primer elemento de la lista
Pregunta *lista = NULL;              //lista



/* Imprime el menu principal. Devuelve un 'char' que sea usado para un caso 'switch'*/ 
char mainmenu();

/* Imprime el menu secundario (Añadir, eliminar o ver pretuntas), devuele un 'char' para un caso switch */
char submenu();

/* Función que pide al usuario que introduzca un número que se devuelve */
int getIntegerFromUser();

/* Función inserta valores dados a la lista enlazada */
void insertar(char pregunta[length_pregunta], int letras, int nr, int rA, int rB, int rC, int rD, int iter);

/* Retira un elemento de la lista elegido por la variable 'Pregunta numPregunta'*/
/* En caso de falta de ortografía, el usuario puede eliminar la pregunta erronea. */
void eliminar(int nr_pregunta);

/*renumerar todas las preguntas de 1 hasta el final de la lista - Struct variable numPregunta*/
void renumerateQuestions();

//copia todas las lineas del fichero a la lista enlazada si no es vacio.
void copyFileToList(const char *nombre_fichero);

/* copia todos los elementos de la variable 'Pregunta texto' al fichero */
void copyListToFile(const char *nombre_fichero);

/*Función imprime la lista enlazada (Preguntas que han sido anteriormente añadido al archivo 'fichero.txt' */
void printQuestions();

/*Función devuelve cantidad de elementos que hay en la lista enlazada*/
int listSize();

/* agregar y eleminar preguntas a la lista e emprime la lista.  Mantiene un submemú 'submenu()' para realizarlo */
void treatQuestions(const char *nombre_fichero);





void printList(){
    lista = pNodo;
    while(lista!=NULL){
        printf("%d. %s  Length: %d, Stats: A=%d, B=%d, C=%d, D=%d, Iter=%d\n", lista->numPregunta, lista->texto, lista->tamano, lista->respA, lista->respB, lista->respC, lista->respD, lista->iteraciones);
        lista = lista->next;
    }
}



/*******************************************************************************/
/**********************           main - function          *********************/
/*******************************************************************************/
int main(){
    const char *fichero = "fichero.txt";
    copyFileToList(fichero);              //Actualiza la lista enlazada con datos en fichero si existen
    
    bool loop = True; //Valor para determinar el loop.
    while(loop==True){
        switch(mainmenu()){
            case 1:
                    printf("*** Iniciar Encuesta ***\n"); 
                    break;
            case 2:
                    treatQuestions(fichero);
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
                            "Elige un numero del menú de 1 a 4 por favor.\n"
                            "*********************************************\n");
                    break;   
        }
    }

    return EXIT_SUCCESS;
}





char mainmenu(){
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



char submenu(){
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



/*Inserta un elemento nuevo al final de la lista enlazada.*/
void insertar(char pregunta[length_pregunta], int letras, int nr, int rA, int rB, int rC, int rD, int iter){
    Pregunta *new = malloc(sizeof(Pregunta));
    if(new == NULL){
        printf("ERROR, no se podía asignar espacio en la memoría RAM!\n");
        exit(EXIT_FAILURE);
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
    if(pNodo == NULL){              //Añade primer elemento a la lista si no existe aún.
        pNodo = new;
        lista = new;
    } else  {                      //Añade un elemento a la lista si ya contiene mínimo un Elemento.
        lista = pNodo;
        while(lista!=NULL){
            if(lista->next == NULL){
                lista->next = new;
                break;
            } else{
                lista = lista->next;
            }
        }

    }
    renumerateQuestions();   //renumera la variable 'numPregunta' de 1 hasta final.
}




/* Retira un elemento de la lista elegido por la variable 'Pregunta numPregunta'*/
void eliminar(int nr_pregunta){
    lista = pNodo;  // la lista ponemos al prinicipio para luego recorrerla
    //Primero buscamos el elemento anterior para cambiar la referencia de *next
    Pregunta * anterior = NULL;
    while(lista!=NULL){
        if(lista->numPregunta == nr_pregunta){
            if(anterior==NULL){    //El caso de que el usuario quiere eleminar el primer elemento de la lista.
                pNodo = NULL;
                free(pNodo);
                pNodo = lista->next;  //Si se bora el primer elemento, el segundo elemento se convierte en el primero
            }
            else{    //Caso que no se quiere anular el primero elemento. Estamos un elemento atras de lo que queremos eliminar
                anterior->next = NULL;
                free(anterior->next);  
                anterior->next = lista->next;   //Vamos un pasa para adelante
            }
        }
        anterior = lista;
        lista = lista->next;
    }
    renumerateQuestions();   //renumera la variable 'numPregunta' de 1 hasta final.
}




/*renumera las preguntas de 1 hasta el final de la lista - Struct variable numPregunta*/
void renumerateQuestions(){
    int counter = 1;
    lista = pNodo;       // lista al principio
    while(lista!=NULL){    //recorre lista hasta el final
        lista->numPregunta = counter;         //asignamos la entrada de la lista numPregunta
        counter++;
        lista = lista->next;
    }
}



//copia todas las lineas del fichero a la lista enlazada si no es vacio.
void copyFileToList(const char *nombre_fichero){
    char linia[length_pregunta];
    int linelenght;           //variable para el tamaño (longitud) de la pregunta
    int nr_pregunta = 1;     //Inicializamos los números con 1
    FILE *fichero = fopen(nombre_fichero, "a+");    // a+ en vez de 'r' por si el archivo no existe aún
    if(fichero == NULL){
        printf( "\tProblemas al leer el fichero!\n");
        exit(1);
    }
    //Comprobamos si el fichero contiene datos
    fseek(fichero, 0, SEEK_END);            //cambia la posición en el fichero al final
    if(ftell(fichero) != 0){                //función devuelve la posición actual
        fseek(fichero, 0, SEEK_SET);        //cambia de vuelta al principio del fichero
        while(fgets(linia, sizeof(linia), fichero) != NULL){     //lee linea por linea del fichero con fgets
            char *p = strchr(linia, '\n');  // encuenta '\n' al final de la pregunta 
            if (p != NULL) *p = '\0';       // elimina '\n'
            linelenght = strlen(linia);     //Tamaño de la pregunta
            insertar(linia, linelenght, nr_pregunta, 0, 0, 0, 0, 1);
            nr_pregunta++;                  //incrementa el número de las preguntas
        }
    } 
    fclose(fichero);
    renumerateQuestions();   //renumera la variable 'numPregunta' de 1 hasta final por si estan mal numerados anteriormente
}



/* copia todos los elementos de la variable 'Pregunta texto' al fichero */
void copyListToFile(const char *nombre_fichero){
        char pregunta[length_pregunta];    
        //Abrimos el fichero con 'w' para cambiarlo a la longitud '0'.
        FILE *fichero = fopen(nombre_fichero, "w");
        if(!fichero){
            printf( "\tProblemas al abrir el fichero!\n"
                    "\tEl problema puede tener varios motivos.\n"
                    "\tComprueban sus derechos de escribir en la carpeta!\n" );
        }
        renumerateQuestions();   //renumera la variable 'numPregunta' de 1 hasta final por si estan mal numerados anteriormente
        lista = pNodo;           //lista al elemento principal
        while(lista!=NULL){       //recorrer la lista
            strcpy(pregunta, lista->texto);  //copiamos el contenido de la variable 'texto' a la pregunta
            fputs(pregunta, fichero);  //Añade la pregunta al fichero
            fputs("\n", fichero);      //Añade 'salto linea' a la pregunta    
            lista = lista->next;
        }
        fclose(fichero);
}    





/*Función imprime la lista (Preguntas que han sido anteriormente añadido al archivo 'fichero.txt' */
void printQuestions(){
    printf("****************** Lista de Preguntas  ********************\n\n");
    lista = pNodo;                 //mueve lista al primer elemento
    if(pNodo == NULL){                
        printf("\tNo hay preguntas añadidas a la lista aún!\n"
                "\tElige número 1 en el menú para añadir preguntas.\n");
        printf("\n***********************************************************\n");
    } else {
        while(lista!=NULL){
            printf("\t%d. %s\n", lista->numPregunta, lista->texto);
            lista = lista->next;
        }
        printf("\n***********************************************************\n\n");
    }
}



/*Función devuelve cantidad de elementos que hay en la lista enlazada*/
int listSize(){
    int counter;
    lista = pNodo;                //poner lista al principio
    while(lista!=NULL){           //recorrer lista hasta el final
        counter++;
        lista= lista->next;
    }
    return counter;
}




/* agregar , print e ileminar preguntas de la lista. Mantiene un submemú para realizarlo */
void treatQuestions(const char *nombre_fichero){
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
                        insertar(question, len, 0, 0, 0, 0, 0, 1);       //insertamos cada pregunta en la lista, por defecto valores con 0 y 1.
                    }
                    copyListToFile(nombre_fichero);    //pasamos la lista que ha sidoa actualizada al fichero.
                    break;
            case 2:
                    /* Se pide al usuario elegir un número de una pregunta para eliminarlo para luego eliminarlo
                    en la lista enlazada. El próximo paso, se actualiza el fichero con la lista actúal */
                    printf("\n*********************************************\n"
                            "***********   Eliminar preguntas  ***********\n\n");
                    printQuestions();
                    printf("Introduzca el número de la pregunta que desa iliminar: ");
                    int numeroPregunta;
                    int listsize;
                    numeroPregunta = getIntegerFromUser();
                    listsize = listSize();
                    if(numeroPregunta>=0 && numeroPregunta<=listsize){  //comprueba si el numero introducido está dentro del limite
                        eliminar(numeroPregunta);
                        copyListToFile(nombre_fichero);
                    }else{
                        printf("\n\tNúmero no existe en la lista!\n");
                    } 
                    break;
            case 3:  
                    /*Imprime los números de las preguntas con la pregunta correspondiente. */
                    printQuestions(); 
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
