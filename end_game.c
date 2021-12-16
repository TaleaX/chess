#include <stdlib.h>
#include <stdio.h>
#include "headers/basis.h"
#include "headers/game.h"
#include "headers/get_fields.h"
#include "headers/validate.h"

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
            if (is_valid_move(board, &board[i][j], king))
            {
                printf("check valid move: x = %d, y = %d, name = %c, color = %d\n", board[i][j].x, board[i][j].y, board[i][j].fig.name, board[i][j].fig.color);
                printf("check valid move: x = %d, y = %d, name = %c, color = %d\n", king->x, king->y, king->fig.name, king->fig.color);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int checkmate(field **board, field *king, int player_color)
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
    players_figs = get_players_figs(board, player_color);
    while (*players_figs)
    {
        counter++;
        i = 0;
        while (i < ROW)
        {
            j = 0;
            while (j < COL)
            {
                if (is_valid_move(board, *players_figs, &board[i][j]) && next_not_in_check(board, *players_figs, &board[i][j], king))
                {
                    printf("%c can be moved from %d %d to %d %d %c\n", (*players_figs)->fig.name, (*players_figs)->x, (*players_figs)->y, board[i][j].x, board[i][j].y, board[i][j].fig.name);
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