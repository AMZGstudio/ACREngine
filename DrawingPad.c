#include "ConsoleEngine.h"

#define WIDTH 50
#define HEIGHT 30

int main()
{
	initalize(WIDTH, HEIGHT, White, Cyan);
	int x = 5, y = 5, selectedColor = Blue, amountColors = 8;

	int colors[48][24] = { 0 };
	for (int x = 0; x < 48; x++)
		for (int y = 0; y < 24; y++)
			colors[x][y] = White;

	while (1)
	{
		for (int i = 0; i < WIDTH - 2; i++)
			for (int j = 0; j < HEIGHT - 10; j++)
				drawChar(' ', i + 2, j + 2, Default, colors[i][j]);

		input(&y, HEIGHT - 9, 2, Y);
		input(&x, WIDTH - 1, 2, X);

		if (getKeyInput('1')) selectedColor = Black;
		if (getKeyInput('2')) selectedColor = Black + 1;
		if (getKeyInput('3')) selectedColor = Black + 2;
		if (getKeyInput('4')) selectedColor = Black + 3;
		if (getKeyInput('5')) selectedColor = Black + 4;
		if (getKeyInput('6')) selectedColor = Black + 5;
		if (getKeyInput('7')) selectedColor = Black + 6;
		if (getKeyInput('8')) selectedColor = Black + 7;
		if (getKeyInput('E')) colors[x - 2][y - 2] = selectedColor;
		
		drawChar('#', x, y, Yellow, Yellow);
		drawText("Welcome to the drawing Pad!", 2, 23, Black, Default);
		drawText("Use WASD keys to move, and press E to draw!", 2, 24, Black, Default);
		drawText("These are the colors you can use:", 2, 26, Black, Default);
		drawText("  1    2    3    4    5    6    7", 2, 28, White, Default);		
		
		int color = Black;
		for (int i = 2; i < amountColors * 5; i += 5)
		{
			drawSquare(i, 27, i + 4, 29, Default, color);
			color++;
		}
		drawChar('8', 39, 28, Black, White);
		render();
	}
	return 0;
}
