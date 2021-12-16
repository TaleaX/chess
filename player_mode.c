#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers/basis.h"

#include "headers/init_board.h"

#include "headers/game.h"
#include "headers/movements_list.h"
#include "headers/get_fields.h"

#include "headers/check_moves.h"

int* parse_inp_arr(char *inp)
{
    int *val = (int *)malloc(sizeof(int) * 2);
    int i = 0;
    while (*inp && i < 2)
    {
        if (*inp >= '0' && *inp <= '7')
        {
            val[i] = *inp - '0';
            i++;
        }
        inp++;
    }
    if (i < 2)
        return (NULL);
    return (val);
}



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
    field       *prev;
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
    char        *buffer = (char *)malloc(10);
    int         *inp;
    int         step_counter = 1;
    const char  *command = "clear";
    node_t  *tail = NULL;

    while (1)
    {
        system(command);
        if (player)
            printf(BOLD "\n\n\n\nPlayer 1\n" STYLE_RESET);
        else
            printf(MAGENTA "\n\n\n\nPlayer 2\n" STYLE_RESET);
        
        int i = 0;
        while (i < 2)
        {
            if (i == 0)
                printf("From x y>\n");
            else
                printf("To x y>\n");
            fflush(stdout);
            fgets(buffer, 10, stdin);
            fflush(stdin);
            inp = parse_inp_arr(buffer);
            if (inp == NULL)
            {
                printf("invalid input");
                print_board(board);
                break ;
            }
            if (i == 0) {
                current_x = inp[0];
                current_y = inp[1];
            } else {
                next_x = inp[0];
                next_y = inp[1];
            }
            i++;
        }
        if (i < 2)
            continue ;

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
            insert_at_tail(&tail, create_node(*current, *next, step_counter));
            move(current, next);
        }
        else if (valid_castle(board, current, next))
        {
            node_t *tmp = create_node(*current, *next, step_counter);
            insert_at_tail(&tail, tmp);
            prev_king = *current;
            prev_king_next = *next;
            rock = get_rock(board, current, next);
            prev_rock = *rock;
            if (rock->x == 0)
                rock_next = &board[next->y][next->x + 1];
            else
                rock_next = &board[next->y][next->x - 1];
            prev_rock_next = *rock_next;
            move(current, next);
            move(rock, rock_next);
            if (check(board, next))
            {
                remove_last_node(&tail, tmp);
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
        change_fig(board, current);
        if (check(board, opp_king))
        {
            if (checkmate(board, opp_king, opp_king->fig.color))
            {
                printf("Checkmate: Player %d won\n", player);
                print_board(board);
                print_nodes(tail);
                break;
            }
            printf("CHECK\n");
        }
        player = !player;
        step_counter++;
        print_board(board);
    }
}
