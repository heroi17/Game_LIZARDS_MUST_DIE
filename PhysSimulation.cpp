#include "PhysSimulation.h"
using namespace PSimulation;

//collision class realisation
Collision::~Collision() {
	detach();
}

void Collision::detach() {
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

Collision::Collision(double time_when_collision, PO::Object* ptr_obj_1, PO::Object* ptr_obj_2): time_when_collision_sec(time_when_collision), ptr_obj_1(ptr_obj_1), ptr_obj_2(ptr_obj_2){

}

bool Collision::is_coverages_will_overloop(double aftertime, PO::Object* obj1, PO::Object* obj2) {
	
	
	//ve can do not use it but it get optimisation \V/
	if (obj1->get_ptr_speed()->get_lenth() == 0 and obj2->get_ptr_speed()->get_lenth() == 0) {
		return false;
	}

	// \V/ get points of two lines
	PMathO::Vec2D pos1_start = obj1->get_position_at_time(aftertime);
	PMathO::Vec2D pos2_start = obj2->get_position_at_time(aftertime);
	PMathO::Vec2D pos1_stop(0, 0);
	PMathO::Vec2D pos2_stop(0, 0);
	//

	// \V/     find pos1_stop, pos2_stop
	{
		double how_time_to_stop_1 = obj1->get_how_time_to_stop();
		if (how_time_to_stop_1 == -1.0) {
			pos1_stop = pos1_start + obj1->get_speed() * 1.0E200;
		}
		else {
			pos1_stop = obj1->get_position_at_time(obj1->get_last_update_time_sec() + how_time_to_stop_1);
		}

		double how_time_to_stop_2 = obj2->get_how_time_to_stop();
		if (how_time_to_stop_2 == -1.0) {
			pos2_stop = pos2_start + obj2->get_speed() * 1.0E200;
		}
		else {
			pos2_stop = obj2->get_position_at_time(obj2->get_last_update_time_sec() + how_time_to_stop_1);
		}
	}
	// /A\

	//find intersect covverages or not
	double min_distanse = obj1->get_collider()->get_coverage_radious() + obj2->get_collider()->get_coverage_radious();
	if (PMathO::Section2D(pos1_start, pos1_stop).get_distance_to_point(pos2_start) < min_distanse) {
		return true;
	}
	return false;
}

double Collision::get_time_collision(PO::Object* obj1, PO::Object* obj2) {



	//just test programm
	const double rad1 = obj1->get_collider()->get_coverage_radious();
	const double rad2 = obj2->get_collider()->get_coverage_radious();
	PMathO::Vec2D pos1 = obj1->get_position() - obj2->get_position();
	PMathO::Vec2D pos2 = obj2->get_position() - obj2->get_position();
	if ((pos1 - pos2).get_lenth() < rad1 + rad2) return -1.0;
	
	
	
	
	double time1 = obj1->get_last_update_time_sec();
	double time2 = obj2->get_last_update_time_sec();
	double start_time;
	if (time1 > time2) {
		start_time = time1;
	}
	else {
		start_time = time2;
	}
	if (is_coverages_will_overloop(start_time, obj1, obj2)) {
		return -1.0;//����� ����� ��������� �������
	}
	return -1.0;
	//we are find time where we should calculate collision if find collision is less then start_time => return -1.0


	//��� ������ ������ ������� ��� ����� �� �������� ����������� �����������
	//if objects already under collision, we should return -1.0 course they should go away from ech other and there can be some problems with module add_object.
	//here we are calculate time when object will intersect among themselves
	//firstly we are find will or not intersect coverage_cricle of object
	//if not then we return -1.0
	//if all right then we find ryally these object intersect or not - if true then return time when it heppened , else return -1.0
	//position(time_to) = position(time_to_stop) if time_to_stop < time_to
	//
	//
	//time in sec!!!

	//��� �� ����������� ������ ��������� ����� �������� ���� ��� ����������� � ������� �� ������
}
//solwe this


void Collision::insert_collision(Collision* insert_collision) {//here i insert collisiom *insert_collision in *this
	Collision* iterator_collision = this;//                                                          \V/ simbol <= mabe should be just <
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

void simulation_room::UpdateOneTic(double time_to_msec) { // time_to_msec - is time when we want to see phisic simulation: if time_now = 1000, and temre_to = 1500 then we shold update all for 500ms
	/*here we are update collision
	update position
	update speed(because friction and another things)*/
	double time_to_sec = time_to_msec / 1000.;
	while (collision_header.next_collision != 0 && collision_header.next_collision->time_when_collision_sec < time_to_sec) {//get first future collision in collision timeline
		Collision* working_collision = collision_header.next_collision; //our working collision for one iteration of loop
		working_collision->detach();//we are detach collision from collision linkd lst
		PO::Object* obj1 = working_collision->ptr_obj_1;
		PO::Object* obj2 = working_collision->ptr_obj_2;
		obj1->my_next_collision_pointer = 0;
		obj2->my_next_collision_pointer = 0;

		obj1->update_mechanics_parameters(collision_header.next_collision->time_when_collision_sec);//here we move obj1 to time when collision
		obj2->update_mechanics_parameters(collision_header.next_collision->time_when_collision_sec);//and obj2 moveing too

		solve_collision_between(obj1, obj2); // solve collision using two object: obj_1, obj_2
		update_future_collision_for(obj1);                  //here we should update future collision for this object and solve problem with this chenges
		update_future_collision_for(obj2);					//								     and for this object too
		delete working_collision;//delete this collision because we already worked with it and it is in past now


	//after working with kollision of all our objects we mowe all our object to correct finish time
	}//here i move every object to time_to_sec
	for (auto& element : objects) {
		element->update_mechanics_parameters(time_to_sec);
	}


	//system("cls");
	//output_debug_information(time_to_sec);
}

void simulation_room::add_object(PO::Object* new_object) {
	new_object->set_last_update_time_sec((double)clock() / 1000.);
	objects.push_back(new_object); //add object
	//update_future_collision_for(new_object); //find collision if it'll be
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

void simulation_room::solve_collision_between(PO::Object* ptr_obj_1, PO::Object* ptr_obj_2) {
	//here we change speed in time when collision
	//you should use this function when the objects are next to each other
	//mabe we should reaalyse this method using collider, therefor get position of collision and get parallel line of point collision

	//this is just for test!!!!!!!!!
	*(ptr_obj_1->get_ptr_speed()) *= -1.;//just chanje vector of speed
	*(ptr_obj_2->get_ptr_speed()) *= -1.;//here we make te same things with the second object
}

void simulation_room::update_future_collision_for(PO::Object* updater_obj){

	//here we start find nearest collision for updater_obj
	PO::Object* find_collider = 0; // ferstly there no objects


	double time_nearest_collision;
	if (updater_obj->my_next_collision_pointer == 0) {
		time_nearest_collision = 1.0E300;//if our obj havent collision
	}
	else {
		
		time_nearest_collision = static_cast<Collision*>(updater_obj->my_next_collision_pointer)->time_when_collision_sec; // if our object have future collision
	}

	//������ ���� ������� ������� ���������� ������ ��� �������� ������ ������� ���� ��� ����
	for (auto& element : objects) {
		
		if (element == updater_obj) continue;//if we meet updater_obj then skip
		double time_when_element_collid_updater_obj = collision_header.get_time_collision(updater_obj, element);
		 // here i must realisate pointer from obj to his future collision
		if (0. < time_when_element_collid_updater_obj && time_when_element_collid_updater_obj < time_nearest_collision) {//firstly time_when_element_collid should be not (-1.0 <=> will no collision)
			Collision* collision_of_this_object = static_cast<Collision*>(element->my_next_collision_pointer);
			if (collision_of_this_object == 0 || collision_of_this_object->time_when_collision_sec > time_when_element_collid_updater_obj) {
				find_collider = element;
				time_nearest_collision = time_when_element_collid_updater_obj;
			}
		}
	}

	//���� find_collider=0 �� ���� �������� ��� ������� � ��� ����
	//���� find_collider!=0 �� � ��� ��� ������ � �� ������ ������� �������� � �������� ��� ���������
	if (find_collider != 0) {//if will_no_collision
		//if we find collision_obj
		
		Collision* new_collision = new Collision(time_nearest_collision, updater_obj, find_collider);
		PO::Object* second_broken_collision_1=0;
		PO::Object* second_broken_collision_2=0;

		if (find_collider->my_next_collision_pointer != 0) {
			if (find_collider == static_cast<Collision*>(find_collider->my_next_collision_pointer)->ptr_obj_1) {
				second_broken_collision_1 = static_cast<Collision*>(find_collider->my_next_collision_pointer)->ptr_obj_2;
			}
			else {
				second_broken_collision_1 = static_cast<Collision*>(find_collider->my_next_collision_pointer)->ptr_obj_1;
			}
			delete find_collider->my_next_collision_pointer;
			second_broken_collision_1->my_next_collision_pointer = 0;

		}
		if (updater_obj->my_next_collision_pointer != 0) {
			if (updater_obj == static_cast<Collision*>(updater_obj->my_next_collision_pointer)->ptr_obj_1) {
				second_broken_collision_2 = static_cast<Collision*>(updater_obj->my_next_collision_pointer)->ptr_obj_2;
			}
			else {
				second_broken_collision_2 = static_cast<Collision*>(updater_obj->my_next_collision_pointer)->ptr_obj_1;
			}
			delete static_cast<Collision*>(updater_obj->my_next_collision_pointer);//�������� �� ���������� � �� �� �������
			second_broken_collision_2->my_next_collision_pointer = 0;
		}

		updater_obj->my_next_collision_pointer = new_collision;
		find_collider->my_next_collision_pointer = new_collision;
		collision_header.insert_collision(new_collision);

		if (second_broken_collision_1!=0) { //���� ���������� ������ �� ��������� �������� �� �� ��� ���������
			update_future_collision_for(second_broken_collision_1);
			}

		if (second_broken_collision_2!=0) { //���� ���������� ������ �� ��������� �������� �� �� ��� ���������
			update_future_collision_for(second_broken_collision_2);
		}
	}
}

//solwe this