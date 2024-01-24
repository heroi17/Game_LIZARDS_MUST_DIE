#include "test_Game_engine.h"
#include "move_test.h"
#include <iostream>
#include <queue>
#include <functional>
#include <thread>
int test1GE() {


	int update_rate_PE = 61;
	int update_rate_console = 60;
	std::vector<char> input_data;

	PSimulation::simulation_room room1(update_rate_PE);
	Console_Output console_1(&room1, update_rate_console);
	inputEngine input_module(&input_data);
	PO::Object* my_hero = new PO::MovebleObject(PMathO::Vec2D(350, 100), new PColliderO::CricleCollider(console_1.temp.right / 50), 1, 0, PMathO::Vec2D(0, 0));
	mover hero_mover(my_hero, &input_data);

	room1.add_object(my_hero);
	room1.add_object(new PO::StaticObject(PMathO::Vec2D(100, 100), new PColliderO::CricleCollider(console_1.temp.right / 50)));
	room1.add_object(new PO::StaticObject(PMathO::Vec2D(500, 100), new PColliderO::CricleCollider(console_1.temp.right / 50)));
	room1.add_object(new PO::MovebleObject(PMathO::Vec2D(350, 100), new PColliderO::CricleCollider(console_1.temp.right / 50), 5, 0.1, PMathO::Vec2D(25, 0)));
	room1.add_object(new PO::MovebleObject(PMathO::Vec2D(250, 100), new PColliderO::CricleCollider(console_1.temp.right / 50), 2, 0.1, PMathO::Vec2D(100, 0)));
	
	
	console_1.StartOutput();
	room1.StartSimulation();
	input_module.startEngine();
	hero_mover.startMove();

	std::this_thread::sleep_for(std::chrono::milliseconds(100000));

	hero_mover.stopMove();
	input_module.stopEngine();
	room1.StopSimulation();
	console_1.StopOutput();

	console_1.~Console_Output();
	room1.~simulation_room();
	return 0;
}