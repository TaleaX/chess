#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "headers/basis.h"
#include "headers/rules.h"
#include "headers/rules.h"

int check(field **board, field *current, field *king)
{
    if (is_valid_move(board, current, king))
        return (1);
    return (0);
}

field   *opponent_king_neighbours(field **board, int player_color)
{
    int     i;
    int     j;
    int     n;
    int     found_king;
    field   *king_neighbours;
    field   *ret;

    king_neighbours = (field *)malloc(sizeof(field) * 10);
    ret = king_neighbours;
    i = 0;
    n = 0;
    found_king = 0;
    while (i < 8)
    {
        j = 0;
        while (j < 8)
        {
            if (board[i][j].fig.name == 'K' && board[i][j].fig.color != player_color)
            {
                found_king = 1;
                while (n < 9)
                {
                    if (((i - 1) < 0 && (n == 0 || n == 1 || n == 2))
                        || ((i + 1 > 7) && (n == 6 || n == 7 || n == 8))
                        || j + (n % 3 - 1) > 7 || j + (n % 3 - 1) < 0)
                    {
                        n++;
                        continue ;
                    }
                    if (n == 0 || n == 1 || n == 2)
                        *king_neighbours = board[i - 1][j + (n % 3 - 1)];
                    else if(n == 3 || n == 4 || n == 5)
                        *king_neighbours = board[i][j + (n % 3 - 1)];
                    else
                        *king_neighbours = board[i + 1][j + (n % 3 - 1)];
                    king_neighbours++;
                    n++;
                }
                break;
            }
            j++;
        }
        if (found_king)
            break;
        i++;
    }
    king_neighbours->empty = -1;
    return (ret);
}

int checkmate(field **board, field *current, field *king, int player_color)
{
    int     i;
    int     j;
    int     counter;
    int     check_;
    int     max_possible_pos;
    field   *king_neighbours;
    figure  temp_fig;

    king_neighbours = opponent_king_neighbours(board, player_color);
    i = 0;
    counter = 0;
    max_possible_pos = 0;
    check_ = 0;
    while (king_neighbours->empty != -1)
    {
        check_ = 0;
        if (is_valid_move(board, king, king_neighbours))
        {
            max_possible_pos++;
            temp_fig = king_neighbours->fig;
            king_neighbours->fig = king->fig;
            i = 0;
            while (i < 8)
            {
                j = 0;
                while (j < 8)
                {
                    if (is_valid_move(board, &board[i][j], current))
                    {
                        printf("fig name = %c\n", board[i][j].fig.name);
                        return (0);
                    }
                    if (check(board, &board[i][j], king_neighbours))
                    {
                        if (!check_)
                            counter++;
                        check_ = 1;
                    }
                    j++;
                }
                i++;
            }
            king_neighbours->fig = temp_fig;
        }
        king_neighbours++;
    }
    free(king_neighbours);
    printf("max = %d, counter = %d", max_possible_pos, counter);
    if (counter == max_possible_pos)
        return (1);
    return (0);
}