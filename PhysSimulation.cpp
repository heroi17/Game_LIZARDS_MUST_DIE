#include "PhysSimulation.h"
using namespace PSimulation;

//collision class realisation
collision::~collision() {
	detach();
}

void collision::detach() {
	//connect (collision before_collision) and (collision next_collision)
	if (this->next_collision != 0 && this->before_collision != 0) {
		this->before_collision->next_collision = this->next_collision;
		this->next_collision->before_collision = this->before_collision;
	}
	else if (this->next_collision == 0 and this->before_collision != 0) {
		this->before_collision->next_collision = 0;
	}
	else if (this->next_collision != 0 and this->before_collision == 0) {
		this->next_collision->before_collision = 0;
	}
}

collision::collision(double time_when_collision, PO::Object* ptr_obj_1, PO::Object* ptr_obj_2): time_when_collision_sec(time_when_collision), ptr_obj_1(ptr_obj_1), ptr_obj_2(ptr_obj_2){

}

double collision::get_time_collision(PO::Object* obj1, PO::Object* obj2) {


	//if objects already under collision, we should return -1.0 course they should go away from ech other and there can be some problems with module add_object.
	//here we are calculate time when object will intersect among themselves
	//firstly we are find will or not intersect coverage_cricle of object
	//if not then we return -1.0
	//if all right then we find ryally these object intersect or not - if true then return time when it heppened , else return -1.0
	//position(time_to) = position(time_to_stop) if time_to_stop < time_to
	//
	//
	//
	return -1.0;
}

void collision::insert_collision(collision* insert_collision) {//here i insert collisiom *insert_collision in *this
	collision* iterator_collision = this;//                                                          \V/ simbol <= mabe should be just <
	while ((iterator_collision->next_collision != 0) && (iterator_collision->time_when_collision_sec <= insert_collision->time_when_collision_sec))//find position for our collision
		iterator_collision = iterator_collision->next_collision;
	insert_collision->before_collision = iterator_collision->before_collision;//here i just insert in linked_lst -- collision new item
	insert_collision->before_collision->next_collision = insert_collision;
	insert_collision->next_collision = iterator_collision;
	iterator_collision->before_collision = insert_collision;
}










//simulation_room class realisation

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
	while (start.next_collision != 0 && start.next_collision->time_when_collision_sec < time_to_sec) {
		//make_new_mehanicks_parameter_for
		/*here we go firstly to first time collision in linked_list_collision
		remake speed after tuching object 
		change collision_linked_lst*/
		collision* working_collision = start.next_collision;
		working_collision->detach();
		working_collision->ptr_obj_1->update_mechanics_parameters(start.next_collision->time_when_collision_sec);//here we move obj1
		working_collision->ptr_obj_2->update_mechanics_parameters(start.next_collision->time_when_collision_sec);//and obj2 to there collision position
		// calculate collision using two object: obj_1, obj_2
		//(working_collision->ptr_obj_1)                  //here we should update future collision for this object
		//(working_collision->ptr_obj_2)                  //								   and for this object
		delete working_collision;//delete this collision because we already worked with it and it is in past now


	//after working kollision all our object is in time between last_update and time_to_sec
	}//here i move every object to time_to_sec
	for (auto& element : objects) {
		element->update_mechanics_parameters(time_to_sec);
	}


	//system("cls");
	//output_debug_information(time_to_sec);
}

void simulation_room::add_object(PO::Object* new_object) {
	objects.push_back(new_object);
	//update_collision for objets course we change all
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
	while (simulation_is_working) {//�������� ���� ������ ����� �� ������ ��������� �������� �����!!! �� + ���-�� ��� ���� ������ ��������� �������
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

void simulation_room::calculate_collision_between(PO::Object* ptr_obj_1, PO::Object* ptr_obj_2) {
	//here we change speed in time when collision
	//you should use this function when the objects are next to each other
	//mabe we should reaalyse this method using collider, therefor get position of collision and get parallel line of point collision

	//this is just for test!!!!!!!!!
	*(ptr_obj_1->get_ptr_speed()) *= -1.;//just chanje vector of speed
	*(ptr_obj_2->get_ptr_speed()) *= -1.;//here we make te same things with the second object
}
