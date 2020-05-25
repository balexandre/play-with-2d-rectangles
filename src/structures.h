/*
** File: structures.h
*/
#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef struct t_rectangulo RECTANGULO;
struct t_rectangulo
{
    int x0, y0, x1, y1, x2, y2, x3, y3;
    int largura, altura;
};

enum TIPO_COMANDO {
    CREATE = 1,
    MOVE_LEFT = 2,
    MOVE_RIGHT = 3,
    ROTATE = 4,
    AREA = 5
};

typedef struct t_comando COMANDO;
struct t_comando
{
    enum TIPO_COMANDO tipo;
    int x, y, w, h, p;
};

#endif
/* EOF */
