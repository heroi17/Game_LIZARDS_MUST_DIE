#pragma once
#include "PhysObj.h"
using namespace PO;


Object::Object(PMathO::Vec2D position, PMeshO::Mesh mesh) : position(position), mesh(mesh) {}

MovebleObject::MovebleObject(PMathO::Vec2D position, PMeshO::Mesh mesh, double mass = 1., double Frict = 1., PMathO::Vec2D speed = PMathO::Vec2D(0., 0.), PMathO::Vec2D force = PMathO::Vec2D(0., 0.)) : Object(position, mesh), mass(mass), Frict(Frict), speed(speed), force(force) {}

void MovebleObject::update_mechanics_parameters(double to_time_sec) {
	PMathO::Vec2D acceleration = this->force * this->mass;
	double delta_time = to_time_sec - this->last_update_time_sec;//add frict to finish this part course here we are not use frict
	this->position += this->speed * delta_time + acceleration * (delta_time * delta_time);
	this->speed += this->force * delta_time;
	this->last_update_time_sec = to_time_sec;
}
void MovebleObject::set_last_update_time_sec(double new_time_sec) {//do not use when update_mechanics_parameters is working for another MovebleObject
	this->last_update_time_sec = new_time_sec;
}
void Object::collision_on() { IsCollisionDo = true; }

void Object::collision_off() { IsCollisionDo = false; }

bool Object::get_IsCollisionDo() const { return IsCollisionDo; }

PMathO::Vec2D Object::get_position() {
	return this->position;
}


StaticObject::StaticObject(PMathO::Vec2D position, PMeshO::Mesh mesh): Object(position, mesh) {

}