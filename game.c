#include <stdio.h>
#include "headers/basis.h"
#include "headers/rules.h"
#include "headers/end_game.h"

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

field   *get_current_king(field **board, int player_color)
{
    int     i;
    int     j;
    
    i = 0;
    while (i < 8)
    {
        j = 0;
        while (j < 8)
        {
            if (board[i][j].fig.name == 'K' && board[i][j].fig.color == player_color)
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

int is_valid_move(field **board, field *current, field *next)
{
    int     valid;

    valid = 0;
    if (current->fig.name == 'R' && next->fig.name == 'K')
    {
        printf("cR x = %d, y = %d, empty = %d, nK x = %d, y = %d, empty = %d\n", current->x, current->y, current->empty, next->x, next->y, next->empty);
    }
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

int next_not_in_check(field **board, field *current, field *next, field *current_king)
{
    field  temp_c;
    field  temp_n;
    
    printf("current fig name %c, current fig x %d, current fig y %d, next name %c, next x %d, next y %d\n", current->fig.name, current->x, current->y, next->fig.name, next->x, next->y);
    temp_c = *current;
    temp_n = *next;
    move(current, next);
    /*next->fig.color = current->fig.color;
    next->fig.name = current->fig.name;
    next->empty = 0;
    current->fig = empty;
    current->empty = 1;*/
    //checks if current == current king and returns 0 if king stands in check after he has moved to the desired position
    printf("current fig name %c, current fig x %d, current fig y %d, next name %c, next x %d, next y %d\n", current->fig.name, current->x, current->y, next->fig.name, next->x, next->y);
    printf("current empty = %d, next empty = %d\n", current->empty, next->empty);
    if (next->fig.name == 'K')
    {
        //board[current->y][current->x].empty = 1;
        //board[current->y][current->x].fig.name = 'X';
        printf("board: x = %d, y = %d, empyt = %d, name = %c\n", board[0][3].x, board[0][3].y, board[0][3].empty, board[0][3].fig.name);
        printf("board: x = %d, y = %d, empyt = %d, name = %c\n", board[0][2].x, board[0][2].y, board[0][2].empty, board[0][2].fig.name);
        printf("board: x = %d, y = %d, empty = %d, name = %c\n", board[0][4].x, board[0][4].y, board[0][4].empty, board[0][4].fig.name);
        if (check(board, next))
        {
            printf("passed check *next");
            reset(temp_c, temp_n, current, next);
            /*current->fig = temp_c;
            current->empty = 0;
            next->fig = temp_n.fig;
            next->empty = temp_n.empty;*/
            return (0);
        }
    }
    else if (check(board, current_king)) //if current != king, checks if the movement of current figure results in check of your king
    {
        reset(temp_c, temp_n, current, next);
        /*current->fig = temp_c;
        current->empty = 0;
        next->fig = temp_n.fig;
        next->empty = temp_n.empty;*/
        return (0);
    }
    /*current->fig = temp_c;
    current->empty = 0;
    next->fig = temp_n.fig;
    next->empty = temp_n.empty;*/
    reset(temp_c, temp_n, current, next);
    return (1);
}