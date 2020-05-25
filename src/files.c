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

    // comandos possiveis
    // create;1;3;12;5
    // moveleft;12;6;3
    // moveright;12;6;3
    // rotate;

    const char delimitar[2] = ";";
    int i = 0;
    char *token = strtok(linha, delimitar);

    while (token != NULL)
    {
        switch (i)
        {
        case 0:
            if (strcmp(token, "create") == 0)
                comando->tipo = CREATE;
            else if (strcmp(token, "moveleft") == 0)
                comando->tipo = MOVE_LEFT;
            else if (strcmp(token, "moveright") == 0)
                comando->tipo = MOVE_RIGHT;
            else if (strcmp(token, "rotate") == 0)
                comando->tipo = ROTATE;
            break;
        case 1:
            // x
            if (comando->tipo != ROTATE)
                comando->x = atoi(token);
            break;
        case 2:
            // y
            if (comando->tipo != ROTATE)
                comando->y = atoi(token);
            break;
        case 3:
            // w or p
            if (comando->tipo == CREATE)
                comando->w = atoi(token);
            else if (comando->tipo == MOVE_LEFT || comando->tipo == MOVE_RIGHT)
                comando->p = atoi(token);
            break;
        case 4:
            // h
            if (comando->tipo == CREATE)
                comando->h = atoi(token);
        }

        // linha seguinte
        token = strtok(NULL, delimitar);
        i += 1;
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
