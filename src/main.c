#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

typedef struct RECTANGULO
{
    int x0, y0, x1, y1, x2, y2, x3, y3;
    int largura, altura;
} RECTANGULO;

void green_bold() { printf("\033[1;32m"); }
void green() { printf("\033[0;32m"); }
void red() { printf("\033[1;31m"); }
void yellow() { printf("\033[1;33m"); }
void cyan() { printf("\033[0;36m"); }
void reset() { printf("\033[0m"); }

void imprimeTitulo(char *texto)
{
    green_bold();
    printf("\n***************************************\n");
    printf("%s", texto);
    reset();
}

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

RECTANGULO *rodaObjecto(RECTANGULO objecto, int largura_do_plano)
{
    /*
         6,9            17,9
        x2,y2-----------x3,y3       x0,y0-----------x2,y2
          |                |   -->   |                |
          |                |   -->   |                |
        x0,y0-----------x1,y1       x1,y1-----------x3,y3
         6,5            17,5        y0,w-0          
    */

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

// clear && gcc -Wall -Werror -o rectangles src/main.c && ./rectangles
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
