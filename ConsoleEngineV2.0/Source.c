#include "ACREngine.h"

int main()
{
	initalize(Default, 200, 110, 6,6, Black, White);
	Image bird = createImage("C:/Uriel/birdUp.acre");
	float x = 1;
	while (!key(EscapeKey).pressed)
	{
		drawImage(x, Centered, bird);
		x+=50 * elapsedTime;
		render(true);
	}
	render(true);
	while (!key(EscapeKey).pressed);
	return terminate();
}