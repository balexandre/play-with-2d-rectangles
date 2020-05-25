/*
** File: printing.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "printing.h"
#include "structures.h"

char qualCaractereQueImprimePorPlano(RECTANGULO *plano, int x, int y)
{
    int altura = plano->altura;
    int largura = plano->largura;

    // cantos
    if (x == -1 && y == altura)
        return 'o';
    else if (x == largura && y == altura)
        return 'o';
    else if (x == largura && y == -1)
        return 'o';
    else if (x == -1 && y == -1)
        return 'o';
    // linha
    else if (x == -1 || x == largura)
        return '|';
    // coluna
    else if (y == altura || y == -1)
        return '-';
    // nada
    return ' ';
}
char qualCaractereQueImprimePorObjecto(RECTANGULO objecto, int x, int y)
{
    // interseccoes
    if ((x == objecto.x0 && y == objecto.y0) ||
        (x == objecto.x1 && y == objecto.y1) ||
        (x == objecto.x2 && y == objecto.y2) ||
        (x == objecto.x3 && y == objecto.y3))
    {
        return '+';
    }
    // linhas
    else if ((y == objecto.y0 || y == objecto.y2) && (x > objecto.x0 && x < objecto.x1))
    {
        return '-';
    }
    // colunas
    else if ((x == objecto.x0 || x == objecto.x1) && (y > objecto.y0 && y < objecto.y2))
    {
        return '|';
    }
    return ' ';
}

void desenha(RECTANGULO *area, RECTANGULO *objectos, int num_objectos)
{
    // especifica o que vai desenhar
    printf("Plano: %dx%d\n", area->largura, area->altura);
    for (int i = 0; i < num_objectos; i += 1)
    {
        RECTANGULO objecto = objectos[i];
        printf("Objecto %d: x(%d) y(%d), %dx%d\n",
               i + 1, objecto.x0, objecto.y0,
               objecto.largura, objecto.altura);
    }

    // desenha
    for (int y = area->altura; y >= -1; y -= 1) // de cima para baixo
    {
        for (int x = -1; x <= area->largura; x += 1) // da esquerda para a direita
        {
            // plano
            char plano_a_imprimir = qualCaractereQueImprimePorPlano(area, x, y);
            if (plano_a_imprimir != ' ')
            {
                cyan();
                printf("%c", plano_a_imprimir);
                reset();
            }
            else
            {
                // printf("x%d|y%d ", x, y);
                // objecto
                char caractere_a_imprimir = ' ';
                char *caracteres_a_imprimir = malloc(sizeof(char) * num_objectos);

                // recolhe todos as possibilidade de cada objecto para o ponto x,y
                for (int i = 0; i < num_objectos; i += 1)
                {
                    RECTANGULO objecto = objectos[i];
                    caracteres_a_imprimir[i] = qualCaractereQueImprimePorObjecto(objecto, x, y);
                }

                // verifica a prioridade do caracter (+ tem prioridade sobre os outros)
                for (int i = 0; i < num_objectos; i += 1)
                {
                    if (caracteres_a_imprimir[i] == '+')
                    {
                        caractere_a_imprimir = '+';
                        break;
                    }
                    if (caracteres_a_imprimir[i] != ' ')
                        caractere_a_imprimir = caracteres_a_imprimir[i];
                }

                // imprime os objectos
                if (caractere_a_imprimir == '+')
                    red();

                else if (caractere_a_imprimir == '-' || caractere_a_imprimir == '|')
                    yellow();

                // imprime o caracter certo
                printf("%c", caractere_a_imprimir);

                if (caractere_a_imprimir != ' ')
                    reset();

                // livra a memoria usada
                free(caracteres_a_imprimir);
            }
        }
        printf("\n");
    }
}

/* EOF */
