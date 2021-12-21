//#include <stdio.h>
//#include <stdlib.h>
#include "../headers/basis.h"

void    move(field *current, field *next)
{
    next->fig.name = current->fig.name;
    next->fig.color = current->fig.color;
    next->fig.value = current->fig.value;
    next->empty = 0;
    next->fig.moved = 1;
    current->fig.name = 'X';
    current->fig.color = -1;
    current->fig.moved = -1;
    current->fig.value = -1;
    current->empty = 1;
}

void    reset(field prev_current, field prev_next, field *current, field *next)
{
    next->empty = prev_next.empty;
    next->fig = prev_next.fig;
    current->fig = prev_current.fig;
    current->empty = prev_current.empty;
}



void    change_fig(field **board, field *current)
{
    char    new_fig;
    char    *buffer = (char *)malloc(3);

    while (1)
    {
        if (current->fig.color == BLACK && current->y == 7 && current->fig.name == 'P')
        {
            printf("Enter letter of desired figure (capital letter):");
            fflush(stdout);
            fgets(buffer, 3, stdin);
            if (buffer[0] >= 'a' && buffer[0] <= 'z')
                buffer[0] -= 32;
            if (buffer[0] != 'P' && buffer[0] != 'H' && buffer[0] != 'R' && buffer[0] != 'B' && buffer[0] !='Q')
                continue ;
            current->fig.name = buffer[0];
        }
        else if (current->fig.color == WHITE && current->y == 0 && current->fig.name == 'P')
        {
            printf("Enter letter of desired figure (capital letter):");
            fflush(stdout);
            fgets(buffer, 3, stdin);
            if (buffer[0] >= 'a' && buffer[0] <= 'z')
                buffer[0] -= 32;
            if (buffer[0] != 'P' && buffer[0] != 'H' && buffer[0] != 'R' && buffer[0] != 'B' && buffer[0] !='Q')
                continue ;
            current->fig.name = buffer[0];
        }
        break ;
    }
}
