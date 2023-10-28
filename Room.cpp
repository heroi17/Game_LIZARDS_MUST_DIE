#include "Room.h"

#include <vector>

#include "Item.h"
#include "Entity.h"
#include "Lizard.h"

using namespace GameLogic;

GameLogic::Room::Room()
{
	_enemies = {};
	_rewardItem = nullptr;
}

GameLogic::Room::~Room()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		delete _enemies[i];
	}
	delete _rewardItem;
}

GameLogic::Room::Room(std::vector<Entity*> enemies, Item* rewardItem)
{
	std::vector<Entity*> tempvec = _enemies;
	_enemies = enemies;

	for(int i = 0; i < tempvec.size(); i++)
	{
		delete tempvec[i];
	}

	Item* tempit = _rewardItem;
	_rewardItem = rewardItem;
	delete tempit;
}

GameLogic::Room::Room(const Room& otherRoom)
{
	std::vector<Entity*> tempvec = _enemies;
	_enemies = otherRoom._enemies;

	for (int i = 0; i < tempvec.size(); i++)
	{
		delete tempvec[i];
	}

	Item* tempit = _rewardItem;
	_rewardItem = otherRoom._rewardItem;
	delete tempit;
}

Room& GameLogic::Room::operator=(const Room& otherRoom)
{
	if (this != &otherRoom) {
		_enemies = otherRoom._enemies;
		_rewardItem = otherRoom._rewardItem;
	}
	return *this;
}