//make sure height is half of width
#define WIDTH 100
#define HEIGHT 50
#define FONT_WIDTH 7
#define FONT_HEIGHT 14
#define WAIT 0

#include "ConsoleEngine.h"
bool darkMode = true;

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
	render(true);
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
			drawArray(*cycles, i, values);
		}
	while (!key(escapeKey, 0));
}

void menu()
{
	int selected = 0, pressed = 0;
	char menuOptions[][100] = { "Start Sorting", "Switch mode ", "Resize Window" };
	char input[100] = { 0 };
	Window* Window1 = createWindow(3, 2, WIDTH - 3, HEIGHT - 2, singl, true, Default, Default);
	Menu* menu = createMenu(menuOptions, 3, 20, 1, &selected, true, false, Window1);
	
	while (!pressed || selected != 0)
	{
		clearScreen();
		pressed = key(enterKey, 200);
		arrowInput(&selected, 2, 0, Y);
		drawWindow(Window1);

		if(pressed == 1 && selected == 1)
		{
			if (darkMode == true) darkMode = false, defaultFrontColor = Black, defaultBackColor = White;
			else if (darkMode == false) darkMode = true, defaultFrontColor = White, defaultBackColor = Black;
		}
		render(true);
	}
	deleteWindow(Window1);
	deleteMenu(menu);
}


int main()
{
	initalize("Sorting Algorithm", None, None);
	menu();

	int numbers[WIDTH / 2] = { 0 }, cycles = 0;
	randomizeNumbers(numbers, WIDTH / 2);
	bubbleSort(&cycles, numbers, WIDTH / 2);

	return terminate();
}
