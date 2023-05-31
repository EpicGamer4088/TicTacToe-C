#include <stdio.h>
#include "functions.h"

#define SIZE 3

void printBoard(char board[SIZE][SIZE]) {
    printf("   1   2   3\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j != SIZE - 1)
                printf("|");
        }
        printf("\n");
        if (i != SIZE - 1) {
            printf("  ---+---+---\n");
        }
    }
}

int checkWin(char board[SIZE][SIZE], char player) {
    for (int i = 0; i < SIZE; i++) {
        // Check rows
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;

        // Check columns
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1;
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1;
    if (board[2][0] == player && board[1][1] == player && board[0][2] == player)
        return 1;

    return 0;
}
