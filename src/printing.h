/*
** File: printing.h
*/
#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED

#include "structures.h"

char qualCaractereQueImprimePorPlano(RECTANGULO *plano, int x, int y);
char qualCaractereQueImprimePorObjecto(RECTANGULO objecto, int x, int y);
void desenha(RECTANGULO *area, RECTANGULO *objectos, int num_objectos);

#endif

/*
** References
** - adding color to text
**   http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/
*/


/* EOF */
