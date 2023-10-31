#pragma once
#include "PhysObj.h"
#include <iostream>
#include <thread>
#include <time.h> 
#include <vector>
namespace PSimulation {



	struct Collision {//when you use this structure you should make start collision and finish collision, finish_collision_time you should set maximum
		// START_COLLISION(TIME = -10000000, ....., before_colision=0) -> ....... -> collision(time=...., next_collision=0))
		Collision *next_collision=0;
		Collision *before_collision=0;
		PO::Object* ptr_obj_1=0;
		PO::Object* ptr_obj_2=0;
		double time_when_collision_sec;
		Collision(double time_when_collision_sec =-1.0E30, PO::Object* ptr_obj_1=0, PO::Object* ptr_obj_2=0);
		~Collision();
		double get_time_collision(PO::Object* obj1, PO::Object* obj2); // return -1.0 if collision won't be
		void insert_collision(Collision* insert_collision);
		void detach();
		bool is_coverages_will_overloop(double aftertime, PO::Object* obj1, PO::Object* obj2);
	};

	class simulation_room {
	private:
		Collision collision_header = Collision();
		std::thread myThread;
		bool simulation_is_working = false;
		int TicPerSecond = 20;
		double resource = 0.;
		double PeriodForTicInMSec = 1000. / TicPerSecond;
	public:
		std::vector<PO::Object*> objects;
		simulation_room(int NewTicPerSecond=20);
		~simulation_room();
		void update_future_collision_for(PO::Object* updater_obj);
		void add_object(PO::Object* new_object);
		void UpdateOneTic(double time_to_msec);
		void set_time_all_object(double time_to_sec);
		void simulationCicle();
		void StartSimulation();
		void StopSimulation();
		//debug functions
		void output_debug_information(double time_to_msec);
		void solve_collision_between(PO::Object* ptr_obj_1, PO::Object* ptr_obj_2);
	};
}