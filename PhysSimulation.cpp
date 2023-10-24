#include "PhysSimulation.h"
using namespace PSimulation;
simulation_room::simulation_room(double width, double height): width(width), height(height){
	}

simulation_room::~simulation_room() {
	StopSimulation();
}

void simulation_room::UpdateOneTic(double time_to_sec) { // time - is time when we want to see phisic simulation: if time_now = 1000, and temre_to = 1500 then we shold update all for 500
	/*here we are update collision
	update position
	update speed(because trenie and another thigs)*/
	std::cout << "Physic Engine update" << std::endl;;
	std::cout << "resource - " << resource << std::endl;
	std::cout << "update to time - " << time_to_sec << std::endl;
	std::cout << "collision - 0" << std::endl;
	std::cout << std::endl;
}

void simulation_room::simulationCicle() {
	double time_of_work;
	int ms_time_to_wait;
	clock_t start, end;
	double next = clock() + PeriodForTicInMSec;
	std::cout << clock();
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
	//we should update time of all object course if we stoop wait and start, then 
	myThread = std::thread (&simulation_room::simulationCicle, this);
}

void simulation_room::StopSimulation() {
	if (simulation_is_working) {
		simulation_is_working = false;
		myThread.join();
	}
}
