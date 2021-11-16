#include <stdlib.h>
#include <stdio.h>
#include "headers/basis.h"
#include "headers/game.h"

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
                //printf("check valid move: x = %d, y = %d\n", board[i][j].x, board[i][j].y);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

field   *get_other_players_figs(field **board, int other_player_color)
{
    field   *figs;
    field   *ret;
    int     i;
    int     j;
    int     found;
    int     m;

    figs = (field *)malloc(sizeof(field) * 17);
    ret = figs;
    i = 0;
    m = 0;
    printf("in here\n");
    found = 0;
    while (i < ROW)
    {
        j = 0;
        while (j < COL)
        {
            if (board[i][j].fig.color == other_player_color)
            {
                found += 1;
                *figs = board[i][j];
                figs++;
            }
            j++;
        }
        i++;
    }
    figs->empty = -1;
    return (ret);
}

int checkmate(field **board, field *king, int other_player_color)
{
    int     i;
    int     j;
    int     k;
    int     m;
    int     counter;
    int     check_;
    int     max_possible_pos;
    field   *king_neighbours;
    field   *players_figs;
    field   *current;
    figure  temp_fig;

    i = 0;
    counter = 0;
    max_possible_pos = 0;
    check_ = 0;
    m = 0;
    printf("in here\n");
    players_figs = get_other_players_figs(board, other_player_color);
    printf("king x %d, y %d\n", king->x, king->y);
    while (players_figs->empty != -1)
    {
        counter++;
        i = 0;
        while (i < ROW)
        {
            j = 0;
            while (j < COL)
            {
                //printf("current: name = %c, x = %d, y = %d\nnext: name = %c, x = %d, y = %d\n\n", players_figs->fig.name, players_figs->x, players_figs->y, board[i][j].fig.name, board[i][j].x, board[i][j].y);
                if (is_valid_move(board, players_figs, &board[i][j]))
                {
                    //printf("valid move: name = %c, x = %d, y = %d\n", board[i][j].fig.name, board[i][j].x, board[i][j].y);
                }
                if (is_valid_move(board, players_figs, &board[i][j]))
                {
                    current = get_field(board, players_figs->x, players_figs->y);
                    if (next_not_in_check(board, current, &board[i][j], king))
                    {
                        free(players_figs);
                        return (0);
                    }
                }
                j++;
            }
            i++;
        }
        players_figs++;
    }
    free(players_figs);
    printf("counter %d\n", counter);
    return (1);
}