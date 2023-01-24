#pragma once
#include "Entity.h"
#include "Player.h"

#include <vector>
#define RADIUS 5

class Wave
{
public:
	static bool waveStarted;
	static int waveNum;
	static int amountSpawned;
	static float timeFromSpawned;

public:
	static void attemptNext(bool startCondition);
	static bool spawnZombie(float secsForZombieSpawn);
	static int getNumEntities();
};

class Zombie : public Entity
{
private:
	Player& _player;
	std::vector<Zombie>& _zombies;
	float _speed;

public:
	Zombie(Player& p, std::vector<Zombie>& zombies, float speed);
	Zombie(const Zombie& other);

	Zombie& operator=(const Zombie& other);
	bool operator==(const Zombie& rhs);

	void update() override;
	void draw() override;
	bool zombieCollide() const;
	bool playerCollide() const;

	float getRadius();
};

