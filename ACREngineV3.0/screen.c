
#include "screen.h"

screenData initalizeScreen()
{
	screenData s;
	s.doFade = false;
	s.fadeProgress = 0;
	s.area = createArea(Width(Screen), Height(Screen), Default, Blue);

	return s;
}

void drawScreen(screenData* s)
{
	if (s->doFade)
	{
		if (s->fadeProgress < 3)
			for (int i = 0; i < Width(Screen); i++)
				for (int j = 0; j < Height(Screen); j++)
				{
					short r, g, b;
					Xterm(s->area.colBack[j * Width(Screen) + i], &r, &g, &b);
					drawPixel(i, j, Color(clamp(r - map(s->fadeProgress, 0, 1, 0, 255), 0, 255), clamp(g - map(s->fadeProgress, 0, 1, 0, 255), 0, 255), clamp(b - map(s->fadeProgress, 0, 1, 0, 255), 0, 255)));

				}
		else
			drawRectFilled(0, 0, Width(s->area), Height(s->area), Black);

		s->fadeProgress += timePerSec(3);
	}
	else
		drawArea(0, 0, s->area);
}