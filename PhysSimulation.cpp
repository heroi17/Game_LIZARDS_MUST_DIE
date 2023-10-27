#include "PhysSimulation.h"
using namespace PSimulation;
simulation_room::simulation_room(double width, double height): width(width), height(height){
	}

simulation_room::~simulation_room() {
	StopSimulation();
}

void simulation_room::UpdateOneTic(double time_to_msec) { // time - is time when we want to see phisic simulation: if time_now = 1000, and temre_to = 1500 then we shold update all for 500
	/*here we are update collision
	update position
	update speed(because trenie and another thigs)*/
	double time_to_sec = time_to_msec / 1000.;
	for (auto& element : moveble_objects) {// it's not finish just for test course here we are also should update collision!
		element.update_mechanics_parameters(time_to_sec);
	}
	output_debug_information(time_to_sec);
	test_output();
}

void simulation_room::test_output() {
	const int console_height = 22;
	const int console_width = 50;
	const int size = console_height * console_width;
	char lst[size];
	memset(lst, ' ', size);
	char* str_ykaz[console_height];
	for (char i = 0; i < console_height; i++) {
		str_ykaz[i] = lst + i * console_width;
	}
	for (auto& element : moveble_objects){
		PMathO::Vec2D pos = element.get_position();
		int x = pos.get_x();
		int y = pos.get_y();
		if (0 <= x && x < console_width && 0 <= y && y < console_height) {
			str_ykaz[y][x] = '#';
		}
	}
	for (auto& element : static_objects) {
		PMathO::Vec2D pos = element.get_position();
		int x = pos.get_x();
		int y = pos.get_y();
		if (0 <= x && x < console_width && 0 <= y && y < console_height) {
			str_ykaz[y][x] = '@';
		}
	}
	for (int i = 0; i < console_height; i++) {
		for (int j = 0; j < console_width; j++) {
			std::cout << str_ykaz[i][j];
		}
		std::cout << std::endl;
	}

}

void simulation_room::set_time_all_object(double new_time_sec) {
	for (auto& element : moveble_objects) {// it's not finish just for test course here we are also should update collision!
		element.set_last_update_time_sec(new_time_sec);
	}

}

void simulation_room::output_debug_information(double time_to_msec) {
	std::cout << "Physic Engine update" << std::endl;;
	std::cout << "resource - " << resource << std::endl;
	std::cout << "update to time - " << time_to_msec << std::endl;
	std::cout << "collision - 0" << std::endl;
	std::cout << std::endl;
}

void simulation_room::simulationCicle() {
	double time_of_work;
	int ms_time_to_wait;
	clock_t start, end;
	double next = clock() + PeriodForTicInMSec;
	while (simulation_is_working){//добавить ласт апдейт чтобы мы всегда обновляли идеально ровно!!! не + что-то там изза работы некоторых функций
		start = clock();//get time start 1 update
		UpdateOneTic(next);//give that time to update we want
		end = clock();
		time_of_work = end - start;
		ms_time_to_wait = (next - clock());//time for waiting
		if (ms_time_to_wait > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(ms_time_to_wait));//wait for next tic
		}
		next += PeriodForTicInMSec;
		resource = time_of_work / PeriodForTicInMSec;//this is our prog resource, if 0 more then time, then resource > 1
	}
}

void simulation_room::StartSimulation() {
	simulation_is_working = true;
	set_time_all_object((double)clock() / 1000.); // if we stopped simulation, when all obj start move, ferstly they go far away
	myThread = std::thread (&simulation_room::simulationCicle, this);
}

void simulation_room::StopSimulation() {
	if (simulation_is_working) {
		simulation_is_working = false;
		myThread.join();
	}
}
