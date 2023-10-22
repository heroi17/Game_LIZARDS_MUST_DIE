#include "PhysObj.cpp"
#include <iostream>
#include <thread>
#include <time.h> 
#include <vector>
using namespace PO;//PhysicObj namespace
class simulation_room {
private:
	std::thread myThread;
	double width;
	double height;
	bool simulation_is_working=false;
	std::vector<StaticObject> static_objects;
	std::vector<MovebleObject> moveble_objects;
	int TicPerSecond = 10;
	double resource = 0.;
	double PeriodForTicInSec = 1. / TicPerSecond;
public:
	simulation_room(double width=10., double height=10.): width(width), height(height){
	}

	~simulation_room() {
		StopSimulation();
	}

	void UpdateOneTic(double time_to_sec) { // time - is time when we want to see phisic simulation: if time_now = 1000, and temre_to = 1500 then we shold update all for 500
		/*here we are update collision
		update position
		update speed(because trenie and another thigs)*/
		std::cout << "Physic Engine update" << std::endl;;
		std::cout << "resource - " << resource << std::endl;
		std::cout << "update to time - " << time_to_sec << std::endl;
		std::cout << "collision - 0" << std::endl;
		std::cout << std::endl;
	}

	void simulationCicle() {
		double time_to_wait, time_of_work;
		int ms_time_to_wait;
		clock_t start, end;
		while (simulation_is_working){
			start = clock();//get time start 1 update
			UpdateOneTic((double)start / CLOCKS_PER_SEC + PeriodForTicInSec);//give that time to update we want
			end = clock();
			time_of_work = (double)(end - start) / CLOCKS_PER_SEC;
			time_to_wait = (PeriodForTicInSec - time_of_work);//how many time we should wait for next tic
			ms_time_to_wait = time_to_wait * 1000;//time for waiting
			if (ms_time_to_wait > 0) {
				std::this_thread::sleep_for(std::chrono::milliseconds(ms_time_to_wait));//wait for next tic
			}
			resource = time_of_work / PeriodForTicInSec;//this is our prog resource, if 0 more then time, then resource > 1
		}
	}

	void StartSimulation() {
		simulation_is_working = true;
		//we should update time of all object course if we stoop wait and start, then 
		myThread = std::thread (&simulation_room::simulationCicle, this);
	}

	void StopSimulation() {
		if (simulation_is_working) {
			simulation_is_working = false;
			myThread.join();
		}
	}

};