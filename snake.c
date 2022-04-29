#define FONT_WIDTH 10
#define FONT_HEIGHT 20
#define MAP_W 30
#define MAP_H 17

#include "ConsoleEngine.h"

void spawnApple(int map[MAP_W][MAP_W], int* appleX, int* appleY)
{
	do
	{
		*appleX = rand() % (MAP_W - 2 - 1) + 2;
		*appleY = rand() % (MAP_H - 2 - 1) + 2;
	} while (map[*appleY][*appleX] != 1);

	map[*appleY - 1][*appleX - 1] = -1; // apple number
}

void drawMap(int map[MAP_H][MAP_W])
{
	int xReal = 1, yReal = 1;
	for (int y = 0; y < MAP_H; y++)
	{
		for (int x = 0; x < MAP_W; x++)
		{
			if (map[y][x] == 1) drawSquare(xReal, yReal, xReal + 4, yReal + 2, Default, Black);
			if (map[y][x] == 0) drawSquare(xReal, yReal, xReal + 4, yReal + 2, Default, Blue);
			if (map[y][x] == -1) drawSquare(xReal, yReal, xReal + 4, yReal + 2, Default, Red);
			if (map[y][x] > 1) drawSquare(xReal, yReal, xReal + 4, yReal + 2, Default, White);
			xReal += 4;
		}
		yReal += 2;
		xReal = 1;
	}
}

int snakeLoop()
{
	int grid[MAP_H][MAP_W] = { 0 };
	char direction = 'D', tempDirection = 'D';
	int headX = 4, headY = 3, length = 4, appleX = 0, appleY = 0, elapsed = 0, score = 0;

	// set grid to default
	for (int y = 0; y < MAP_H; y++)
		for (int x = 0; x < MAP_W; x++)
			grid[y][x] = (y == 0 || y == MAP_H - 1 || x == 0 || x == MAP_W - 1) ? 0 : 1;

	spawnApple(grid, &appleX, &appleY);
	//put snake on map
	grid[2][1] = 2;
	grid[2][2] = 3;
	grid[2][3] = 4;

	bool run = true, moveSnakeBody = true;

	clearScreen();
	while (run)
	{
		time_t prevTime = clock();

		// render everything to the screen
		drawMap(grid);
		drawText("Score: ", 2, 1, Default, Default);
		drawNumber(score, 9, 1, Default, Default);
		render(false);

		// move head
		if (direction == 'W') headY--;
		else if (direction == 'A') headX--;
		else if (direction == 'S') headY++;
		else if (direction == 'D') headX++;

		//check if head hit apple
		if (grid[headY - 1][headX - 1] == -1) // -1 is apple code
		{
			moveSnakeBody = false, length++, score += 10;
			spawnApple(grid, &appleX, &appleY);
		}
		else moveSnakeBody = true;
		//check if snake hit a wall/itself
		if (grid[headY - 1][headX - 1] > 1 || grid[headY - 1][headX - 1] == 0) run = false;

		//move snakes body
		if (moveSnakeBody)
			for (int y = 0; y < MAP_H; y++)
				for (int x = 0; x < MAP_W; x++)
					if (grid[y][x] > 1) grid[y][x]--;

		//move head
		grid[headY - 1][headX - 1] = length;

		//get input and wait
		tempDirection = direction, elapsed = 0;
		while (elapsed < 150)
		{
			time_t currentTime = clock();
			elapsed = ((int)currentTime) - ((int)prevTime);

			if (key('W', 0) && tempDirection != 'S') direction = 'W';
			if (key('S', 0) && tempDirection != 'W') direction = 'S';
			if (key('A', 0) && tempDirection != 'D') direction = 'A';
			if (key('D', 0) && tempDirection != 'A') direction = 'D';
		}
	}
	return score;
}

int main()
{
	srand(time(0));
	initalize("Snake demo", MAP_W * 4, MAP_H * 2, 8, 16, Default, Default);
	int highScore = 0; bool playAgain = true;

	Window* window = createWindow(thirds(1, X, No), thirds(1, Y, No), thirds(2, X, No), thirds(2, Y, No), 1, No, Default, Cyan);
	Menu* menu = createMenu("Play", 1, 10, 0, 0, true, true, window);
		
	while (!key(enterKey, 0))
	{
		drawWindow(window);
		render(true);
	}
	deleteMenu(menu);
	window->optionMenu = 0;

	while (playAgain)
	{
		int score = snakeLoop();
		if (score > highScore) highScore = score;

		window->colorFront = Black;

		drawWindow(window);
		drawText("Press Enter To Play", central(20, 1, width()), 13, Black, Default);
		drawText("Highscore: ", central(20, 1, width()), 15, Black, Default);
		drawNumber(highScore, central(20, 1, width()) + 11, 15,Black, Default);

		render(false);
		while (!key(enterKey, 0));
	}
	deleteWindow(window);

	return terminate();
}