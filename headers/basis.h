#ifndef BOARD_H
# define BOARD_H
# define FIELDS 64
# define EMPTY 0
# define BLACK 0
# define WHITE 1
# define ABS(Value) (Value < 0 ? -Value : Value)

typedef struct f
{
    char    name;
    int     color;
    int     moved;
}   figure;

typedef struct s
{
    int     x;
    int     y;
    int     empty;
    figure  fig;
}   field;

#endif