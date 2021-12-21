#include <stdio.h>
#include <stdlib.h>
#include "../headers/basis.h"

//#include "headers/game.h"
//#include "headers/movements_list.h"
#include "../headers/init_board.h"
//#include "headers/get_fields.h"
//#include "headers/check_way.h"

//#include "headers/figure_rules.h"

//#include "headers/check_moves.h"

//#include "headers/game.h"

#include "../headers/player_modes.h"

int main(void)
{
    int     player;
    char    buf[5];
    field   **board;

    player = 1;
    print_menu();
    printf("\nPlayer Mode > ");
    setbuf(stdin, NULL);
    fflush(stdout);
    fgets(buf, 5, stdin);
    board = init_board();
    print_board(board);
    if (buf[0] == '2')
        player_mode_2(board, player);
    else
        player_mode_1(board, player);
    return (0);
}