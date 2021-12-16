#include <stdio.h>
#include <stdlib.h>
#include "headers/basis.h"
#include "headers/rules.h"
#include "headers/end_game.h"
#include "headers/check_way.h"

void    move(field *current, field *next)
{
    next->fig.name = current->fig.name;
    next->fig.color = current->fig.color;
    next->empty = 0;
    next->fig.moved = 1;
    current->fig.name = 'X';
    current->fig.color = -1;
    current->fig.moved = -1;
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

    if (current->fig.color == BLACK && current->y == 7 && current->fig.name == 'P')
    {
        printf("Enter letter of desired figure (capital letter):");
        fflush(stdout);
        scanf("%c", &new_fig);
        current->fig.name = new_fig;
    }
    else if (current->fig.color == WHITE && current->y == 0 && current->fig.name == 'P')
    {
        printf("Enter letter of desired figure (capital letter):");
        fflush(stdout);
        scanf("%c", &new_fig);
        current->fig.name = new_fig;
    }
}

int next_not_in_check(field **board, field *current, field *next, field *current_king)
{
    field  temp_c;
    field  temp_n;
    
    temp_c = *current;
    temp_n = *next;
    move(current, next);
    if (next->fig.name == 'K')
    {
        if (check(board, next))
        {
            reset(temp_c, temp_n, current, next);
            return (0);
        }
    }
    else if (check(board, current_king)) //if current != king, checks if the movement of current figure results in check of your king
    {
        reset(temp_c, temp_n, current, next);
        return (0);
    }
    reset(temp_c, temp_n, current, next);
    return (1);
}
