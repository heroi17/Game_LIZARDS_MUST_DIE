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
	double time_when_stop_obj1 = 1.;
	double time_when_stop_obj2 = 1.; 
	if (obj1->get_ptr_speed()->get_lenth()==0 and obj2->get_ptr_speed()->get_lenth() == 0) {
		return false;
	}
	else if (obj1->get_ptr_speed()->get_lenth() != 0 and obj2->get_ptr_speed()->get_lenth() == 0) {

	}
	else if (obj1->get_ptr_speed()->get_lenth() == 0 and obj2->get_ptr_speed()->get_lenth() != 0) {

	}
	else {

	}
	return false;//доделать
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
		return -1.0;//здесь более серьезный подсчет
	}
	return -1.0;
	//we are find time where we should calculate collision if find collision is less then start_time => return -1.0


	//для начала просто сделаем так чтобы мы находили пересечение коллайдеров
	//if objects already under collision, we should return -1.0 course they should go away from ech other and there can be some problems with module add_object.
	//here we are calculate time when object will intersect among themselves
	//firstly we are find will or not intersect coverage_cricle of object
	//if not then we return -1.0
	//if all right then we find ryally these object intersect or not - if true then return time when it heppened , else return -1.0
	//position(time_to) = position(time_to_stop) if time_to_stop < time_to
	//
	//
	//time in sec!!!

	//тут мы обязательно должны учитывать время коллизии если они пересекутся в прошлом то бобобо
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
		//make_new_mehanicks_parameter_for
		/*here we go firstly to first time collision in linked_list_collision
		remake speed after tuching object 
		change collision_linked_lst*/
		Collision* working_collision = collision_header.next_collision; //our working collision for one iteration of loop
		working_collision->detach();//we are detach collision from collision linkd lst
		working_collision->ptr_obj_1->update_mechanics_parameters(collision_header.next_collision->time_when_collision_sec);//here we move obj1 to time when collision
		working_collision->ptr_obj_2->update_mechanics_parameters(collision_header.next_collision->time_when_collision_sec);//and obj2 moveing too
		solve_collision_between(working_collision->ptr_obj_1, working_collision->ptr_obj_2); // solve collision using two object: obj_1, obj_2
		update_future_collision_for(working_collision->ptr_obj_1);                  //here we should update future collision for this object and solve problem with this chenges
		update_future_collision_for(working_collision->ptr_obj_2);					//								     and for this object too
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
	objects.push_back(new_object); //add object
	update_future_collision_for(new_object); //find collision if it'll be
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

	//теперь ищем обьекты которые колизируют раньше чем коллизия нашего обьекта если она есть
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

	//если find_collider=0 то нету коллизий для обьекта и все окей
	//если find_collider!=0 то у нас все пучком и мы должны создать коллизию и починить все остальное
	if (find_collider != 0) {//if will_no_collision
		//if we find collision_obj
		if (find_collider->my_next_collision_pointer == 0 && updater_obj->my_next_collision_pointer==0) {
			Collision* new_collision = new Collision(time_nearest_collision, updater_obj, find_collider);
			updater_obj->my_next_collision_pointer = new_collision;
			find_collider->my_next_collision_pointer = new_collision;
			collision_header.insert_collision(new_collision);
		}
		else if (find_collider->my_next_collision_pointer != 0 && updater_obj->my_next_collision_pointer == 0) {
			Collision* new_collision = new Collision(time_nearest_collision, updater_obj, find_collider);
			PO::Object* second_broken_collision;


			//find collider of find_collider->my_next_collision_pointer
			if (find_collider == static_cast<Collision*>(find_collider->my_next_collision_pointer)->ptr_obj_1) {
				second_broken_collision = static_cast<Collision*>(find_collider->my_next_collision_pointer)->ptr_obj_2;
			}
			else {
				second_broken_collision = static_cast<Collision*>(find_collider->my_next_collision_pointer)->ptr_obj_1;
			}
			delete find_collider->my_next_collision_pointer;
			second_broken_collision->my_next_collision_pointer = 0;




			updater_obj->my_next_collision_pointer = new_collision;
			find_collider->my_next_collision_pointer = new_collision;
			collision_header.insert_collision(new_collision); //+ solve collision



			update_future_collision_for(second_broken_collision);
		}
		else if (find_collider->my_next_collision_pointer == 0 && updater_obj->my_next_collision_pointer != 0) {
			Collision* new_collision = new Collision(time_nearest_collision, updater_obj, find_collider);
			PO::Object* second_broken_collision;


			

			if (updater_obj == static_cast<Collision*>(updater_obj->my_next_collision_pointer)->ptr_obj_1) {
				second_broken_collision = static_cast<Collision*>(updater_obj->my_next_collision_pointer)->ptr_obj_2;
			}
			else {
				second_broken_collision = static_cast<Collision*>(updater_obj->my_next_collision_pointer)->ptr_obj_1;
			}
			delete updater_obj->my_next_collision_pointer;
			second_broken_collision->my_next_collision_pointer = 0;



			updater_obj->my_next_collision_pointer = new_collision;
			find_collider->my_next_collision_pointer = new_collision;
			collision_header.insert_collision(new_collision); //+ solve collision


			update_future_collision_for(second_broken_collision);
		}
		else{
			Collision* new_collision = new Collision(time_nearest_collision, updater_obj, find_collider);
			PO::Object* second_broken_collision_1;
			PO::Object* second_broken_collision_2;

			

			if (find_collider == static_cast<Collision*>(find_collider->my_next_collision_pointer)->ptr_obj_1) {
				second_broken_collision_1 = static_cast<Collision*>(find_collider->my_next_collision_pointer)->ptr_obj_2;
			}
			else {
				second_broken_collision_1 = static_cast<Collision*>(find_collider->my_next_collision_pointer)->ptr_obj_1;
			}
			delete find_collider->my_next_collision_pointer;
			second_broken_collision_1->my_next_collision_pointer = 0;


			if (updater_obj == static_cast<Collision*>(updater_obj->my_next_collision_pointer)->ptr_obj_1) {
				second_broken_collision_2 = static_cast<Collision*>(updater_obj->my_next_collision_pointer)->ptr_obj_2;
			}
			else {
				second_broken_collision_2 = static_cast<Collision*>(updater_obj->my_next_collision_pointer)->ptr_obj_1;
			}
			delete static_cast<Collision*>(updater_obj->my_next_collision_pointer);
			second_broken_collision_2->my_next_collision_pointer = 0;


			updater_obj->my_next_collision_pointer = new_collision;
			find_collider->my_next_collision_pointer = new_collision;
			collision_header.insert_collision(new_collision); //+ solve collision


			update_future_collision_for(second_broken_collision_1);
			update_future_collision_for(second_broken_collision_2);

		}
	}
}

//solwe this