/*#include "../headers/basis.h"
#include "../headers/figure_rules.h"
#include "../headers/get_fields.h"
#include "../headers/check_way.h"
#include "../headers/game.h"
#include "../headers/end_game.h"
#include <stdio.h>*/
#include "../headers/basis.h"
#include "../headers/figure_rules.h"
#include "../headers/get_fields.h"
#include "../headers/check_way.h"
#include "../headers/game.h"

int is_valid_move(field **board, field *current, field *next, int defense)
{
    int     valid;

    valid = 0;
    if(!defense && current->fig.color == next->fig.color)
        return (0);
    if (current->x == next->x && current->y == next->y)
        return (0);
    if (current->fig.name == 'X')
        return (0);
    if (current->fig.name == 'P')
    {
        valid = check_pawn(current, next);
    }
    if (current->fig.name == 'R')
    {
        valid = check_rock(board, current, next);
    }
    if (current->fig.name == 'B')
    {
        valid = check_bishop(board, current, next);
    }
    if (current->fig.name == 'H')
    {
        valid = check_knight(board, current, next);
    }
    if (current->fig.name == 'Q')
    {
        valid = check_queen(board, current, next);
    }
    if (current->fig.name == 'K')
    {
        valid = check_king(board, current, next);
    }
    return (valid);
}

int check(field **board, field *king)
{
    int i;
    int j;

    i = 0;
    while(i < ROW)
    {
        j = 0;
        while (j < COL)
        {
            if (is_valid_move(board, &board[i][j], king, 0))
            {
                //printf("check valid move: x = %d, y = %d, name = %c, color = %d\n", board[i][j].x, board[i][j].y, board[i][j].fig.name, board[i][j].fig.color);
                //printf("check valid move: x = %d, y = %d, name = %c, color = %d\n", king->x, king->y, king->fig.name, king->fig.color);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int valid_castle(field **board, field *king, field *next)
{
    field   *rock = get_rock(board, king, next);
    field   *inter_step = &board[king->y][next->x - 1];
    field   prev_king = *king;
    field   prev_inter_step;

    //printf("king x = %d, king y = %d\n", king->x, king->y);
    if (check(board, king))
        return (0);
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

    if (king->x > next->x)
    {
        inter_step = &board[king->y][next->x + 1];
    }
    prev_inter_step = *inter_step;
    move(king, inter_step);
    if (check(board, inter_step))
    {
        reset(prev_king, prev_inter_step, king, inter_step);
        printf("you cannot castle through check\n");
        return (0);
    }
    reset(prev_king, prev_inter_step, king, inter_step);
    return (1);
}

int next_not_in_check(field **board, field *current, field *next, field *current_king)
{
    field  temp_c;
    field  temp_n;
    
    temp_c = *current;
    temp_n = *next;
    move(current, next);
    //why did I use this if statement again?
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

int checkmate(field **board, field *king)
{
    int     i;
    int     j;
    int     k;
    int     m;
    int     counter;
    int     check_;
    int     max_possible_pos;
    field   *king_neighbours;
    field   **players_figs;
    field   *current;
    figure  temp_fig;

    i = 0;
    counter = 0;
    max_possible_pos = 0;
    check_ = 0;
    m = 0;
    players_figs = get_players_figs(board, king->fig.color);
    while (*players_figs)
    {
        counter++;
        i = 0;
        while (i < ROW)
        {
            j = 0;
            while (j < COL)
            {
                if (is_valid_move(board, *players_figs, &board[i][j], 0) && next_not_in_check(board, *players_figs, &board[i][j], king))
                {
                    //printf("%c can be moved from %d %d to %d %d %c\n", (*players_figs)->fig.name, (*players_figs)->x, (*players_figs)->y, board[i][j].x, board[i][j].y, board[i][j].fig.name);
                    free(players_figs);
                    return (0);
                }
                j++;
            }
            i++;
        }
        players_figs++;
    }
    free(players_figs);
    return (1);
}
