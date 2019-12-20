#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Move logical representation
typedef struct {
	char srcPiece, srcRow, srcCol, destPiece, destRow, destCol, promotionPiece;
	int iSrc, jSrc, iDest, jDest,iWhiteKingLocation,jWhiteKingLocation, iBlackKingLocation,jBlackKingLocation;//from where the solger come befor we change his place and to where he is going
	int isWhite, isCapture, isPromotion, isCheck, isMate, isLegal, isSearchingForCheck;
} Move;

// PGN characters
const char PAWN = 'P';
const char ROOK = 'R';
const char KNIGHT = 'N';
const char BISHOP = 'B';
const char QUEEN = 'Q';
const char KING = 'K';
const char CAPTURE = 'x';
const char PROMOTION = '=';
const char CHECK = '+';
const char MATE = '#';
const char FIRST_COL = 'a';

// FEN & Board characters
const char WHITE_PAWN = 'P';
const char WHITE_ROOK = 'R';
const char WHITE_KNIGHT = 'N';
const char WHITE_BISHOP = 'B';
const char WHITE_QUEEN = 'Q';
const char WHITE_KING = 'K';
const char BLACK_PAWN = 'p';
const char BLACK_ROOK = 'r';
const char BLACK_KNIGHT = 'n';
const char BLACK_BISHOP = 'b';
const char BLACK_QUEEN = 'q';
const char BLACK_KING = 'k';


// FEN separator for strtok()
const char SEP[] = "/";

// Board characters
const char EMPTY = ' ';

/**************************
 * convert char to digit
 **************************/
int toDigit(char c) {
	assert('0' <= c && c <= '9');
	return c - '0';
}


void printColumns() {
	char column = toupper(FIRST_COL);
	printf("* |");
	for (int i = 0; i < SIZE; i++) {
		if (i) {
			printf(" ");
		}
		printf("%c", column);
		column++;
	}
	printf("| *\n");
}


void printSpacers() {
	printf("* -");
	for (int i = 0; i < SIZE; i++) {
		printf("--");
	}
	printf(" *\n");
}


void createBoard(char board[][SIZE], char fen[])
{
	int rowIdx = 0;
	int spaces = 0;
	char* fenRow = strtok(fen, SEP);
	while (fenRow != NULL) 
	{
		int i = 0;
		for (int j = 0; j < SIZE; j++)
		{
			if (isdigit(fenRow[i]))
			{
			    spaces = toDigit(fenRow[i++]);
				for (int w = 0; w < spaces; w++)
				{
					board[rowIdx][j] = EMPTY;
					j++;
				}
			}
			else 
			{
				board[rowIdx][j] = fenRow[i++];
			}
		}
		rowIdx++;
		fenRow = strtok(NULL, SEP);
	}
}


void printBoard(char board[][SIZE])
{
	int row = SIZE;
	for (int i = 0; i < SIZE; i++)
    {
		if (i== 0)
		{
			printColumns();
			printSpacers();
			printf("%d ", row);
		}
		else
		{
			printf("%d ", row);
		}
		for (int j = 0; j < SIZE; j++)
	    {
			printf("|%c", board[i][j]);
	    }
		printf("| %d\n", row);
		if (i == SIZE-1)
		{
			printSpacers();
			printColumns();
		}
		row--;
    }
}

void resetmove(Move* move)
{
	move->srcPiece = '0';
	move->srcRow = '0';
	move->srcCol = '0';
	move->destPiece = '0';
	move->destRow = '0';
	move->destCol = '0';
	move->promotionPiece = '0';
	move->iSrc = 0;
	move->jSrc = 0;
	move->iDest = 0;
	move->jDest = 0;
	move->iWhiteKingLocation = 0;
	move->jWhiteKingLocation = 0;
	move->iBlackKingLocation = 0;
	move->jBlackKingLocation = 0;
	move->isWhite = 0;
	move->isCapture = 0;
	move->isPromotion = 0;
	move->isCheck = 0;
	move->isMate = 0;
	move->isLegal = 0;
	move->isSearchingForCheck = 0;
}

void printmove(Move* move)
{
	printf("******************\n");
	printf("srcPiece: %c\n", move->srcPiece);
	printf("srcRow: %c\n", move->srcRow);
	printf("srcCol: %c\n", move->srcCol);
	printf("destPiece: %c\n", move->destPiece);
	printf("destRow: %c\n", move->destRow);
	printf("destCol: %c\n", move->destCol);
	printf("promotionPiece %c\n", move->promotionPiece);
	printf("iSrc: %d\n", move->iSrc);
	printf("jSrc: %d\n", move->jSrc);
	printf("iDest: %d\n", move->iDest);
	printf("jDest: %d\n", move->jDest);
	printf("isWhite: %d\n", move->isWhite);
	printf("isCapture: %d\n", move->isCapture);
	printf("isPromotion: %d\n", move->isPromotion);
	printf("isCheck: %d\n", move->isCheck);
	printf("isMate: %d\n", move->isMate);
	printf("isLegal: %d\n", move->isLegal);
	printf("******************\n");
	printf("******************\n");
}

void whitePawnMovement(char board[][SIZE], int row, int column, Move* move)
{
	int tempiSrc = move->iSrc;
	int tempjSrc = move->jSrc;
	int tempiDest = move->iDest;
	int tempjDest = move->jDest;
	if (move->isSearchingForCheck==1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	if (((move->iSrc)-1== move->iDest)&&(move->jSrc == move->jDest))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) - 2 == move->iDest) && (move->jSrc == move->jDest) && ((move->iSrc) - 1 == EMPTY) && (move->iSrc)==6)
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) - 1 == move->iDest) && ((move->jSrc) + 1 == move->jDest) && (move->isCapture) == 1)
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) - 1 == move->iDest) && ((move->jSrc) - 1 == move->jDest) && (move->isCapture) == 1)
	{
		move->isLegal = 1;
	}
	if (move->isLegal == 1)
	{
		if (move->iDest==0 && move->isPromotion==1)
		{
			move->srcPiece = move->promotionPiece;
		}
	}
	else
	{
		move->isLegal = 0;
	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = tempiSrc;
		move->jSrc = tempjSrc;
		move->iDest = tempiDest;
		move->jDest = tempjDest;
	}
}

void whiteRookMovement(char board[][SIZE], int row, int column, Move* move)
{
	int countNotEmpty = 0;
	int tempiSrc = move->iSrc;
	int tempjSrc = move->jSrc;
	int tempiDest = move->iDest;
	int tempjDest = move->jDest;
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	if ((move->iSrc == move->iDest) && (move->jSrc != move->jDest))
	{
		for (int j = min((move->jSrc),(move->jDest))+1; j < max((move->jSrc), (move->jDest)); j++)
		{
			if (board[move->iSrc][j]!=EMPTY)
			{
				countNotEmpty++;
			}
		}
		if (countNotEmpty==0)
		{
			move->isLegal = 1;
		}
		else
		{
			move->isLegal = 0;
		}
		
	}
	if ((move->jSrc == move->jDest) && (move->iSrc != move->iDest))
	{
		for (int i = min((move->iSrc), (move->iDest)) + 1; i < max((move->iSrc), (move->iDest)); i++)
		{
			if (board[i][move->jSrc] != EMPTY)
			{
				countNotEmpty++;
			}
		}
		if (countNotEmpty == 0)
		{
			move->isLegal = 1;
		}
		else
		{
			move->isLegal = 0;
		}

	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = tempiSrc;
		move->jSrc = tempjSrc;
		move->iDest = tempiDest;
		move->jDest = tempjDest;
	}
}

void whiteKnightMovement(char board[][SIZE], int row, int column, Move* move)
{
	int tempiSrc = move->iSrc;
	int tempjSrc = move->jSrc;
	int tempiDest = move->iDest;
	int tempjDest = move->jDest;
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	if (((move->iSrc) + 2 == move->iDest) && (((move->jSrc) + 1 == move->jDest)||((move->jSrc) - 1 == move->jDest)))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) - 2 == move->iDest) && (((move->jSrc) + 1 == move->jDest) || ((move->jSrc) - 1 == move->jDest)))
	{
		move->isLegal = 1;
	}
	else if (((move->jSrc) + 2 == move->jDest) && (((move->iSrc) + 1 == move->iDest) || ((move->iSrc) - 1 == move->iDest)))
	{
		move->isLegal = 1;
	}
	else if (((move->jSrc) - 2 == move->jDest) && (((move->iSrc) + 1 == move->iDest) || ((move->iSrc) - 1 == move->iDest)))
	{
		move->isLegal = 1;
	}
	else
	{
		move->isLegal = 0;
	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = tempiSrc;
		move->jSrc = tempjSrc;
		move->iDest = tempiDest;
		move->jDest = tempjDest;
	}
	
}

void whiteBishopMovement(char board[][SIZE], int row, int column, Move* move)
{
	int countNotEmpty = 0;
	int tempiSrc = move->iSrc;
	int tempjSrc = move->jSrc;
	int tempiDest = move->iDest;
	int tempjDest = move->jDest;
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	if (((move->iDest)-(move->iSrc) == (move->jDest) - (move->jSrc)) || ((move->iDest) - (move->iSrc) == (move->jSrc) - (move->jDest)))
	{
		if (((move->iDest) > (move->iSrc)) && ((move->jDest) > (move->jSrc)))
		{
			int j = move->jSrc;
			for (int i = (move->iSrc)+1; i < (move->iDest); i++)
			{
				j++;
				if (board[i][j] != EMPTY)
					{
						countNotEmpty++;
					}
				
			}
		}
		else if (((move->iDest) > (move->iSrc)) && ((move->jSrc) > (move->jDest)))
		{
			int j = move->jSrc;
			for (int i = (move->iSrc) + 1; i < (move->iDest); i++)
			{
				j--;
				if (board[i][j] != EMPTY)
				{
					countNotEmpty++;
				}

			}
		}
		else if (((move->iSrc) > (move->iDest)) && ((move->jSrc) > (move->jDest)))
		{
			int j = move->jDest;
			for (int i = (move->iDest) + 1; i < (move->iSrc); i++)
			{
				j++;
				if (board[i][j] != EMPTY)
				{
					countNotEmpty++;
				}

			}
		}
		else if (((move->iSrc) > (move->iDest)) && ((move->jDest) > (move->jSrc)))
		{
			int j = move->jDest;
			for (int i = (move->iDest) + 1; i <(move->iSrc); i++)
			{
				j--;
				if (board[i][j] != EMPTY)
				{
					countNotEmpty++;
				}

			}
		}
		if (countNotEmpty == 0)
		{
			move->isLegal = 1;
		}
		else
		{
			move->isLegal = 0;
		}
	}
	else
	{
		move->isLegal = 0;
	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = tempiSrc;
		move->jSrc = tempjSrc;
		move->iDest = tempiDest;
		move->jDest = tempjDest;
	}
	
}

void whiteQueenMovement(char board[][SIZE], int row, int column, Move* move)
{
	int tempiSrc = move->iSrc;
	int tempjSrc = move->jSrc;
	int tempiDest = move->iDest;
	int tempjDest = move->jDest;
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	whiteRookMovement(board,row,column, move);
	if (move->isLegal == 1)
	{
		move->isLegal = 1;
	}
	else
	{
		whiteBishopMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			move->isLegal = 1;
		}
		else
		{
			move->isLegal = 0;
		}
	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = tempiSrc;
		move->jSrc = tempjSrc;
		move->iDest = tempiDest;
		move->jDest = tempjDest;
	}
}

void whiteKingMovement(char board[][SIZE], int row, int column, Move* move)
{
	int tempiSrc = move->iSrc;
	int tempjSrc = move->jSrc;
	int tempiDest = move->iDest;
	int tempjDest = move->jDest;
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	if (((move->iSrc) + 1 == move->iDest) && (move->jSrc == move->jDest))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) - 1 == move->iDest) && (move->jSrc == move->jDest))
	{
		move->isLegal = 1;
	}
	else if (((move->jSrc) + 1 == move->jDest) && (move->iSrc == move->iDest))
	{
		move->isLegal = 1;
	}
	else if (((move->jSrc) - 1 == move->jDest) && (move->iSrc == move->iDest))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) - 1 == move->iDest) && ((move->jSrc) + 1 == move->jDest))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) - 1 == move->iDest) && ((move->jSrc) - 1 == move->jDest))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) + 1 == move->iDest) && ((move->jSrc) + 1 == move->jDest))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) + 1 == move->iDest) && ((move->jSrc) - 1 == move->jDest))
	{
		move->isLegal = 1;
	}
	else
	{
		move->isLegal = 0;
	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = tempiSrc;
		move->jSrc = tempjSrc;
		move->iDest = tempiDest;
		move->jDest = tempjDest;
	}

}

void blackPawnMovement(char board[][SIZE], int row, int column, Move* move)
{
	int tempiSrc = move->iSrc;
	int tempjSrc = move->jSrc;
	int tempiDest = move->iDest;
	int tempjDest = move->jDest;
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	if (((move->iSrc) + 1 == move->iDest) && (move->jSrc == move->jDest))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) + 2 == move->iDest) && (move->jSrc == move->jDest) && ((move->iSrc) + 1 == EMPTY) && (move->iSrc) == 1)
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) + 1 == move->iDest) && ((move->jSrc) + 1 == move->jDest) && (move->isCapture) == 1)
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) + 1 == move->iDest) && ((move->jSrc) - 1 == move->jDest) && (move->isCapture) == 1)
	{
		move->isLegal = 1;
	}
	if (move->isLegal == 1)
	{
		if (move->iDest == 7 && move->isPromotion == 1)
		{
			move->srcPiece = move->promotionPiece;
		}
	}
	else
	{
		move->isLegal = 0;
	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = tempiSrc;
		move->jSrc = tempjSrc;
		move->iDest = tempiDest;
		move->jDest = tempjDest;
	}
}

void blackRookMovement(char board[][SIZE], int row, int column, Move* move)
{
	int countNotEmpty = 0;
	int tempiSrc = move->iSrc;
	int tempjSrc = move->jSrc;
	int tempiDest = move->iDest;
	int tempjDest = move->jDest;
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	if ((move->iSrc == move->iDest) && (move->jSrc != move->jDest))
	{
		for (int j = min((move->jSrc), (move->jDest)) + 1; j < max((move->jSrc), (move->jDest)); j++)
		{
			if (board[move->iSrc][j] != EMPTY)
			{
				countNotEmpty++;
			}
		}
		if (countNotEmpty == 0)
		{
			move->isLegal = 1;
		}
		else
		{
			move->isLegal = 0;
		}

	}
	if ((move->jSrc == move->jDest) && (move->iSrc != move->iDest))
	{
		for (int i = min((move->iSrc), (move->iDest)) + 1; i < max((move->iSrc), (move->iDest)); i++)
		{
			if (board[i][move->jSrc] != EMPTY)
			{
				countNotEmpty++;
			}
		}
		if (countNotEmpty == 0)
		{
			move->isLegal = 1;
		}
		else
		{
			move->isLegal = 0;
		}

	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = tempiSrc;
		move->jSrc = tempjSrc;
		move->iDest = tempiDest;
		move->jDest = tempjDest;
	}
}

void blackKnightMovement(char board[][SIZE], int row, int column, Move* move)
{
	int tempiSrc = move->iSrc;
	int tempjSrc = move->jSrc;
	int tempiDest = move->iDest;
	int tempjDest = move->jDest;
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	if (((move->iSrc) + 2 == move->iDest) && (((move->jSrc) + 1 == move->jDest) || ((move->jSrc) - 1 == move->jDest)))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) - 2 == move->iDest) && (((move->jSrc) + 1 == move->jDest) || ((move->jSrc) - 1 == move->jDest)))
	{
		move->isLegal = 1;
	}
	else if (((move->jSrc) + 2 == move->jDest) && (((move->iSrc) + 1 == move->iDest) || ((move->iSrc) - 1 == move->iDest)))
	{
		move->isLegal = 1;
	}
	else if (((move->jSrc) - 2 == move->jDest) && (((move->iSrc) + 1 == move->iDest) || ((move->iSrc) - 1 == move->iDest)))
	{
		move->isLegal = 1;
	}
	else
	{
		move->isLegal = 0;
	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = tempiSrc;
		move->jSrc = tempjSrc;
		move->iDest = tempiDest;
		move->jDest = tempjDest;
	}
}

void blackBishopMovement(char board[][SIZE], int row, int column, Move* move)
{
	int countNotEmpty = 0;
	int tempiSrc = move->iSrc;
	int tempjSrc = move->jSrc;
	int tempiDest = move->iDest;
	int tempjDest = move->jDest;
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	if (((move->iDest) - (move->iSrc) == (move->jDest) - (move->jSrc)) || ((move->iDest) - (move->iSrc) == (move->jSrc) - (move->jDest)))
	{
		if (((move->iDest) > (move->iSrc)) && ((move->jDest) > (move->jSrc)))
		{
			int j = move->jSrc;
			for (int i = (move->iSrc) + 1; i < (move->iDest); i++)
			{
				j++;
				if (board[i][j] != EMPTY)
				{
					countNotEmpty++;
				}

			}
		}
		else if (((move->iDest) > (move->iSrc)) && ((move->jSrc) > (move->jDest)))
		{
			int j = move->jSrc;
			for (int i = (move->iSrc) + 1; i < (move->iDest); i++)
			{
				j--;
				if (board[i][j] != EMPTY)
				{
					countNotEmpty++;
				}

			}
		}
		else if (((move->iSrc) > (move->iDest)) && ((move->jSrc) > (move->jDest)))
		{
			int j = move->jDest;
			for (int i = (move->iDest) + 1; i < (move->iSrc); i++)
			{
				j++;
				if (board[i][j] != EMPTY)
				{
					countNotEmpty++;
				}

			}
		}
		else if (((move->iSrc) > (move->iDest)) && ((move->jDest) > (move->jSrc)))
		{
			int j = move->jDest;
			for (int i = (move->iDest) + 1; i < (move->iSrc); i++)
			{
				j--;
				if (board[i][j] != EMPTY)
				{
					countNotEmpty++;
				}

			}
		}
		if (countNotEmpty == 0)
		{
			move->isLegal = 1;
		}
		else
		{
			move->isLegal = 0;
		}
	}
	else
	{
		move->isLegal = 0;
	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = tempiSrc;
		move->jSrc = tempjSrc;
		move->iDest = tempiDest;
		move->jDest = tempjDest;
	}
}

void blackQueenMovement(char board[][SIZE], int row, int column, Move* move)
{
	int tempiSrc = move->iSrc;
	int tempjSrc = move->jSrc;
	int tempiDest = move->iDest;
	int tempjDest = move->jDest;
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	blackRookMovement(board, row, column, move);
	if (move->isLegal == 1)
	{
		move->isLegal = 1;
	}
	else
	{
		blackBishopMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			move->isLegal = 1;
		}
		else
		{
			move->isLegal = 0;
		}
	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = tempiSrc;
		move->jSrc = tempjSrc;
		move->iDest = tempiDest;
		move->jDest = tempjDest;
	}
}

void blackKingMovement(char board[][SIZE], int row, int column, Move* move)
{
	int tempiSrc = move->iSrc;
	int tempjSrc = move->jSrc;
	int tempiDest = move->iDest;
	int tempjDest = move->jDest;
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = row;
		move->jSrc = column;
		if (move->isWhite == 0)
		{
			move->iDest = move->iBlackKingLocation;
			move->jDest = move->jBlackKingLocation;
		}
		else
		{
			move->iDest = move->iWhiteKingLocation;
			move->jDest = move->jWhiteKingLocation;
		}
	}
	if (((move->iSrc) + 1 == move->iDest) && (move->jSrc == move->jDest))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) - 1 == move->iDest) && (move->jSrc == move->jDest))
	{
		move->isLegal = 1;
	}
	else if (((move->jSrc) + 1 == move->jDest) && (move->iSrc == move->iDest))
	{
		move->isLegal = 1;
	}
	else if (((move->jSrc) - 1 == move->jDest) && (move->iSrc == move->iDest))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) - 1 == move->iDest) && ((move->jSrc) + 1 == move->jDest))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) - 1 == move->iDest) && ((move->jSrc) - 1 == move->jDest))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) + 1 == move->iDest) && ((move->jSrc) + 1 == move->jDest))
	{
		move->isLegal = 1;
	}
	else if (((move->iSrc) + 1 == move->iDest) && ((move->jSrc) - 1 == move->jDest))
	{
		move->isLegal = 1;
	}
	else
	{
		move->isLegal = 0;
	}
	if (move->isSearchingForCheck == 1)
	{
		move->iSrc = tempiSrc;
		move->jSrc = tempjSrc;
		move->iDest = tempiDest;
		move->jDest = tempjDest;
	}
}

int checkBySrcPiece(char board[][SIZE],int row,int column, Move* move)
{
	if (board[row][column] == WHITE_PAWN)
	{
		whitePawnMovement(board,row,column, move);
		if (move->isLegal == 1)
		{
			return 1;
		}
	}
	else if (board[row][column] == WHITE_ROOK)
	{
		whiteRookMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			return 1;
		}
	}
	else if (board[row][column] == WHITE_KNIGHT)
	{
		whiteKnightMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			return 1;
		}
	}
	else if (board[row][column] == WHITE_BISHOP)
	{
		whiteBishopMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			return 1;
		}
	}
	else if (board[row][column] == WHITE_QUEEN)
	{
		whiteQueenMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			return 1;
		}
	}
	else if (board[row][column] == WHITE_KING)
	{
		whiteKingMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			return 1;
		}
	}
	else if (board[row][column] == BLACK_PAWN)
	{
		blackPawnMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			return 1;
		}
	}
	else if (board[row][column] == BLACK_ROOK)
	{
		blackRookMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			return 1;
		}
	}
	else if (board[row][column] == BLACK_KNIGHT)
	{
		blackKnightMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			return 1;
		}
	}
	else if (board[row][column] == BLACK_BISHOP)
	{
		blackBishopMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			return 1;
		}
	}
	else if (board[row][column] == BLACK_QUEEN)
	{
		blackQueenMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			return 1;
		}
	}
	else if (board[row][column] == BLACK_KING)
	{
		blackKingMovement(board, row, column, move);
		if (move->isLegal == 1)
		{
			return 1;
		}
	}
	else
	{
		return 0;
	}

}

int checkForIJCheck(char copyBoard[][SIZE], Move* move)
{
	move->isLegal = 0;
	move->isSearchingForCheck = 1;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (copyBoard[i][j] != EMPTY)
			{
				if ((move->isWhite == 1 && islower(copyBoard[i][j])) || (move->isWhite == 0 && isupper(copyBoard[i][j])))
				{
					if (checkBySrcPiece(copyBoard, i, j, move) == 1)
					{
						move->isSearchingForCheck = 0;
						move->isLegal = 0;
						return 0;
					}
				}
			}
		}
	}
	move->isSearchingForCheck = 0;
	move->isLegal = 1;
	return 1;
}

int checkForIJSrc(char board[][SIZE], Move* move)
{
	char realSrcPiece = ' ';
	if (move->isWhite == 0)
	{
			realSrcPiece = tolower(move->srcPiece);
	}
	else
	{
		realSrcPiece = move->srcPiece;
	}
	if (move->srcRow!='0')
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[move->iSrc][j] == realSrcPiece)
			{
				move->jSrc = j;
				if (checkBySrcPiece(board,(move->iSrc), j,move) == 1)
				{
					performCopyMove(board, move);
					if (move->isLegal == 1)
					{
						return 1;
					}
				}
			}
		}
	}
	else if (move->srcCol != '0')
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (board[i][move->jSrc] == realSrcPiece)
			{
				move->iSrc = i;
				if (checkBySrcPiece(board,i, (move->jSrc), move) == 1)
				{
					performCopyMove(board, move);
					if (move->isLegal == 1)
					{
						return 1;
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (board[i][j] == realSrcPiece)
				{
					move->iSrc = i;
					move->jSrc = j;
					if (checkBySrcPiece(board, i, j, move) == 1)
					{
						performCopyMove(board,move);
						if (move->isLegal==1)
						{
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

Move parseMove(char board[][SIZE], char pgn[], int isWhiteTurn)
{
	Move move;
	resetmove(&move);
	int i = 0;
	char place[4]=" ";
	int pIndex = 0;
	move.isWhite = isWhiteTurn;
	while (pgn[i] != '\0') 
	{
		if ((pgn[i]>='1'&& pgn[i] <= '9')|| (pgn[i] >= 'a' && pgn[i] <= 'i'))
		{
			place[pIndex++] = pgn[i];
		}

		if (i==0)
		{
			if ((pgn[i] == KING) || (pgn[i] == QUEEN) || (pgn[i] == ROOK) || (pgn[i] == BISHOP) || (pgn[i] == KNIGHT))
			{
				move.srcPiece = pgn[i];
			}
			else
			{
				move.srcPiece = PAWN;
			}
		}

		if (pgn[i]== CAPTURE)
		{
			move.isCapture = 1;
		}
		else if (pgn[i] == PROMOTION)
		{
			move.isPromotion = 1;
			if ((pgn[i+1]==QUEEN)|| (pgn[i + 1] == ROOK) || (pgn[i + 1] ==BISHOP )|| (pgn[i + 1] == KNIGHT))
			{
				move.promotionPiece = pgn[i + 1];
			}
			else
			{
				move.isLegal = 0;
			}
		}
		else if (pgn[i] == CHECK)
		{
			move.isCheck = 1;
		}
		else if (pgn[i] == MATE)
		{
			move.isMate = 1;
		}
		i++;
	}
	if (pIndex==2)
	{
		move.destCol = place[0];
		move.jDest= (move.destCol - 'a' );
		move.destRow = place[1];
		move.iDest = SIZE - (move.destRow - '0');
		if (board[move.iDest][move.jDest]==EMPTY)
		{
			checkForIJSrc(board, &move);
		}
		else if (((move.isWhite == 1) && (islower(board[move.iDest][move.jDest]))) && move.isCapture == 1)
		{
			checkForIJSrc(board, &move);
		}
		else if (((move.isWhite == 0) && (isupper(board[move.iDest][move.jDest]))) && move.isCapture == 1)
		{
			checkForIJSrc(board, &move);
		}
		else
		{
			move.isLegal = 0;
		}
	}
	else if (pIndex == 3)
	{
		move.destCol = place[1];
		move.jDest = (move.destCol - 'a');
		move.destRow = place[2];
		move.iDest = SIZE - (move.destRow - '0');
		if (place[0] >= 'a' && place[0] <= 'i')
		{
			move.srcCol = place[0];
			move.jSrc = (move.srcCol - 'a');
		}
		else
		{
			move.srcRow = place[0];
			move.iSrc = SIZE - (move.srcRow - '0' );
		}
		if ((board[move.iDest][move.jDest] == EMPTY) || (move.isWhite == 1 && (islower(board[move.iDest][move.jDest]) == 1) && move.isCapture == 1) || (move.isWhite == 0 && (isupper(board[move.iDest][move.jDest]) == 1) && move.isCapture == 1))
		{
			checkForIJSrc(board, &move);
		}
		else
		{
			move.isLegal = 0;
		}
	}

	if (pIndex == 4)
	{
		move.srcCol = place[0];
		move.jSrc = (move.srcCol - 'a');
		move.srcRow = place[1];
		move.iSrc = SIZE - (move.srcRow - '0');
		move.destCol = place[2];
		move.jDest = (move.destCol - 'a');
		move.destRow = place[3];
		move.iDest = SIZE - (move.destRow - '0');

	}

	printmove(&move);
	return move;


}
int performCopyMove(char board[][SIZE], Move* move)
{
	char copyBoard[SIZE][SIZE];
	if (move->isWhite == 0)
	{
		move->srcPiece = tolower(move->srcPiece);
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			copyBoard[i][j] = board[i][j];
			if (board[i][j]==WHITE_KING)
			{
				move->iWhiteKingLocation = i;
				move->jWhiteKingLocation = j;
			}
			else if (board[i][j] == BLACK_KING)
			{
				move->iBlackKingLocation = i;
				move->jBlackKingLocation = j;
			}
		}
	}
	copyBoard[move->iDest][move->jDest] = move->srcPiece;
	copyBoard[move->iSrc][move->jSrc] = EMPTY;
	checkForIJCheck(copyBoard, move);
	return 1;
}

void performMove(char board[][SIZE], Move* move)
{
	if (move->isWhite == 0)
	{
		move->srcPiece = tolower(move->srcPiece);
	}
	board[move->iDest][move->jDest] =move->srcPiece ;
	board[move->iSrc][move->jSrc] = EMPTY;
}


int makeMove(char board[][SIZE], char pgn[], int isWhiteTurn)
{
	Move move;
	resetmove(&move);
	move = parseMove(board,pgn, isWhiteTurn);
	if (move.isLegal)
	{
		//performCopyMove(board, &move);
		performMove(board, &move);
		printBoard(board);
		return 1;
	}
	else
	{
		printf("Illegal Move! \n");
		return 0;
	}
}