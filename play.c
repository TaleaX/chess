#include <stdio.h>
#include <stdlib.h>
#include "headers/basis.h"

//#include "headers/game.h"
//#include "headers/movements_list.h"
#include "headers/init_board.h"
//#include "headers/get_fields.h"
//#include "headers/check_way.h"

//#include "headers/figure_rules.h"

//#include "headers/check_moves.h"

//#include "headers/game.h"

#include "headers/player_modes.h"

int main(void)
{
    int     player;
    int     player_mode;
    char    buf[5];
    field   **board;

    player = 1;
    print_menu();
    printf("\nPlayer Mode > ");
    fflush(stdout);
    //scanf("%d", &player_mode);
    fgets(buf, 5, stdin);
    //getchar();
    board = init_board();
    print_board(board);
    if (buf[0] == '2')
    {
        player_mode_2(board, player);
    }
    else
    {
        printf("invalid mode\n");
    }
    return (0);
}