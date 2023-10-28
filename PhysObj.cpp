#pragma once
#include <iostream>
#include "PhysObj.h"
using namespace PO;

//parent class Object here
Object::Object(PMathO::Vec2D position, PColliderO::Collider mesh) : position(position), mesh(mesh) {}

void Object::update_mechanics_parameters(double to_time_sec) {};

void Object::set_last_update_time_sec(double new_time_sec) {};

void Object::collision_on() { IsCollisionDo = true; }

void Object::collision_off() { IsCollisionDo = false; }

bool Object::get_IsCollisionDo() const { return IsCollisionDo; }

char Object::get_type() const {
	return type;
}

const PColliderO::Collider Object::get_collider() const{
	return mesh;
}



//MovebleObject here

MovebleObject::MovebleObject(PMathO::Vec2D position, PColliderO::Collider mesh, double mass = 1., double FrictCoef = 1., PMathO::Vec2D speed = PMathO::Vec2D(0., 0.)) : Object(position, mesh), mass(mass), FrictCoef(FrictCoef), speed(speed) {
	type = 35;
}

void MovebleObject::update_mechanics_parameters(double to_time_sec){
	//here just test for start course i don't now will be or not force;
	double delta_time = to_time_sec - this->last_update_time_sec;//add frict to finish this part course here we are not use frict
	if (speed.get_lenth() != 0) {
		PMathO::Vec2D friction_acceleration = speed * (mass * (-9.8) * FrictCoef / speed.get_lenth());
		double how_time_to_stop = speed.get_lenth() / friction_acceleration.get_lenth();
		if (last_update_time_sec + how_time_to_stop > to_time_sec) {
			position += speed * delta_time + friction_acceleration * delta_time * delta_time * 0.5;
			speed += friction_acceleration * delta_time;
		}
		else {
			position += speed * how_time_to_stop + friction_acceleration * how_time_to_stop * how_time_to_stop * 0.5;
			speed *= 0;
			std::cout << speed.get_lenth();
		}
	}
	this->last_update_time_sec = to_time_sec;
}

void MovebleObject::set_last_update_time_sec(double new_time_sec) {//do not use when update_mechanics_parameters is working for another MovebleObject
	this->last_update_time_sec = new_time_sec;
}

PMathO::Vec2D Object::get_position() {
	return this->position;
}



//StaticObject here

StaticObject::StaticObject(PMathO::Vec2D position, PColliderO::Collider mesh): Object(position, mesh) {
	type = 64;
}