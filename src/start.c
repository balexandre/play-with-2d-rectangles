/*
** File: start.c
*/
#include <stdio.h>
#include <stdlib.h>

#include "start.h"
#include "utilities.h"

void com_menu_de_opcoes()
{
    system("cls||clear"); // limpa o ecran
    int menu = 1, x, y, w, h, p;
    int posicaoObjSeleccionado = -1;

    int num_objectos = 0;
    RECTANGULO *area = cria_objecto(0, 0, 80, 25);
    RECTANGULO *objectos = malloc(sizeof(*objectos));

    while (menu != 0)
    {
        printf("--------------------------------------------\n");
        green(); printf("[PLANO]"); reset();
        printf(" %dx%d\n", area->largura, area->altura);
        for (int iObj = 0; iObj < num_objectos; iObj += 1)
        {
            RECTANGULO obj = objectos[iObj];
            green(); printf("[RECTANGULO %d]", iObj + 1); reset();
            printf(" x(%d) y(%d), %dx%d\n",
                   obj.x0, obj.y0, obj.largura, obj.altura);
        }
        printf("--------------------------------------------\n");

        printf("digite '0' para SAIR\n");
        printf("digite '1' para modificar PLANO inicial\n");
        printf("digite '2' para CRIAR rectangulo\n");
        printf("digite '3' para MOVER rectangulo para a ESQUERDA (<<)\n");
        printf("digite '4' para MOVER rectangulo para a DIREITA (>>)\n");
        printf("digite '5' para RODAR conteúdo do plano\n");
        printf("digite '6' para MOSTRAR plano com rectangulos\n");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            printf("\n[DEFINIR plano]");
            printf("\n digite largura: ");
            scanf("%d", &w);
            printf(" digite altura: ");
            scanf("%d", &h);
            area = cria_objecto(0, 0, w, h);
            system("cls||clear"); // limpa o ecran
            break;
        case 2:
            printf("\n[CRIAR rectangulo]");
            printf("\n digite a posicao inicial x: ");
            scanf("%d", &x);
            printf(" digite a posicao inicial y: ");
            scanf("%d", &y);
            printf(" digite largura: ");
            scanf("%d", &w);
            printf(" digite altura: ");
            scanf("%d", &h);

            RECTANGULO *objecto = cria_objecto(x, y, w, h);
            num_objectos += 1; // aumenta o numero total de objectos
            objectos = realloc(objectos, sizeof(*objectos) * num_objectos);
            objectos[num_objectos - 1] = *objecto;
            activaGravidade(objectos, num_objectos);

            system("cls||clear"); // limpa o ecran
            break;
        case 3:
            printf("\n[MOVER rectangulo ESQUERDA (<<)]");
            printf("\n digite a posicao x: ");
            scanf("%d", &x);
            printf(" digite a posicao y: ");
            scanf("%d", &y);
            printf(" digite as posicoes a mover: ");
            scanf("%d", &p);

            posicaoObjSeleccionado = seleccionaObjecto(x, y, objectos, num_objectos);
            if (posicaoObjSeleccionado >= 0)
            {
                RECTANGULO *a = moveObjectoParaEsquerda(objectos[posicaoObjSeleccionado], p);
                objectos[posicaoObjSeleccionado] = *a;
            }
            activaGravidade(objectos, num_objectos);

            system("cls||clear"); // limpa o ecran
            break;
        case 4:
            printf("\n[MOVER rectangulo DIREITA (>>)]");
            printf("\n digite a posicao x: ");
            scanf("%d", &x);
            printf(" digite a posicao y: ");
            scanf("%d", &y);
            printf(" digite as posicoes a mover: ");
            scanf("%d", &p);

            posicaoObjSeleccionado = seleccionaObjecto(x, y, objectos, num_objectos);
            if (posicaoObjSeleccionado >= 0)
            {
                RECTANGULO *a = moveObjectoParaDireita(objectos[posicaoObjSeleccionado], p);
                objectos[posicaoObjSeleccionado] = *a;
            }

            activaGravidade(objectos, num_objectos);
            system("cls||clear"); // limpa o ecran
            break;
        case 5:
            imprimeTitulo("Plano rodado 90 graus\n\n");
            rodaObjectos(objectos, num_objectos, area->largura);
            activaGravidade(objectos, num_objectos);
            break;
        case 6:
            imprimeTitulo("Plano com gravidade activada\n\n");
            desenha(area, objectos, num_objectos);
            break;
        }
    }

    free(area);
    free(objectos);
}
void com_instrucoes()
{
    system("cls||clear"); // limpa o ecran

    int num_objectos = 0;
    // area do plano
    RECTANGULO *area = cria_objecto(0, 0, 30, 20);
    // rectangulos
    RECTANGULO *objecto1 = cria_objecto(1, 3, 12, 5);
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

    free(area);
    free(objectos);
    free(objecto1);
    free(objecto2);
    free(objecto3);
}
void le_o_ficheiro()
{
    system("cls||clear"); // limpa o ecran
    
    int num_objectos = 0;
    int posicaoObjSeleccionado = -1;
    RECTANGULO *area = cria_objecto(0, 0, 80, 25);
    RECTANGULO *objectos = malloc(sizeof(*objectos));

    COMANDO *comandos[99];
    int numComandos = readFileComandos(comandos);

    // mostra comandos
    imprimeTitulo("Comandos recebidos pelo ficheiro\n\n");

    for (int i = 0; i < numComandos; i += 1)
    {
        COMANDO *comando = comandos[i];

        if (comando->tipo == AREA)
        {
            printf("COMANDO %d => AREA %dx%d\n",
                   i + 1, comando->w, comando->h);

            area = cria_objecto(0, 0, comando->w, comando->h);
        }
        else if (comando->tipo == CREATE)
        {
            printf("COMANDO %d => CREATE x(%d) y(%d) %dx%d\n",
                   i + 1, comando->x, comando->y, comando->w, comando->h);

            RECTANGULO *objecto = cria_objecto(comando->x, comando->y, comando->w, comando->h);
            num_objectos += 1; // aumenta o numero total de objectos
            objectos = realloc(objectos, sizeof(*objectos) * num_objectos);
            objectos[num_objectos - 1] = *objecto;
            activaGravidade(objectos, num_objectos);
        }
        else if (comando->tipo == MOVE_LEFT)
        {
            printf("COMANDO %d => MOVE LEFT x(%d) y(%d) %d posicoes\n",
                   i + 1, comando->x, comando->y, comando->p);

            posicaoObjSeleccionado = seleccionaObjecto(comando->x, comando->y, objectos, num_objectos);
            if (posicaoObjSeleccionado >= 0)
            {
                RECTANGULO *a = moveObjectoParaEsquerda(objectos[posicaoObjSeleccionado], comando->p);
                objectos[posicaoObjSeleccionado] = *a;
            }
            activaGravidade(objectos, num_objectos);
        }
        else if (comando->tipo == MOVE_RIGHT)
        {
            printf("COMANDO %d => MOVE RIGHT x(%d) y(%d) %d posicoes\n",
                   i + 1, comando->x, comando->y, comando->p);

            posicaoObjSeleccionado = seleccionaObjecto(comando->x, comando->y, objectos, num_objectos);
            if (posicaoObjSeleccionado >= 0)
            {
                RECTANGULO *a = moveObjectoParaDireita(objectos[posicaoObjSeleccionado], comando->p);
                objectos[posicaoObjSeleccionado] = *a;
            }
            activaGravidade(objectos, num_objectos);
        }
        else if (comando->tipo == ROTATE)
        {
            printf("COMANDO %d => ROTATE\n", i + 1);
            rodaObjectos(objectos, num_objectos, area->largura);
            activaGravidade(objectos, num_objectos);
        }
    }

    imprimeTitulo("Plano com gravidade activada\n\n");
    desenha(area, objectos, num_objectos);

    free(area);
    free(objectos);
}

/* EOF */
