#ifndef TIKTACTOEC_FUNCTIONS_H
#define TIKTACTOEC_FUNCTIONS_H

#define SIZE 3

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
