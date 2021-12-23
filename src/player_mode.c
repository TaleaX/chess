#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/basis.h"

#include "../headers/init_board.h"

#include "../headers/game.h"
#include "../headers/linked_list.h"
#include "../headers/get_fields.h"

#include "../headers/check_moves.h"
//#include "../headers/comp.h"

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
    printf("Sorry, this mode doesn't exist yet... :/\n");
}

void player_mode_2(field **board, int player)
{
    int         coordinates[4];
    int         play;
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
    char        *buffer = (char *)malloc(5);
    int         *inp;
    int         step_counter = 1;
    const char  *command = "clear";
    node_t      *tail = NULL;

    play = 1;
    while (1)
    {
        system(command);
        if (player)
            printf(BOLD "\n\n\n\nPlayer 1\n" STYLE_RESET);
        else
            printf(BOLD MAGENTA "\n\n\n\nPlayer 2\n" STYLE_RESET);
        
        int i = 0;
        while (i < 2)
        {
            if (i == 0)
                printf("From x y>\n");
            else
                printf("To x y>\n");
            fflush(stdout);
            fgets(buffer, 5, stdin);
            if (buffer[0] == 'q')
            {
                play = 0;
                break ;
            }
            inp = parse_inp_arr(buffer);
            if (inp == NULL)
            {
                printf("invalid input");
                print_board(board);
                break ;
            }
            if (i == 0) {
                coordinates[0] = inp[0];
                coordinates[1] = inp[1];
            } else {
                coordinates[2] = inp[0];
                coordinates[3] = inp[1];
            }
            i++;
        }
        if (!play)
            break ;
        if (i < 2)
            continue ;

        if (coordinates[0] < 0 || coordinates[0] > 7 || coordinates[1] < 0 || coordinates[1] > 7 || coordinates[2] < 0 || coordinates[2] > 7 || coordinates[3] < 0 || coordinates[3] > 7)
        {
            printf("invalid coordinates\n");
            print_board(board);
            continue ;
        }

        current = get_field(board, coordinates[0], coordinates[1]);
        next = get_field(board, coordinates[2], coordinates[3]);
        opp_king = get_king(board, !player);
        current_king = get_king(board, player);
        if (player == current->fig.color && is_valid_move(board, current, next, 0) && next_not_in_check(board, current, next, current_king))
        {
            insert_at_tail(&tail, create_node(*current, *next, step_counter));  // linked list to track the steps that were made during play
            move(current, next);
        }
        else if (current->fig.name == 'K' && ABS((current->x - next->x)) && valid_castle(board, current, next))
        {
            node_t *tmp = create_node(*current, *next, step_counter); // linked list to track the steps that were made during play
            insert_at_tail(&tail, tmp);
            prev_king = *current;
            prev_king_next = *next;
            //rock = get_rock(board, current, next);
            if (current->x < next->x)
            {
               rock = &board[next->y][7];
               rock_next = &board[next->y][next->x - 1];
            }
            else
            {
                rock = &board[next->y][0];
                rock_next = &board[next->y][next->x + 1];
            }
            prev_rock = *rock;
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
            if (checkmate(board, opp_king))
            {
                printf("Checkmate: Player %d won\n", player);
                print_board(board);
                //prints all the steps that happened during play
                print_nodes(tail);
                break;
            }
            printf("CHECK\n");
        }
        player = !player;
        step_counter++;
        print_board(board);
    }
    free(buffer);
}

//PLEASE IGNORE

/*void player_mode_1(field **board, int player)
{
    field   *comps_king;
    field   *player_king;
    field   ***all_moves;
    field       *current;
    field       *next;
    char        *buffer = (char *)malloc(5);
    int         *inp;
    int         current_x;
    int         current_y;
    int         next_x;
    int         next_y;
    int         play = 1;
    while (1)
    {
        comps_king = get_king(board, BLACK);
        player_king = get_king(board, WHITE);
        if (player == WHITE)
        {
            printf(BOLD "\n\n\n\nPlayer 1\n" STYLE_RESET);
            int i = 0;
            while (i < 2)
            {
                if (i == 0)
                    printf("From x y>\n");
                else
                    printf("To x y>\n");
                fflush(stdout);
                fgets(buffer, 5, stdin);
                if (buffer[0] == 'q')
                {
                    play = 0;
                    break ;
                }
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
            if(!play)
                break ;
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
            if (is_valid_move(board, current, next, 0) && next_not_in_check(board, current, next, player_king))
            {
                move(current, next);
            }
        }
        else
        {
            all_moves = get_current_possible_moves(board, comps_king);
            int i = 0;
            while (all_moves[i])
            {
                printf("from %d %d to %d %d\n", all_moves[i][0]->x, all_moves[i][0]->y, all_moves[i][1]->x, all_moves[i][1]->y);
                i++;
            }
            if (!check(board, comps_king))
            {
                beat_figure(board, comps_king, player_king, all_moves);
                {
                    /*field **comps_figs = get_players_figs(board, BLACK);
                    field **to_be_defendet = defense(board, comps_king, comps_figs);
                    while (*to_be_defendet)
                    {
                        printf("to be_defendet%d %d\n", (*to_be_defendet)->x, (*to_be_defendet)->y);
                        to_be_defendet++;
                    }*/
                /*}
            }
            free(all_moves);
        }
        player = !player;
        print_board(board);
    }
    free(buffer);
}*/
