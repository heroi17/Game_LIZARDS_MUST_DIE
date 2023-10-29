#pragma once
#include "PhysObj.h"
#include <iostream>
#include <thread>
#include <time.h> 
#include <vector>
namespace PSimulation {



	struct collision {//when you use this structure you should make start collision and finish collision, finish_collision_time you should set maximum
		// START_COLLISION(TIME = -10000000) -> ....... -> FINISH_COLLISION(tIME = 10000000000)
		collision *after_collision=0;
		collision *before_collision=0;
		PO::Object* ptr_obj_1=0;
		PO::Object* ptr_obj_2=0;
		double time_when_collision_sec;
		collision(double time_when_collision_sec =-1.0E30, PO::Object* ptr_obj_1=0, PO::Object* ptr_obj_2=0);
		~collision();
		void insert_collision(collision* insert_collision);
	};

	class simulation_room {
	private:
		collision start = collision();
		std::thread myThread;
		bool simulation_is_working = false;
		int TicPerSecond = 20;
		double resource = 0.;
		double PeriodForTicInMSec = 1000. / TicPerSecond;
	public:
		std::vector<PO::Object*> objects;
		simulation_room(int NewTicPerSecond=20);
		~simulation_room();
		void add_object(PO::Object* new_object);
		void UpdateOneTic(double time_to_msec);
		void set_time_all_object(double time_to_sec);
		void simulationCicle();
		void StartSimulation();
		void StopSimulation();
		//debug functions
		void output_debug_information(double time_to_msec);
	};
}