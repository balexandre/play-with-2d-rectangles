/*
** File: files.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"

COMANDO *getComando(char *linha)
{
    COMANDO *comando = malloc(sizeof(COMANDO));
    char *found;

    // comandos possiveis
    char *create = "create";       // create 1,3+12,5
    char *moveLeft = "moveleft";   // moveleft 12,6+3
    char *moveRight = "moveright"; // moveright 12,6+3
    char *rotate = "rotate";       // rotate

    // create
    found = strstr(linha, create);
    if (found != NULL)
    {
        comando->tipo = CREATE;
    }

    // moveLeft
    found = strstr(linha, moveLeft);
    if (found != NULL)
    {
        comando->tipo = MOVE_LEFT;
    }

    // moveRight
    found = strstr(linha, moveRight);
    if (found != NULL)
    {
        comando->tipo = MOVE_RIGHT;
    }

    // rotate
    found = strstr(linha, rotate);
    if (found != NULL)
    {
        comando->tipo = ROTATE;
    }

    return comando;
}
int readFileComandos(COMANDO *comandos[])
{
    printf("\nFicheiro de leitura: commands.txt\n");
    FILE *ficheiro = fopen("./files/commands.txt", "r");

    int count = 0;
    int tamLinha = 70;
    char linha[tamLinha];

    COMANDO *output;
    output = malloc(sizeof(output));

    if (ficheiro != NULL)
    {
        while (fgets(linha, tamLinha, ficheiro) != 0)
        {
            output = getComando(linha);
            comandos[count++] = output;
        }
    }

    fclose(ficheiro);
    return count;
}

/* EOF */
