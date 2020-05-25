/*
** File: files.h
*/
#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#include "structures.h"

COMANDO *getComando(char *linha);
int readFileComandos(COMANDO *comandos[]);

#endif
/* EOF */
