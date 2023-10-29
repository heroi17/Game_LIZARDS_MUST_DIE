#include "PhysSimulation.h"
using namespace PSimulation;


PSimulation::collision::~collision() {
	//connect before and after collision
	this->before_collision->after_collision = this->after_collision;
	this->after_collision->before_collision = this->before_collision;
}
PSimulation::collision::collision(double time_when_collision, PO::Object* ptr_obj_1, PO::Object* ptr_obj_2): time_when_collision_sec(time_when_collision), ptr_obj_1(ptr_obj_1), ptr_obj_2(ptr_obj_2){

}


void PSimulation::collision::insert_collision(collision* insert_collision) {
	collision* iterator_collision = this;
	while ((iterator_collision->after_collision != 0) && (iterator_collision->time_when_collision_sec < insert_collision->time_when_collision_sec))//find position for our collision
		iterator_collision = iterator_collision->after_collision;
	insert_collision->before_collision = iterator_collision->before_collision;//here i just insert in linked_lst -- collision new item
	insert_collision->before_collision->after_collision = insert_collision;
	insert_collision->after_collision = iterator_collision;
	iterator_collision->before_collision = insert_collision;
}



simulation_room::simulation_room(int NewTicPerSecond){
	if (NewTicPerSecond < 1) {
		TicPerSecond = 1;
		PeriodForTicInMSec = 1000. / TicPerSecond;
	}
	else {
		TicPerSecond = NewTicPerSecond;
		PeriodForTicInMSec = 1000. / TicPerSecond;
	}
}

simulation_room::~simulation_room() {
	StopSimulation();
}

void simulation_room::UpdateOneTic(double time_to_msec) { // time - is time when we want to see phisic simulation: if time_now = 1000, and temre_to = 1500 then we shold update all for 500
	/*here we are update collision
	update position
	update speed(because trenie and another thigs)*/
	double time_to_sec = time_to_msec / 1000.;
	while (start.after_collision != 0 && start.after_collision->time_when_collision_sec < time_to_sec) {
		/*here we go firstly to first time collision in linked_list_collision
		remake speed after tuching object 
		change collision_linked_lst*/
	}//here i move every object to time_to_sec course there positions in time between last update_time and time_to_sec
	for (auto& element : objects) {// it's not finish just for test course here we are also should update collision!
		element->update_mechanics_parameters(time_to_sec);
	}


	//system("cls");
	//output_debug_information(time_to_sec);
}


void simulation_room::add_object(PO::Object* new_object) {
	objects.push_back(new_object);
	//+ add collision i think
}

void simulation_room::set_time_all_object(double new_time_sec) {
	for (auto& element : objects) {// it's not finish just for test course here we are also should update collision!
		element->set_last_update_time_sec(new_time_sec);
	}

}

void simulation_room::output_debug_information(double time_to_msec) {
	std::cout << "Physic Engine update" << std::endl;;
	std::cout << "resource - " << resource << std::endl;
	std::cout << "update to time - " << time_to_msec << std::endl;
	std::cout << "collision - 0" << std::endl;
	std::cout << std::endl;
}

void simulation_room::simulationCicle() {
	double time_of_work;
	int ms_time_to_wait;
	clock_t start, end;
	double next = clock() + PeriodForTicInMSec;
	while (simulation_is_working) {//добавить ласт апдейт чтобы мы всегда обновляли идеально ровно!!! не + что-то там изза работы некоторых функций
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
	set_time_all_object((double)clock() / 1000.); // if we stopped simulation, when all obj start move, ferstly they go far away
	myThread = std::thread(&simulation_room::simulationCicle, this);
}

void simulation_room::StopSimulation() {
	if (simulation_is_working) {
		simulation_is_working = false;
		myThread.join();
	}
}
