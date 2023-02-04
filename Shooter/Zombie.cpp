#include "Zombie.hpp"
#include "Player.hpp"
#include "Collision.hpp"

#include "../ACRE Files/ACRE_Fonts.h"

#include "../ACRE Files/ACRE_Transform.h"

#include "../ACRE Files/ACRE_Gameplay.h"

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

Zombie::Zombie(const Zombie& other) : Entity(other), _player(other._player), _zombies(other._zombies), _speed(other._speed)
{
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
	if (playerCollide())
	{
		_player.hit(timePerSec(10));
		//acre::Renderer::doShake = true;
	}

	float dx = _player.getX() - x;
	float dy = _player.getY() - y;

	if (abs(dx) < 0.3) dx = 0;
	if (abs(dy) < 0.3) dy = 0;

	if (dx < 0) vx -= timePerSec(_speed);
	if (dx > 0) vx += timePerSec(_speed);
	if (dy < 0) vy -= timePerSec(_speed);
	if (dy > 0) vy += timePerSec(_speed);

	vx = clamp(vx, _speed * -1, _speed);
	vy = clamp(vy, _speed * -1, _speed);
	
	if (vx != 0) vx += (vx < 0 ? timePerSec(30) : -timePerSec(30));
	if (vy != 0) vy += (vy < 0 ? timePerSec(30) : -timePerSec(30));

	if (abs(vx) < 0.1) vx = 0;
	if (abs(vy) < 0.1) vy = 0;

	x += timePerSec(vx);
	if (zombieCollide())
		x -= timePerSec(vx);

	y += timePerSec(vy);
	if (zombieCollide())
		y -= timePerSec(vy);

	// drawNumber(x, y, vx, EightBit, Pink);
}

void Zombie::draw()
{
	Space sp = drawCircle(x, y, RADIUS, DarkGreen);
	spDrawNumber(Centered, -RADIUS-3, sp, health, 0, Pzim, DarkRed);
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
	return 2 + waveNum * 2;
}

void Wave::reset()
{
	waveStarted = false;
	waveNum = 0;
	amountSpawned = 0;
	timeFromSpawned = 0;
}

bool Wave::spawnZombie()
{
	if (Wave::amountSpawned >= Wave::getNumEntities())
		Wave::waveStarted = false;

	if (!Wave::waveStarted)
		return false;

	Wave::timeFromSpawned += timePerSec(1);

	float secsForZombieSpawn = 2 - (Wave::waveNum / 10);
	if (Wave::timeFromSpawned > secsForZombieSpawn)
	{
		Wave::timeFromSpawned -= secsForZombieSpawn;
		Wave::amountSpawned += 1;
		return true;
	}
	return false;
}

bool Wave::nextWave()
{
	if (!Wave::waveStarted)
	{
		waveNum++;
		Wave::waveStarted = true;
		return true;
	}	
	return false;
}