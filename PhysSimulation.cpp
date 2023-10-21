#include "PhysObj.cpp"
#include <thread>
const int MaxStaticObjectsInRoom = 15;
const int MaxMovebleObjectsInRoom = 15;
const double MaxSizeObject = 10;
const int TicPerSecond = 15;
const int PeriodForTicInMs = 1000 / TicPerSecond;

class simulation_room {
private:
	double width;
	double height;
	bool simulation_is_working;
	StaticObject* static_objects[MaxStaticObjectsInRoom];
	MovebleObject* moveble_objects[MaxMovebleObjectsInRoom];
public:
	simulation_room(double width, double height): width(width), height(height){}
	void UpdateOneTic(TimeObject time) {
		/*here we are update collision
		update position
		update speed(because trenie and another thigs)*/
	}
	void simulationCicle() {
		TimeObject time = 1.2;
		while (simulation_is_working){
			//get time1 in ms
			UpdateOneTic(time);
			//get time2 in ms
			/*
			sleep for next(timesleep = PeriodForTicInMs - time2 + time1)
			if timesleep>0 then sleep, else without sleep. and time_from_last_tic!= PeriodForTicInMs
			PeriodForTicInMs for update position with our speed
			*/

		}
	}
	void StartSimulation() {
		simulation_is_working = true;
		//std::thread t1(simulationCicle, this);
	}
	void StopSimulation() {
		simulation_is_working = false;
	}
};