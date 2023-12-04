#include <stdio.h>
#include <string.h>
#define MAX_CARACTERES_POR_LINEA 100
#define INFINITO 10
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
#define leerTokens() strtok(LECTURA_CADENA, &DELIMITADOR)

/**
 * @brief Macro para obtener el siguiente token de una cadena.
 * 
 * @return Puntero al siguiente token encontrado.
 */
#define siguienteToken() strtok(NULL, &DELIMITADOR)


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
    struct Arista *aristas;
};

struct Cinta
{
    int cabezal;
    char simbolos[INFINITO];
};

struct Automata
{
    struct Estado **estados;
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
 * Esta función lee los tokens utilizando la función leerTokens() y los imprime en la consola.
 * Cada token se imprime seguido de un delimitador.
 * La función continúa imprimiendo tokens hasta que se llegue al final de los tokens.
 */
void imprimirTokens()
{
    TOKEN = leerTokens();
    printf("%s", TOKEN);
    while (TOKEN != NULL)
    {
        printf("%c",DELIMITADOR);
        printf("%s", TOKEN);
        TOKEN = siguienteToken();
    }
}
int main()
{
    const char *cadena = leerCadena();
    while (cadena != NULL)
    {
        imprimirTokens();
        cadena = leerCadena();
    }
    return 0;
}
