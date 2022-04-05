#include "ConsoleEngine.h"

//make sure height is half of width
#define WIDTH 80
#define HEIGHT 40

void drawArray(int cycles, int selected, int* values)
{
	clearScreen();
	char cyclesString[100] = { 0 }; _itoa_s(cycles, cyclesString, 100, 10);
	drawText("Cycles:", 2, 2, Default, Default); drawText(cyclesString, 10, 2, Default, Default);

	int realLoc = 1;
	for (int j = 1; j <= WIDTH / 2; j++)
	{
		if (j - 2 == selected)
		{
			drawSquare(realLoc, values[j - 1], realLoc + 1, HEIGHT, Default, Red);
			drawSquare(realLoc - 2, values[j - 2], realLoc - 1, HEIGHT, Default, Yellow);
		}
		else drawSquare(realLoc, values[j - 1], realLoc + 1, HEIGHT, Default, defaultFrontColor);
		realLoc += 2;
	}
	render();
}

void randomizeNumbers(int numbers[], int amountNums)
{
	srand(time(NULL));
	for (int i = 0; i < amountNums; i++)
		while (1)
		{
			int inNumbers = 0, number = rand() % (amountNums + 1);;
			//check if the number is in the numbers already.
			for (int j = 0; j < amountNums; j++) if (number == numbers[j]) inNumbers = 1;
			if (inNumbers == 0) { numbers[i] = number; break; }
		}
}

void bubbleSort(int* cycles, int* values, int size)
{
	for (int run = size; run > 1; run--)
		for (int i = 0; i < run - 1; i++)
		{
			(*cycles)++;
			if (values[i] < values[i + 1] && i != size - 1)
			{
				int temp = values[i]; //swap two values.
				values[i] = values[i + 1]; values[i + 1] = temp;
			}
			startRender();
			drawArray(*cycles, i, values);
		}
}

int main()
{
	int enterPressed = 0, menuWidth = 20, selected = 0, darkLight = 2, cycles = 0, numbers[WIDTH / 2] = { 0 };
	char menuOptions[][100] = { "Start Sorting", "Light mode ", "Change Speed" };
	
	initalize("Sorting Algorithm", WIDTH, HEIGHT, 8, 16, None, None);

	while (enterPressed == 0 || selected != 0)
	{
		clearScreen();
		enterPressed = getKeyInput(enterKey);
		keyInput(&selected, 2, 0, Y);

		if (enterPressed == 1 && selected == 1)
		{
			if (darkLight == 1)
			{
				strcpy_s(menuOptions[1], 11, "Light mode");
				defaultFrontColor = White, defaultBackColor = Black, darkLight = 2;
			}
			else if (darkLight == 2)
			{
				strcpy_s(menuOptions[1], 11, "Dark mode");
				defaultFrontColor = Black, defaultBackColor = White, darkLight = 1;
			}
		}
		drawText("Demo program - consoleEngine - AMZG", 3, HEIGHT - 1, Default, Default);
		drawWindow(3, 2, 9 + menuWidth, 10, 1, Default, Default);
		drawMenu(selected, menuOptions, 3, menuWidth, 1, 6, 4);
		render();
	}
	randomizeNumbers(numbers, WIDTH / 2);
	bubbleSort(&cycles, numbers, WIDTH / 2);

	terminate();
	return 0;
}
