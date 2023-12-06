#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
bool LOGS_ACTIVADO = false;
int min(int a, int b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}
#define MAX_CARACTERES_POR_LINEA 40
#define INFINITO 2147483647
#define VACIO ' '
/**
 * Imprime un arreglo de números en el formato [num1, num2, num3, ...].
 *
 * @param arr El arreglo de números a imprimir.
 * @param size El tamaño del arreglo.
 */
#define imprimirArregloNumeros(arr, size) \
    printf("[");                          \
    for (int i = 0; i < size; i++)        \
    {                                     \
        printf("%d", arr[i]);             \
        if (i != size - 1)                \
        {                                 \
            printf(", ");                 \
        }                                 \
    }                                     \
    printf("]\n");

 /**
  * Imprime un arreglo de caracteres en el formato [elemento1, elemento2, ...].
  *
  * @param arr El arreglo de caracteres a imprimir.
  * @param size El tamaño del arreglo.
  */
#define imprimirArregloCaracteres(arr, size) \
    printf("[");                             \
    for (int i = 0; i < size; i++)           \
    {                                        \
        printf("'%c'", arr[i]);              \
        if (i != size - 1)                   \
        {                                    \
            printf(",");                     \
        }                                    \
    }                                        \
    printf("]\n");
  /**
   * @brief Imprime el valor de una variable numérica junto con su nombre.
   *
   * @param variable La variable numérica a imprimir.
   */
#define imprimirVariableNumerica(variable) printf("%s = %d\n", #variable, variable);
   /**
    * @brief Imprime el valor de una variable de tipo caracter.
    *
    * @param variable La variable de tipo caracter a imprimir.
    */
#define imprimirVariableCaracter(variable) printf("%s = '%c'\n", #variable, variable)

    /**
     * @brief Macro para logear un error y terminar el programa con error.
     *
     * @param mensaje El mensaje de error a logear.
     */
#define logError(mensaje) \
        fprintf(stderr, "MAIN::ERROR:: %s\n", mensaje); \
        exit(EXIT_FAILURE); \

char LECTURA_CADENA[MAX_CARACTERES_POR_LINEA];
char* TOKEN = NULL;
const char DELIMITADOR = ' ';
/**
 * @brief Macro para leer una cadena de caracteres desde la entrada estándar.
 *
 * @return Puntero a la cadena leída.
 */
#define leerCadena() fgets(LECTURA_CADENA, MAX_CARACTERES_POR_LINEA, stdin)

 /**
  * @brief Macro para leer los tokens de una cadena.
  *
  * @return Puntero al primer token encontrado.
  */
#define tokenizar() strtok(LECTURA_CADENA, &DELIMITADOR)

  /**
   * @brief Macro para obtener el siguiente token de una cadena.
   *
   * @return Puntero al siguiente token encontrado.
   */
#define siguienteToken() strtok(NULL, &DELIMITADOR)

   /**
    * Macro que se utiliza para saltar al valor ignorando la etiqueta en input.txt
    * Esta macro realiza dos acciones: tokenizar y obtener el siguiente token.
    */
#define saltarEtiqueta() \
    TOKEN = tokenizar(); \
    TOKEN = siguienteToken()
#define imprimirOperacionEscrituraCinta(ptr)         \
    imprimirVariableNumerica(ptr->numeroCinta);      \
    imprimirVariableCaracter(ptr->simboloEscritura); \
    imprimirVariableCaracter(ptr->operacion)
    /**
     * @brief Imprime los detalles de una arista.
     *
     * Esta macro imprime el símbolo de lectura, el estado de destino y las operaciones de escritura de una arista.
     *
     * @param arista Puntero a la estructura de datos de la arista.
     */
#define imprimirArista(arista)                                                                           \
    printf("Arista:\n");                                                                                 \
    imprimirVariableCaracter(arista->simboloLectura);                                                    \
    imprimirVariableNumerica(arista->estadoDestino);                                                     \
    imprimirVariableNumerica(arista->numeroOperacionesEscrituraCinta);                                   \
    for (int i = 0; i < arista->numeroOperacionesEscrituraCinta; i++)                                    \
    {                                                                                                    \
        struct OperacionEscrituraCinta *operacionEscrituraCinta = arista->operacionesEscrituraCinta + i; \
        imprimirOperacionEscrituraCinta(operacionEscrituraCinta);                                        \
    }
     /**
      * Function to print the position of the tape head.
      *
      * @param cabezal The position of the tape head.
      */
#define imprimirCabezal(cabezal)                              \
    if (cabezal < 0)                                          \
    {                                                         \
        printf("^\n");                                        \
    }                                                         \
    else if (cabezal == 0)                                    \
    {                                                         \
        printf("  ^\n");                                      \
    }                                                         \
    else                                                      \
    {                                                         \
        printf("  ");                                         \
        for (int i = 0; i < cabezal - 1; i++)                 \
        {                                                     \
            printf("    ");                                   \
        }                                                     \
        printf("    ^\n");                                    \
    }
      /**
       * @brief Imprime la estructura de la cinta.
       *
       * Esta macro imprime el arreglo de símbolos de la cinta y muestra un símbolo '^' en el índice donde se encuentra el valor del cabezal.
       *
       * @param cinta Puntero a la estructura de datos de la cinta.
       * @param indiceCabezal Índice donde se encuentra el valor del cabezal.
       */
#define imprimirCinta(cinta, longitudCinta)                         \
    printf("%s\n", #cinta);                                         \
    imprimirVariableNumerica(cinta->cabezal);                       \
    imprimirArregloCaracteres(cinta->simbolos, longitudCinta);      \
    imprimirCabezal(cinta->cabezal)



#define imprimirAutomata(automata) \
    imprimirVariableNumerica(automata->numeroEstadosFinales);                                 \
    imprimirVariableNumerica(automata->estadoInicial);                                        \
    printf("Estados finales:\n");                                                             \
    imprimirArregloNumeros(automata->estadosFinales, automata->numeroEstadosFinales);         \
    imprimirVariableNumerica(automata->numElementosSigma);                                    \
    printf("Sigma:\n");                                                                       \
    imprimirArregloCaracteres(automata->sigma, automata->numElementosSigma);                  \
    imprimirVariableNumerica(automata->numElementosGamma);                                    \
    printf("Gamma:\n");                                                                       \
    imprimirArregloCaracteres(automata->gamma, automata->numElementosGamma);                  \
    imprimirVariableNumerica(automata->numeroEstados);                                        \
    for (int i = 0; i < automata->numeroEstados; i++)                                         \
    {                                                                                         \
        struct Estado *estado = automata->estados + i;                                        \
        imprimirVariableNumerica(estado->estado);                                             \
        imprimirVariableNumerica(estado->numAristas);                                         \
        for (int j = 0; j < estado->numAristas; j++)                                          \
        {                                                                                     \
            struct Arista *arista = estado->aristas + j;                                      \
            imprimirArista(arista);                                                           \
        }                                                                                     \
    }\
    imprimirVariableNumerica(automata->estadoActual->estado);\
    imprimirVariableNumerica(automata->estadoActual->numAristas);\
    for (int i = 0; i < automata->estadoActual->numAristas; i++)\
    {\
        struct Arista *arista = automata->estadoActual->aristas + i;\
        imprimirArista(arista);\
    }\




       /**
        * @struct OperacionEscrituraCinta
        * @brief Estructura que representa una operación de escritura en una cinta de una máquina de Turing.
        *
        * Esta estructura contiene información sobre el número de la cinta, el símbolo a escribir y la operación a realizar ('L' o 'R').
        */
struct OperacionEscrituraCinta
{
    int numeroCinta;
    char simboloEscritura;
    char operacion; // 'L' o 'R'
};
/**
 * Estructura que representa una arista en una máquina de Turing.
 * Contiene el símbolo de lectura, el estado destino, el número de operaciones de escritura en la cinta
 * y un puntero a una lista de operaciones de escritura en la cinta.
 */
struct Arista
{
    char simboloLectura;                                       // Símbolo que se debe leer para seguir la arista
    int estadoDestino;                                         // Estado al que se llega al seguir la arista
    int numeroOperacionesEscrituraCinta;                       // Número de operaciones de escritura en la cinta
    struct OperacionEscrituraCinta* operacionesEscrituraCinta; // Puntero a una lista de operaciones de escritura en la cinta
};
/**
 * @struct Estado
 * @brief Estructura que representa un estado en una máquina de Turing.
 *
 * Esta estructura contiene información sobre el estado actual, el número de aristas
 * y un puntero a un arreglo de aristas.
 */
struct Estado
{
    int estado;
    int numAristas;
    struct Arista* aristas;
};

/**
 * @struct Cinta
 * @brief Representa una cinta en una máquina de Turing.
 *
 * Esta estructura de datos almacena la posición del cabezal de lectura/escritura
 * y los símbolos presentes en la cinta.
 *
 * El cabezal indica la posición actual en la cinta y se utiliza para leer y escribir
 * símbolos en esa posición.
 *
 * Los símbolos se almacenan en un arreglo de caracteres y pueden ser cualquier carácter
 * válido en el contexto del programa y las máquinas de Turing.
 *
 * Esta estructura es utilizada para representar el estado de la cinta en una máquina de Turing
 * y facilita la manipulación de los símbolos y la posición del cabezal.
 */
struct Cinta
{
    int cabezal;
    char simbolos[INFINITO];
};

/**
 * @struct Automata
 * @brief Estructura de datos que representa un autómata de Turing.
 *
 * Un autómata de Turing consta de un conjunto de estados, un alfabeto de entrada,
 * un alfabeto de la cinta, un estado inicial, un conjunto de estados finales y una
 * función de transición que define cómo se mueve el autómata en la cinta.
 *
 * Esta estructura de datos almacena la información necesaria para representar un autómata
 * de Turing, incluyendo el número de estados finales, el estado inicial, los estados finales,
 * el número de elementos del alfabeto de entrada, el alfabeto de entrada, el número de elementos
 * del alfabeto de la cinta, el alfabeto de la cinta, el número de estados y la función de transición.
 * También almacena dos cintas, que son utilizadas por el autómata para realizar las operaciones.
 */
struct Automata
{
    int numeroEstadosFinales;    /**< Número de estados finales */
    int estadoInicial;           /**< Estado inicial */
    int* estadosFinales;         /**< Estados finales */
    int numElementosSigma;       /**< Número de elementos del alfabeto de entrada */
    char* sigma;                 /**< Alfabeto de entrada */
    int numElementosGamma;       /**< Número de elementos del alfabeto de la cinta */
    char* gamma;                 /**< Alfabeto de la cinta */
    int numeroEstados;           /**< Número de estados */
    struct Estado* estados;      /**< Función de transición */
    struct Estado* estadoActual; /**< Estado actual */
    struct Cinta* cinta1;        /**< Cinta 1 */
    struct Cinta* cinta2;        /**< Cinta 2 */
};

/**
 * Función que imprime los tokens obtenidos.
 *
 * Esta función lee los tokens utilizando la función tokenizar() y los imprime en la consola.
 * Cada token se imprime seguido de un delimitador.
 * La función continúa imprimiendo tokens hasta que se llegue al final de los tokens.
 */
void imprimirTokens()
{
    TOKEN = tokenizar();
    printf("%s", TOKEN);
    TOKEN = siguienteToken();
    while (TOKEN != NULL)
    {
        printf("%c", DELIMITADOR);
        printf("%s", TOKEN);
        TOKEN = siguienteToken();
    }
}
/**
 * Función que lee el valor del estado inicial.
 * Formato de la entrada:
 * q0: <valor_num_estadoInicial>
 * @return El valor del estado inicial.
 */
int leerValorEstadoInicial()
{
    leerCadena();
    saltarEtiqueta();
    int estadoInicial = atoi(TOKEN);
    return estadoInicial;
}
/**
 * Función que lee un número de estados finales.
 * Formato de la entrada:
 * |F|: <valor_num_estadosFinales>
 * @return El número de estados finales leído.
 */
int leerNumEstadosFinales()
{
    leerCadena();
    saltarEtiqueta();
    int numeroEstadosFinales = atoi(TOKEN);
    return numeroEstadosFinales;
}
/**
 * Lee los estados finales desde la entrada y los almacena en un arreglo dinámico.
 * Formato de la entrada:
 * F: <valor_estado_final_1> <valor_estado_final_2> ... <valor_estado_final_n>
 * @param numeroEstadosFinales El número de estados finales a leer.
 * @return Un puntero al arreglo de estados finales leídos.
 */
int* leerEstadosFinales(int numeroEstadosFinales)
{
    int* estadosFinales = (int*)malloc(sizeof(int) * numeroEstadosFinales);
    leerCadena();
    saltarEtiqueta();
    for (int i = 0; i < numeroEstadosFinales; i++)
    {
        estadosFinales[i] = atoi(TOKEN);
        TOKEN = siguienteToken();
    }
    return estadosFinales;
}
/**
 * Función que lee una cadena y salta una etiqueta.
 * Luego convierte el token a un entero y lo devuelve como el número de elementos de Sigma.
 * Formato de la entrada:
 * |S|: <numero_elementos_sigma>
 * @return El número de elementos de Sigma.
 */
int leerNumElementosSigma()
{
    leerCadena();
    saltarEtiqueta();
    int numElementosSigma = atoi(TOKEN);
    return numElementosSigma;
}
/**
 * @brief Lee una cadena de caracteres y devuelve un puntero a un arreglo de caracteres.
 * Formato de la entrada:
 * S: <elemento_1> <elemento_2> ... <elemento_n>
 * @param numElementosSigma El número de elementos en el arreglo sigma.
 * @return Un puntero a un arreglo de caracteres.
 */
char* leerSigma(int numElementosSigma)
{
    char* sigma = (char*)malloc(sizeof(char) * numElementosSigma);
    leerCadena();
    saltarEtiqueta();
    for (int i = 0; i < numElementosSigma; i++)
    {
        sigma[i] = TOKEN[0];
        TOKEN = siguienteToken();
    }
    return sigma;
}
/**
 * Función para leer una cadena de caracteres gamma.
 * Formato de la entrada:
 * G: <elemento_1> <elemento_2> ... <elemento_n>
 * @param numElementosGamma El número de elementos en la cadena gamma.
 * @return Un puntero a la cadena gamma leída.
 */
char* leerGamma(int numElementosGamma)
{
    char* gamma = (char*)malloc(sizeof(char) * numElementosGamma);
    leerCadena();
    saltarEtiqueta();
    for (int i = 0; i < numElementosGamma; i++)
    {
        gamma[i] = TOKEN[0];
        TOKEN = siguienteToken();
    }
    return gamma;
}
/**
 * Función que lee una cadena, salta una etiqueta y convierte el token en un número entero.
 * Formato de la entrada:
 * |G|: <numero_elementos_gamma>
 * @return El número de elementos gamma leídos.
 */
int leerNumeroElementosGamma()
{
    leerCadena();
    saltarEtiqueta();
    int numeroElementosGamma = atoi(TOKEN);
    return numeroElementosGamma;
}
/**
 * Función que lee un número de estados desde una cadena y lo devuelve.
 * Formato de la entrada:
 * |Q|: <numero_estados>
 * @return El número de estados leído.
 */
int leerNumeroEstados()
{
    leerCadena();
    saltarEtiqueta();
    int numeroEstados = atoi(TOKEN);
    return numeroEstados;
}

/**
 * @brief Lee una operación de escritura de la cinta.
 * Formato de la entrada:
 * <numero_cinta> <simbolo_escritura> <operacion>
 * @return Puntero a la estructura de la operación de escritura de la cinta.
 */
struct OperacionEscrituraCinta* leerOperacionEscritura()
{
    struct OperacionEscrituraCinta* operacionEscritura = (struct OperacionEscrituraCinta*)malloc(sizeof(struct OperacionEscrituraCinta));
    leerCadena();
    TOKEN = tokenizar();
    operacionEscritura->numeroCinta = atoi(TOKEN);
    TOKEN = siguienteToken();
    operacionEscritura->simboloEscritura = TOKEN[0];
    TOKEN = siguienteToken();
    operacionEscritura->operacion = TOKEN[0];
    return operacionEscritura;
}
/**
 * Función que lee las aristas de un estado.
 * Formato de la entrada:
 * <simbolo_lectura> <estado_destino> <numero_operaciones_escritura_cinta>
 * <numero_cinta> <simbolo_escritura> <operacion> Operaciones de escritura de la cinta
 * <numero_cinta> <simbolo_escritura> <operacion>
 * ...
 * <simbolo_lectura> <estado_destino> <numero_operaciones_escritura_cinta>
 * <numero_cinta> <simbolo_escritura> <operacion>
 * ...
 * <simbolo_lectura> <estado_destino> <numero_operaciones_escritura_cinta>
 * ...
 * @param numeroDeAristas El número de aristas a leer.
 * @return Un puntero a un arreglo de estructuras Arista que contiene las aristas leídas.
 */
struct Arista* leerAristasDelEstado(int numeroDeAristas)
{
    struct Arista* aristas = (struct Arista*)malloc(sizeof(struct Arista) * numeroDeAristas);
    for (int i = 0; i < numeroDeAristas; i++)
    {
        leerCadena();
        TOKEN = tokenizar();
        aristas[i].simboloLectura = TOKEN[0];
        TOKEN = siguienteToken();
        aristas[i].estadoDestino = atoi(TOKEN);
        TOKEN = siguienteToken();
        aristas[i].numeroOperacionesEscrituraCinta = atoi(TOKEN);
        int numeroOperacionesEscrituraCinta = aristas[i].numeroOperacionesEscrituraCinta;
        aristas[i].operacionesEscrituraCinta = (struct OperacionEscrituraCinta*)malloc(sizeof(struct OperacionEscrituraCinta) * numeroOperacionesEscrituraCinta);
        for (int j = 0; j < numeroOperacionesEscrituraCinta; j++)
        {
            aristas[i].operacionesEscrituraCinta[j] = *leerOperacionEscritura();
        }
    }
    return aristas;
}
/**
 * @brief Lee y crea un arreglo de estados.
 * Formato de la entrada:
 * q: <numero_estado>
 * |A|: <numero_aristas>
 * <simbolo_lectura> <estado_destino> <numero_operaciones_escritura_cinta>
 * <numero_cinta> <simbolo_escritura> <operacion>
 * <numero_cinta> <simbolo_escritura> <operacion>
 * ...
 * <simbolo_lectura> <estado_destino> <numero_operaciones_escritura_cinta>
 * ...
 * q: <numero_estado>
 * |A|: <numero_aristas>
 * <simbolo_lectura> <estado_destino> <numero_operaciones_escritura_cinta>
 * <numero_cinta> <simbolo_escritura> <operacion>
 * <numero_cinta> <simbolo_escritura> <operacion>
 * ...
 * <simbolo_lectura> <estado_destino> <numero_operaciones_escritura_cinta>
 * ...
 * @param numeroEstados El número de estados a leer.
 * @return struct Estado* Un puntero al arreglo de estados creado.
 */
struct Estado* leerEstados(int numeroEstados)
{
    struct Estado* estados = (struct Estado*)malloc(sizeof(struct Estado) * numeroEstados);
    for (int i = 0; i < numeroEstados; i++)
    {
        leerCadena();
        saltarEtiqueta();
        int estado = atoi(TOKEN);
        estados[i].estado = estado;
        leerCadena();
        saltarEtiqueta();
        int numeroAristas = atoi(TOKEN);
        estados[i].aristas = leerAristasDelEstado(numeroAristas);
        estados[i].numAristas = numeroAristas;
    }
    return estados;
}

struct Estado* buscarEstado(int estado, struct Estado* estados, int numeroEstados)
{
    for (int i = 0; i < numeroEstados; i++)
    {
        if (estado == estados[i].estado)
        {
            return estados + i;
        }
    }
    return NULL;
}
/**
 * Función que lee un autómata desde la entrada estándar.
 *
 * @return Puntero a la estructura del autómata.
 */
struct Automata* leerAutomata()
{
    struct Automata* automata = (struct Automata*)malloc(sizeof(struct Automata));
    automata->estadoInicial = leerValorEstadoInicial();
    automata->numeroEstadosFinales = leerNumEstadosFinales();
    automata->estadosFinales = leerEstadosFinales(automata->numeroEstadosFinales);
    automata->numElementosSigma = leerNumElementosSigma();
    automata->sigma = leerSigma(automata->numElementosSigma);
    automata->numElementosGamma = leerNumeroElementosGamma();
    automata->gamma = leerGamma(automata->numElementosGamma);
    automata->numeroEstados = leerNumeroEstados();
    automata->estados = leerEstados(automata->numeroEstados);
    automata->cinta1 = (struct Cinta*)malloc(sizeof(struct Cinta));
    automata->cinta2 = (struct Cinta*)malloc(sizeof(struct Cinta));
    automata->cinta1->cabezal = 0;
    automata->cinta2->cabezal = 0;
    automata->estadoActual = buscarEstado(automata->estadoInicial, automata->estados, automata->numeroEstados);
    return automata;
}
bool simboloEnSigma(char simbolo, char* sigma, int numElementosSigma)
{
    for (int i = 0; i < numElementosSigma; i++)
    {
        if (simbolo == sigma[i])
        {
            return true;
        }
    }
    return false;
}
bool simboloEnGamma(char simbolo, char* gamma, int numElementosGamma)
{
    for (int i = 0; i < numElementosGamma; i++)
    {
        if (simbolo == gamma[i])
        {
            return true;
        }
    }
    return false;
}

/**
 * Inserta un valor en la cinta especificada de una máquina de Turing.
 * @attention El cabezal se mueve de su posición actual a la derecha.
 * @param maquina Puntero a la estructura de la máquina de Turing.
 * @param valor Valor a insertar en la cinta.
 * @param numeroCinta Número de la cinta en la que se insertará el valor (1 o 2).
 */
void insertarValorACinta(const struct Automata* maquina, int valor)
{
    const bool simboloMenosEnSigma = simboloEnSigma('-', maquina->sigma, maquina->numElementosSigma);
    const bool simboloUnoEnSigma = simboloEnSigma('1', maquina->sigma, maquina->numElementosSigma);
    if (!simboloUnoEnSigma)
    {
        logError("El símbolo '1' no está en el alfabeto de entrada");
    }
    if (!simboloMenosEnSigma)
    {
        logError("El símbolo '-' no está en el alfabeto de entrada");
    }
    struct Cinta* c = maquina->cinta1;
    if (valor < 0)
    {
        c->simbolos[c->cabezal] = '-';
        c->cabezal++;
        valor = -valor;
    }
    for (int i = 0; i < valor; i++)
    {
        c->simbolos[c->cabezal] = '1';
        c->cabezal++;
    }
}
/**
 * Inserta un valor en la cinta especificada de un autómata.
 * @attention El cabezal se mueve de su posición actual a la derecha.
 * @param maquina Puntero a la estructura del autómata.
 * @param simbolo Símbolo a insertar en la cinta.
 * @param numeroCinta Número de la cinta en la que se insertará el símbolo (1 o 2).
 */
void insertarUnValorACinta(const struct Automata* maquina, char simbolo, int numeroCinta) {
    struct Cinta* c = NULL;
    if (numeroCinta == 1) {
        // const bool simboloEnConjuntoSigma = simboloEnSigma(simbolo, maquina->sigma, maquina->numElementosSigma);
        // if (!simboloEnConjuntoSigma)
        // {
        //     logError("El símbolo no está en el alfabeto de entrada");
        // }
        c = maquina->cinta1;
    }
    else {
        // const bool simboloEnConjuntoGamma = simboloEnGamma(simbolo, maquina->gamma, maquina->numElementosGamma);
        // if (!simboloEnConjuntoGamma)
        // {
        //     logError("El símbolo no está el Gamma");
        // }
        c = maquina->cinta2;
    }
    c->simbolos[c->cabezal] = simbolo;
    c->cabezal++;
}
bool esEstadoFinal(int estado, int* estadosFinales, int numeroEstadosFinales)
{
    for (int i = 0; i < numeroEstadosFinales; i++)
    {
        if (estado == estadosFinales[i])
        {
            return true;
        }
    }
    return false;
}
struct Arista* buscarArista(char simboloLeido, struct Arista* aristas, int numeroAristas) {
    for (int i = 0; i < numeroAristas; i++)
    {
        if (simboloLeido == aristas[i].simboloLectura)
        {
            return aristas + i;
        }
    }
    return NULL;
}
void escribirEnCinta(const struct Automata* maquina, struct OperacionEscrituraCinta* operacionEscrituraCinta) {
    struct Cinta* cinta = NULL;
    if (operacionEscrituraCinta->numeroCinta == 1)
    {
        cinta = maquina->cinta1;
    }
    else if (operacionEscrituraCinta->numeroCinta == 2)
    {
        cinta = maquina->cinta2;
    }
    else {
        logError("El número de cinta no es válido");
    }
    cinta->simbolos[cinta->cabezal] = operacionEscrituraCinta->simboloEscritura;
    if (operacionEscrituraCinta->operacion == 'L')
    {
        cinta->cabezal--;
    }
    else if (operacionEscrituraCinta->operacion == 'R')
    {
        cinta->cabezal++;
    }
    else {
        logError("La operación no es válida");
    }
}
void resolverArista(const struct Arista* aristaAEjecutar, const struct Automata* maquina) {
    if (aristaAEjecutar == NULL) {
        logError("No se encontró la arista");
    }
    for (int i = 0; i < aristaAEjecutar->numeroOperacionesEscrituraCinta; i++)
    {
        struct OperacionEscrituraCinta* operacionEscrituraCinta = aristaAEjecutar->operacionesEscrituraCinta + i;
        escribirEnCinta(maquina, operacionEscrituraCinta);
    }
}
bool ejecutar(struct Automata* maquina, bool logs) {
    if (logs == true) {
        printf("__________________________________________EJECUCION__________________________________________\n");
    }
    bool esFinal = esEstadoFinal(maquina->estadoActual->estado, maquina->estadosFinales, maquina->numeroEstadosFinales);
    struct Arista* aristaAEjecutar = NULL;
    struct Estado* siguienteEstado = NULL;
    maquina->cinta1->cabezal = 1;
    char simboloLeido = maquina->cinta1->simbolos[maquina->cinta1->cabezal];
    bool simboloLeidoEnSigma = simboloEnSigma(simboloLeido, maquina->sigma, maquina->numElementosSigma);
    while (!esFinal)
    {
        if (!simboloLeidoEnSigma) {
            return false;
        }
        if (LOGS_ACTIVADO == true) {
            printf("__________________________________________ITERACION__________________________________________\n");
        }
        aristaAEjecutar = buscarArista(simboloLeido, maquina->estadoActual->aristas, maquina->estadoActual->numAristas);
        if (logs == true) {
            imprimirVariableNumerica(maquina->estadoActual->estado);
            imprimirVariableCaracter(simboloLeido);
            imprimirVariableNumerica(aristaAEjecutar->estadoDestino);
            imprimirCinta(maquina->cinta1, MAX_CARACTERES_POR_LINEA);
            imprimirCinta(maquina->cinta2, MAX_CARACTERES_POR_LINEA);
        }
        resolverArista(aristaAEjecutar, maquina);
        simboloLeido = maquina->cinta1->simbolos[maquina->cinta1->cabezal];
        siguienteEstado = buscarEstado(aristaAEjecutar->estadoDestino, maquina->estados, maquina->numeroEstados);
        maquina->estadoActual = siguienteEstado;
        esFinal = esEstadoFinal(siguienteEstado->estado, maquina->estadosFinales, maquina->numeroEstadosFinales);
        if (!esFinal && aristaAEjecutar == NULL) {
            return false;
        }
    }
    maquina->cinta2->simbolos[maquina->cinta2->cabezal] = '$';
    return true;
}
void inicializarAutomata(struct Automata* maquina, int numero1, int numero2) {
    maquina->cinta1->cabezal = 0;
    maquina->cinta2->cabezal = 0;
    maquina->estadoActual = buscarEstado(maquina->estadoInicial, maquina->estados, maquina->numeroEstados);
    insertarUnValorACinta(maquina, 'B', 1);
    insertarValorACinta(maquina, numero1);
    insertarUnValorACinta(maquina, '*', 1);
    insertarValorACinta(maquina, numero2);
    insertarUnValorACinta(maquina, '$', 1);
}
int determinarValorMulti(struct Automata* maquina) {
    int resultado = 0;
    int signo = 1;
    for (int i = 0; i < INFINITO; i++)
    {
        if (maquina->cinta2->simbolos[i] == '1')
        {
            resultado++;
        }
        else if (maquina->cinta2->simbolos[i] == '-') {
            signo = -1;
        }
        else if (maquina->cinta2->simbolos[i] == '$') {
            if (LOGS_ACTIVADO == true) {
                imprimirVariableNumerica(resultado * signo)
                    imprimirVariableNumerica(i)
            }
            break;
        }
    }
    return resultado * signo;
}
bool hayDesbordamiento(int a, int b) {
    long long producto = (long long)a * b;
    int maxPositivo = (1 << 31) - 1;
    int maxNegativo = -1 * (1 << 31);
    if (producto >= maxPositivo) return true;
    if (producto <= maxNegativo) return true;
    return false;
}
bool esEntero(const char* cadena) {
    if (cadena == NULL || *cadena == '\0') {
        return false;
    }
    int i = 0;
    if (cadena[0] == '-' || cadena[0] == '+') {
        i++;
    }
    for (; cadena[i] != '\0'; i++) {
        if (cadena[i] < '0' || cadena[i] > '9') {
            return false;
        }
    }
    return true;
}
void insertarCadenaACinta(struct Automata* maquina, const char* cadena) {
    int longitud = strlen(cadena);
    for (int i = 0; i < longitud; i++) {
        insertarUnValorACinta(maquina, cadena[i], 1);
    }
}

void ejecutarTestCases(struct Automata* maquina) {
    leerCadena();
    saltarEtiqueta();
    int numeroTestCases = atoi(TOKEN);
    imprimirVariableNumerica(numeroTestCases);
    int testCasesEjecutados = 1;
    while (numeroTestCases--) {
        TOKEN = leerCadena();
        TOKEN = tokenizar();
        int numero1;
        int numero2;
        bool esEntero1 = esEntero(TOKEN);
        if (esEntero1 == true) {
            numero1 = atoi(TOKEN);
        }
        else {
            insertarUnValorACinta(maquina, 'B', 1);
            insertarCadenaACinta(maquina, TOKEN);
        }
        TOKEN = siguienteToken();
        bool esEntero2 = esEntero(TOKEN);
        if (esEntero2 == true) {
            numero2 = atoi(TOKEN);
        }
        else {
            insertarCadenaACinta(maquina, TOKEN);
        }
        TOKEN = siguienteToken();
        int debeAceptar = atoi(TOKEN);
        if (esEntero1 == true && esEntero2 == true) {
            inicializarAutomata(maquina, numero1, numero2);
        }
        if (hayDesbordamiento(numero1, numero2)) {
            printf("_________________________________________________________TEST_CASE:: %d: OVERFLOW::EL PRODUCTO NO CABE EN UN INT\n", testCasesEjecutados);
            testCasesEjecutados++;
            continue;
        }
        int valorEsperado = numero1 * numero2;
        bool aceptacion = ejecutar(maquina, LOGS_ACTIVADO == true && valorEsperado < 15);
        int resultado;
        if (aceptacion) {
            resultado = determinarValorMulti(maquina);
        }
        if (resultado == valorEsperado && aceptacion == debeAceptar) {
            printf("_________________________________________________________TEST_CASE:: %d: OK\n", testCasesEjecutados);
        }
        else {
            printf("_________________________________________________________TEST_CASE:: %d: ERROR\n", testCasesEjecutados);
        }
        if (LOGS_ACTIVADO == true) {
            if (maquina->cinta2->cabezal <= MAX_CARACTERES_POR_LINEA) {
                imprimirCinta(maquina->cinta1, maquina->cinta1->cabezal + 5);
                imprimirCinta(maquina->cinta2, maquina->cinta2->cabezal + 5);
            }
            else {
                printf("LOG::ADVERTENCIA::EL TOPE DE LA CINTA 2 ES MAYOR A %d\n", MAX_CARACTERES_POR_LINEA);
                printf("LOG::ADVERTENCIA::SE IMPRIMIRÁN SOLO LOS CABEZALES\n");
                imprimirVariableNumerica(maquina->cinta1->cabezal);
                imprimirVariableNumerica(maquina->cinta2->cabezal);
            }
        }
        testCasesEjecutados++;
    }
}

int main()
{
    struct Automata* automata = leerAutomata();
    if (LOGS_ACTIVADO == true) {
        printf("__________________________________________AUTOMATA__________________________________________\n");
        imprimirAutomata(automata);
    }
    printf("__________________________________________TEST_CASES__________________________________________\n");
    ejecutarTestCases(automata);
    return 0;
}
