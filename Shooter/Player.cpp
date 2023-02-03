#include "Player.hpp"

Player::Player() : Entity(100)
{
	x = Width(Screen) / 2;
	y = Height(Screen) / 2;
}

void Player::draw()
{
	drawCircle(x, y, RADIUS, Cyan);
}

void Player::update()
{
	if (key(W).held || key(Up).held) vy -= timePerSec(60);
	if (key(A).held || key(Left).held) vx -= timePerSec(60);
	if (key(S).held || key(Down).held) vy += timePerSec(60);
	if (key(D).held || key(Right).held) vx += timePerSec(60);

	if (vx > 120) vx = 120;
	if (vx < -120) vx = -120;

	if (vy > 120) vy = 120;
	if (vy < -120) vy = -120;

	if(vx != 0) vx += (vx < 0 ? timePerSec(10) : -timePerSec(10)) * 3;
	if(vy != 0) vy += (vy < 0 ? timePerSec(10) : -timePerSec(10)) * 3;

	if (vx < 0.2 && vx > -0.2) vx = 0;
	if (vy < 0.2 && vy > -0.2) vy = 0;

	x += timePerSec(vx);
	y += timePerSec(vy);

	if (x > Width(Screen)) x = 0;
	if (x < 0) x = Width(Screen);

	if (y > Height(Screen)) y = 0;
	if (y < 0) y = Height(Screen);
}

float Player::getRadius() const
{
	return RADIUS;
}

