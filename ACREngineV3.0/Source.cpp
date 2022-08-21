//sysDrawNumber(0, 0, Screen, wbsr.dwSize.X, 0, DefaultFont, White, Black);
#define SHOW_FPS
#define ACRE_START
#include "ACREngine.h"

int main()
{
	initalize("TITLE", 60, 60, 9, 9, Default, Red);

	while (!key(Esc).pressed)
	{
		if (key(R).held)
		{
			
		}

		for (int i = 0; i < Screen.width; i++)
			for (int j = 0; j < Screen.height; j++)
				drawPixel(i, j, Color(Random(0, 255), Random(0, 255), Random(0, 255)));

		sysDrawNumber(0, 0, Screen, buffH, 0, DefaultFont, White, Black);
		//if (key(E).held)
		render(true);
		//else
			//printf("%d, %d. Sw:%d, Sh:%d\n", buffW, buffH, Screen.width, Screen.height);

	}
}

/*
#include <Windows.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	while (1)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int columns, rows;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

		printf("columns: %d, rows: %d\n", columns, rows);
	}

	return 0;
}
*/