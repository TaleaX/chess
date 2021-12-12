#ifndef BOARD_H
# define BOARD_H
# define EMPTY 0
# define BLACK 0
# define ROW 8
# define COL 8
# define WHITE 1
# define VALID_CASTLE 2
# define BOLD "\x1b[1m"
# define RED "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define ANSI_WHITE    "\x1b[37m"
# define CYAN_BACKGROUND "\x1b[46m"
# define STYLE_RESET "\x1b[0m"
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