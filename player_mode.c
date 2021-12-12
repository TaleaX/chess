#include <stdio.h>
#include <stdlib.h>
#include "headers/basis.h"
#include "headers/rules.h"
#include "headers/init_game.h"
#include "headers/end_game.h"
#include "headers/game.h"

void player_mode_1(field **board, int player)
{
    printf("player mode 1 doesn't exist yet");
}

void player_mode_2(field **board, int player)
{
    int         current_x;
    int         current_y;
    int         next_x;
    int         next_y;
    char        fig_name;
    field       prev_next;
    field       prev_current;
    field       *prev;
    field       prev_opp_king;
    field       *current;
    field       *next;
    field       *opp_king;
    field       *current_king;
    field       *rock;
    field       *rock_next;
    field       prev_rock;
    field       prev_rock_next;
    field       prev_king;
    field       prev_king_next;
    field       *inter_step;
    const char  *command = "clear";
    while (1)
    {
        system(command);
        if (player)
            printf(BOLD "\n\n\n\nPlayer 1\n" STYLE_RESET);
        else
            printf(MAGENTA "\n\n\n\nPlayer 2\n" STYLE_RESET);
        
        printf("From x y>\n");
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

        current = get_field(board, current_x, current_y);
        next = get_field(board, next_x, next_y);
        opp_king = get_opponent_king(board, current->fig.color);
        current_king = get_current_king(board, current->fig.color);

        if (player == current->fig.color && is_valid_move(board, current, next) && next_not_in_check(board, current, next, current_king))
        {
            move(current, next);
        }
        else if (valid_castle(board, current, next) && !check(board, current_king))
        {
            prev_king = *current;
            prev_king_next = *next;
            rock = get_rock(board, current, next);
            prev_rock = *rock;
            if (rock->x == 0)
            {
                rock_next = &board[next->y][next->x + 1];
                inter_step = &board[current_king->y][current_king->x - 1];

            }
            else
            {
                rock_next = &board[next->y][next->x - 1];
                inter_step = &board[current_king->y][current_king->x + 1];
            }
            prev_rock_next = *rock_next;
            if (check(board, inter_step))
            {
                print_board(board);
                printf("you cannot castle through check\n");
                continue ;
            }
            move(current, next);
            move(rock, rock_next);
            if (check(board, next))
            {
                reset(prev_king, prev_king_next, current, next);
                reset(prev_rock, prev_rock_next, rock, rock_next);
                printf("you cannot castle in check\n");
                print_board(board);
                continue ;
            }
        }
        else
        {
            printf("invalid move\n");
            print_board(board);
            continue ;
        }
        current = next;
        get_queen(board, current);
        if (check(board, opp_king))
        {
            if (checkmate(board, opp_king, opp_king->fig.color))
            {
                printf("Checkmate: Player %d won\n", player);
                print_board(board);
                break;
            }
            printf("CHECK\n");
        }
        player = !player;
        print_board(board);
    }
}
