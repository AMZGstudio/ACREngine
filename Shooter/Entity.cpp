#include "Entity.h"

Entity::Entity(float health)
{
	x = 0, y = 0, vx = 0, vy = 0, this->health = health;
}

void Entity::hit(float amount)
{
	health -= amount;
}

void Entity::kill()
{
	health = 0;
}

bool Entity::isAlive() const
{
	return health > 0;
}

float Entity::getX()
{
	return x;
}

float Entity::getY()
{
	return y;
}

float Entity::getHealth()
{
	return health;
}
