#include <stdio.h>
#include <stdlib.h>
#include "headers/basis.h"
#include "headers/rules.h"
#include "headers/end_game.h"
#include "headers/check_way.h"

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

field   *get_current_field(field **board, char fig_name, int player_color)
{
    int     i;
    int     j;
    
    i = 0;
    while (i < 8)
    {
        j = 0;
        while (j < 8)
        {
            if (board[i][j].fig.name == fig_name && board[i][j].fig.color == player_color)
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

field   **get_players_figs(field **board, int player_color)
{
    field   **figs;
    field   **ret;
    int     i;
    int     j;

    figs = (field **)malloc(sizeof(field *) * 17);
    ret = figs;
    i = 0;
    while (i < 17)
    {
        figs[i] = (field *)malloc(sizeof(field));
        i++;
    }
    i = 0;
    while (i < ROW)
    {
        j = 0;
        while (j < COL)
        {
            if (board[i][j].fig.color == player_color)
            {
                *figs = &board[i][j];
                figs++;
            }
            j++;
        }
        i++;
    }
    *figs = (void *)0;
    return (ret);
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

void    get_queen(field **board, field *current)
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

field   *get_rock(field **board, field *king, field *next)
{
    if (king->x < next->x)
        return (&board[king->y][7]);
    return (&board[king->y][0]);
}

int valid_castle(field **board, field *king, field *next)
{
    field *rock = get_rock(board, king, next);

    printf("king x = %d, king y = %d\n", king->x, king->y);
    if (king->fig.name != 'K' || king->fig.moved == 1 || rock->fig.moved == 1)
    {
        printf("king or rock moved\n");
        return (0);
    }
    if (ABS((king->x - next->x)) != 2 || king->y != next->y)
    {
        printf("next not possible for castle\n");
        return (0);
    }   
    if (!row_is_free(board, king->y, king->x, rock->x))
    {
        printf("rock x = %d, king x = %d, king y = %d, row isnt free\n", rock->x, king->x, king->y);
        return (0);
    }
    return (1);
}


