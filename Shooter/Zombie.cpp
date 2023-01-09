#include "Zombie.h"
#include <cmath>

Zombie::Zombie(Player& p) : Entity(100), player(p)
{
	x = Width(Screen) + RADIUS;
	y = Random(4, Height(Screen)-4);
}

Zombie::Zombie(const Zombie& other) : Entity(other.health), player(other.player)
{
	x = other.x;
	y = other.y;
}

Zombie& Zombie::operator=(const Zombie& other)
{
	this->health = other.health;
	this->player = other.player;
	this->vx = other.vx;
	this->vy = other.vy;
	this->x = other.x;
	this->y = other.y;
	return *this;
}

void Zombie::update()
{
	float dx = player.getX() - x;
	float dy = player.getY() - y;

	if (dx < 0) vx -= timePerSec(40);
	if (dx > 0) vx += timePerSec(40);
	if (dy < 0) vy -= timePerSec(40);
	if (dy > 0) vy += timePerSec(40);

	if (vx < -40) vx = -40;
	if (vy < -40) vy = -40;
	if (vx > 40) vx = 40;
	if (vy > 40) vy = 40;

	if (vx != 0) vx += (vx < 0 ? timePerSec(10) : -timePerSec(10)) * 3;
	if (vy != 0) vy += (vy < 0 ? timePerSec(10) : -timePerSec(10)) * 3;

	if (vx < 0.2 && vx > -0.2) vx = 0;
	if (vy < 0.2 && vy > -0.2) vy = 0;

	x += timePerSec(vx);
	y += timePerSec(vy);
}

void Zombie::draw()
{
	Space sp = drawCircle(x, y, RADIUS, Green);
	spDrawNumber(Centered, -RADIUS-3, sp, health, 0, EightBit, Red);
}

float Zombie::getRadius()
{
	return RADIUS;
}

bool Zombie::pointCollide(int x, int y)
{
	float distX = x - this->x;
	float distY = y - this->y;

	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= RADIUS) {
		return true;
	}
	return false;
}