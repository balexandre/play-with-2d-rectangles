/*
** File: main.c
*/
#include <stdio.h>
#include <stdlib.h>

#include "start.h"
#include "utilities.h"

// clear && gcc -Wall -Werror -o rectangles src/*.c && ./rectangles
int main(int argc, char *argv[])
{
    int menuInicial = 1;

    green_bold(); printf("Opcao 1"); reset();
    printf(" (digite '1'): Ver programa com menu\n");
    printf(" > mostra um menu onde pode criar e mover objectos assim como definir o plano\n\n");
    green_bold(); printf("Opcao 2"); reset();
    printf(" (digite '2'): Ver programa lendo ficheiro de comandos\n");
    printf(" > executa os comandos do ficheiro './files/commands.txt'\n\n");
    green_bold(); printf("Opcao 3"); reset();
    printf(" (digite '3'): Ver programa com inscrucoes pre-definidas\n");
    printf(" > cria um plano 30x20\n");
    printf(" > cria um rectangulo 1,3+12,5\n");
    printf(" > cria um rectangulo 6,5+11,3\n");
    printf(" > cria um rectangulo 15,10+6,3\n");
    printf(" > imprime posicoes originais\n");
    printf(" > activa gravidade\n");
    printf(" > imprime novas posicoes\n");
    printf(" > roda o conteudo do plano 90 graus\n");
    printf(" > imprime novas posicoes originais\n");
    printf(" > activa gravidade\n");
    printf(" > imprime novas posicoes\n");
    printf(" > roda o conteudo do plano 90 graus\n");
    printf(" > imprime novas posicoes originais\n");
    printf(" > activa gravidade\n");
    printf(" > imprime novas posicoes\n");
    green_bold(); printf("Digite qualquer outro número ou Ctrl+C para terminar\n"); reset();
    scanf("%d", &menuInicial);

    if (menuInicial == 1)
        com_menu_de_opcoes();
    else if (menuInicial == 2)
        le_o_ficheiro();
    else if (menuInicial == 3)
        com_instrucoes();

    exit(EXIT_SUCCESS);
}

/* EOF */
