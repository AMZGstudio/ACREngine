#define WIDTH 25
#define HEIGHT 20
#include "../ConsoleEngine.h"

char xPic[6][8] = { "       ",
					" \\   / ",
					"  \\ /  ",
					"  / \\  ",
					" /   \\ ",
					"       " };
char oPic[6][8] = { "       ",
					" /---\\ ",
					" |   | ",
					" |   | ",
					" \\___/ ",
					"       " };

int board[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int main()
{
	initalize("TikTakToe", Black, White);

	int row = 0, column = 0, turn = 0, location = 0;
	char message[] = "Press To Play", input[2] = { 0 };
	drawText(message, central(strlen(message), 1, WIDTH), 5, Black, Default);
	render(false);
	while (!key(enterKey, 0));

	while (1)
	{
		clearScreen();

		drawLine(thirds(1, X, Yes), 1, HEIGHT, Down, Default, Yellow);
		drawLine(thirds(2, X, Yes), 1, HEIGHT, Down, Default, Yellow);
		drawLine(1, thirds(1, Y, Yes), WIDTH, Right, Default, Yellow);
		drawLine(1, thirds(2, Y, Yes), WIDTH, Right, Default, Yellow);

		row = 0, column = 0, location = 0;
		for (int y = 1; y <= HEIGHT; y += thirds(1, Y, Yes))
		{
			for (int x = 1; x <= WIDTH; x += thirds(1, X, Yes))
			{
				if (board[column + row] == 1) drawBuffer(xPic, 6, x, y, Red, Default);
				if (board[column + row] == 2) drawBuffer(oPic, 6, x, y, Blue, Default);
				row++;
			}
			row = 0, column += 3;
		}
		render(true);
		
		do { input[0] = _getch(); location = atoi(input); }
		while (board[location - 1] != 0);
		
		turn % 2 == 0 ? (board[location - 1] = 1) : (board[location - 1] = 2); 
		turn++;
	}
	return 0;
}