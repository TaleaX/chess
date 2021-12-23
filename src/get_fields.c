#include "../headers/basis.h"
#include <stdio.h>
#include <stdlib.h>

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

field   *get_king(field **board, int player_color)
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