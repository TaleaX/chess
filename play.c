#include <stdio.h>
#include "headers/basis.h"
#include "headers/rules.h"
#include "headers/init_game.h"
#include "headers/player_modes.h"

int main(void)
{
    int     player;
    int     player_mode;
    //char    buf[3];
    field   **board;

    player = 1;
    print_menu();
    printf("\nPlayer Mode > ");
    fflush(stdout);
    scanf("%d", &player_mode);
    //fgets(buf, 2, stdin);
    board = init_board();
    print_board(board);
    if (player_mode == 2)
    {
        player_mode_2(board, player);
    }
    else
    {
        printf("invalid mode\n");
    }
    return (0);
}