#include <stdio.h>
#include <string.h>
#define MAX_CARACTERES_POR_LINEA 100
#define INFINITO 10
char LECTURA_CADENA[MAX_CARACTERES_POR_LINEA];
char *TOKEN = NULL;
const char DELIMITADOR = ' ';
#define leerCadena() fgets(LECTURA_CADENA, MAX_CARACTERES_POR_LINEA, stdin)
#define leerTokens() strtok(LECTURA_CADENA, &DELIMITADOR)
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
void imprimirOperacionEscrituraCintaJSON(struct OperacionEscrituraCinta *operacion)
{
    printf("{\n");
    printf("\t\"numeroCinta\": %d,\n", operacion->numeroCinta);
    printf("\t\"simboloEscritura\": \"%c\",\n", operacion->simboloEscritura);
    printf("\t\"operacion\": \"%c\"\n", operacion->operacion);
    printf("}\n");
}
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
