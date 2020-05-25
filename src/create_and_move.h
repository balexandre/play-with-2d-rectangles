/*
** File: create_and_move.h
*/
#ifndef CREATEMOVE_H_INCLUDED
#define CREATEMOVE_H_INCLUDED

#include "structures.h"

RECTANGULO *cria_objecto(int x, int y, int w, int h);

RECTANGULO *moveObjectoParaBaixo(RECTANGULO objecto, int posicoes_a_mover);
RECTANGULO *moveObjectoParaEsquerda(RECTANGULO objecto, int posicoes_a_mover);
RECTANGULO *moveObjectoParaDireita(RECTANGULO objecto, int posicoes_a_mover);

RECTANGULO *rodaObjecto(RECTANGULO objecto, int largura_do_plano);
void rodaObjectos(RECTANGULO *objectos, int num_objectos, int largura_do_plano);

int seleccionaObjecto(int x, int y, RECTANGULO *objectos, int num_objectos);

#endif
/* EOF */
