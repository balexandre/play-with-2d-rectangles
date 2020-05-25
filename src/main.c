#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "create_and_move.h"
#include "gravity.h"
#include "printing.h"

// clear && gcc -Wall -Werror -o rectangles src/*.c && ./rectangles
int main(int argc, char *argv[])
{
    int num_objectos = 0;

    // area do plano
    RECTANGULO *area = cria_objecto(0, 0, 30, 20);

    // rectangulos
    RECTANGULO *objecto1 = cria_objecto(1, 1, 12, 5);
    num_objectos += 1;
    RECTANGULO *objecto2 = cria_objecto(6, 5, 11, 3);
    num_objectos += 1;
    RECTANGULO *objecto3 = cria_objecto(15, 10, 6, 3);
    num_objectos += 1;

    // lista de rectangulos
    RECTANGULO *objectos = malloc(sizeof(*objectos) * num_objectos);
    objectos[0] = *objecto1;
    objectos[1] = *objecto2;
    objectos[2] = *objecto3;

    // desenhamos as posicoes originais que foram introduzidas
    imprimeTitulo("Posicoes originais\n\n");
    desenha(area, objectos, num_objectos);

    // activamos a gravidade
    imprimeTitulo("Activar gravidade\n\n");
    activaGravidade(objectos, num_objectos);

    // desenhamos agora, com a gravidade activada
    imprimeTitulo("Com gravidade activada\n\n");
    desenha(area, objectos, num_objectos);

    // #region roda +90 graus
    // rodamos o conteudo do plano 90 graus para a direita
    imprimeTitulo("Roda +90 graus\n\n");
    rodaObjectos(objectos, num_objectos, area->largura);

    // desenhamos a rotacao
    imprimeTitulo("Com rotacao a +90 graus\n\n");
    desenha(area, objectos, num_objectos);

    // activamos a gravidade
    imprimeTitulo("Activar gravidade\n\n");
    activaGravidade(objectos, num_objectos);

    // desenhamos a rotacao com a gravidade activada
    imprimeTitulo("Com rotacao a +90 graus e gravidade activada\n\n");
    desenha(area, objectos, num_objectos);
    // #endregion

    // #region roda +90 graus
    // rodamos o conteudo do plano 90 graus para a direita
    imprimeTitulo("Roda +90 graus\n\n");
    rodaObjectos(objectos, num_objectos, area->largura);

    // desenhamos a rotacao
    imprimeTitulo("Com rotacao a +90 graus\n\n");
    desenha(area, objectos, num_objectos);

    // activamos a gravidade
    imprimeTitulo("Activar gravidade\n\n");
    activaGravidade(objectos, num_objectos);

    // desenhamos a rotacao com a gravidade activada
    imprimeTitulo("Com rotacao a +90 graus e gravidade activada\n\n");
    desenha(area, objectos, num_objectos);
    // #endregion

    exit(EXIT_SUCCESS);
}

/*
** References
** - adding color to text
**   http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/
*/
