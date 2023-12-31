#include "Room.h"

#include <vector>
#include "Console_Output.h"
#include "first_test_PO.h"
#include "Controller.h"

using namespace GameLogic;

GameLogic::Room::Room()
{
	_enemies = {};
	_rewardItem = nullptr;
	_simulationRoom = new PSimulation::simulation_room();
}

GameLogic::Room::Room(std::vector<Entity*> enemies, Item* rewardItem)
{
	_simulationRoom = new PSimulation::simulation_room();
	_enemies = enemies;
	_rewardItem = rewardItem;
}

GameLogic::Room::Room(const Room& otherRoom)
{
	_simulationRoom = new PSimulation::simulation_room();
	_enemies = otherRoom._enemies;
	_rewardItem = otherRoom._rewardItem;
}

GameLogic::Room::~Room()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		delete _enemies[i];
	}
	delete _rewardItem;

	if (_simulationRoom)
	{
		delete _simulationRoom;
	}
}

Room& GameLogic::Room::operator=(const Room& otherRoom)
{
	_simulationRoom = new PSimulation::simulation_room();
	if (this != &otherRoom) {
		_enemies = otherRoom._enemies;
		_rewardItem = otherRoom._rewardItem;
	}
	return *this;
}

Item* GameLogic::Room::GetRewardItem()
{
	return _rewardItem;
}

std::vector<Entity*> GameLogic::Room::GetEnemies()
{
	return _enemies;
}

void GameLogic::Room::Show()
{
	int update_rate = 20;
	int moveble_obj = _enemies.size();
	int static_obj = 5;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	Console_Output console_1(_simulationRoom, update_rate);

	//make wall for room
	_simulationRoom->add_object(new PO::StaticObject(PMathO::Vec2D(console_1.temp.right / 2, 0), new PColliderO::RectangleCollider(console_1.temp.right, 5.)));
	_simulationRoom->add_object(new PO::StaticObject(PMathO::Vec2D(console_1.temp.right / 2, console_1.temp.bottom), new PColliderO::RectangleCollider(console_1.temp.right, 5.)));
	_simulationRoom->add_object(new PO::StaticObject(PMathO::Vec2D(0, console_1.temp.bottom / 2), new PColliderO::RectangleCollider(5., console_1.temp.bottom)));
	_simulationRoom->add_object(new PO::StaticObject(PMathO::Vec2D(console_1.temp.right, console_1.temp.bottom / 2), new PColliderO::RectangleCollider(5., console_1.temp.bottom)));
	
	
	for (int i = 0; i < moveble_obj; i++) {
		PMathO::Vec2D pos(rand_between(0., console_1.temp.right), rand_between(0., console_1.temp.bottom));
		PMathO::Vec2D speed((double)_enemies[i]->GetSpeed(), (double)_enemies[i]->GetSpeed());
		_simulationRoom->add_object(new PO::MovebleObject(pos, new PColliderO::RectangleCollider((double)_enemies[i]->GetSize(), (double)_enemies[i]->GetSize()), 1., 1., speed));
	}

	for (int i = 0; i < static_obj; i++) {
		PMathO::Vec2D pos(rand_between(0., console_1.temp.right), rand_between(0., console_1.temp.bottom));
		_simulationRoom->add_object(new PO::StaticObject(pos, new PColliderO::CricleCollider(rand_between(4, 10.))));
	}

	PO::MovebleObject* playerObject = new PO::MovebleObject(PMathO::Vec2D(console_1.temp.right / 2, console_1.temp.bottom / 2), new PColliderO::RectangleCollider(25., 25.), 1., 10., PMathO::Vec2D(0, 0));
	_simulationRoom->add_object(playerObject);

	//start physic engine
	console_1.StartOutput();
	_simulationRoom->StartSimulation();

	// Asserting control on main character
	Controller controller;
	controller.AssertControllOver(playerObject);


	_simulationRoom->StopSimulation();
	console_1.StopOutput();

	_simulationRoom->~simulation_room();
}