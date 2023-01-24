#include "Zombie.hpp"
#include "Player.hpp"
#include "Collision.hpp"

#include "../ACRE Files/ACRE_Fonts.h"

#include <cmath>
#include <algorithm>
#include <vector>

Zombie::Zombie(Player& p, std::vector<Zombie>& zombies, float speed) : Entity(100), _player(p), _zombies(zombies), _speed(speed)
{
	float distanceToCornerX = Width(Screen) / 2;
	float distanceToCornerY = Height(Screen) / 2;

	float distance = sqrt(distanceToCornerX * distanceToCornerX + distanceToCornerY * distanceToCornerY) + (RADIUS / 2.0f) + 4;

	do
	{
		float round = Random(0, 360);

		x = (distance * cos(round));
		y = (distance * sin(round));

		x += Width(Screen) / 2;
		y += Height(Screen) / 2;
	} while (zombieCollide());
}

Zombie::Zombie(const Zombie& other) : Entity(other.health), _player(other._player), _zombies(other._zombies), _speed(other._speed)
{
	x = other.x;
	y = other.y;
}

Zombie& Zombie::operator=(const Zombie& other)
{
	this->health = other.health;
	this->_player = other._player;
	this->_speed = other._speed;
	this->_zombies = other._zombies;
	this->vx = other.vx;
	this->vy = other.vy;
	this->x = other.x;
	this->y = other.y;
	return *this;
}

void Zombie::update()
{
	if(playerCollide())
		_player.hit(timePerSec(10));

	float dx = _player.getX() - x;
	float dy = _player.getY() - y;

	if (dx < 0) vx -= timePerSec(_speed);
	if (dx > 0) vx += timePerSec(_speed);
	if (dy < 0) vy -= timePerSec(_speed);
	if (dy > 0) vy += timePerSec(_speed);

	if (vx < -_speed) vx = -_speed;
	if (vy < -_speed) vy = -_speed;
	if (vx > _speed) vx = _speed;
	if (vy > _speed) vy = _speed;

	if (vx != 0) vx += (vx < 0 ? timePerSec(10) : -timePerSec(10)) * 3;
	if (vy != 0) vy += (vy < 0 ? timePerSec(10) : -timePerSec(10)) * 3;

	if (vx < 0.1 && vx > -0.1) vx = 0;
	if (vy < 0.1 && vy > -0.1) vy = 0;

	x += timePerSec(vx);
	if (zombieCollide())
		x -= timePerSec(vx);

	y += timePerSec(vy);
	if (zombieCollide())
		y -= timePerSec(vy);
}

void Zombie::draw()
{
	Space sp = drawCircle(x, y, RADIUS, Green);
	spDrawNumber(Centered, -RADIUS-3, sp, health, 0, Pzim, Red);
}

float Zombie::getRadius()
{
	return RADIUS;
}

bool Zombie::operator==(const Zombie& rhs)
{
	return x == rhs.x && y == rhs.y && health == rhs.health && vx == rhs.vx && vy == rhs.vy;
}

bool Zombie::zombieCollide() const
{
	for (auto& zombie : _zombies)
	{
		// collsion with other zombies, but make sure it is not checking against itself
		if (Collision::c2cCollide(x, y, RADIUS, zombie.getX(), zombie.getY(), zombie.getRadius()) && !(zombie == *this))
			return true;
	}
	return false;
}

bool Zombie::playerCollide() const
{
	// check collision with player, if hit than damage player
	return Collision::c2cCollide(_player.getX(), _player.getY(), _player.getRadius(), x, y, RADIUS);
	}

int Wave::waveNum = 0;
bool Wave::waveStarted = false;
int Wave::amountSpawned = 0;
float Wave::timeFromSpawned = 0;

int Wave::getNumEntities()
{
	return waveNum * 3;
}

bool Wave::spawnZombie(float secsForZombieSpawn)
{
	if (Wave::amountSpawned >= Wave::getNumEntities())
		Wave::waveStarted = false;

	if (!Wave::waveStarted)
		return false;

	Wave::timeFromSpawned += timePerSec(1);

	if (Wave::timeFromSpawned > secsForZombieSpawn)
	{
		Wave::timeFromSpawned -= secsForZombieSpawn;
		Wave::amountSpawned += 1;
		return true;
	}
	return false;
}

void Wave::attemptNext(bool startCondition)
{
	if (!Wave::waveStarted && startCondition)
	{
		waveNum++;
		Wave::waveStarted = true;
	}	
}