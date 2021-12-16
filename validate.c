#include "headers/basis.h"
#include "headers/rules.h"
#include "headers/get_fields.h"
#include "headers/check_way.h"
#include "headers/game.h"
#include "headers/end_game.h"
#include <stdio.h>

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

int valid_castle(field **board, field *king, field *next)
{
    field   *rock = get_rock(board, king, next);
    field   *inter_step = &board[king->y][next->x - 1];
    field   prev_king = *king;
    field   prev_inter_step;

    printf("king x = %d, king y = %d\n", king->x, king->y);
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

