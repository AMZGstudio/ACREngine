#define WAIT 10
#include "ConsoleEngine.h"

int main()
{
	initalize("Flappy Bird", 80, 48, 12, 12, Default, Cyan);
	float birdPosition = 10.0f;
	float birdVelocity = 0.0f;
	float birdAcceleration = 0.0f;
	float gravity = 0.05f;
	while (true)
	{
		drawSquare(1, height() - 2, width(), height(), Default, Green);

		if (key(A).pressed && birdVelocity > gravity + 0.05f)
		{
			birdAcceleration = 0.0f;
			birdVelocity = -1.3f;
		}
		else
			birdAcceleration += gravity;

		if (birdAcceleration >= gravity)
			birdAcceleration = gravity;

		birdVelocity += birdAcceleration;
		birdPosition += birdVelocity;

		
		drawSquare((int)(width() / 3), (int)birdPosition, (int)(width() / 3) + 3, (int)(birdPosition)+3, Default, Yellow);


		render(true);
	}
	//render(true);
	while (!key(A).pressed);
}