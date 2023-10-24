#pragma once
#include "PhysObj.h"
using namespace PO;


Object::Object(PMathO::Vec2D position, PMeshO::Mesh mesh) : position(position), mesh(mesh) {}

MovebleObject::MovebleObject(PMathO::Vec2D position, PMeshO::Mesh mesh, double mass, double Frict, PMathO::Vec2D speed, PMathO::Vec2D force) : Object(position, mesh), mass(mass), Frict(Frict), speed(speed), force(force) {}

void MovebleObject::update_position(double time) {
	position += speed * time;
}
void Object::collision_on() { IsCollisionDo = true; }

void Object::collision_off() { IsCollisionDo = false; }