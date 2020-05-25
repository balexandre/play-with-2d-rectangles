/*
** File: gravity.c
*/
#include <stdio.h>

#include "structures.h"
#include "gravity.h"
#include "printing.h"

#define DEBUG 0

void activaGravidadePorObjecto(RECTANGULO *objectos, int posicao, int num_objectos)
{
    // verifica o espaco por baixo do objecto na "posicao" em relacao aos outros no plano,
    // e certifica-se que nao há intercecoes

    RECTANGULO objecto_a_verificar = objectos[posicao];
    int xMin = objecto_a_verificar.x0 + 1; // (+1) ignora margem
    int xMax = objecto_a_verificar.x1 - 1; // (-1) ignora margem
    int yMin = 0;
    int yMax = objecto_a_verificar.y0 - 1; // (-1) ignora linha

    int podemos_mover_objecto = 1; // 0: Nao, 1: Sim -> assumimos que pode ser movido
    int posicoes_a_mover = objecto_a_verificar.y0;

    for (int i = 0; i < num_objectos; i += 1)
    {
        if (i == posicao) // nao precisamos comparar o mesmo objecto
            continue;

        RECTANGULO objecto = objectos[i];
        if (DEBUG == 1)
            printf("*** a verificar Objecto %d com Objecto %d\n", posicao + 1, i + 1);

        for (int y = yMax; y >= yMin; y -= 1)
        {
            for (int x = xMin; x <= xMax; x += 1)
            {
                char simbolo = qualCaractereQueImprimePorObjecto(objecto, x, y);
                if (DEBUG == 1)
                    printf("o%dx%dy%d>%c<", i, x, y, simbolo);
                /*
                    x2,y2-----------x3,y3
                    |                |
                    |                |
                    x0,y0-----------x1,y1
                */
                if (simbolo != ' ')
                {
                    posicoes_a_mover = (yMax - y) == 0 ? 0 : yMax - y + 1;
                    // if (posicoes_a_mover == objecto.y0)
                    {
                        podemos_mover_objecto = 0;
                        red();
                        if (DEBUG == 1)
                            printf("%d", posicoes_a_mover);
                        reset();
                    }
                }

                // nao precisamos de verificar mais, ja existe uma occorrencia
                if (podemos_mover_objecto == 0)
                    break;
            }
            if (DEBUG == 1)
                printf("\n");

            // nao precisamos de verificar mais, ja existe uma occorrencia
            if (podemos_mover_objecto == 0)
                break;
        }

        // nao precisamos de verificar mais, ja existe uma occorrencia
        if (podemos_mover_objecto == 0)
            break;
    }

    if (posicoes_a_mover > 0)
    {
        podemos_mover_objecto = 1;
    }

    if (DEBUG == 1)
        printf("Objecto %d (%d) => %d\n", posicao + 1, podemos_mover_objecto, posicoes_a_mover);

    printf("Objecto %d verificado -> x(%d,%d) y(%d,%d) => ", posicao + 1, xMin, xMax, yMin, yMax);
    if (podemos_mover_objecto == 0 || posicoes_a_mover == 0)
    {
        red();
        printf("NAO PODE SER MOVIDO\n");
        reset();
    }
    else
    {
        green();
        printf("move-se %d posicao(oes) para BAIXO\n", posicoes_a_mover);
        reset();
    }

    // move objecto para baixo
    if (podemos_mover_objecto == 1 && posicoes_a_mover > 0)
    {
        RECTANGULO *a = moveObjectoParaBaixo(objectos[posicao], posicoes_a_mover);
        objectos[posicao] = *a;
    }
}
void activaGravidade(RECTANGULO *objectos, int num_objectos)
{
    int objectos_resolvidos = 0;
    while (objectos_resolvidos < num_objectos)
    {
        for (int i = 0; i < num_objectos; i += 1)
            activaGravidadePorObjecto(objectos, i, num_objectos);
        objectos_resolvidos += 1;
    }
}

/* EOF */
