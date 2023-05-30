#include "../ConsoleEngine.h"

int main()
{
	initalize("Performace", 300, 100, 2, 4, Default, Default);
	int xLoc = 1;
	while (true)
	{
		drawSquare(xLoc, 3, xLoc + 4, 10, Default, Blue);
		//Sleep(1);
		render(false);
		xLoc++;
	}
	return terminate();
}