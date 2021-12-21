#include <stdio.h>
#include "../headers/basis.h"

int row_is_free(field **board, int row, int start, int end)
{
    if (start < end)
        start++;
    else if (start > end)
        start--;
    while (start != end)
    {
        if (!board[row][start].empty)
            return (0);
        if (start > end)
            start--;
        if (start < end)
            start++;
    }
    return (1);
}

int col_is_free(field **board, int col, int start, int end)
{
    if (start < end)
        start++;
    else if (start > end)
        start--;
    while (start != end)
    {
        if (!board[start][col].empty)
            return (0);
        if (start > end)
            start--;
        if (start < end)
            start++;
    }
    return (1);
}

int diagonal_is_free(field **board, field current, field next)
{
    if (current.x < next.x)
        current.x++;
    else if (current.x > next.x)
        current.x--;
    if (current.y < next.y)
        current.y++;
    else if (current.y > next.y)
        current.y--;
    while (current.x != next.x || current.y != next.y)
    {
        if (!board[current.y][current.x].empty)
            return (0);
        if (current.x > next.x)
            current.x--;
        if (current.x < next.x)
            current.x++;
        if (current.y > next.y)
            current.y--;
        if (current.y < next.y)
            current.y++;
    }
    return (1);
}
