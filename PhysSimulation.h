#pragma once
#include "PhysObj.h"
#include <iostream>
#include <thread>
#include <time.h> 
#include <vector>
namespace PSimulation {



	struct collision {//when you use this structure you should make start collision and finish collision, finish_collision_time you should set maximum
		// START_COLLISION(TIME = -10000000, ....., before_colision=0) -> ....... -> collision(time=...., next_collision=0))
		collision *next_collision=0;
		collision *before_collision=0;
		PO::Object* ptr_obj_1=0;
		PO::Object* ptr_obj_2=0;
		double time_when_collision_sec;
		collision(double time_when_collision_sec =-1.0E30, PO::Object* ptr_obj_1=0, PO::Object* ptr_obj_2=0);
		~collision();
		double get_time_collision(PO::Object* obj1, PO::Object* obj2); // return -1.0 if collision won't be
		void insert_collision(collision* insert_collision);
		void detach();
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
		void calculate_collision_between(PO::Object* ptr_obj_1, PO::Object* ptr_obj_2);
	};
}