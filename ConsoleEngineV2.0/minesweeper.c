#define BOMB_SYMBOL 'B'
#define NOTHING_SYMBOL '.'
#define FLAG 'f'
#define SHOW_FPS true
#include "ACREngine.h"

int* grid;
int* found;

int touching(int x, int y, int gameWidth, int gameHeight, int* arr, int touchingThing)
{
	int amount = 0;
	if (x > 0)
		if (arr[y * gameWidth + (x - 1)] == touchingThing) amount++;

	if (x < gameWidth - 1)
		if (arr[y * gameWidth + (x + 1)] == touchingThing) amount++;

	if (y > 0)
		if (arr[(y - 1) * gameWidth + x] == touchingThing) amount++;

	if (y < gameHeight - 1)
		if (arr[(y + 1) * gameWidth + x] == touchingThing) amount++;

	if (y > 0 && x > 0)
		if (arr[(y - 1) * gameWidth + (x - 1)] == touchingThing) amount++;

	if (y < gameHeight - 1 && x < gameWidth - 1)
		if (arr[(y + 1) * gameWidth + (x + 1)] == touchingThing) amount++;

	if (y > 0 && x < gameWidth - 1)
		if (arr[(y - 1) * gameWidth + (x + 1)] == touchingThing) amount++;

	if (y < gameHeight - 1 && x > 0)
		if (arr[(y + 1) * gameWidth + (x - 1)] == touchingThing) amount++;

	return amount;
}

int calculateNum(int gameWidth, int gameHeight)
{
	for (int x = 0; x < gameWidth; x++)
		for (int y = 0; y < gameHeight; y++)
		{
			if (grid[y * gameWidth + x] == BOMB_SYMBOL) continue;

			grid[y * gameWidth + x] = '0' + touching(x, y, gameWidth, gameHeight, grid, BOMB_SYMBOL);
		}
}

void drawBoard(int gameWidth, int gameHeight, Image square, Image bomb, Image flag, bool showBombs, bool showFlags)
{
	for (int x = 0; x < gameWidth; x++)
		for (int y = 0; y < gameHeight; y++)
		{
			int xStart = map(x, 0, gameWidth, 0, width(Screen));
			int yStart = map(y, 0, gameHeight, 0, height(Screen));

			if (found[y * gameWidth + x] == 1)
			{
				drawRectFilled(xStart, yStart, xStart + 10, yStart + 10, 8);
				if (grid[y * gameWidth + x] == '1')
					sysDrawFontChar(xStart + 2, yStart + 2, Screen, grid[y * gameWidth + x], Default, Blue);

				else if (grid[y * gameWidth + x] == '2')
					sysDrawFontChar(xStart + 2, yStart + 2, Screen, grid[y * gameWidth + x], Default, Green);

				else if (grid[y * gameWidth + x] == '3')
					sysDrawFontChar(xStart + 2, yStart + 2, Screen, grid[y * gameWidth + x], Default, Red);

				else if (grid[y * gameWidth + x] == '4')
					sysDrawFontChar(xStart + 2, yStart + 2, Screen, grid[y * gameWidth + x], Default, 17);
				
				else if(grid[y * gameWidth + x] != '0' && grid[y * gameWidth + x] != BOMB_SYMBOL)
					sysDrawFontChar(xStart + 2, yStart + 2, Screen, grid[y * gameWidth + x], Default, White);

			}
			else
				drawImage(xStart, yStart, square);

			if (grid[y * gameWidth + x] == BOMB_SYMBOL && showBombs)
				drawImage(xStart + 2, yStart + 2, bomb);

			if (found[y * gameWidth + x] == FLAG && showFlags)
				drawImage(xStart + 2, yStart + 2, flag);			
		}
}
void calculateNothing(int width, int height, int xOrigin, int yOrigin)
{
	if (xOrigin >= width || xOrigin < 0 || yOrigin >= height || yOrigin < 0) return;
	if (grid[yOrigin * width + xOrigin] == '0' && found[yOrigin * width + xOrigin] != 1)
	{
		found[yOrigin * width + xOrigin] = 1;
		calculateNothing(width, height, xOrigin + 1, yOrigin);
		calculateNothing(width, height, xOrigin - 1, yOrigin);
		calculateNothing(width, height, xOrigin, yOrigin + 1);
		calculateNothing(width, height, xOrigin, yOrigin - 1);
	}
	//found[yOrigin * width + xOrigin] = 1;
	if (grid[yOrigin * width + xOrigin] == '0')
	{
		if (xOrigin > 0)
			if (grid[yOrigin * width + (xOrigin - 1)] != '0' && grid[yOrigin * width + (xOrigin - 1)] != BOMB_SYMBOL) found[yOrigin * width + (xOrigin - 1)] = 1;

		if (xOrigin < width - 1)
			if (grid[yOrigin * width + (xOrigin + 1)] != '0' && grid[yOrigin * width + (xOrigin + 1)] != BOMB_SYMBOL) found[yOrigin * width + (xOrigin + 1)] = 1;

		if (yOrigin > 0)
			if (grid[(yOrigin-1) * width + xOrigin] != '0' && grid[(yOrigin - 1) * width + xOrigin] != BOMB_SYMBOL) found[(yOrigin - 1) * width + xOrigin] = 1;

		if (yOrigin < height - 1)
			if (grid[(yOrigin + 1) * width + xOrigin] != '0' && grid[(yOrigin + 1) * width + xOrigin] != BOMB_SYMBOL) found[(yOrigin+1) * width + xOrigin] = 1;

		if (yOrigin > 0 && xOrigin > 0)
			if (grid[(yOrigin - 1) * width + (xOrigin - 1)] != '0' && grid[(yOrigin - 1) * width + (xOrigin - 1)] != BOMB_SYMBOL) found[(yOrigin - 1) * width + (xOrigin - 1)] = 1;

		if (yOrigin < height - 1 && xOrigin < width - 1)
			if (grid[(yOrigin + 1) * width + (xOrigin + 1)] != '0' && grid[(yOrigin + 1) * width + (xOrigin + 1)] != BOMB_SYMBOL) found[(yOrigin + 1) * width + (xOrigin + 1)] = 1;

		if (yOrigin > 0 && xOrigin < width - 1)
			if (grid[(yOrigin - 1) * width + (xOrigin + 1)] != '0' && grid[(yOrigin - 1) * width + (xOrigin + 1)] != BOMB_SYMBOL) found[(yOrigin - 1) * width + (xOrigin + 1)] = 1;

		if (yOrigin < height - 1 && xOrigin > 0)
			if (grid[(yOrigin + 1) * width + (xOrigin - 1)] != '0' && grid[(yOrigin + 1) * width + (xOrigin - 1)] != BOMB_SYMBOL) found[(yOrigin + 1) * width + (xOrigin - 1)] = 1;
	}
}

int main()
{
	int gameWidth = 15;
	int gameHeight = 15;
	int amountBombs = 45;

	initalize(Default, gameWidth*12, gameHeight*12, 3, 3, Default, Color(40,40,40));
	Image square = createImage("./Sprites/square.acre");
	Image bomb = createImage("./Sprites/bomb.acre");
	Image flag = createImage("./Sprites/flag.acre");

	while (true)
	{
		int selectedX = 0, selectedY = 0;
		grid = malloc(sizeof(int) * gameWidth * gameHeight);
		found = malloc(sizeof(int) * gameWidth * gameHeight);
		for (int i = 0; i < gameWidth * gameHeight; i++)
			found[i] = 0, grid[i] = 0;

		for (int i = 0; i < amountBombs; i++)
		{
			int bombX = rand() % gameWidth;
			int bombY = rand() % gameHeight;
			grid[bombY * gameWidth + bombX] = BOMB_SYMBOL;
		}

		bool end = false;
		calculateNum(gameWidth, gameHeight);

		while (!end)
		{
			if (key(Right).pressed) selectedX++;
			if (key(Left).pressed) selectedX--;
			if (key(Up).pressed) selectedY--;
			if (key(Down).pressed) selectedY++;
			
			if (key(Q).pressed)
			{
				if (grid[selectedY * gameWidth + selectedX] != BOMB_SYMBOL)
					calculateNothing(gameWidth, gameHeight, selectedX, selectedY);
				else
					end = true;

				found[selectedY * gameWidth + selectedX] = 1;
			}
			if (key(W).pressed)
			{
				if (found[selectedY * gameWidth + selectedX] == FLAG)
					found[selectedY * gameWidth + selectedX] = 0;
				else if (found[selectedY * gameWidth + selectedX] != 1)
					found[selectedY * gameWidth + selectedX] = FLAG;
			}
			drawBoard(gameWidth, gameHeight, square, bomb, flag, false, true);
			drawRect(selectedX * 12, selectedY * 12, selectedX * 12 + 11, selectedY * 12 + 11, Red);
			//drawPoint(Mouse.x, Mouse.y, Yellow);
			render(true);
		}
		drawBoard(gameWidth, gameHeight, square, bomb, flag, true, false);
		free(grid);
		free(found);
		render(false);
		while (!key(EnterKey).pressed);
	}
	return 0;
}
