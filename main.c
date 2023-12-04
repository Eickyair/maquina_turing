#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CARACTERES_POR_LINEA 100
#define INFINITO 10
#define BLANCO 'B'
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
    int numeroEstados;      // Q
    struct Estado *estados; // Delta
    struct Cinta *cinta1;
    struct Cinta *cinta2;
};
/**
 * Imprime una operación de escritura en formato JSON.
 *
 * @param operacion Puntero a la estructura de la operación de escritura.
 */
void imprimirOperacionEscrituraCintaJSON(struct OperacionEscrituraCinta *operacion)
{
    printf("{\n");
    printf("\t\"numeroCinta\": %d,\n", operacion->numeroCinta);
    printf("\t\"simboloEscritura\": \"%c\",\n", operacion->simboloEscritura);
    printf("\t\"operacion\": \"%c\"\n", operacion->operacion);
    printf("}\n");
}
/**
 * Imprime una arista en formato JSON.
 *
 * @param arista La arista a imprimir.
 */
void imprimirAristaJSON(struct Arista *arista)
{
    printf("{\n");
    printf("\t\"simboloLectura\": \"%c\",\n", arista->simboloLectura);
    printf("\t\"estadoDestino\": %d,\n", arista->estadoDestino);
    printf("\t\"numeroOperacionesEscrituraCinta\": %d,\n", arista->numeroOperacionesEscrituraCinta);
    printf("\t\"operacionesEscrituraCinta\": [\n");
    for (int i = 0; i < arista->numeroOperacionesEscrituraCinta; i++)
    {
        imprimirOperacionEscrituraCintaJSON(&(arista->operacionesEscrituraCinta[i]));
        if (i < arista->numeroOperacionesEscrituraCinta - 1)
        {
            printf(",\n");
        }
    }
    printf("\n\t]\n");
    printf("}\n");
}
/**
 * Imprime el estado actual de la cinta.
 *
 * @param cinta Puntero a la estructura de la cinta.
 */
void imprimirCinta(struct Cinta *cinta)
{
    printf("Cabezal: %d\n", cinta->cabezal);
    printf("Simbolos: ");
    for (int i = 0; i < INFINITO; i++)
    {
        printf("%c ", cinta->simbolos[i]);
    }
    printf("\n");
}
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
 * Función que lee un autómata desde la entrada estándar.
 *
 * @return Puntero a la estructura del autómata.
 */
struct Automata *leerAutomata()
{
    struct Automata *automata = (struct Automata *)malloc(sizeof(struct Automata));
    leerCadena();
    saltarEtiqueta();
    int estadoInicial = atoi(TOKEN);
    automata->estadoInicial = estadoInicial;
    printf("Estado inicial: %d\n", automata->estadoInicial);
    leerCadena();
    saltarEtiqueta();
    int numeroEstadosFinales = atoi(TOKEN);
    automata->numeroEstadosFinales = numeroEstadosFinales;
    printf("Numero de estados finales: %d\n", automata->numeroEstadosFinales);
    automata->estadosFinales = (int *)malloc(sizeof(int) * numeroEstadosFinales);
    leerCadena();
    saltarEtiqueta();
    for (int i = 0; i < numeroEstadosFinales; i++)
    {
        automata->estadosFinales[i] = atoi(TOKEN);
        printf("Estado final %d: %d\n", i, automata->estadosFinales[i]);
        TOKEN = siguienteToken();
    }
    leerCadena();
    saltarEtiqueta();
    int numElementosSigma = atoi(TOKEN);
    automata->numElementosSigma = numElementosSigma;
    printf("Numero de elementos del alfabeto de entrada: %d\n", automata->numElementosSigma);
    automata->sigma = (char *)malloc(sizeof(char) * numElementosSigma);
    leerCadena();
    saltarEtiqueta();
    for (int i = 0; i < numElementosSigma; i++)
    {
        automata->sigma[i] = TOKEN[0];
        printf("Elemento %d del alfabeto de entrada: %c\n", i, automata->sigma[i]);
        TOKEN = siguienteToken();
    }
    leerCadena();
    saltarEtiqueta();
    int numElementosGamma = atoi(TOKEN);
    automata->numElementosGamma = numElementosGamma;
    printf("Numero de elementos del alfabeto de la cinta: %d\n", automata->numElementosGamma);
    automata->gamma = (char *)malloc(sizeof(char) * numElementosGamma);
    leerCadena();
    saltarEtiqueta();
    for (int i = 0; i < numElementosGamma; i++)
    {
        automata->gamma[i] = TOKEN[0];
        printf("Elemento %d del alfabeto de la cinta: %c\n", i, automata->gamma[i]);
        TOKEN = siguienteToken();
    }
    leerCadena();
    saltarEtiqueta();
    int numeroEstados = atoi(TOKEN);
    automata->numeroEstados = numeroEstados;
    printf("Numero de estados: %d\n", automata->numeroEstados);
    automata->estados = (struct Estado *)malloc(sizeof(struct Estado) * numeroEstados);
    for (int i = 0; i < numeroEstados; i++)
    {
        leerCadena();
        saltarEtiqueta();
        int estado = atoi(TOKEN);
        automata->estados[i].estado = estado;
        printf("Estado %d: %d\n", i, automata->estados[i].estado);
        leerCadena();
        saltarEtiqueta();
        int numeroAristas = atoi(TOKEN);
        automata->estados[i].aristas = (struct Arista *)malloc(sizeof(struct Arista) * numeroAristas);
        automata->estados[i].numAristas = numeroAristas;
        printf("Numero de aristas: %d\n", automata->estados[i].numAristas);
        for (int j = 0; j < numeroAristas; j++)
        {
            leerCadena();
            leerCadena();
            TOKEN = tokenizar();
            automata->estados[i].aristas[j].simboloLectura = TOKEN[0];
            printf("Simbolo de lectura: %c\n", automata->estados[i].aristas[j].simboloLectura);
            TOKEN = siguienteToken();
            automata->estados[i].aristas[j].estadoDestino = atoi(TOKEN);
            printf("Estado destino: %d\n", automata->estados[i].aristas[j].estadoDestino);
            TOKEN = siguienteToken();
            automata->estados[i].aristas[j].numeroOperacionesEscrituraCinta = atoi(TOKEN);
            int numeroOperacionesEscrituraCinta = automata->estados[i].aristas[j].numeroOperacionesEscrituraCinta;
            printf("Numero de operaciones de escritura: %d\n", automata->estados[i].aristas[j].numeroOperacionesEscrituraCinta);
            automata->estados[i].aristas[j].operacionesEscrituraCinta = (struct OperacionEscrituraCinta *)malloc(sizeof(struct OperacionEscrituraCinta) * numeroOperacionesEscrituraCinta);
            leerCadena();
            for (int k = 0; k < numeroOperacionesEscrituraCinta; k++)
            {
                leerCadena();
                TOKEN = tokenizar();
                automata->estados[i].aristas[j].operacionesEscrituraCinta[k].numeroCinta = atoi(TOKEN);
                printf("Numero de cinta: %d\n", automata->estados[i].aristas[j].operacionesEscrituraCinta[k].numeroCinta);
                TOKEN = siguienteToken();
                automata->estados[i].aristas[j].operacionesEscrituraCinta[k].simboloEscritura = TOKEN[0];
                printf("Simbolo de escritura: %c\n", automata->estados[i].aristas[j].operacionesEscrituraCinta[k].simboloEscritura);
                TOKEN = siguienteToken();
                automata->estados[i].aristas[j].operacionesEscrituraCinta[k].operacion = TOKEN[0];
                printf("Operacion: %c\n", automata->estados[i].aristas[j].operacionesEscrituraCinta[k].operacion);
            }
        }
    }

    return automata;
}

int main()
{
    const struct Automata *automata = leerAutomata();
    return 0;
}
