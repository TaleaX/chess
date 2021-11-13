#include <stdio.h>
#include <stdlib.h>
#include "headers/basis.h"
#include "headers/rules.h"
#include "headers/init_game.h"
#include "headers/end_game.h"
#include "headers/game.h"

int    player_mode_2(field **board, int player)
{
    int     current_x;
    int     current_y;
    int     next_x;
    int     next_y;
    int     check_;
    field   prev_next;
    field   prev_current;
    field   *prev;
    field   *prev_opp_king;

    check_ = 0;
    while (1)
    {
        printf("From x y>\n");
        fflush(stdout);
        scanf("%d %d", &current_x, &current_y);
        printf("To x y>\n");
        fflush(stdout);
        scanf("%d %d", &next_x, &next_y);
        if (current_x < 0 || current_x > 7 || current_y < 0 || current_y > 7 || next_x < 0 || next_x > 7 || next_y < 0 || next_y > 7)
        {
            printf("invalid coordinates\n");
            continue ;
        }
        field   *current = get_field(board, current_x, current_y);
        field   *next = get_field(board, next_x, next_y);
        field   *opp_king = get_opponent_king(board, current->fig.color);
        if (is_valid_move(board, current, next) && player == current->fig.color)
        {
            prev_next = *next;
            prev_current = *current;
            move(current, next);
            if (check_ && check(board, prev, prev_opp_king))
            {
                printf("You are in check...you need to move out of it!\n");
                //printf("curent name %c,  next name %c, prev_current name %c, prev_next name %c !\n", current->fig.name, next->fig.name, prev_current.fig.name, prev_next.fig.name);
                reset(prev_current, prev_next, current, next);
                continue ;
            }
            check_ = 0;
            print_board(board);
        }
        else
        {
            printf("invalid move\n");
            continue ;
        }
        current = next;
        if (check(board, current, opp_king))
        {
            prev = current;
            prev_opp_king = opp_king;
            check_ = 1;
            if (checkmate(board, current, opp_king, current->fig.color))
            {
                printf("Checkmate: Player %d won\n", player);
                break;
            }
            printf("CHECK\n");
        }
        player = !player;
    }
}

/** TODO
 *  MOVE MUST NOT RESULT IN A CHECK POSITION
 *  DONT JUST CHECK CURRENT POSITION AND PREV POSITION FOR CHECK -> LOOK FOR ANY
 * **/