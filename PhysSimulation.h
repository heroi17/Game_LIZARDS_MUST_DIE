#pragma once
#include "PhysObj.h"
#include <iostream>
#include <thread>
#include <time.h> 
#include <vector>
namespace PSimulation {
	class simulation_room {
	private:
		std::thread myThread;
		double width;
		double height;
		bool simulation_is_working = false;
		std::vector<PO::StaticObject> static_objects;
		std::vector<PO::MovebleObject> moveble_objects;
		int TicPerSecond = 10;
		double resource = 0.;
		double PeriodForTicInMSec = 1000. / TicPerSecond;
	public:
		simulation_room(double width = 10., double height = 10.);
		~simulation_room();
		void UpdateOneTic(double time_to_sec);
		void simulationCicle();
		void StartSimulation();
		void StopSimulation();
	};
}