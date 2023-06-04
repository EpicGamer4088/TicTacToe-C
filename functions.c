#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "functions.h"

#define SIZE 3

void Main() {
    char board[SIZE][SIZE] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int currentPlayer = 1;
    int moves = 0;
    int repInputKIorPlayer;
    int playerChoiceRes;
    char *ki = "KI", *player = "Player";
    char *playerChoice = (char*)malloc(6 * sizeof(char));
    char *player1 = (char*) malloc(12 * sizeof(char));
    char *player2 = (char*) malloc(12 * sizeof(char));

    printf("Schreibe 'KI' um gegen eine KI zu spielen oder 'Player' um gegen einen anderen Spieler zu spielen:");
    scanf("%s", playerChoice);

    if (strcmp(playerChoice, player) == 0) {
        printf("Gib den Namen des ersten Spielers ein (maximal 12 zeichen): ");
        scanf("%s", player1);
        printf("Gib den Namen des zweiten Spielers ein (maximal 12 zeichen): ");
        scanf("%s", player2);
    } else if (strcmp(playerChoice, ki) == 0) {
        printf("Gib deinen Namen ein (maximal 12 zeichen): ");
        scanf("%s", player1);
    }

    do {
        playerChoiceRes = strcmp(playerChoice, player);
        if (playerChoiceRes == 0) {
            gameWithPlayer(board, currentPlayer, moves, player1, player2);
        } else {
            playerChoiceRes = strcmp(playerChoice, ki);
            if (playerChoiceRes == 0) {
                gameWithKi(board, currentPlayer, moves, player1);
            } else {
                printf("Du hast weder 'KI' noch 'Player' eingegeben.\nWiederhole deine Eingabe:\n");
                repInputKIorPlayer = 1;
            }
        }
    } while (repInputKIorPlayer == 1);
}

void gameWithPlayer(char board[SIZE][SIZE], int currentPlayer, int moves, char* player1, char* player2) {
    while (1) {
        char* currentPlayerName = (currentPlayer == 1) ? player1 : player2;
        printf("%s, bitte geben Sie die Koordinaten (Zeile Spalte) Ihres Zuges ein: ", currentPlayerName);
        int row;
        char col;
        scanf(" %d %c", &row, &col);

        // Convert col to index
        int colIndex = col - 'a';

        // Check the validity of the move
        if (row < 1 || row > SIZE || colIndex < 0 || colIndex >= SIZE || board[row - 1][colIndex] != ' ') {
            printf("Ungueltiger Zug! Bitte versuchen Sie es erneut.\n");
            continue;
        }

        // Place the move on the field
        board[row - 1][colIndex] = (currentPlayer == 1) ? 'X' : 'O';

        // Update the game
        printBoard(board);
        moves++;

        // Check the score
        if (checkWin(board, (currentPlayer == 1) ? 'X' : 'O')) {
            printf("%s hat gewonnen!\n\n", currentPlayerName);
            system("PAUSE");
            exit(0);
        } else if (moves == SIZE * SIZE) {
            printf("Unentschieden!\n\n");
            system("PAUSE");
            exit(0);
        }

        // Change player
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}

void gameWithKi(char board[SIZE][SIZE], int currentPlayer, int moves, char* player1) {
    char* player2 = "KI";
    while (1) {
        char* currentPlayerName = (currentPlayer == 1) ? player1 : player2;
        printf("%s, bitte geben Sie die Koordinaten (Zeile Spalte) Ihres Zuges ein: ", currentPlayerName);
        int row;
        char col;
        scanf(" %d %c", &row, &col);

        // Convert col to index
        int colIndex = col - 'a';

        // Check the validity of the move
        if (row < 1 || row > SIZE || colIndex < 0 || colIndex >= SIZE || board[row - 1][colIndex] != ' ') {
            printf("Ungueltiger Zug! Bitte versuchen Sie es erneut.\n");
            continue;
        }

        // Place the move on the field
        board[row - 1][colIndex] = (currentPlayer == 1) ? 'X' : 'O';

        // Update the game
        printBoard(board);
        moves++;

        // Check the score
        if (checkWin(board, (currentPlayer == 1) ? 'X' : 'O')) {
            printf("%s hat gewonnen!\n\n", currentPlayerName);
            system("PAUSE");
            exit(0);
        } else if (moves == SIZE * SIZE) {
            printf("Unentschieden!\n\n");
            system("PAUSE");
            exit(0);
        }

        // Change player
        currentPlayer = (currentPlayer == 1) ? 2 : 1;

        // KI-Zug
        if (strcmp(player2, "KI") == 0) {
            printf("KI ist am Zug");
            for (int i = 0; i < 3; i++) {
                sleep(1);
                printf(".");
            }
            sleep(1);
            printf("\n");
            srand(time(NULL));
            do {
                row = rand() % SIZE + 1;
                colIndex = rand() % SIZE;
            } while (board[row - 1][colIndex] != ' ');

            board[row - 1][colIndex] = (currentPlayer == 1) ? 'X' : 'O';

            // Update the game
            printBoard(board);
            moves++;

            // Check the score after KI's move
            if (checkWin(board, (currentPlayer == 1) ? 'X' : 'O')) {
                printf("Die KI gewinnt!\n\n");
                system("PAUSE");
                exit(0);
            } else if (moves == SIZE * SIZE) {
                printf("Unentschieden!\n\n");
                system("PAUSE");
                exit(0);
            }

            // Change player
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
    }
}

void printBoard(char board[SIZE][SIZE]) {
    printf("   a   b   c\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%c ", '1' + i);
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
