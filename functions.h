#ifndef TIKTACTOEC_FUNCTIONS_H
#define TIKTACTOEC_FUNCTIONS_H

#define SIZE 3

/**
 * The Main code
 */
void Main();

/**
 *
 * @param board ... The Game Board
 * @param currentPlayer ... The current player
 * @param moves ... The amount of moves
 * @param player1 ... Name of player 1
 * @param player2 ... Name of player 2
 */
void gameWithPlayer(char board[SIZE][SIZE], int currentPlayer, int moves, char* player1, char* player2);

/**
 *
 * @param board ... The Game Board
 * @param currentPlayer ... The current player
 * @param moves ... The amount of moves
 * @param player1 ... Name of player 1
 */
void gameWithKi(char board[SIZE][SIZE], int currentPlayer, int moves, char* player1);

/**
 *
 * @param board ... The Game Board
 */
void printBoard(char board[SIZE][SIZE]);

/**
 *
 * @param board ... The Game Board
 * @param player ... The Current player
 * @return
 */
int checkWin(char board[SIZE][SIZE], char player);

#endif //TIKTACTOEC_FUNCTIONS_H
