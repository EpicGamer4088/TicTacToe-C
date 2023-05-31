#include <stdio.h>

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
