#define WIDTH 100
#define HEIGHT 40

#include "../ConsoleEngine.h"

int main()
{
	initalize("Demo", None, None);
	char menuOptions[3][100] = { "Option 1", "Option 2", "diamond" }, input[100] = { 0 };
	
	int selected = 0;

	Window* window = createWindow(thirds(1, X, No), thirds(1, Y, No), thirds(2, X, No), thirds(2, Y, No), singl, true, Default, Default);
	Menu* menu = createMenu(menuOptions, 3, 20, 2, &selected, true, true, window);

	drawWindow(window);
	render(false);
	
	while (!key(escapeKey, 100))
	{
		arrowInput(&selected, 2, 0, Y);
		drawWindow(window);
		drawText(input, 2, 2, Default, Default);
		render(true);
	}
	deleteMenu(menu), deleteWindow(window);
	return terminate();
}