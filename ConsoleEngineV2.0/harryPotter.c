#define FPS 58
#include "ACREngine.h"

int main()
{
	initalize("Test", 200, 100, 6, 6, Default, 234);
	Image harry = createImage("C:/Uriel/harry.acre");
	Image ball = createImage("C:/Uriel/ball.acre");
	Point balls[30] = { NULL };

	int location = 1;

	while (key(EscapeKey).pressed == false)
	{
		drawImage(2,location, harry);
		drawImage(Centered, Centered, ball);

		if (key(A).held) location++;
		if (key(Q).held) location--;
		render(true);
	}
	return terminate();
}