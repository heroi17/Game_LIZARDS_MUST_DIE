#include "PhysObj.cpp"
const int MaxStaticObjectsInRoom = 15;
const int MaxMovebleObjectsInRoom = 15;
const int MaxSpecialObjectsInRoom = 15;
const double MaxSizeObject = 10;
const int TicPerSecond = 15;
const int PeriodForTicInMs = 1000 / TicPerSecond;

class simulation_room {
private:
	double width;
	double height;
	bool simulation_is_working;
	static_object* static_objects[MaxStaticObjectsInRoom];
	static_object* static_objects[MaxStaticObjectsInRoom];
	static_object* static_objects[MaxStaticObjectsInRoom];
public:
	simulation_room(double width, double height): width(width), height(height){}
	void UpdateCollision() {

	}
	void Updateposition() {

	}
	void UpdateOneTic() {
		UpdateCollision();
		Updateposition();
	}
	void simulationCicle() {
		while (simulation_is_working){
			//get time1 in ms
			UpdateOneTic();
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
		simulationCicle();
	}
	void StopSimulation() {
		simulation_is_working = false;
	}
};