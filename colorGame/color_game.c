#include "../ConsoleEngine.h"
#define AMOUNT_TILES_W 10
#define AMOUNT_TILES_H 10

int** createSquares(int width, int height)
{
	int** squares = malloc(sizeof(int*) * height);
	for (int i = 0; i < height; i++)
		squares[i] = malloc(sizeof(int) * width);

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		//{
			squares[y][x] = rand() % 7 + 3;
			//drawNumber(squares[y][x], x + 1, y + 1, Blue, Default);
		//}
	return squares;
}

void drawSquares(int** squares, int width, int height)
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			int xStart = map(x, 0, 10, 10, 110), yStart = map(y, 0, 10, 10, 110);
			drawSquare(xStart + 1, yStart + 1, xStart + 10, yStart + 10, Default, squares[y][x]);
		}
}

void drawSelector(int selected, int amountTall)
{
	for (int x = 0; x < 7; x++)
	{
		int xStart = map(x, 0, 10, 10, 110);
		if (x == selected)
		{
			drawSquare(xStart + 1, amountTall * 10 + 21, xStart + 10, amountTall * 10 + 30, Default, White);
			drawSquare(xStart + 2, amountTall * 10 + 22, xStart + 9, amountTall * 10 + 29, Default, x + 3);
		}
		else
		drawSquare(xStart + 1, amountTall * 10 + 21, xStart + 10, amountTall * 10 + 30, Default, x + 3);
	}
}

void setColors(int** squares, bool** collected, int color, int width, int height)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (collected[i][j] == true) 
				squares[i][j] = color;
}

void collectedColors(int** squares, bool** collected, int width, int height)
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			if (squares[y][x] == squares[0][0])
			{
				if (x < width - 1)
					if ((collected[y][x + 1] == true)) collected[y][x] = true;
				if (y < height - 1)
					if ((collected[y + 1][x] == true)) collected[y][x] = true;
				if (x > 0)
					if ((collected[y][x - 1] == true)) collected[y][x] = true;
				if (y > 0)
					if ((collected[y - 1][x] == true)) collected[y][x] = true;
			}
		}		
}

int main()
{
	int amountWide = 15, amountTall = 12;
	initalize("Color Game", 50, 50, 5, 5, Default, Default);
	drawSquare(4, 4, 10, 10, Default, Blue);
	render(false);
	while (!key(enterKey, 100));

	initalize("Color Game", amountWide * 10 + 20, amountTall * 10 + 40, 5, 5, Default, Default);
	srand(time(0));

	int** squares = createSquares(amountWide, amountTall);
	bool** collected = malloc(sizeof(bool*) * amountTall);
	for (int i = 0; i < amountTall; i++)
		collected[i] = malloc(sizeof(bool) * amountWide);
	
	for (int i = 0; i < amountTall; i++)
		for (int j = 0; j < amountWide; j++) collected[i][j] = false;
	collected[0][0] = true;
	
	int selected = 0;
	while (!key(escapeKey, 0))
	{
		collectedColors(squares, collected, amountWide, amountTall);
		drawSquares(squares, amountWide, amountTall);
		drawSelector(selected, amountTall);
		arrowInput(&selected, 6, 0, X);

		if (key(VK_SPACE, 0)) setColors(squares, collected, selected+3, amountWide, amountTall);
		render(false);
	}
	for (int i = 0; i < amountWide; i++)
		free(collected[i]);
	free(collected);
	return terminate();
}