#include "PhysSimulation.h"
using namespace PSimulation;
Collision* hhds = 0;
//collision class realisation
Collision::~Collision() {
	detach();
}

void Collision::print_me() {
	Collision* iterator_collision = this;
	 do {
		std::cout << "<-(" << iterator_collision->time_when_collision_sec << ")";
		iterator_collision = iterator_collision->next_collision;
	 } while (iterator_collision != 0);
	std::cout << std::endl;
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
	this->next_collision = 0;
	this->before_collision = 0;
}

Collision::Collision(double time_when_collision, PO::Object* ptr_obj_1, PO::Object* ptr_obj_2): time_when_collision_sec(time_when_collision), ptr_obj_1(ptr_obj_1), ptr_obj_2(ptr_obj_2){

}



bool Collision::is_coverages_will_overloop(double aftertime, PO::Object* obj1, PO::Object* obj2) {
	//in func we put objects from different time so we should move them to time of last updatet object
	

	double time1 = obj1->get_last_update_time_sec() + obj1->get_how_time_to_stop();
	double time2 = obj2->get_last_update_time_sec() + obj2->get_how_time_to_stop();




	double end_timeline_1 = time1;
	double end_timeline_2 = time2;
	bool O1StopBefoO2 = true;
	if (time1 > time2) {
		end_timeline_1 = time2;
		end_timeline_2 = time1;
		O1StopBefoO2 = false;
	}
	//				 \V/ (end_timeline_2)		 \V/     (end_timeline_2)
	//obj1------------>							  |
	//				  |						      |
	//obj2---------------------------------------->
	//				 /A\ stop obj1               /A\ stop obj2

	if (aftertime > end_timeline_2) return false;
	//��� ������������ /A\ 


	double min_distanse_for_true = obj1->get_collider()->get_coverage_radious() + obj2->get_collider()->get_coverage_radious();
	if (aftertime < end_timeline_1) {
		PMathO::Vec2D pos1_aftertime = obj1->get_position_at_time(aftertime);
		PMathO::Vec2D pos2_aftertime = obj2->get_position_at_time(aftertime);


		PMathO::Vec2D D_pos_aftertime = pos1_aftertime - pos2_aftertime;
		PMathO::Vec2D speed1 = obj1->get_speed() - obj1->get_acceleration() * (aftertime - obj1->get_last_update_time_sec());
		PMathO::Vec2D speed2 = obj2->get_speed() - obj2->get_acceleration() * (aftertime - obj2->get_last_update_time_sec());
		PMathO::Vec2D D_speed_aftertime = speed1 - speed2;
		PMathO::Vec2D D_acceleration_aftertime = obj1->get_acceleration() - obj2->get_acceleration();
		// we should find min(pos([time_start, time_end]).get_lenth())
		//whe pos(t) = D_pos_start + D_speed * t + D_acceleration * t * t * 0.5
		//derivative_of_lenth_in_squere = (2*X + 2*Vx*t + Ax*t*t)(Vx + Ax*t) + (2*Y + 2*Vy*t + Ay*t*t)(Vy + Ay*t)
		//derivative_of_lenth_in_squere=0
		// (2*X + 2*Vx*t + Ax*t*t)(Vx + Ax*t) + (2*Y + 2*Vy*t + Ay*t*t)(Vy + Ay*t)=0 <=>
		// <=> (2xVx - 2yVy) + t(2xax - 2yay + 2VxVx - 2VyVy) + tt(3Vxax - 3vyay) + ttt(axax-ayay) = 0
		{
			if (D_pos_aftertime.get_lenth() < min_distanse_for_true) return true;
			double x = D_pos_aftertime.get_x();
			double y = D_pos_aftertime.get_y();
			double Vx = D_speed_aftertime.get_x();
			double Vy = D_speed_aftertime.get_y();
			double Ax = D_acceleration_aftertime.get_x();
			double Ay = D_acceleration_aftertime.get_y();

			double a1 = Ay * Ay + Ax * Ax;
			double a2 = 3 * (Ax * Vx + Ay * Vy);
			double a3 = 2 * (Vx * Vx + x * Ax + Vy * Vy + y * Ay);
			double a4 = 2 * (x * Vx + y * Vy);
			double solves[4];
			PMathO::solve3(solves, a1, a2, a3, a4);
			for (int i = 1; i <= solves[0]; i++) {
				if (0 < solves[i] && solves[i] <= end_timeline_1 - aftertime) {
					double distance = (obj1->get_position_at_time(aftertime + solves[i]) - obj2->get_position_at_time(aftertime + solves[i])).get_lenth();
					if (distance < min_distanse_for_true) return true;
				}
			}
			double distance_at_end_timeline_1 = (obj1->get_position_at_time(end_timeline_1) - obj2->get_position_at_time(end_timeline_1)).get_lenth();
			if (distance_at_end_timeline_1 < min_distanse_for_true) return true;
		}
	}
	// ����� �� ����������� /A\




	//����������� ������ 1 �� ���
	PMathO::Vec2D speed1(0, 0);
	PMathO::Vec2D speed2(0, 0);
	PMathO::Vec2D acceleration1(0, 0);
	PMathO::Vec2D acceleration2(0, 0);
	if (aftertime < end_timeline_1) {
		aftertime = end_timeline_1;
	}
	if (O1StopBefoO2) {
		speed2 = obj2->get_speed() - obj2->get_acceleration() * (aftertime - obj2->get_last_update_time_sec());
		acceleration2 = obj2->get_acceleration();
	}
	else {
		speed1 = obj1->get_speed() - obj1->get_acceleration() * (aftertime - obj1->get_last_update_time_sec());
		acceleration1 = obj1->get_acceleration();
	}
	PMathO::Vec2D D_pos_aftertime = obj1->get_position_at_time(aftertime) - obj2->get_position_at_time(aftertime);
	PMathO::Vec2D D_speed_aftertime = speed1 - speed2;
	PMathO::Vec2D D_acceleration_aftertime = acceleration1 - acceleration2;
	{
		if (D_pos_aftertime.get_lenth() < min_distanse_for_true) return true;
		double x = D_pos_aftertime.get_x();
		double y = D_pos_aftertime.get_y();
		double Vx = D_speed_aftertime.get_x();
		double Vy = D_speed_aftertime.get_y();
		double Ax = D_acceleration_aftertime.get_x();
		double Ay = D_acceleration_aftertime.get_y();
		double a1 = Ay * Ay + Ax * Ax;
		double a2 = 3 * (Ax * Vx + Ay * Vy);
		double a3 = 2 * (Vx * Vx + x * Ax + Vy * Vy + y * Ay);
		double a4 = 2 * (x * Vx + y * Vy);
		double solves[4];
		PMathO::solve3(solves, a1, a2, a3, a4);
		for (int i = 1; i <= solves[0]; i++) {
			if (0 < solves[i] && solves[i] <= end_timeline_2 - end_timeline_1) {
				double distance = (obj1->get_position_at_time(aftertime + solves[i]) - obj2->get_position_at_time(aftertime + solves[i])).get_lenth();
				if (distance < min_distanse_for_true) return true;
			}
		}
		double distance_at_end_timeline_2 = (obj1->get_position_at_time(end_timeline_2) - obj2->get_position_at_time(end_timeline_2)).get_lenth();
		if (distance_at_end_timeline_2 < min_distanse_for_true) return true;
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
		//using solwe_polynom fing intersection
		double time11 = obj1->get_last_update_time_sec() + obj1->get_how_time_to_stop();
		double time22 = obj2->get_last_update_time_sec() + obj2->get_how_time_to_stop();

		double end_timeline_1 = time11;
		double end_timeline_2 = time22;
		bool O1StopBefoO2 = true;
		if (time11 > time22) {
			end_timeline_1 = time22;
			end_timeline_2 = time11;
			O1StopBefoO2 = false;
		}

		if (start_time > end_timeline_2) return -1.0;

		if (start_time <= end_timeline_1) {
			PMathO::Vec2D d_pos = obj1->get_position_at_time(start_time) - obj2->get_position_at_time(start_time);
			PMathO::Vec2D speed1 = obj1->get_speed() - obj1->get_acceleration() * (start_time - obj1->get_last_update_time_sec());
			PMathO::Vec2D speed2 = obj2->get_speed() - obj2->get_acceleration() * (start_time - obj2->get_last_update_time_sec());
			PMathO::Vec2D d_speed = speed1 - speed2;
			PMathO::Vec2D d_acceleration = obj1->get_acceleration() - obj2->get_acceleration();
			double x = d_pos.get_x();
			double y = d_pos.get_y();
			double Vx = d_speed.get_x();
			double Vy = d_speed.get_y();
			double Ax = d_acceleration.get_x();
			double Ay = d_acceleration.get_y();
			//we should find t from 
			// rad1+rad2 = ((d_x_pos + t*d_x_speed + t*t*d_x_acceleration/2)^2 + (d_y_pos + t*d_y_speed + t*t*d_y_acceleration/2)^2)^0.5
			// 
			//or other wariant:
			//solwe this:
			// 0 = t^4(Ax * Ax/4 + Ay * Ay / 4) + t^3(Ax*vx + Ay*vy) + t^2(y * Ay + vy*vy + x*Ax + x*Ax) + t(2yVy + 2 xVx) + x*x + y*y - (rad1+rad2)^2
			int stepen = 4;
			double* polynom_solweing = new double[(stepen + 1) * (stepen + 1)];
			polynom_solweing[stepen + 0] = Ax * Ax / 4 + Ay * Ay / 4;
			polynom_solweing[stepen + 1] = Vy * Ay + Ax * Vx;
			polynom_solweing[stepen + 2] = Vx * Vx + Ax * x + Vy * Vy + Ay * y;
			polynom_solweing[stepen + 3] = 2 * x * Vx + 2 * y * Vy;
			polynom_solweing[stepen + 4] = x * x + y * y - (rad1 + rad2) * (rad1 + rad2);
			int how_answer = PMathO::solvepolynom(polynom_solweing, polynom_solweing + stepen, stepen);
			for (int i = 0; i < how_answer; i++) {
				if (start_time + polynom_solweing[i] <= end_timeline_1 and polynom_solweing[i] > 0) {
					double answer = polynom_solweing[i] + start_time;
					delete[] polynom_solweing;
					return answer;
				}
			}
			delete[] polynom_solweing;
		}

		PMathO::Vec2D speed1(0, 0);
		PMathO::Vec2D speed2(0, 0);
		PMathO::Vec2D acceleration1(0, 0);
		PMathO::Vec2D acceleration2(0, 0);

		// fix hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee wrong work with time
		if (start_time < end_timeline_1) {
			start_time = end_timeline_1;
		}
		if (O1StopBefoO2) {
			speed2 = obj2->get_speed() - obj2->get_acceleration() * (start_time - obj2->get_last_update_time_sec());
			acceleration2 = obj2->get_acceleration();
		}
		else {
			speed1 = obj1->get_speed() - obj1->get_acceleration() * (start_time - obj1->get_last_update_time_sec());
			acceleration1 = obj1->get_acceleration();
		}
		PMathO::Vec2D d_pos = obj1->get_position_at_time(start_time) - obj2->get_position_at_time(start_time);
		PMathO::Vec2D d_speed = speed1 - speed2;
		PMathO::Vec2D d_acceleration = acceleration1 - acceleration2;



		double x = d_pos.get_x();
		double y = d_pos.get_y();
		double Vx = d_speed.get_x();
		double Vy = d_speed.get_y();
		double Ax = d_acceleration.get_x();
		double Ay = d_acceleration.get_y();
		//we should find t from 
		// rad1+rad2 = ((d_x_pos + t*d_x_speed + t*t*d_x_acceleration/2)^2 + (d_y_pos + t*d_y_speed + t*t*d_y_acceleration/2)^2)^0.5
		// 
		//or other wariant:
		//solwe this:
		// 0 = t^4(Ax * Ax/4 + Ay * Ay / 4) + t^3(Ax*vx + Ay*vy) + t^2(y * Ay + vy*vy + x*Ax + x*Ax) + t(2yVy + 2 xVx) + x*x + y*y - (rad1+rad2)^2
		int stepen = 4;
		double* polynom_solweing = new double[(stepen + 1) * (stepen + 1)];
		polynom_solweing[stepen + 0] = Ax * Ax / 4 + Ay * Ay / 4;
		polynom_solweing[stepen + 1] = Vy * Ay + Ax * Vx;
		polynom_solweing[stepen + 2] = Vx * Vx + Ax * x + Vy * Vy + Ay * y;
		polynom_solweing[stepen + 3] = 2 * x * Vx + 2 * y * Vy;
		polynom_solweing[stepen + 4] = x * x + y * y - (rad1 + rad2) * (rad1 + rad2);
		int how_answer = PMathO::solvepolynom(polynom_solweing, polynom_solweing + stepen, stepen);
		for (int i = 0; i < how_answer; i++) {
			if (polynom_solweing[i] <= end_timeline_2-end_timeline_1 and polynom_solweing[i] > 0) {
				double answer = polynom_solweing[i] + start_time;
				delete[] polynom_solweing;
				return answer;
			}
		}
		delete[] polynom_solweing;
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
	//this->print_me();
	Collision* iterator_collision = this;//                                                          \V/ simbol <= mabe should be just <
	hhds += 0;
	int tt = 0;
	while ((iterator_collision->next_collision != 0) and (iterator_collision->next_collision->time_when_collision_sec <= insert_collision->time_when_collision_sec))//find position for our collision
	{
		iterator_collision = iterator_collision->next_collision; tt++;
	}

	if (iterator_collision->next_collision == 0) {
		insert_collision->before_collision = iterator_collision;//here i just insert in linked_lst -- collision new item
		iterator_collision->next_collision = insert_collision;
		insert_collision->next_collision = 0;
	}
	else {
		insert_collision->before_collision = iterator_collision;
		insert_collision->next_collision = iterator_collision->next_collision;
		iterator_collision->next_collision = insert_collision;
		insert_collision->next_collision->before_collision = insert_collision;
	}
	hhds = insert_collision;
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


void simulation_room::UpdateOneTic(double time_to_msec) {
	double time_to_sec = time_to_msec / 1000.;
	while (collision_header.next_collision != 0 && collision_header.next_collision->time_when_collision_sec < time_to_sec) {//get first future collision in collision timeline
		//collision_header.print_me();
		
		//std::cout << time_to_sec << std::endl;
		//std::cout << collision_header.next_collision->time_when_collision_sec << std::endl;
		//solve broken collision
		Collision* working_collision = collision_header.next_collision; //our working collision for one iteration of loop
		working_collision->detach();//we are detach collision from collision linkd lst
		PO::Object* obj1 = working_collision->ptr_obj_1;
		PO::Object* obj2 = working_collision->ptr_obj_2;
		obj1->my_next_collision_pointer = 0;
		obj2->my_next_collision_pointer = 0;

		obj1->update_mechanics_parameters(working_collision->time_when_collision_sec);//here we move obj1 to time when collision
		obj2->update_mechanics_parameters(working_collision->time_when_collision_sec);//and obj2 moveing too
		delete working_collision;//delete this collision because we already worked with it and it is in past now
		solve_collision_between(obj1, obj2);									  // solve collision using two object: obj_1, obj_2
		update_future_collision_for(obj1);										  //here we should update future collision for this object and solve problem with this chenges
		update_future_collision_for(obj2);									      //								     and for this object too
		
	//after working with kollision of all our objects we mowe all our object to correct finish time
	}//here i move every object to time_to_sec
	for (auto& element : objects) {
		element->update_mechanics_parameters(time_to_sec);
	}
	solve_functionQueue();
}

void simulation_room::add_object(PO::Object* new_object) {
	new_object->set_last_update_time_sec(game_time_sec);
	new_object->my_room = this;
	objects.push_back(new_object); //add object
	update_future_collision_for(new_object); //find collision if it'll be
}

void simulation_room::set_time_all_object(double new_time_sec) {
	return void();
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
	game_time_sec += PeriodForTicInMSec;
	double start_this_cicle = (double)clock();
	while (simulation_is_working) {
		start = clock();
		UpdateOneTic(game_time_sec);//give that time to update we want
		end = clock();
		time_of_work = end - start;
		ms_time_to_wait = (game_time_sec - (double)clock() + start_this_cicle);//time for waiting
		if (ms_time_to_wait > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(ms_time_to_wait));//wait for next tic
		}
		game_time_sec += PeriodForTicInMSec;
		resource = time_of_work / PeriodForTicInMSec;//this is our prog resource, if 0 more then time, then resource > 1
	}
	game_time_sec -= PeriodForTicInMSec;
}

void simulation_room::StartSimulation() {
	if (not simulation_is_working) {
		simulation_is_working = true;
		myThread = std::thread(&simulation_room::simulationCicle, this);
	}
}

void simulation_room::StopSimulation() {
	if (simulation_is_working) {
		simulation_is_working = false;
		solve_functionQueue();
		myThread.join();
	}
}

void simulation_room::solve_collision_between(PO::Object* ptr_obj_1, PO::Object* ptr_obj_2) {
	//this is just for test!!!!!!!!!
	//first of all 
	
	//if both objects are moveble
	if (ptr_obj_1->get_type() == 2 and ptr_obj_2->get_type() == 2) {

		//first and second collider are cricles and both of them are moveble
		if (ptr_obj_1->get_collider()->get_type() == 2 and ptr_obj_2->get_collider()->get_type() == 2) {
			/////////////////////////////////////////////////////////////////
			// (Y)         _A_  
			//  A         / | \
			//  |         \_|_/           A
			//  |    ------_|_-----       |-- impulse_line -- line between two centers of object 
			//  |         / | \           |
			//  |         \_|_/
			//  |
			//  O----------->(X)           
			// 
			// X speed of object will saved and y speed will changed. 
			// 
			// X - vec perpendicular impuls_line
			// Y - vec perallel impuls_line
			// 
			//
			PMathO::Vec2D impulse_line = ptr_obj_2->get_position() - ptr_obj_1->get_position(); // it's tangent scalar
			if (impulse_line.get_lenth() != 0) {
				impulse_line = impulse_line / impulse_line.get_lenth();//we are normalyze our vec
			}
			PMathO::Vec2D impulse_perp_line(impulse_line.get_y(), -impulse_line.get_x());
			// speed1_X + speed1_Y = ptr_obj_1->get_speed()
			// speed2_X + speed2_Y = ptr_obj_2->get_speed()
			//C(xc, yc) = ((x1 * x2 + y1 * y2) / (x2^2 + y2^2)) * (x2, y2)
			//C = (A � B) / (||B||^2) * B
			double mass1 = ptr_obj_1->get_mass();
			double mass2 = ptr_obj_2->get_mass();
			PMathO::Vec2D speed1 = ptr_obj_1->get_speed();
			PMathO::Vec2D speed2 = ptr_obj_2->get_speed();
			double lenth1_Y = (speed1.get_x() * impulse_line.get_x() + speed1.get_y() * impulse_line.get_y());
			double lenth2_Y = (speed2.get_x() * impulse_line.get_x() + speed2.get_y() * impulse_line.get_y());
			PMathO::Vec2D speed1_X = impulse_perp_line * (speed1.get_x() * impulse_perp_line.get_x() + speed1.get_y() * impulse_perp_line.get_y());
			PMathO::Vec2D speed1_Y = impulse_line * lenth1_Y;
			PMathO::Vec2D speed2_X = impulse_perp_line * (speed2.get_x() * impulse_perp_line.get_x() + speed2.get_y() * impulse_perp_line.get_y());
			PMathO::Vec2D speed2_Y = impulse_line * lenth2_Y;
			double Impuls = 0;
			if (lenth1_Y > 0) {
				Impuls += mass1 * speed1_Y.get_lenth();
			}
			else {
				Impuls -= mass1 * speed1_Y.get_lenth();
			}
			if (lenth2_Y > 0) {
				Impuls += mass2 * speed2_Y.get_lenth();
			}
			else {
				Impuls -= mass2 * speed2_Y.get_lenth();
			}
			double TwinSumEKin = mass1 * speed1_Y.get_lenth() * speed1_Y.get_lenth() + mass2 * speed2_Y.get_lenth() * speed2_Y.get_lenth();
			double answer[3];//answer on V1^2(m1m2 + m1m1) -2Pm1V1 + p^2 - Em1=0 for V1
			PMathO::solve2(answer, mass1 * (mass1 + mass2), -2 * Impuls * mass1, Impuls * Impuls - TwinSumEKin * mass2);
			double Double_speed1_Y_new = answer[1];
			double Double_speed2_Y_new = (Impuls - mass1 * Double_speed1_Y_new) / mass2;
			PMathO::Vec2D speed1_Y_new = impulse_line * Double_speed1_Y_new;
			PMathO::Vec2D speed2_Y_new = impulse_line * Double_speed2_Y_new;





			*(ptr_obj_1->get_ptr_speed()) = speed1_X + speed1_Y_new;
			*(ptr_obj_2->get_ptr_speed()) = speed2_X + speed2_Y_new;
		}
		//if objects are not cricle but moveble
		else {
			//impuls and mehanic work should be saved for collision.
			*(ptr_obj_1->get_ptr_speed()) *= -1.;//just chanje vector of speed
			*(ptr_obj_2->get_ptr_speed()) *= -1.;//here we make te same things with the second object
		}
	}
	//if one of objects is static(not moveble)
	else {
		if (ptr_obj_1->get_collider()->get_type() == 2 and ptr_obj_2->get_collider()->get_type() == 2) {
			PO::Object* static_obj_ptr = ptr_obj_1;
			PO::Object* moveble_obj_ptr = ptr_obj_2;

			if (ptr_obj_2->get_type() == 1) {
				static_obj_ptr = ptr_obj_2;
				moveble_obj_ptr = ptr_obj_1;
			}

			PMathO::Vec2D impulse_line = moveble_obj_ptr->get_position() - static_obj_ptr->get_position(); // it's tangent scalar
			if (impulse_line.get_lenth() != 0) {
				impulse_line = impulse_line / impulse_line.get_lenth();//we are normalyze our vec
			}
			PMathO::Vec2D impulse_perp_line(impulse_line.get_y(), -impulse_line.get_x());
			PMathO::Vec2D speed1 = moveble_obj_ptr->get_speed();
			PMathO::Vec2D speed1_X = impulse_perp_line * (speed1.get_x() * impulse_perp_line.get_x() + speed1.get_y() * impulse_perp_line.get_y());
			PMathO::Vec2D speed1_Y = impulse_line * (speed1.get_x() * impulse_line.get_x() + speed1.get_y() * impulse_line.get_y());
			*(moveble_obj_ptr->get_ptr_speed()) = speed1_X - speed1_Y;
		}
		else {
			//impuls and mehanic work should be saved for collision.
			*(ptr_obj_1->get_ptr_speed()) *= -1.;//just chanje vector of speed
			*(ptr_obj_2->get_ptr_speed()) *= -1.;//here we make te same things with the second object
		}

	}
}


void simulation_room::update_future_collision_for(PO::Object* updater_obj){

	//here we start find nearest collision for updater_obj
	PO::Object* find_collider = 0; // firstly we are not find collision


	double time_nearest_collision;
	if (updater_obj->my_next_collision_pointer == 0) {
		time_nearest_collision = 1.0E100;//if our obj havn't collision
	}
	else {
		
		time_nearest_collision = static_cast<Collision*>(updater_obj->my_next_collision_pointer)->time_when_collision_sec; // if our object have future collision
	}
	//find obj that we will collide
	for (auto& element : objects) {
		
		if (element == updater_obj) continue;//if we meet updater_obj then skip
		double time_when_element_collid_updater_obj = collision_header.get_time_collision(updater_obj, element);
		 // here i must realisate pointer from obj to his future collision
		if ((0. < time_when_element_collid_updater_obj) and (time_when_element_collid_updater_obj < time_nearest_collision)) {//firstly time_when_element_collid should be not (-1.0 <=> will no collision)
			Collision* collision_of_this_object = static_cast<Collision*>(element->my_next_collision_pointer);
			if (collision_of_this_object == 0 or collision_of_this_object->time_when_collision_sec > time_when_element_collid_updater_obj) {
				find_collider = element;
				
				time_nearest_collision = time_when_element_collid_updater_obj;
			}
		}
	}

	//If find_collider=0 then we are not find new collision.
	//If find_collider!=0 then we should to incsert new collision and fix another collision.
	if (find_collider != 0) {

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
			delete static_cast<Collision*>(find_collider->my_next_collision_pointer);//collision will not heppened becouse we find collision which is earlier in time
			second_broken_collision_1->my_next_collision_pointer = 0;

		}
		if (updater_obj->my_next_collision_pointer != 0) {
			if (updater_obj == static_cast<Collision*>(updater_obj->my_next_collision_pointer)->ptr_obj_1) {
				second_broken_collision_2 = static_cast<Collision*>(updater_obj->my_next_collision_pointer)->ptr_obj_2;
			}
			else {
				second_broken_collision_2 = static_cast<Collision*>(updater_obj->my_next_collision_pointer)->ptr_obj_1;
			}
			delete static_cast<Collision*>(updater_obj->my_next_collision_pointer);//collision will not heppened becouse we find collision which is earlier in time
			second_broken_collision_2->my_next_collision_pointer = 0;
		}

		updater_obj->my_next_collision_pointer = new_collision;
		find_collider->my_next_collision_pointer = new_collision;
		collision_header.insert_collision(new_collision);
		

		if (second_broken_collision_1!=0) { //fix object from collision that we delete
			update_future_collision_for(second_broken_collision_1);
			}

		if (second_broken_collision_2!=0) { //fix object from collision that we delete
			update_future_collision_for(second_broken_collision_2);
		}
	}
}

void simulation_room::solve_functionQueue() {
	std::pair<std::function<void(void*)>, void*> operation;
	for (int i = 0; i < operationQueue.size(); i++) {
		operation = operationQueue.front();
		operationQueue.pop();
		//genious of thought
		//don't hit me please for this code
		(operation.first)(operation.second);
	}
}

void simulation_room::add_operation_in_queue(std::pair<std::function<void(void*)>, void*> operation){
	operationQueue.push(operation);
}