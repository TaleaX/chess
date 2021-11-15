#include <stdio.h>
#include <stdlib.h>
#include "headers/basis.h"
#include "headers/rules.h"
#include "headers/init_game.h"
#include "headers/end_game.h"
#include "headers/game.h"

int player_mode_2(field **board, int player)
{
    int         current_x;
    int         current_y;
    int         next_x;
    int         next_y;
    field       prev_next;
    field       prev_current;
    field       *prev;
    field       prev_opp_king;
    const char  *command = "clear";

    while (1)
    {
        //system(command);
        if (player)
            printf(BOLD "\n\n\n\nPlayer 1\n" STYLE_RESET);
        else
            printf(MAGENTA "\n\n\n\nPlayer 2\n" STYLE_RESET);
        printf("\nFrom x y>\n");
        fflush(stdout);
        scanf("%d %d", &current_x, &current_y);
        printf("To x y>\n");
        fflush(stdout);
        scanf("%d %d", &next_x, &next_y);
        if (current_x < 0 || current_x > 7 || current_y < 0 || current_y > 7 || next_x < 0 || next_x > 7 || next_y < 0 || next_y > 7)
        {
            printf("invalid coordinates\n");
            print_board(board);
            continue ;
        }
        field   *current = get_field(board, current_x, current_y);
        field   *next = get_field(board, next_x, next_y);
        field   *opp_king = get_opponent_king(board, current->fig.color);
        field   *current_king = get_current_king(board, current->fig.color);
        //printf("current king x = %d, y = %d\n", current_king.x, current_king.y);
        if (player == current->fig.color && is_valid_move(board, current, next) && next_not_in_check(board, current, next, current_king))
        {
            //prev_next = *next;
            //prev_current = *current;
            move(current, next);
            print_board(board);
        }
        else
        {
            printf("invalid move\n");
            print_board(board);
            continue ;
        }
        current = next;
        printf("opp_king coloc %d\n", opp_king->fig.color);
        if (check(board, opp_king))
        {
            //prev = current;
            //prev_opp_king = opp_king;
            if (checkmate(board, opp_king, opp_king->fig.color))
            {
                printf("Checkmate: Player %d won\n", player);
                print_board(board);
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