#ifndef TIKTACTOEC_FUNCTIONS_H
#define TIKTACTOEC_FUNCTIONS_H

#define SIZE 3

/**
 * The Main code
 */
void Main();

/**
 * Prints out a Titel Screen
 */
void printTitleScreen();

/**
 * Prints the menu options
 * @param selectedOption ... The selected option for the Game
 */
void printMenuOptions(int selectedOption);

/**
 * Prints out a Loading Screen
 */
void printLoadingScreen();

/**
 * @param board ... The Game Board
 * @param currentPlayer ... The current player
 * @param moves ... The amount of moves
 * @param player1 ... Name of player 1
 * @param player2 ... Name of player 2
 */
void gameWithPlayer(char board[SIZE][SIZE], int currentPlayer, int moves, char* player1, char* player2);

/**
 * @param board ... The Game Board
 * @param currentPlayer ... The current player
 * @param moves ... The amount of moves
 * @param player1 ... Name of player 1
 */
void gameWithKi(char board[SIZE][SIZE], int currentPlayer, int moves, char* player1);



int generateRandomMove(char board[SIZE][SIZE], int* selectedRow, int* selectedCol);
int generateWinningMove(char board[SIZE][SIZE], int currentPlayer, int* selectedRow, int* selectedCol);
int generateBlockingMove(char board[SIZE][SIZE], int currentPlayer, int* selectedRow, int* selectedCol);
int generateStrategicMove(char board[SIZE][SIZE], int currentPlayer, int* selectedRow, int* selectedCol);







/**
 *
 * @param board ... The Game Board
 * @param selectedRow ... The currently selected Row
 * @param selectedCol ... The currently selected Col
 */
void printBoard(char board[SIZE][SIZE], int selectedRow, int selectedCol);

/**
 * @param board ... The Game Board
 * @param player ... The Current player
 * @return
 */
int checkWin(char board[SIZE][SIZE], char player);

#endif //TIKTACTOEC_FUNCTIONS_H
