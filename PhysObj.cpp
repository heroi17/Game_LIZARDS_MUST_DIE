#pragma once
#include <iostream>
#include "PhysObj.h"
using namespace PO;





//parent class Object here
Object::Object(PMathO::Vec2D position, PColliderO::Collider *mesh) : position(position), mesh(mesh) {}

PMathO::Vec2D* Object::get_ptr_speed() {
	return &speed;
}

PMathO::Vec2D Object::get_speed() const {
	return speed;
}
PMathO::Vec2D Object::get_friction_acceleration() const{
	return speed * (mass * (-9.8) * FrictCoef / speed.get_lenth());
}
const PMathO::Vec2D Object::get_position() const  {
	return this->position;
}

void Object::update_mechanics_parameters(double to_time_sec) {}

void Object::set_last_update_time_sec(double new_time_sec) {}

void Object::set_new_speed(PMathO::Vec2D new_speed) {}

void Object::set_new_position(PMathO::Vec2D new_position){
	position = new_position;
}

void Object::collision_on() { IsCollisionDo = true; }

void Object::collision_off() { IsCollisionDo = false; }

bool Object::get_IsCollisionDo() const { return IsCollisionDo; }

char Object::get_type() const {
	return type;
}

const PColliderO::Collider* Object::get_collider() const{
	return mesh;
}

double const Object::get_last_update_time_sec() const {
	return this->last_update_time_sec;
}


PMathO::Vec2D Object::get_position_at_time(double time) {
	if (time < last_update_time_sec) return position;
	return position;
	
}

double Object::get_time_when_stop() {
	return 0;
}
//MovebleObject here

MovebleObject::MovebleObject(PMathO::Vec2D position, PColliderO::Collider* mesh, double NewMass = 1., double NewFrictCoef = 1., PMathO::Vec2D StartSpeed = PMathO::Vec2D(0., 0.)) : Object(position, mesh) {
	mass = NewMass;
	FrictCoef = NewFrictCoef;
	
	speed = StartSpeed;
	type = 2;
}

void MovebleObject::update_mechanics_parameters(double to_time_sec){
	//here just test for start course i don't now will be or not force;
	double delta_time = to_time_sec - this->last_update_time_sec;//add frict to finish this part course here we are not use frict
	if (speed.get_lenth() != 0) {
		PMathO::Vec2D friction_acceleration = get_friction_acceleration();
		double how_time_to_stop = speed.get_lenth() / friction_acceleration.get_lenth();
		if (last_update_time_sec + how_time_to_stop > to_time_sec) {
			position += speed * delta_time + friction_acceleration * delta_time * delta_time * 0.5;
			speed += friction_acceleration * delta_time;
		}
		else {
			position += speed * how_time_to_stop + friction_acceleration * how_time_to_stop * how_time_to_stop * 0.5;
			speed *= 0;
		}
	}
	this->last_update_time_sec = to_time_sec;
}

void MovebleObject::set_last_update_time_sec(double new_time_sec) {//do not use when update_mechanics_parameters is working for another MovebleObject
	this->last_update_time_sec = new_time_sec;
}


void MovebleObject::set_new_speed(PMathO::Vec2D new_speed) {
	this->speed = new_speed;
};

//StaticObject here

StaticObject::StaticObject(PMathO::Vec2D position, PColliderO::Collider* mesh): Object(position, mesh) {
	type = 1;
}