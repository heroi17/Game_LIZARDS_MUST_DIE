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
		int TicPerSecond = 20.;
		double resource = 0.;
		double PeriodForTicInMSec = 1000. / TicPerSecond;
	public:
		std::vector<PO::Object*> objects;
		simulation_room(double width = 10., double height = 10.);
		~simulation_room();
		void UpdateOneTic(double time_to_msec);
		void set_time_all_object(double time_to_sec);
		void simulationCicle();
		void StartSimulation();
		void StopSimulation();
		//debug functions
		void output_debug_information(double time_to_msec);
	};
}