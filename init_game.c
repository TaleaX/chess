#include <stdio.h>
#include <stdlib.h>
#include "headers/basis.h"

field   **init_board()
{
    int     row;
    int     col;
    char    *figures = "RHBQKBHR";
    field    **board;
    field   square;

    board = (field **)malloc(sizeof(field *) * 8 + 1);
    row = 0;
    while (row < 8)
    {
        square.y = row;
        col = 0;
        board[row] = (field *)malloc(sizeof(field) * 8);
        while (col < 8)
        {
            square.x = col;
            if ((row == 0 || row == 7))
            {
                square.fig.name = figures[col];
                square.empty = 0;
                square.fig.moved = 0;
            }
            else if ((row == 1 || row == 6))
            {
                square.fig.name = 'P';
                square.empty = 0;
                square.fig.moved = 0;
            }
            else
            {
                square.fig.name = 'X';
                square.empty = 1;
                square.fig.color = -1;
            }

            if (row < 2)
                square.fig.color = BLACK;
            else if (row > 5)
                square.fig.color = WHITE;
            board[row][col] = square;
            col++;
        }
        row++;
    }
    board[row] = (void *)0;
    return (board);
}

void    print_board(field **board)
{
    int row;
    int col;

    row = 0;
    col = 0;
    puts("");
    while (row < 8)
    {
        if (row == 0)
        {
            printf("\t\t\t\t  Y\n");
            printf("\t\t\t\t  ^\n");
            printf("\t\t\t\t  |");
        }
        printf("\n\t\t\t\t  ---------------------------------     \n");
        col = 0;
        printf("\t\t\t\t%d |", row);
        while(col < 8)
        {
            if (!board[row][col].empty)
            {
                if (board[row][col].fig.color == 1)
                    printf(" %c ", board[row][col].fig.name);
                else if (board[row][col].fig.color == 0)
                    printf(MAGENTA " %c " COLOR_RESET, board[row][col].fig.name);
                printf("|");
            }
            else
                printf("   |");
            /*if (row == 7)
            {
                if (col == 7)
                {
                    printf("\n");
                    printf("\t  |");
                }
                printf("  %d ", col);
            }*/
            col++;
        }
        col = 0;
        printf("\n");
        printf("\t\t\t\t  |");
        while(col < 8)
        {
            printf("   |");
            col++;
        }
        row++;
    }
    printf("\n\t\t\t\t  -----------------------------------> X\n");
    col = 0;
    printf("\t\t\t\t  ");
    while (col < 8)
    {
        printf("  %d ", col);
        col++;
    }
    puts("");
}

void print_menu()
{
    int i;
    int j;

    i = 0;
    printf("\n\t\t== == == == == == == == == == M E N U == == == == == == == == == ==\t\t\n");
    while (i < 12)
    {
        j = 0;
        while (j < 75)
        {
            if (i == 3 && j == 38)
            {
                printf("P L A Y E R  M O D E");
                j += 19;
            }
            else if ((i == 6 && j == 22) || (i == 8 && j == 22) || (i == 6 && j == 51) || (i == 8 && j == 51))
            {
                printf("----------------------");
                j += 21;
            }
            else if (i == 7 && j == 22)
            {
                printf("| Single Player > 1 |");
                j += 21;
            }
            else if (i == 7 && j == 52)
            {
                printf("| Double Player > 2 |");
                j += 21;
            }
            else
                printf(" ");
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n\t\t== == == == == == == == == == == == == == == == == == == == == == ==\t\t\n");
}