#include "Bullet.h"
#include <cmath>
#include <algorithm>

Bullet::Bullet(int px, int py, int mx, int my) : Entity(100)
{
	x = px, y = py;
	float th = atan((float)abs(my - py) / (float)abs(mx - px));

	vx = (cos(th) * _vel);
	vy = (sin(th) * _vel);

	if (mx < px) vx *= -1;
	if (my < py) vy *= -1;
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
		if (z[i].pointCollide(x, y))
		{
			z[i].hit(hitAmount);
			return true;
		}
			
	return false;
}
