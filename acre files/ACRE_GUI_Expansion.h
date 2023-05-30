#ifndef MENU_EXPANSION
#define MENU_EXPANSION

void drawMenu(int xStart, int yStart, Space screenSpace, int menuWidth, int seperation, int selected, int numOptions, int colorFront, int colorBack, ...)
{
	char** options = (char**)malloc(sizeof(char*) * numOptions);
	Space rect;

	va_list ptr;
	va_start(ptr, colorBack);

	for (int i = 0; i < numOptions; i++)
	{
		options[i] = (char*)malloc(sizeof(char) * 100);
		for (int j = 0; j < 100; j++) options[i][j] = 0;
		strcpy(options[i], va_arg(ptr, char*));
	}
	va_end(ptr);
	int longestOption = 0;
	for (int i = 0; i < numOptions; i++)
		if ((signed)strlen(options[i]) >= longestOption) longestOption = strlen(options[i]);

	int menuPadding = ((menuWidth - longestOption) / 2);
	for (int i = 0; i < numOptions; i++)
	{
		if (i == selected)
		{
			if (xStart == Centered) rect = sysDrawRect(xStart, yStart, menuWidth, 1, screenSpace, Default, true, colorFront, colorBack);
			else rect = sysDrawRect(xStart, yStart, xStart + menuWidth, yStart, screenSpace, Default, true, colorFront, colorBack);
			sysDrawText(Centered, 0, rect, options[i], Default, Default, Default);
		}
		else
		{
			if (xStart == Centered) rect = sysDrawRect(xStart, yStart, menuWidth, 1, screenSpace, Default, false, colorBack, Default);
			else rect = sysDrawRect(xStart, yStart, xStart + menuWidth, yStart, screenSpace, Default, true, Default, Default);
			sysDrawText(Centered, 0, rect, options[i], Default, Default, Default);
		}
		yStart += seperation;
	}
	for (int i = 0; i < numOptions; i++)
		free(options[i]);
	free(options);
}



#endif