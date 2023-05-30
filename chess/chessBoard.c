#include <stdio.h>
#include <conio.h>

#define WIDTH 120
#define HEIGHT 70
#define FONT_WIDTH 5
#define FONT_HEIGHT 8

#include "../ConsoleEngine.h"

char pon[][8] = { "  ___  ",
				  " (   ) ",
				  "  | |  ",
				  " /___\\ ",
				  "(_____)" };


void drawCheckerBoard()
{
	int color = 0, realX = 1, realY = 1;

	for (int y = 1; y <= 10; y += 1)
	{
		for (int x = 1; x <= 10; x += 1)
		{
			if (color == Green) color = Red;
			else color = Green;
	
			drawSquare(realX, realY, realX + 11 , realY + 6, Default, color);
			if (y < 3) drawBuffer(pon, 5, realX + 2, realY + 1, Black, Default);
			if (y > 8) drawBuffer(pon, 5, realX + 2, realY + 1, White, Default);
			realX += 12;
		}
		realY += 7, realX = 1;
		if (color == Green) color = Red;
		else color = Green;
	}
}

int main()
{
	initalize("Chess", None, None);

	while (true)
	{
		drawCheckerBoard();
		render(false);
	}

	terminate();
	return 0;
}











































/*
enum locations {lobby, tutorial, game, house};

int main(void)
{
	int location = lobby, selected = 0;
	initalize(WIDTH, HEIGHT, "Dork V3");

	char options[][100] = {"yes", "no ", "umm"};

	while (1)
	{
		switch (location)
		{
		case lobby: appendMenu(selected, options, 3, 6, 54, 10);
					char letter = _getch();
					if (letter == 's') selected++;
					if (letter == 'w') selected -= 1;
					break;

		case tutorial:
			break;

		case game:
			break;

		case house:
			break;
		}

		render(screens, WIDTH, HEIGHT);
	}

	return 0;
}*/