/**
 * @file main.c
 * @brief Este archivo contiene el código principal de la máquina de Turing.
 *        Incluye las bibliotecas necesarias y define las funciones principales.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CARACTERES_POR_LINEA 100
#define INFINITO 10
#define BLANCO 'B'
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
            printf(", ");                    \
        }                                    \
    }                                        \
    printf("]\n")
   /**
    * @brief Imprime el valor de una variable numérica junto con su nombre.
    *
    * @param variable La variable numérica a imprimir.
    */
#define imprimirVariableNumerica(variable) printf("%s = %d\n", #variable, variable)
    /**
     * @brief Imprime el valor de una variable de tipo caracter.
     *
     * @param variable La variable de tipo caracter a imprimir.
     */
#define imprimirVariableCaracter(variable) printf("%s = '%c'\n", #variable, variable)

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
    int numeroEstadosFinales; /**< Número de estados finales */
    int estadoInicial;        /**< Estado inicial */
    int* estadosFinales;      /**< Estados finales */
    int numElementosSigma;    /**< Número de elementos del alfabeto de entrada */
    char* sigma;              /**< Alfabeto de entrada */
    int numElementosGamma;    /**< Número de elementos del alfabeto de la cinta */
    char* gamma;              /**< Alfabeto de la cinta */
    int numeroEstados;        /**< Número de estados */
    struct Estado* estados;   /**< Función de transición */
    struct Cinta* cinta1;     /**< Cinta 1 */
    struct Cinta* cinta2;     /**< Cinta 2 */
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
/**
 * Función que lee un autómata desde la entrada estándar.
 *
 * @return Puntero a la estructura del autómata.
 */
struct Automata* leerAutomata()
{
    struct Automata* automata = (struct Automata*)malloc(sizeof(struct Automata));
    automata->estadoInicial = leerValorEstadoInicial();
    imprimirVariableNumerica(automata->estadoInicial);
    automata->numeroEstadosFinales = leerNumEstadosFinales();
    imprimirVariableNumerica(automata->numeroEstadosFinales);
    automata->estadosFinales = leerEstadosFinales(automata->numeroEstadosFinales);
    imprimirArregloNumeros(automata->estadosFinales, automata->numeroEstadosFinales);
    automata->numElementosSigma = leerNumElementosSigma();
    imprimirVariableNumerica(automata->numElementosSigma);
    automata->sigma = leerSigma(automata->numElementosSigma);
    imprimirArregloCaracteres(automata->sigma, automata->numElementosSigma);
    automata->numElementosGamma = leerNumeroElementosGamma();
    imprimirVariableNumerica(automata->numElementosGamma);
    automata->gamma = leerGamma(automata->numElementosGamma);
    imprimirArregloCaracteres(automata->gamma, automata->numElementosGamma);
    automata->numeroEstados = leerNumeroEstados();
    imprimirVariableNumerica(automata->numeroEstados);
    automata->estados = leerEstados(automata->numeroEstados);
    imprimirArista(automata->estados[0].aristas);
    const struct Arista* arista = automata->estados[0].aristas + 1;
    imprimirArista(arista);
    return automata;
}

int main()
{
    const struct Automata* automata = leerAutomata();
    return 0;
}
