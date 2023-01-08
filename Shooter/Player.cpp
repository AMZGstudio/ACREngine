#include "Player.h"

Player::Player() : Entity(100)
{
	x = Width(Screen) / 2;
	y = Height(Screen) / 2;
}

void Player::draw()
{
	drawCircle(x, y, RADIUS, LightBlue);
}

void Player::update()
{
	if (key(W).held) vy -= timePerSec(60);
	if (key(A).held) vx -= timePerSec(60);
	if (key(S).held) vy += timePerSec(60);
	if (key(D).held) vx += timePerSec(60);

	if(vx != 0) vx += (vx < 0 ? timePerSec(10) : -timePerSec(10)) * 3;
	if(vy != 0) vy += (vy < 0 ? timePerSec(10) : -timePerSec(10)) * 3;

	if (vx < 0.2 && vx > -0.2) vx = 0;
	if (vy < 0.2 && vy > -0.2) vy = 0;

	x += timePerSec(vx);
	y += timePerSec(vy);
}