#include "ConsoleEngine.h"

int main()
{
	srand(time(0));
	initalize("Demo", 140, 100, 7, 7, Default, Default);

	while (true)
	{
		for (int i = 1; i <= height(); i++)
			for (int j = 1; j <= width(); j++)
				drawChar(' ', j, i, Black, rand() % 8);

		render(false);
	}
	return terminate();
}