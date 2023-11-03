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
		Collision(double time_when_collision_sec =-1.0, PO::Object* ptr_obj_1=0, PO::Object* ptr_obj_2=0);
		~Collision();
		/// <summary>
		/// check future collision of two objects
		/// </summary>
		/// <param name="obj1"> pointer to object 1 to check </param>
		/// <param name="obj2"> pointer to object 2 to check </param>
		/// <returns> -1.0 if the collision does not occur, else time when a collision occur</returns>
		double get_time_collision(PO::Object* obj1, PO::Object* obj2); // return -1.0 if collision won't be
		/// <summary>
		/// the function inserts an element(insert_collision) into the linked list the object in which the function is called.
		/// </summary>
		/// <param name="insert_collision"> - object that we should to insert in this</param>
		void insert_collision(Collision* insert_collision);
		/// <summary>
		/// the function detaches an element from the linked list sequence
		/// </summary>
		void detach();
		/// <summary>
		/// checks whether the circles described around the object intersect
		/// </summary>
		/// <param name="aftertime"> the time after which it should be checked </param>
		/// <param name="obj1"> pointer to object 1 to check </param>
		/// <param name="obj2"> pointer to object 2 to check </param>
		/// <returns> true if coverages will intersect, else: false</returns>
		bool is_coverages_will_overloop(double aftertime, PO::Object* obj1, PO::Object* obj2);
		void print_me();
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
		/// <summary>
		/// Checks for collisions that may occur and makes changes to the collision linked_lst. If other collisions broke down at the same time, then he solves them by recursion.
		/// </summary>
		/// <param name="updater_obj"> - the object for which we want to find a collision </param>
		void update_future_collision_for(PO::Object* updater_obj);
		void add_object(PO::Object* new_object);
		/// <summary>
		/// the function moves objects to the desired time, taking into account collisions
		/// </summary>
		/// <param name="time_to_msec"> - the time to move objects to</param>
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