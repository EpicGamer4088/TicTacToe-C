#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>

#include "functions.h"

#define SIZE 3

void Main() {
    char board[SIZE][SIZE] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int currentPlayer = 1;
    int moves = 0;
    int selectedOption = 1;
    int option;
    char *player1 = (char*)malloc(12 * sizeof(char));
    char *player2 = (char*)malloc(12 * sizeof(char));

    while (1) {
        system("cls");
        printTitleScreen();
        printMenuOptions(selectedOption);

        // Input with arrow keys
        option = getch();
        if (option == 224) {  // Arrow key detected
            option = getch();
            if (option == 72) {
                selectedOption = (selectedOption == 1) ? 3 : selectedOption - 1;
            } else if (option == 80) {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        } else if (option == 13) {
            break;
        }
    }

    switch (selectedOption) {
        case 1:
            system("cls");
            printLoadingScreen();
            printf("Gib den Namen des ersten Spielers ein (maximal 12 Zeichen): ");
            scanf("%s", player1);
            printf("Gib den Namen des zweiten Spielers ein (maximal 12 Zeichen): ");
            scanf("%s", player2);
            gameWithPlayer(board, currentPlayer, moves, player1, player2);
            break;
        case 2:
            system("cls");
            printLoadingScreen();
            printf("Gib deinen Namen ein (maximal 12 Zeichen): ");
            scanf("%s", player1);
            gameWithKi(board, currentPlayer, moves, player1);
            break;
        case 3:
            printf("\nDas Programm wird beendet. Auf Wiedersehen!\n");
            exit(0);
        default:
            printf("\nUngültige Option. Bitte eine gültige Option wählen.\n\n");
            break;
    }
}


void printTitleScreen() {
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*           Tic Tac Toe           *\n");
    printf("*                                 *\n");
    printf("***********************************\n\n");
}

void printMenuOptions(int selectedOption) {
    printf("Waehle eine Option:\n");
    printf("%s  Gegen einen Spieler spielen\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  Gegen die KI spielen\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  Beenden\n\n", (selectedOption == 3) ? ">>" : "  ");
}

void printLoadingScreen() {
    printf("Lade Spiel\n\n[");
    fflush(stdout);
    usleep(500000);

    int i;
    for (i = 0; i < 20; i++) {
        printf("=");
        fflush(stdout);
        usleep(500000);
    }

    printf("]");
    fflush(stdout);
    usleep(500000);

    system("cls");
}

void gameWithPlayer(char board[SIZE][SIZE], int currentPlayer, int moves, char* player1, char* player2) {
    int selectedRow = 0;
    int selectedCol = 0;

    while (1) {
        system("cls");
        char *currentPlayerName = (currentPlayer == 1) ? player1 : player2;
        printf("%s, bitte waehlen Sie die Koordinaten Ihres Zuges mit den Pfeiltasten und bestaetigen Sie mit ENTER:\n\n",
               currentPlayerName);

        // Print the board with selected cell indicator
        printBoard(board, selectedRow, selectedCol);

        int keyPressed = getch();

        if (keyPressed == 0 || keyPressed == 224) {
            keyPressed = getch(); // Ignore arrow key prefix

            // Move selection up
            if (keyPressed == 72 && selectedRow > 0) {
                selectedRow--;
            }
                // Auswahl nach unten verschieben
            else if (keyPressed == 80 && selectedRow < SIZE - 1) {
                selectedRow++;
            }
                // Auswahl nach links verschieben
            else if (keyPressed == 75 && selectedCol > 0) {
                selectedCol--;
            }
                // Move selection to the right
            else if (keyPressed == 77 && selectedCol < SIZE - 1) {
                selectedCol++;
            }
        } else if (keyPressed == 13) {
            // Check the validity of the move
            if (board[selectedRow][selectedCol] != ' ') {
                continue;
            }

            // Place the move on the field
            board[selectedRow][selectedCol] = (currentPlayer == 1) ? 'X' : 'O';

            // Update the game
            system("cls");
            printBoard(board, selectedRow, selectedCol);
            moves++;

            // Check the score
            if (checkWin(board, (currentPlayer == 1) ? 'X' : 'O')) {
                system("cls");
                selectedRow = -1, selectedCol = -1;
                printBoard(board, selectedRow, selectedCol);
                usleep(500000);
                printf("%s hat gewonnen!\n\n", currentPlayerName);
                usleep(500000);
                system("PAUSE");
                exit(0);
            } else if (moves == SIZE * SIZE) {
                system("cls");
                selectedRow = -1, selectedCol = -1;
                printBoard(board, selectedRow, selectedCol);
                usleep(500000);
                printf("Unentschieden!\n\n");
                usleep(500000);
                system("PAUSE");
                exit(0);
            }

            // Change player
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }

        // Print the updated board with selected cell indicator
        printBoard(board, selectedRow, selectedCol);
    }
}





//
int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

//
void generateAiMove(char board[SIZE][SIZE], int difficultyLevel, int currentPlayer, int* selectedRow, int* selectedCol) {
    int moveCount = 0;
    int availableMoves[SIZE * SIZE][2];

    // Find available moves
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == ' ') {
                availableMoves[moveCount][0] = row;
                availableMoves[moveCount][1] = col;
                moveCount++;
            }
        }
    }

    // Generate random move for the "Easy" difficulty level
    if (difficultyLevel == 1) {
        int randomIndex = getRandomNumber(0, moveCount - 1);
        *selectedRow = availableMoves[randomIndex][0];
        *selectedCol = availableMoves[randomIndex][1];
    }
        // Implement AI move generation logic for other difficulty levels
    else if (difficultyLevel == 2) {
        // Challenging difficulty: Random move for now
        int randomIndex = getRandomNumber(0, moveCount - 1);
        *selectedRow = availableMoves[randomIndex][0];
        *selectedCol = availableMoves[randomIndex][1];
    }
    else if (difficultyLevel == 3) {
        // Hard difficulty: Prioritize winning moves, otherwise random
        for (int i = 0; i < moveCount; i++) {
            int row = availableMoves[i][0];
            int col = availableMoves[i][1];
            board[row][col] = (currentPlayer == 1) ? 'X' : 'O';

            if (checkWin(board, (currentPlayer == 1) ? 'X' : 'O')) {
                *selectedRow = row;
                *selectedCol = col;
                break;
            }

            board[row][col] = ' ';
        }

        if (*selectedRow == -1 && *selectedCol == -1) {
            int randomIndex = getRandomNumber(0, moveCount - 1);
            *selectedRow = availableMoves[randomIndex][0];
            *selectedCol = availableMoves[randomIndex][1];
        }
    }
    else if (difficultyLevel == 4) {
        // Hacker difficulty: Always selects the center position if available
        for (int i = 0; i < moveCount; i++) {
            int row = availableMoves[i][0];
            int col = availableMoves[i][1];

            if (row == 1 && col == 1) {
                *selectedRow = row;
                *selectedCol = col;
                break;
            }
        }

        if (*selectedRow == -1 && *selectedCol == -1) {
            // If center position is not available, choose randomly
            int randomIndex = getRandomNumber(0, moveCount - 1);
            *selectedRow = availableMoves[randomIndex][0];
            *selectedCol = availableMoves[randomIndex][1];
        }
    }
}






void gameWithKi(char board[SIZE][SIZE], int currentPlayer, int moves, char* player1) {
    char* player2 = "KI";
    int selectedRow = 0;
    int selectedCol = 0;
    int difficultyLevel = 1; // Default difficulty level: Easy

    // Select difficulty level
    system("cls");
    printf("Bitte wählen Sie den Schwierigkeitsgrad:\n");
    printf("1. Easy\n");
    printf("2. Challenging\n");
    printf("3. Hard\n");
    printf("4. Hacker\n");

    int difficultySelection = 0;

    while (difficultySelection < 1 || difficultySelection > 4) {
        printf("Geben Sie die entsprechende Zahl ein: ");
        scanf("%d", &difficultySelection);
    }

    difficultyLevel = difficultySelection;

    while (1) {
        system("cls");
        char* currentPlayerName = (currentPlayer == 1) ? player1 : player2;
        printf("%s, bitte wählen Sie die Koordinaten Ihres Zuges mit den Pfeiltasten und bestätigen Sie mit ENTER:\n\n", currentPlayerName);

        printBoard(board, selectedRow, selectedCol);

        int keyPressed = getch();

        if (keyPressed == 0 || keyPressed == 224) {
            keyPressed = getch(); // Ignore arrow key prefix

            // Move selection up
            if (keyPressed == 72 && selectedRow > 0) {
                selectedRow--;
            }
                // Move selection down
            else if (keyPressed == 80 && selectedRow < SIZE - 1) {
                selectedRow++;
            }
                // Move selection left
            else if (keyPressed == 75 && selectedCol > 0) {
                selectedCol--;
            }
                // Move selection to the right
            else if (keyPressed == 77 && selectedCol < SIZE - 1) {
                selectedCol++;
            }
        }
        else if (keyPressed == 13) {
            // Check the validity of the move
            if (board[selectedRow][selectedCol] != ' ') {
                printf("Ungültiger Zug! Bitte wählen Sie ein leeres Feld.\n");
                continue;
            }

            // Place the move on the field
            board[selectedRow][selectedCol] = (currentPlayer == 1) ? 'X' : 'O';

            // Update the game
            system("cls");
            printBoard(board, selectedRow, selectedCol);
            moves++;

            // Check the score
            if (checkWin(board, (currentPlayer == 1) ? 'X' : 'O')) {
                system("cls");
                printBoard(board, -1, -1);
                usleep(500000);
                printf("%s hat gewonnen!\n\n", currentPlayerName);
                usleep(500000);
                system("PAUSE");
                exit(0);
            }
            else if (moves == SIZE * SIZE) {
                system("cls");
                printBoard(board, -1, -1);
                usleep(500000);
                printf("Unentschieden!\n\n");
                usleep(500000);
                system("PAUSE");
                exit(0);
            }

            // Change player
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
        else if (keyPressed == 224) {
            getch(); // Ignore arrow key prefix
            keyPressed = getch(); // Read the actual arrow key code

            // Change difficulty level
            if (keyPressed == 72) { // Up arrow key
                difficultyLevel = (difficultyLevel == 1) ? 4 : difficultyLevel - 1;
            }
            else if (keyPressed == 80) { // Down arrow key
                difficultyLevel = (difficultyLevel == 4) ? 1 : difficultyLevel + 1;
            }
        }

        // AI-Moves
        if (strcmp(player2, "KI") == 0 && currentPlayer == 2) {
            printf("KI ist am Zug");
            for (int i = 0; i < 3; i++) {
                sleep(1);
                printf(".");
            }
            sleep(1);
            printf("\n");

            // Generate AI move based on the selected difficulty level
            generateAiMove(board, difficultyLevel, currentPlayer, &selectedRow, &selectedCol);

            board[selectedRow][selectedCol] = (currentPlayer == 1) ? 'X' : 'O';

            // Update the game
            system("cls");
            printBoard(board, selectedRow, selectedCol);
            moves++;

            // Check the score after KI's move
            if (checkWin(board, (currentPlayer == 1) ? 'X' : 'O')) {
                system("cls");
                printBoard(board, -1, -1);
                usleep(500000);
                printf("Die KI gewinnt!\n\n");
                usleep(500000);
                system("PAUSE");
                exit(0);
            }
            else if (moves == SIZE * SIZE) {
                system("cls");
                printBoard(board, -1, -1);
                usleep(500000);
                printf("Unentschieden!\n\n");
                usleep(500000);
                system("PAUSE");
                exit(0);
            }

            // Change player
            currentPlayer = 1;
        }
    }
}









void printBoard(char board[SIZE][SIZE], int selectedRow, int selectedCol) {
    printf("     a     b     c\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%c ", '1' + i);
        for (int j = 0; j < SIZE; j++) {
            if (i == selectedRow && j == selectedCol) {
                printf("| [%c] ", board[selectedRow][selectedCol]);
            }
            else {
                printf("|  %c  ", board[i][j]);
            }
        }
        printf("|\n");
        if (i != SIZE - 1) {
            printf("   -----+-----+----\n");
        }
    }
    printf("\n");
}







//
int checkWin(char board[SIZE][SIZE], char player) {
    // Check rows
    for (int row = 0; row < SIZE; row++) {
        if (board[row][0] == player && board[row][1] == player && board[row][2] == player) {
            return 1;
        }
    }

    // Check columns
    for (int col = 0; col < SIZE; col++) {
        if (board[0][col] == player && board[1][col] == player && board[2][col] == player) {
            return 1;
        }
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return 1;
    }

    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return 1;
    }

    return 0;
}
