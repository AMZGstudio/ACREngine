#include "Bullet.hpp"
#include "Collision.hpp"
#include <cmath>
#include <algorithm>

Bullet::Bullet(int px, int py, float playerRadius, int mx, int my) : Entity(500)
{
	
	float th = atan((float)abs(my - py) / (float)abs(mx - px));

	x = cos(th) * (playerRadius+1);
	y = sin(th)* (playerRadius+1);

	if (mx < px) x *= -1;
	if (my < py) y *= -1;

	x += px;
	y += py;

	vx = cos(th) * _vel;
	vy = sin(th) * _vel;

	if (mx < px) vx *= -1;
	if (my < py) vy *= -1;

	//vx += pvx;
	//vy += pvy;

}

void Bullet::draw()
{
	drawPixel(x, y, DarkYellow);
}

void Bullet::update()
{
	x += timePerSec(vx);
	y += timePerSec(vy);
}

bool Bullet::damageZombie(std::vector<Zombie>& z, float hitAmount)
{
	for (int i = 0; i < z.size(); i++)
		if (Collision::p2cCollide(x, y, z[i].getX(), z[i].getY(), z[i].getRadius()))
		{
			if (rand() % 2 == 0 ) Audio::playSound("dead");
			z[i].hit(hitAmount);
			return true;
		}
			
	return false;
}

bool Bullet::damagePlayer(Player& player, float hitAmount)
{
	if (Collision::p2cCollide(x, y, player.getX(), player.getY(), player.getRadius()))
	{
		player.hit(hitAmount);
		return true;
	}

	return false;
}
