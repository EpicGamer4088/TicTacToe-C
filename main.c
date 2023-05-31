#include <stdio.h>
#include "functions.h"

#define SIZE 3

int main() {
    char board[SIZE][SIZE] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int currentPlayer = 1;
    int moves = 0;

    while (1) {
        printf("Spieler %d, bitte geben Sie die Koordinaten (Zeile Spalte) Ihres Zuges ein: ", currentPlayer);
        int row;
        int col;
        scanf(" %d %d", &row, &col);

        // Convert col to index
        int colIndex = col - 1;

        // Check the validity of the move
        if (row < 1 || row > SIZE || colIndex < 0 || colIndex >= SIZE || board[row - 1][colIndex] != ' ') {
            printf("Ungültiger Zug! Bitte versuchen Sie es erneut.\n");
            continue;
        }

        // Place the move on the field
        board[row - 1][colIndex] = (currentPlayer == 1) ? 'X' : 'O';

        // Update the game
        printBoard(board);
        moves++;

        // Check the score
        if (checkWin(board, (currentPlayer == 1) ? 'X' : 'O')) {
            printf("Spieler %d gewinnt!\n", currentPlayer);
            break;
        } else if (moves == SIZE * SIZE) {
            printf("Unentschieden!\n");
            break;
        }

        // Change player
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    return 0;
}
