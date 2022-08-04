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
#define length_filename 12


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






char menu();

char submenu();

/* Añade una pregunta nueva al archivo de texto de preguntas */
void writePregunta(const char nombre_fichero[length_filename], char pregunta[length_pregunta]);

/* Lee el fichero 'fichero.txt' completo y cada linea (pregunta) del fichero se añade a la lista como un elemento. */
void copyToList(const char nombre_fichero[length_filename]);


/*----------  ???? --------------- */
void writeStatistics(){

}


/* Añade un elemento en la pila */
void insertar(char pregunta[length_pregunta], int letras, int nr, int rA, int rB, int rC, int rD, int iter);

/* Retira un elemento de la pila */
void eliminar(int nr_pregunta);


/* agregar , print e ileminar preguntas de la lista. Mantiene un submemú para realizarlo */
void agregarPreguntas(const char fichero[length_filename]);


/* */
int numeroParaEliminar(){
    char buffer[1024];
    char *p;
    long numero_long;
    int  numero_int;
    printf("Nr de la pregunta que desea eliminiar: ");
    fgets(buffer, sizeof buffer, stdin);              //guarda una linea de flujo de dato
        if(strchr(buffer, '\n') == NULL){               //Comprueba que toda la linea està leida y el 'buffer' no se ha quedado pequeño
            printf("ERROR! El numero introducido es demasiado largo!\n");
            exit(EXIT_FAILURE);
        }
        numero_long = strtol(buffer, &p, 10);    // cambiar una cadena a un número entero del tipo 'long'
        if(p == buffer){
            printf("ERROR, error en introducir el número!\n");
            exit(EXIT_FAILURE);
        }
        numero_int = (int)numero_long;       //cambiar número entero del tipo long a número entero
        /*Comprobamos cuantos elementos hay en la lista*/
        int counter;
        lista = pNodo;                //poner lista al principio
        while(lista!=NULL){           //recorrer lista hasta el final
            counter++;
            lista= lista->next;
        }
        if(numero_int>=0 && numero_int<=counter){
            return numero_int;
        }else{
            printf("Número no existe en la lista!");
            return 0;
        } 
}



void copyListToFile(const char nombre_fichero[length_filename]){
    FILE *fichero = fopen(nombre_fichero, "r");
    if(fichero == NULL){
        printf( "\tProblemas al leer el fichero!\n");
        exit(1);
    }
    
    // copiar elemento de la lista en cada linea


    fclose(fichero);
}




/*Función imprime la lista (Preguntas que han sido anteriormente añadido al archivo 'fichero.txt' */
void printPreguntas();


/* Función devuelve '0' si el fichero es vacio, sino devuelve '1'         ???????   Funcion necesario ????? */
int checkFileIsEmpty(const char nombre_fichero[length_filename]){
    FILE *fichero = fopen(nombre_fichero, "a+");
    if(fichero == NULL){
        printf( "\tProblemas al leer el fichero!\n");
    }
    /*Cambiamos la posicón al final del fichero. Si luego, la posicón da 0, no hay datos en el fichero */
    fseek(fichero, 0, SEEK_END);   //cambia la posición en el fichero al final
    if(ftell(fichero) == 0){       //función devuelve la posición actual
        return 0;                  
    } else{
        return 1;
    }
    fclose(fichero);

}


void printList(){
    lista = pNodo;
    while(lista!=NULL){
        printf("%d. %s  Length: %d, Stats: A=%d, B=%d, C=%d, D=%d, Iter=%d\n", lista->numPregunta, lista->texto, lista->tamano, lista->respA, lista->respB, lista->respC, lista->respD, lista->iteraciones);
        lista = lista->next;
    }
}


int main(){
    const char fichero[length_filename]="fichero.txt";

    bool loop = True; //Valor para determinar el loop.
    while(loop==True){
        switch(menu()){
            case '1':
                    printf("*** Iniciar Encuesta ***\n"); 
                    break;
            case '2':
                    agregarPreguntas(fichero);
                    break;
            case '3':
                    printf("Fichero con resultados de las STATS\n");
                    break;
            case '4':
                    printf("\n*********************************************************\n"
                            "*******************  FIN DEL PROGRAMA  ******************\n"
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

    /*
    insertar("Que tal la atención?", 22, 1, 30, 25, 24, 21, 1);
    */
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


char menu(){
    char c[MAX];  //proponer mas elementos para evitar errores de introducción
    printf("\n*********************************************************\n");
    printf("*************  Encuesta - menú principal  ***************\n\n");
    printf("(1) Iniciar encusta\n");
    printf("(2) Agregar preguntas al fichero de preguntas\n");
    printf("(3) Visualizar el fichero con los últimos resultados\n");
    printf("(4) Salir\n");
    printf("\n\tElige un número [1-4]: ");
    do{
        fflush(stdin);
        fgets(c, MAX, stdin);    //uso de fgets para evitar overflow
        if((c[0]<'0'||c[0]>'4')){
            printf("\n\tERROR al introduzir número!\n"
                    "\tPor favor, eliga un número de 1 a 4: ");
        }
    }while(c[0]<'0'||c[0]>'4');
    printf("\n\n");
    return c[0];
}


char submenu(){
    char c[MAX];  //proponer mas elementos para evitar errores de introducción
    printf("\t*******  Submenú  *******\n\n");
    printf("\t(1) Agregar preguntas\n");
    printf("\t(2) Eliminar preguntas\n");
    printf("\t(3) Imprimir Preguntas\n");
    printf("\t(4) Volver al menú principal\n");
    printf("\n\tElige un número [1-4]: ");
    do{
        fflush(stdin);
        fgets(c, MAX, stdin);    //uso de fgets para evitar overflow
        if((c[0]<'0'||c[0]>'4')){
            printf("\n\tERROR al introduzir número!\n"
                    "\tPor favor, eliga un número de 1 a 4: ");
        }
    }while(c[0]<'0'||c[0]>'4');
    printf("\n\n");
    return c[0];
}



/* agregar , print e ileminar preguntas de la lista. Mantiene un submemú para realizarlo */
void agregarPreguntas(const char fichero[length_filename]){
    bool loop = True; //Valor para determinar el loop.
    while(loop==True){
        switch(submenu()){
            case '1':
                    printf("\n*********************************************\n"
                            "***********   Agregar preguntas  ************\n\n");
                    char question[length_pregunta] = "";                  //Inizialisación de la variable 'question'
                    while(question[0] != 'Q'){                            //Tecla 'Q' termina el bucle
                        printf("Introduzca una pregunta [\'Q\'-Quit]:\n");
                        fgets(question, length_pregunta, stdin);
                        char *p = strchr(question, '\n');              // encuentra '\n' al final de la pregunta y lo elimina
                        if (p != NULL){
                             *p = '\0';                      
                        }
                        if(question[0] !='Q'){               // evita para no añadir la letra 'Q' a la lista como pregunta
                            writePregunta(fichero, question);
                        }
                    }
                    copyToList(fichero);                             //Todas las preguntas del fichero se añaden a la lista enlazada
                    break;
            case '2':
                    printf("\n*********************************************\n"
                            "***********   Eliminar preguntas  ***********\n\n");

                    printf("\tInformación: Antes de eliminar una pregunta\n"
                            "\ttiene que añadir una pregunta anteriormente!\n\n");
                    int numero_int;
                    numero_int = numeroParaEliminar();   //El usuario elige un número de la lista para eliminar
                    eliminar(numero_int);
                    if(remove(fichero) != 0){    // Eliminar fichero
                            printf("ERROR en guardar el cambio!\n");
                    }



                    
                    break;
            case '3':
                    printPreguntas(); 
                    break;
            case '4':
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
}



/*Función imprime la lista (Preguntas que han sido anteriormente añadido al archivo 'fichero.txt' */
void printPreguntas(){
    lista = pNodo;
    if(pNodo == NULL){
        printf("****************** Lista de Preguntas  ********************\n\n");
        printf("\tNo hay preguntas añadidas a la lista aún!\n");
        printf("\t¡Ojo! Puede haber datos guardados desde\n"
               "\tla última sessión. Para comprobarlo, agrega\n"
                "\tuna pregunta nueva y vuelva a imprimir.\n");
        printf("\n***********************************************************\n\n");
    } else {
        printf("****************** Lista de Preguntas  ********************\n\n");
        while(lista!=NULL){
            printf("\t%d. %s\n", lista->numPregunta, lista->texto);
            lista = lista->next;
        }
        printf("\n*********************************************************\n");
    }
}






/* Añade una pregunta nueva al archivo de texto de preguntas */
void writePregunta(const char nombre_fichero[length_filename], char pregunta[length_pregunta]){
    FILE *fichero = fopen(nombre_fichero, "a");
    if(!fichero){
        printf( "\tProblemas al abrir el fichero!\n"
                "\tEl problema puede tener varios motivos.\n"
                "\tComprueban sus derechos de escribir en la carpeta!\n" );
    }
    fputs(pregunta, fichero);
    fputs("\n", fichero);
    if(!fclose(fichero)){
        printf( "\n\tPregunta añadido correctamente!\n" );
    } else {
        printf( "\n\tError en añadir pregunta al fichero\n");
    }
}


/* Lee el archivo de texto que incluye las preguntas y lo inserta en la lista enlazada*/
void copyToList(const char nombre_fichero[length_filename]){
    char pregunta[length_pregunta];
    int len;
    int nr = 1;
    FILE *fichero = fopen(nombre_fichero, "r");
    if(fichero == NULL){
        printf( "\tProblemas al leer el fichero!\n");
        exit(1);
    }
    while(fgets(pregunta, sizeof(pregunta), fichero) != NULL){
        char *p = strchr(pregunta, '\n');  // encuenta '\n' al final de la pregunta 
        if (p != NULL) *p = '\0';          // elimina '\n'
        len = strlen(pregunta);
        insertar(pregunta, len, nr, 0, 0, 0, 0, 1);
        nr++;
    } 
    fclose(fichero);
}





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
}


void eliminar(int nr_pregunta){
    bool numero_existe = False;
    lista = pNodo;  // la lista ponemos al prinicipio para luego recorrerla
    //Primero buscamos el elemento anterior para cambiar la referencia de *next
    Pregunta * anterior = NULL;
    while(lista!=NULL){
        if(lista->numPregunta == nr_pregunta){
            numero_existe = True;
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
    /*renumerar todas las preguntas de 1 hasta el final de la lista*/
    int counter = 1;
    lista = pNodo;
    while(lista!=NULL){
        lista->numPregunta = counter;
        counter++;
        lista = lista->next;
    }

    if(numero_existe == False){
        printf("\tError borrar pregunta!\n" 
                "\tLa pregunta con el número '%d' no existe!\n", nr_pregunta);
    }
}