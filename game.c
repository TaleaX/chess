#include <stdio.h>
#include "headers/basis.h"
#include "headers/rules.h"

field   *get_field(field **board, int x, int y)
{
    int     i;
    int     j;
    
    i = 0;
    while (i < 8)
    {
        j = 0;
        while (j < 8)
        {
            if (board[i][j].x == x && board[i][j].y == y)
                return (&board[i][j]);
            j++;
        }
        i++;
    }
    return ((void *)0);
}

field   *get_opponent_king(field **board, int player_color)
{
    int     i;
    int     j;
    
    i = 0;
    while (i < 8)
    {
        j = 0;
        while (j < 8)
        {
            if (board[i][j].fig.name == 'K' && board[i][j].fig.color != player_color)
                return (&board[i][j]);
            j++;
        }
        i++;
    }
    return ((void *)0);
}

void    move(field *current, field *next)
{
    next->fig.name = current->fig.name;
    next->fig.color = current->fig.color;
    next->empty = 0;
    next->fig.moved = 1;
    current->fig.name = 'X';
    current->fig.color = -1;
    current->empty = 1;
}

void    reset(field prev_current, field prev_next, field *current, field *next)
{
    next->fig.name = prev_next.fig.name;
    next->fig.color = prev_next.fig.color;
    next->empty = prev_next.empty;
    next->fig.moved = prev_next.fig.moved;
    current->fig.name = prev_current.fig.name;
    current->fig.color = prev_current.fig.color;
    current->empty = prev_current.empty;
}

int     is_valid_move(field **board, field *current, field *next)
{
    int     valid;
    
    valid = 0;
    if(current->fig.color == next->fig.color)
        return (0);
    if (current->x == next->x && current->y == next->y)
        return (0);
    if (current->fig.name == 'X')
        return (0);
    if (current->fig.name == 'P')
    {
        valid = check_pawn(current, next);
        //printf("pawn valid = %d\n", valid);
    }
    if (current->fig.name == 'R')
    {
        valid = check_rock(board, current, next);
        //printf("rock valid = %d\n", valid);
    }
    if (current->fig.name == 'B')
    {
        valid = check_bishop(board, current, next);
        //printf("bishop valid = %d\n", valid);
    }
    if (current->fig.name == 'H')
    {
        valid = check_knight(board, current, next);
        //printf("knight valid = %d\n", valid);
    }
    if (current->fig.name == 'Q')
    {
        valid = check_queen(board, current, next);
        //printf("queen valid = %d\n", valid);
    }
    if (current->fig.name == 'K')
    {
        valid = check_king(board, current, next);
        //printf("king valid = %d\n", valid);
    }
    return (valid);
}
