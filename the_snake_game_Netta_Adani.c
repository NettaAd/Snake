/* Name: Netta Adani,
   The Snake Game - project number 2 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

#define UP 72    // Up Arrow 
#define DOWN 80  // Down Arrow 
#define LEFT 75  // Left Arrow 
#define RIGHT 77 // Right Arrow 
#define ESC 27   // Escape Key

struct Location
{
	int y; // row
	int x; // col

}typedef Loc;

int getKey();
void gotoxy(int y, int x);
void print_borders();
void snakeToCenter(Loc* snake, int* size, int x, int y);
void move(Loc* snake, int* size, Loc* food, bool* endGame);
void random_food(int* size, Loc* snake, Loc* food);
bool limit_crash(Loc* snake);
bool selfCrash(Loc* snake, int* size, int x, int y);
bool foodOnSnake(int* size, Loc* snake, Loc* food);
bool win(int counter);
Loc* snake_growth(Loc* snake, int* size, char direction);


void main()
{
	bool endGame = false;
	int n, size = 10;
	Loc food;
	Loc* snake = (Loc*)malloc(size * sizeof(Loc));
	/* check if memory allocation succeeded */
	if (snake == NULL)
	{
		printf("Memory allocation unsucceeded! \n");
		exit(0);
	}
	while (endGame == false)
	{
		printf(" ******************************************************* \n");
		printf(" * Pick Your Level, to exit press 0 \n * 0 - Exit \n * 1 - Basic Level \n * 2 - Intermidiate Level \n * 3 - Advanced Level \n");
		printf(" ******************************************************* \n");
		scanf("%d", &n);

		/*****  chack if the input is valid *****/
		if (n != 0 && n != 1 && n != 2 && n != 3)
			continue;
		system("cls"); // clean screen

		switch (n)
		{
		case 0:
			endGame = true;
			break;
		case 1:       /*  1 - Basic Level        */
			move(snake, &size, &food, &endGame);
			break;
		case 2:       /*  2 - Intermidiate Level */
			printf("To be continue...");
			break;
		case 3:       /*  3 - Advanced Level     */
			printf("To be continue...");
			break;
		}
	}
	free(snake);  	  /* free allocated memory of arr */
}



void gotoxy(int y, int x)
{
	printf("\x1b[%d;%df", x + 1, y + 1);
}
int getKey()
{
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}

void print_borders()
{
	int i;

	// top & botom border
	for (i = 0; i <= 75; i++)
	{
		gotoxy(i, 0);
		printf("%c ", '#');
		gotoxy(i, 25);
		printf("%c ", '#');
	}

	// right & left border
	for (i = 0; i <= 25; i++)
	{
		gotoxy(75, i);
		printf("%c", '#');
		gotoxy(0, i);
		printf("%c", '#');
	}
}
void snakeToCenter(Loc* snake, int* size, int x, int y)
{
	int i;
	for (i = 0; i < (*size); i++)
	{
		snake[i].y = y; // row
		snake[i].x = x; // col
	}
}
bool limit_crash(Loc* snake)
{
	/* chack if the snake hit a border */
	if (snake[0].y == 0 || snake[0].y == 25 || snake[0].x == 0 || snake[0].x == 75)
	{
		return true;
	}

	return false;
}
bool selfCrash(Loc* snake, int* size, int x, int y)
{
	/* chack if the snake hit himself */
	int i;
	for (i = 1; i < (*size); i++)
	{
		if (snake[i].y == y && snake[i].x == x)
		{
			return true;
		}
	}
	return false;
}
bool foodOnSnake(int* size, Loc* snake, Loc* food)
{
	/* chack if $ randomly assigned on the snakes body */
	int i;
	for (i = 0; i < (*size); i++)
	{
		if (food->y == snake[i].y && food->x == snake[i].x)
		{
			return true;
		}
	}
	return false;
}
void random_food(int* size, Loc* snake, Loc* food) 	// the $ can't be in the limits or the snake
{
	int flag = 0;
	srand(time(NULL));

	while (flag == 0)
	{
		food->y = 1 + rand() % 24;    /* food.y = number between 1+0 to 1+23 = 1 to 24 */
		food->x = 1 + rand() % 74;    /* food.x = number between 1+0 to 1+73 = 1 to 74 */

		if (foodOnSnake(size, snake, food) == false)   	/* chack if $ randomly assigned on the snakes body */
		{
			gotoxy(food->x, food->y);
			printf("$");
			flag = 1;
		}
	}
}
Loc* snake_growth(Loc* snake, int* size, char direction)
{
	int i;
	int new_size = (*size) + 1;

	Loc* bigger_snake = (Loc*)malloc(new_size * sizeof(Loc));

	/* check if memory allocation succeeded */
	if (bigger_snake == NULL)
	{
		printf("Memory allocation unsucceeded! \n");
		exit(0);
	}

	/* copy snake into new_snake */
	for (i = 0; i < (*size); i++)
	{
		bigger_snake[i].y = snake[i].y;
		bigger_snake[i].x = snake[i].x;
	}

	/* assigne the row and col of the new snake in the last index by the corrent direction */
	switch (direction)
	{
	case RIGHT:
		bigger_snake[new_size - 1].y = snake[(*size) - 1].y;
		bigger_snake[new_size - 1].x = snake[(*size) - 1].x - 1;
		break;

	case LEFT:
		bigger_snake[new_size - 1].y = snake[(*size) - 1].y;
		bigger_snake[new_size - 1].x = snake[(*size) - 1].x + 1;
		break;

	case DOWN:
		bigger_snake[new_size - 1].y = snake[(*size) - 1].y - 1;
		bigger_snake[new_size - 1].x = snake[(*size) - 1].x;
		break;

	case UP:
		bigger_snake[new_size - 1].y = snake[(*size) - 1].y + 1;
		bigger_snake[new_size - 1].x = snake[(*size) - 1].x;
		break;
	}

	/* free allocated memory of arr */
	free(snake);
	(*size)++;
	return bigger_snake;
}
bool win(int counter)
{
	if (counter == 10)
		return true;

	return false;
}
void move(Loc* snake, int* size, Loc* food, bool* endGame)
{
	int i, counter = 0;
	int snake_size = 0;
	char direction = '0';
	char touch = '0';
	int x = 37, y = 13;

	print_borders();
	random_food(size, snake, food);
	snakeToCenter(snake, size, x, y);  // locate the snake in the center of the board
	gotoxy(26, 81);

	touch = getKey();

	/*****************************    chack if the input is valid    *****************************/
	if (touch == RIGHT || touch == LEFT || touch == UP || touch == DOWN || touch == ESC)
	{
		direction = touch;
	}

	if (direction == ESC)
	{
		system("cls");
		*endGame = true;
	}

	while (direction != ESC)
	{
		/********************************   make a move   ********************************/
		Sleep(800);

		if (_kbhit())
			touch = getKey();
		/*****************************    chack if the input is valid    *****************************/
		if (touch == RIGHT || touch == LEFT || touch == UP || touch == DOWN || touch == ESC)
		{
			direction = touch;
		}

		switch (direction)
		{
		case RIGHT:
			x++;
			break;
		case LEFT:
			x--;
			break;
		case DOWN:
			y++;
			break;
		case UP:
			y--;
			break;
		}

		gotoxy(snake[(*size) - 1].x, snake[(*size) - 1].y); // put space in the less part of the snake
		printf(" ");

		gotoxy(26, 81);

		for (i = (*size) - 1; i > 0; i--) // take each part fowrod
		{
			snake[i].y = snake[i - 1].y;
			snake[i].x = snake[i - 1].x;
		}
		snake[0].y = y;
		snake[0].x = x;

		gotoxy(snake[0].x, snake[0].y);
		printf("@");
		gotoxy(26, 81);

		/********************************   chack if end game    ********************************/
		if (limit_crash(snake) == true || selfCrash(snake, size, x, y) == true)
		{
			system("cls");

			printf(" ####################################################### \n");
			printf("                      GAME OVER \n");
			printf(" ####################################################### \n");
			break;
		}
		/********************************   chack for win   ********************************/
		if (win(counter) == true)
		{
			system("cls");

			printf(" ####################################################### \n");
			printf("                       YOU WON!! \n");
			printf(" ####################################################### \n");
			break;
		}
		/********************************   chake if the snake ate $   ********************************/
		if (snake[0].y == food->y && snake[0].x == food->x)
		{
			random_food(size, snake, food);  		// 1. call again to random food and ftint ander $ somewhere else (again, not on border or snakes body)
			snake = snake_growth(snake, size, direction);      // 2. make the snake grough to size + 1
			counter++;
		}
	}
}
