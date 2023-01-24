#include "Entity.hpp"

Entity::Entity(float health)
{
	x = 0, y = 0, vx = 0, vy = 0, this->health = health;
}

Entity::Entity(const Entity& other)
{
	x = other.x;
	y = other.y;
	vx = other.vx;
	vy = other.vy;
	health = other.health;
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

float Entity::getVX()
{
	return vx;
}

float Entity::getVY()
{
	return vy;
}

float Entity::getHealth()
{
	return health;
}
