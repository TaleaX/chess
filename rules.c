#include <stdio.h>
#include "headers/basis.h"
#include "headers/check_way.h"



int     check_rock(field **board, field *current, field *next)
{
    if (next->x != current->x && next->y != current->y)
        return (0);
    if (next->x != current->x)
        return (row_is_free(board, current->y, current->x, next->x));
    else if (next->y != current->y)
        return (col_is_free(board, current->x, current->y, next->y));
    return (1);
}

int     check_knight(field **board, field *current, field *next)
{
    if ((ABS((current->x - next->x)) != 1 || ABS((current->y - next->y)) != 2) && 
        (ABS((current->x - next->x)) != 2 || ABS((current->y - next->y)) != 1))
        return (0);
    return (1);
}

int     check_bishop(field **board, field *current, field *next)
{
    if (next->x == current->x || next->y == current->y)
        return (0);
    if (ABS((next->x - current->x)) != ABS((next->y - current->y))) //if movement in x direction doesnt equal movement in y direction return false
        return (0);
    return (diagonal_is_free(board, *current, *next));
}

int     check_queen(field **board, field *current, field *next)
{
    if ((ABS((next->x - current->x)) != ABS((next->y - current->y))) && (next->x != current->x && next->y != current->y))
        return (0);
    if (ABS((next->x - current->x)) == ABS((next->y - current->y)))
        return (diagonal_is_free(board, *current, *next));
    else if (next->x != current->x)
        return (row_is_free(board, current->y, current->x, next->x));
    return (col_is_free(board, current->x, current->y, next->y));
}

int     check_king(field **board, field *current, field *next)
{
    if (ABS((next->x - current->x)) > 1 || ABS((next->y - current->y)) > 1)
        return (0);
    return (1);
}

int     check_pawn(field *current, field *next)
{
    if (current->fig.color == WHITE)
    {
        if (next->y > current->y) //checks for backward movements
            return (0);
        if (current->y - next->y > 2 && !current->fig.moved) //can move 2 fields at max if pawn is moved for first time
            return (0);
        if (current->y - next->y > 1 && current->fig.moved) //can move 1 field at max
            return (0);
        if (!next->empty && next->fig.color == WHITE) //cannot go further when there is a white figure
            return (0);
        
    }
    else
    {
        if (next->y < current->y) //checks for backward movements
            return (0);
        if (next->y - current->y > 2 && !current->fig.moved) //can move 2 fields alomg y achsis at max if pawn is moved for first time
            return (0);
        if (next->y - current->y > 1 && current->fig.moved) //can move 1 field along y achsis at max
            return (0);
        if (!next->empty && next->fig.color == BLACK) //cannot go further when there is a white figure
            return (0);
    }
    if (next->y == current->y) //cannot move on x achse
            return (0);
    if (!next->empty && next->x == current->x) //cannot schlagen a figure when pawn moves straight
            return (0);
    if (next->empty && next->x != current->x) //cannot move diagonal when field is empty
        return (0);
    if (next->x - current->x > 1 || next->x - current->x < -1 ) // cannot more than one field diagonal
            return (0);
    return (1);
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
        printf("pawn valid = %d\n", valid);
    }
    if (current->fig.name == 'R')
    {
        valid = check_rock(board, current, next);
        printf("rock valid = %d\n", valid);
    }
    if (current->fig.name == 'B')
    {
        valid = check_bishop(board, current, next);
        printf("bishop valid = %d\n", valid);
    }
    if (current->fig.name == 'H')
    {
        valid = check_knight(board, current, next);
        printf("knight valid = %d\n", valid);
    }
    if (current->fig.name == 'Q')
    {
        valid = check_queen(board, current, next);
        printf("queen valid = %d\n", valid);
    }
    if (current->fig.name == 'K')
    {
        valid = check_king(board, current, next);
        printf("king valid = %d\n", valid);
    }
    else
    {
        printf("%d %d\n", current->x, current->y);
    }
    return (valid);
}