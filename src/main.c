/* =====================
 * Grupo 5, IAED, LEIC-T
 * 81900 - Nuno Anselmo
 * 81943 - Gonçalo Matos
 * 82047 - André Mendes
   ===================== */

#include "main.h"

void parseArguments(int *argc, char argv[ARGUMENTS_NUMBER][ARGUMENT_SIZE]) {
    char line[LINESIZE];
    int linePosition;
    char charRead;

    char insideWord = 0;
    int wordPosition = 0;

    /* We don't like scanf since it can cause a buffer overflow, using fgets prevents it.
     * We use fgets and after it we parse the line in separated arguments. */
    fgets(line, LINESIZE, stdin);
    for (charRead = line[linePosition = 0]; charRead != '\n' && charRead != EOF && charRead != '\0' &&
                                            *argc < ARGUMENTS_NUMBER; charRead = line[++linePosition]) {
        if (!insideWord && charRead != ' ') {
            insideWord = 1;
            wordPosition = 0;
        }
        if (insideWord && charRead != ' ') {
            argv[*argc][wordPosition] = charRead;
            wordPosition++;
        }
        if (insideWord && charRead == ' ') {
            argv[*argc][wordPosition] = '\0';
            insideWord = 0;
            (*argc)++;
        }
    }
    argv[*argc][wordPosition] = '\0';
}

int requestInput(Database *database) {
    int argc = 0;
    char argv[ARGUMENTS_NUMBER][ARGUMENT_SIZE];

    /* Request input from user and parse the arguments value
     * into argv and arguments count into argc */
    parseArguments(&argc, argv);

    if (strcmp(argv[0], "cheque") == 0) {
        unsigned long valor = 0, refe = 0, refb = 0, refc = 0;
        sscanf(argv[1], "%lu", &valor);
        sscanf(argv[2], "%lu", &refe);
        sscanf(argv[3], "%lu", &refb);
        sscanf(argv[4], "%lu", &refc);
        database_cheque(database, valor, refe, refb, refc);
    }
    else if (strcmp(argv[0], "processa") == 0) {
        database_process(database);
    }
    else if (strcmp(argv[0], "processaR") == 0) {
        unsigned long refc = 0;
        sscanf(argv[1], "%lu", &refc);
        database_processr(database, refc);
    }
    else if (strcmp(argv[0], "infocheque") == 0) {
        unsigned long ref = 0;
        sscanf(argv[1], "%lu", &ref);
        database_infocheque(database, ref);
    }
    else if (strcmp(argv[0], "infocliente") == 0) {
        unsigned long ref = 0;
        sscanf(argv[1], "%lu", &ref);
        database_infoclient(database, ref);
    }
    else if (strcmp(argv[0], "info") == 0) {
        database_info(database);
    }
    else if (strcmp(argv[0], "sair") == 0) {
        database_quit(database);
        return QUIT;
    }
    return CONTINUE;
}

int main(int argc, const char *argv[]) {
    /* Create our database */
    Database *database = database_init();

    /* Continuously ask for input */
    while (requestInput(database) != QUIT);

    /* Deallocate our database */
    database_destroy(database);

    /* Program completed successfully! Return 0! */
    return 0;
}
