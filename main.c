#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CARACTERES_POR_LINEA 100
#define INFINITO 10
#define BLANCO 'B'
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
    printf("]\n");
#define imprimirVariableNumerica(variable) printf("%s = %d\n", #variable, variable)
#define imprimirVariableCaracter(variable) printf("%s = '%c'\n", #variable, variable)

char LECTURA_CADENA[MAX_CARACTERES_POR_LINEA];
char *TOKEN = NULL;
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
#define imprimirOperacionEscrituraCinta(ptr)                      \
    imprimirVariableNumerica(ptr->numeroCinta); \
    imprimirVariableCaracter(ptr->simboloEscritura); \
    imprimirVariableCaracter(ptr->operacion)
#define imprimirArista(ptr) \
    imprimirVariableCaracter(ptr->simboloLectura); \
    imprimirVariableNumerica(ptr->estadoDestino); \
    imprimirVariableNumerica(ptr->numeroOperacionesEscrituraCinta)
struct OperacionEscrituraCinta
{
    int numeroCinta;
    char simboloEscritura;
    char operacion; // 'L' o 'R'
};
struct Arista
{
    char simboloLectura;
    int estadoDestino;
    int numeroOperacionesEscrituraCinta;
    struct OperacionEscrituraCinta *operacionesEscrituraCinta;
};

struct Estado
{
    int estado;
    int numAristas;
    struct Arista *aristas;
};

struct Cinta
{
    int cabezal;
    char simbolos[INFINITO];
};

struct Automata
{
    int numeroEstadosFinales;
    int estadoInicial;      // q0
    int *estadosFinales;    // F
    int numElementosSigma;  // Numero de elementos del alfabeto de entrada
    char *sigma;            // Alfabeto de entrada
    int numElementosGamma;  // Numero de elementos del alfabeto de la cinta
    char *gamma;            // Alfabeto de la cintas
    int numeroEstados;      // |Q|
    struct Estado *estados; // Delta
    struct Cinta *cinta1;
    struct Cinta *cinta2;
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
 * <etiqueta> <valor_num_estadoInicial>
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
 * <etiqueta> <valor_num_estadosFinales>
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
 * <etiqueta> <valor_estado_final_1> <valor_estado_final_2> ... <valor_estado_final_n>
 * @param numeroEstadosFinales El número de estados finales a leer.
 * @return Un puntero al arreglo de estados finales leídos.
 */
int *leerEstadosFinales(int numeroEstadosFinales)
{
    int *estadosFinales = (int *)malloc(sizeof(int) * numeroEstadosFinales);
    leerCadena();
    saltarEtiqueta();
    for (int i = 0; i < numeroEstadosFinales; i++)
    {
        estadosFinales[i] = atoi(TOKEN);
        TOKEN = siguienteToken();
    }
    return estadosFinales;
}
int leerNumElementosSigma()
{
    leerCadena();
    saltarEtiqueta();
    int numElementosSigma = atoi(TOKEN);
    return numElementosSigma;
}
char *leerSigma(int numElementosSigma)
{
    char *sigma = (char *)malloc(sizeof(char) * numElementosSigma);
    leerCadena();
    saltarEtiqueta();
    for (int i = 0; i < numElementosSigma; i++)
    {
        sigma[i] = TOKEN[0];
        TOKEN = siguienteToken();
    }
    return sigma;
}
char *leerGamma(int numElementosGamma)
{
    char *gamma = (char *)malloc(sizeof(char) * numElementosGamma);
    leerCadena();
    saltarEtiqueta();
    for (int i = 0; i < numElementosGamma; i++)
    {
        gamma[i] = TOKEN[0];
        TOKEN = siguienteToken();
    }
    return gamma;
}
int leerNumeroElementosGamma()
{
    leerCadena();
    saltarEtiqueta();
    int numeroElementosGamma = atoi(TOKEN);
    return numeroElementosGamma;
}
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
struct OperacionEscrituraCinta *leerOperacionEscritura()
{
    struct OperacionEscrituraCinta *operacionEscritura = (struct OperacionEscrituraCinta *)malloc(sizeof(struct OperacionEscrituraCinta));
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
struct Arista *leerAristasDelEstado(int numeroDeAristas)
{
    struct Arista *aristas = (struct Arista *)malloc(sizeof(struct Arista) * numeroDeAristas);
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
        aristas[i].operacionesEscrituraCinta = (struct OperacionEscrituraCinta *)malloc(sizeof(struct OperacionEscrituraCinta) * numeroOperacionesEscrituraCinta);
        for (int j = 0; j < numeroOperacionesEscrituraCinta; j++)
        {
            aristas[i].operacionesEscrituraCinta[j] = *leerOperacionEscritura();
        }
    }
    return aristas;
}
struct Estado *leerEstados(int numeroEstados, int debug)
{
    struct Estado *estados = (struct Estado *)malloc(sizeof(struct Estado) * numeroEstados);
    for (int i = 0; i < numeroEstados; i++)
    {
        leerCadena();
        saltarEtiqueta();
        int estado = atoi(TOKEN);
        estados[i].estado = estado;
        if (debug == 1)
        {
            imprimirVariableNumerica(estados[i].estado);
        }
        leerCadena();
        saltarEtiqueta();
        int numeroAristas = atoi(TOKEN);
        estados[i].aristas = leerAristasDelEstado(numeroAristas);
        estados[i].numAristas = numeroAristas;
        if (debug == 1)
        {
            imprimirVariableNumerica(estados[i].numAristas);
        }
    }
    return estados;
}
/**
 * Función que lee un autómata desde la entrada estándar.
 *
 * @return Puntero a la estructura del autómata.
 */
struct Automata *leerAutomata()
{
    struct Automata *automata = (struct Automata *)malloc(sizeof(struct Automata));
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
    const struct Arista *aristas = leerAristasDelEstado(2);
    imprimirArista(aristas);
    // imprimirVariableNumerica(automata->numeroEstados);
    // automata->estados = leerEstados(automata->numeroEstados, 1);
    return automata;
}

int main()
{
    const struct Automata *automata = leerAutomata();
    return 0;
}
