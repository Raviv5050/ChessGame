#ifndef __ASS4_H
#define __ASS4_H
#define SIZE 8
#define _CRT_SECURE_NO_WARNINGS

void createBoard(char board[][SIZE], char fen[]);
void printBoard(char board[][SIZE]);
void makeMove(char board[][SIZE], char pgn[], int isWhiteTurn);
//void printBoardFromFEN(char fen[]);

#endif
