#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

//Necessary items
#define Empty "\xDB\xDB"
#define Mine  "*"
#define X "X"
#define Space " "
#define BOARD_SIZE 15
#define HEALTH 6
 
typedef enum Board { EMPTY, MINE,BUSTED,SPACE} Board;
typedef Board mineBoard[BOARD_SIZE][BOARD_SIZE];

// If you want, you create own Board

/*mineBoard board = {
						{0,1,0,0,0,0,0,1,0,0},
						{0,0,0,0,1,0,0,1,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,0,0,0,1,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,1,0,0,1,0,0,0},
						{0,1,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,1,0,0,0,0},
						{0,0,1,0,0,0,0,0,1,0},
						{0,0,0,0,1,0,1,0,0,0}
				};*/

mineBoard board;

// Generate Random Mine Board
void generateRandomBoard(mineBoard board)
{
	for (int r = 0; r < BOARD_SIZE; ++r)
	{
		for (int c = 0; c < BOARD_SIZE; ++c)
		{
			int n = 1 + (rand() % 10);
			int randomValue =  0+(rand() % 500);
			int zeroRone;
			if (randomValue % n == 0)
				zeroRone = 1;
			else zeroRone = 0;
			board[r][c] = zeroRone;
		}
	}
}
// print wanted characters...
void enumBoard(Board enumBoard,int n)
{
	switch (enumBoard)
	{
	case EMPTY:printf(Empty); break;
	case MINE:
		if(n==0)
			printf(Mine); break;
		printf(Empty); break;
	case BUSTED:printf(X); break;
	case SPACE:printf(Space); break;
	
	}
}
// print Minefield Board
void sketchBoard(mineBoard board,int n)
{
	for (int row = 0; row < BOARD_SIZE; ++row)
	{
		for (int col = 0; col < BOARD_SIZE; ++col)
		{
			enumBoard(board[row][col],n);
		}
		printf("\n");
	}
}
// Mine control
bool mineControl(int row, int col, mineBoard board)
{
	if (board[row][col] == MINE)
		return true;
	return false;
}
bool checkEmpty(mineBoard board)
{
	for (int r = 0; r < BOARD_SIZE; ++r)
	{
		for (int c = 0; c < BOARD_SIZE; ++c)
		{
			if (board[r][c] == EMPTY)
				return false;
		}
	}
	return true;
}
void startGame(mineBoard board)
{
	int health = HEALTH;
	int row , col,c;
	for (int i = 0; ; ++i)
	{
		system("cls");
		sketchBoard(board,1);
		printf("Enter the location(x,y): \n");
		scanf_s("%d%d",&row,&col);
		if (mineControl(row, col, board))
		{
			health--;
			printf("BOOm!: Your health: %d\n", health);
			Sleep(1000);
			board[row][col] = BUSTED;
			sketchBoard(board,1);
		}
		else if (!mineControl(row, col, board))
		{
			board[row][col] = SPACE;		
			sketchBoard(board,1);

			if (checkEmpty(board))
			{
				printf("Congratulations....\n");
				return;
			}
		}
		if (health == 0)
		{
			printf("LOSER! Your Health: %d\n", health);
			printf("\n---------OPEN BOARD:---------\n");
			sketchBoard(board,0);
			return;
		}

	}
}
void main()
{
	srand(time(NULL));

	printf("----------Welcome to myMineField----------\n\t[BoardSize: %dx%d - Health: %d]\n", BOARD_SIZE, BOARD_SIZE,HEALTH);
	printf("[*]Busted: %s   EMPTY: %s  MINE: %s \n[*]Please wait 5 second...\n", X, Empty,Mine);
	generateRandomBoard(board);
	Sleep(5000);
	startGame(board);
	
	
}
