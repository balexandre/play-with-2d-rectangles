/*
** File: create_and_move.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "create_and_move.h"

RECTANGULO *cria_objecto(int x, int y, int w, int h)
{
    /*
        x2,y2-----------x3,y3
          |                |
          |                |
        x0,y0-----------x1,y1
    */
    RECTANGULO *o = malloc(sizeof(RECTANGULO));

    o->x0 = x;
    o->y0 = y;
    o->x1 = x + w;
    o->y1 = y;
    o->x2 = x;
    o->y2 = y + h;
    o->x3 = x + w;
    o->y3 = y + h;

    o->largura = w;
    o->altura = h;
    return o;
}

RECTANGULO *moveObjectoParaBaixo(RECTANGULO objecto, int posicoes_a_mover)
{
    RECTANGULO *o = &objecto;
    o->y0 -= posicoes_a_mover;
    o->y1 -= posicoes_a_mover;
    o->y2 -= posicoes_a_mover;
    o->y3 -= posicoes_a_mover;
    return o;
}
RECTANGULO *moveObjectoParaEsquerda(RECTANGULO objecto, int posicoes_a_mover)
{
    RECTANGULO *o = &objecto;
    o->x0 -= posicoes_a_mover;
    o->x1 -= posicoes_a_mover;
    o->x2 -= posicoes_a_mover;
    o->x3 -= posicoes_a_mover;
    return o;
}
RECTANGULO *moveObjectoParaDireita(RECTANGULO objecto, int posicoes_a_mover)
{
    RECTANGULO *o = &objecto;
    o->x0 += posicoes_a_mover;
    o->x1 += posicoes_a_mover;
    o->x2 += posicoes_a_mover;
    o->x3 += posicoes_a_mover;
    return o;
}

RECTANGULO *rodaObjecto(RECTANGULO objecto, int largura_do_plano)
{
    RECTANGULO *o = &objecto;

    int x = objecto.y1;
    int y = largura_do_plano - objecto.x1;
    int w = objecto.altura;
    int h = objecto.largura;

    o->x0 = x;
    o->y0 = y;
    o->x1 = x + w;
    o->y1 = y;
    o->x2 = x;
    o->y2 = y + h;
    o->x3 = x + w;
    o->y3 = y + h;

    o->largura = w;
    o->altura = h;

    // o = cria_objecto(x, y, objecto.largura, objecto.altura);
    return o;
}
void rodaObjectos(RECTANGULO *objectos, int num_objectos, int largura_do_plano)
{
    for (int i = 0; i < num_objectos; i += 1)
    {
        RECTANGULO *a = rodaObjecto(objectos[i], largura_do_plano);
        objectos[i] = *a;

        printf("Objecto %d rodou 90 graus -> x(%d) y(%d), %dx%d\n",
               i + 1, objectos[i].x0, objectos[i].y0,
               objectos[i].largura, objectos[i].altura);
    }
}

int seleccionaObjecto(int x, int y, RECTANGULO *objectos, int num_objectos)
{
    int i, encontrado = 0;

    for (i = 0; i < num_objectos; i += 1)
    {
        RECTANGULO objecto = objectos[i];

        if (x >= objecto.x0 && x <= objecto.x1 
            && y >= objecto.y0 && y <= objecto.y2)
        {
            // na possica x,y existe um objecto desenhado
            encontrado = 1;
            break;
        }
    }

    // printf("Objecto %d foi seleccionado\n", i + 1);
    return encontrado > 0 ? i : -1;
}

/* EOF */
