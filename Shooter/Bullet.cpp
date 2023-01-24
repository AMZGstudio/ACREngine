#include "Bullet.hpp"
#include "Collision.hpp"
#include <cmath>
#include <algorithm>

Bullet::Bullet(int px, int py, float pvx, float pvy, int mx, int my) : Entity(500)
{
	x = px, y = py;
	float th = atan((float)abs(my - py) / (float)abs(mx - px));

	vx = cos(th) * _vel;
	vy = sin(th) * _vel;

	if (mx < px) vx *= -1;
	if (my < py) vy *= -1;

	//vx += pvx;
	//vy += pvy;

}

void Bullet::draw()
{
	drawPixel(x, y, Yellow);
}

void Bullet::update()
{
	x += timePerSec(vx);
	y += timePerSec(vy);
}

bool Bullet::damageOther(std::vector<Zombie>& z, float hitAmount)
{
	for (int i = 0; i < z.size(); i++)
		if (Collision::p2cCollide(x, y, z[i].getX(), z[i].getY(), z[i].getRadius()))
		{
			z[i].hit(hitAmount);
			return true;
		}
			
	return false;
}
