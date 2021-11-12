#include <stdio.h>
#include "headers/basis.h"
#include "headers/rules.h"
#include "headers/init_game.h"
#include "headers/end_game.h"

field   *get_next_field(field **board, int x, int y)
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

field   *get_current_field(field **board, int x, int y)
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

field   *opponent_king(field **board, int player_color)
{
    int     i;
    int     j;
    
    i = 0;
    while (i < 8)
    {
        j = 0;
        while (j < 8)
        {
            if (board[i][j].fig.name == 'K' && board[i][j].fig.color != player_color)
                return (&board[i][j]);
            j++;
        }
        i++;
    }
    return ((void *)0);
}

void    move(field *current, field *next)
{
    next->fig.name = current->fig.name;
    next->fig.color = current->fig.color;
    next->empty = 0;
    next->fig.moved = 1;
    current->fig.name = 'X';
    current->fig.color = -1;
    current->empty = 1;
}

int    main()
{
    int     danger_score;
    int     current_x;
    int     current_y;
    int     next_x;
    int     next_y;
    int     player1;
    int     player_mode;
    field   current;
    field   next;
    field **board;

    player1 = 1;
    print_menu();
    //printf("\nEnter Player Mode > ");
    //fflush(stdout);
    //scanf("%d", &player_mode);
    board = init_board();
    print_board(board);
    while (1)
    {
        if (player1)
        {
            printf("From x y>\n");
            fflush(stdout);
            scanf("%d %d", &current_x, &current_y);
            printf("To x y>\n");
            fflush(stdout);
            scanf("%d %d", &next_x, &next_y);
        }
        if (current_x < 0 || current_x > 7 || current_y < 0 || current_y > 7 || next_x < 0 || next_x > 7 || next_y < 0 || next_y > 7)
        {
            printf("invalid coordinates\n");
            continue ;
        }
        field   *current = get_current_field(board, current_x, current_y);
        field   *next = get_next_field(board, next_x, next_y);
        field   *opp_king = opponent_king(board, current->fig.color);
        if (is_valid_move(board, current, next))
        {
            move(current, next);
            print_board(board);
        }
        else
            printf("invalid move\n");
        current = next;
        if (check(board, current, opp_king))
        {
            if (checkmate(board, current, opp_king, current->fig.color))
            {
                printf("CHeckmate: Player %d won\n", player1);
                break;
            }
            printf("CHECK\n");
        }
    }
    return 0;
}