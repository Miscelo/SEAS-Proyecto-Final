**** Generador de encuestas ****
Elaborar un software que sea capaz de seleccionar de un fichero de texto un número configurable (en tiempo de ejecución) de preguntas para elaborar una encuesta.


Ficheros: 
1. encuesta.c    //Fichero con el código fuente
2. encuesta      //Fichero campilado con gcc en etorno Debian Linux
3. encuesta.exe  //Fichero compilado en Windows con DEV++
4. Manual-de-usuario.pdf
5. fichero.txt   //Fichero con preguntas para realizar una primera encuesta.


Las respuestas a cada pregunta podrán tener sólo uno de entre cuatro valores de antemano predefinidos.
El sistema deberá realizar un número indeterminado de repeticiones de la misma encuesta que pediremos al usuario.
También debe permitirse que las preguntas de la encuesta tienen cierta aleatoriedad a como están introducidas en el fichero origen, además de que el usuario será capaz de agregar preguntas al fichero de preguntas.

Finalmente tendrá que ofrecer estadísticas porcentuales del número de respuestas a cada pregunta del siguiente estilo:
-> PREGUNTA X: Respuesta A 60% Respuesta B 30% Respuesta C 3% Respuesta D 2%

Además será necesario que se genere un fichero denominado “De Solución” donde aparecerán las preguntas realizadas junto con las respuestas que más porcentaje obtuvieron para cada una de ellas.

Para la ejecución del programa, se utilizará una estructura (a la que llamamos “pregunta”) en la que tenemos los siguientes campos:
texto: dato de tipo cadena de caracteres en el que se almacena la pregunta en si.
tamano: dato de tipo entero en el que se almacena el tamaño de la pregunta (numero de caracteres).
numPregunta: dato de tipo entero en el que se almacena el numero de la pregunta.
respA, respB, respC, respD: 4 campos con datos de tipo entero en el que se almacena el numero de veces que el usuario ha elegido la respuesta A, B, C o D respectivamente.
iteraciones: dato de tipo entero en el que se almacena el numero de veces que se ha ejecutado la encuesta (sirve al final para sacar las estadísticas).

La ejecución del programa deberá mostrar un menú como el siguiente:
    1. Iniciar encuesta
    2. Agregar preguntas al fichero de preguntas
    3. Visualizar el fichero con los últimos resultados
    4. Salir

Al seleccionar la opción de “Iniciar encuesta” el procedimiento será:
    1. Cargar la encuesta en una lista enlazada, cada pregunta será un nodo de la lista.
    2. Preguntar al usuario por el número de preguntas que formaran la encuesta definitiva que haremos al usuario.
    3. Cargar una nueva lista seleccionando de la lista anterior de modo aleatorio el número de preguntas (nodos) indicado en el apartado anterior.
    4. Preguntar al usuario el número de veces que se debe de repetir la encuesta.
    5. Ejecutar la encuesta tantas veces como se haya indicado almacenando los resultados en el lugar adecuado para mostrar posteriormente la estadística.
    6. Una vez finalizada la encuesta mostrar los resultados y cargar el fichero con los mismos.
Al seleccionar la opción de “Agregar preguntas al fichero de preguntas” simplemente se agregaran preguntas al fichero original. A la entrega del trabajo deben existir preguntas almacenadas en la encuesta.´
Por último, al seleccionar la opción 3, simplemente se mostrará el fichero resultado_encuesta donde aparecerán las preguntas y las estadísticas de la última encuesta realizada. Ejemplo:

1) Que le ha parecido la materia estudiada?
	a. Mala
	b. Normal
	c. Buena
	d. Excellente
*******************************************************
Resp. A = 66%, Resp. B = 33%, Resp. C = 0%, Resp. D = 0%


Ficheros: 
1. encuesta.c    //Fichero con el código fuente
2. encuesta      //Fichero campilado con gcc en etorno Debian Linux
3. encuesta.exe  //Fichero compilado en Windows con DEV++
4. Manual de usuario




**************** Planificación de la solución ******************************************************

En la planificación del proyecto se tomó la decisión de fraccionar las tareas
en tres bloques:

    I.  Crear funciones básicas para el manejo de las listas enlazadas.
    II. Añadir funciones para crear ficheros y funciones para actualizar listas desde ficheros y viceversa.
    III. Realizar la encuesta y guardar sus resultados en ficheros.

1. Primera parte
En esta parte se agregan las funciones necesarias para el manejo de listas simplemente enlazadas.

- insertar(), 
- eliminar(),
- borrarLista(),
- listSize(), 
- renumerarPreguntas(),
- printPreguntas(). 

La función listSize devuelve cuántas preguntas se han guardado en una lista. No se crea una función ‘listavacia’, sino que se comprueba si la función listSize es '0'.

La función 'renumerarPreguntas()' es una función que renumera las preguntas en la lista. La variable 'numPregunta' se renumera de 1 hasta el último elemento de la lista.
Esta función es necesaria por dos motivos. Si hay datos (preguntas) en la lista guardados desde la última sesión, se evita que los números se repitan a la hora de agregar nuevas preguntas. Por otra parte, también es necesaria cuando se elimina un elemento de la lista. 

La función printPreguntas hace lo que indica el nombre: imprime todas las preguntas al escritorio con su número de pregunta.

2. Agregar y eliminar preguntas
En la segunda parte se agregan nuevas preguntas a la encuesta o se elimina una pregunta. 

Dos problemas que quería mejorar:
    a) Que no se perdieran las preguntas que se encuentran guardadas en el fichero.txt que se han creado en la última sesión cuando termina el programa. 
    b) Que el usuario tenga la posibilidad de borrar una pregunta manualmente. Puede haber preguntas desde la última sesión que ya no son deseados o simplemente una falta de ortografía en una de ellas.

Para mejorarlo es necesario que se actualicen la lista y el fichero continuamente en tiempo de ejecución. Esto se realiza con dos funciones escenciales:
    •  copyFileToList(List *list, File *file)    //Copia los datos del fichero a la lista.
    • copyListToFile(File *file, List *list)     //Copia los datos de la lista al fichero.

Es algo conveniente cuando el programa termina inesperadamente con un error 'exit(1)'. De esta forma, nuevas preguntas añadidas o eliminadas serán consideradas despues de arrancar el programa de nuevo. 

Si hay datos (preguntas) guardados en el fichero ‘fichero.txt’, entonces uno de los primeros pasos en la función main es que se guardan dichas preguntas del fichero en la lista.

La función que abre un submenú para el usuario es 'manejarPreguntas'. Dentro de esta función se agregan y eliminan las preguntas y también se puede imprimir las preguntas para verlas. 

3. Inicio de la encuesta y realización de las estadísticas
Primero creamos una nueva lista que contiene las preguntas que finalmente usamos para la encuesta. El usuario debe tener la posibilidad de elegir las preguntas que desea usar o que sean elegidas aleatoriamente. Barajando las preguntas en el fichero.txt solamente, provoca mucha confusión al usuario cuando desea añadir preguntas a la encuesta manualmente, dado que encuentra siempre con otro orden. La decisión ha sido no cambiar el orden de las preguntas en el fichero ‘fichero.txt’. 
La solución para que haya una selección de preguntas aleatorias, es el uso de un array dinámico. En este array se guardarán los números que elige el usuario manualmente o números que elige el programa aleatoriamente. Cuando arranquemos la encuesta, se  usará una nueva lista para guardar las preguntas elegidas y, en adelante, los resultados de la encuesta. El último paso es realizar las estadísticas usando esta lista nueva.




Evitar problemas:
En vez de usar la función scanf(), se usa en todo el programa fgets() para evitar un ‘bufferoverflow’.  La función fgets asegura que el programa no termina, independientemente de lo que introduzca el usuario.  

