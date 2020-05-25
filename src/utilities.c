/*
** File: utilities.c
*/
#include <stdio.h>
#include "utilities.h"

// print green bold
void green_bold() { printf("\033[1;32m"); }
void green() { printf("\033[0;32m"); }
void red() { printf("\033[1;31m"); }
void yellow() { printf("\033[1;33m"); }
void cyan() { printf("\033[0;36m"); }
void reset() { printf("\033[0m"); }

/* prints header in green bold */
void imprimeTitulo(char *texto)
{
    green_bold();
    printf("\n***************************************\n");
    printf("%s", texto);
    reset();
}
/* EOF */
