#pragma once
#ifndef PhysObjObj
#define PhysObjObj
#include "PhysMathObj.cpp"
#include "PhysMeshObj.cpp"
#include "PhysTimeObj.cpp"
class Object {
private:
	Vec2D position;
	Mesh mesh;
	friend class StaticObject;
	friend class MovebleObject;
public:
	Object(Vec2D position, Mesh mesh) : position(position), mesh(mesh) {}

};
class StaticObject {
};
class MovebleObject : public Object{
private:
	bool IsCollisionDo = true;
	double mass;
	double Frict;
	Vec2D speed;
	Vec2D force;
public:
	MovebleObject(Vec2D position, Mesh mesh, double mass, double Frict, Vec2D speed, Vec2D force) : Object(position, mesh), mass(mass), Frict(Frict), speed(speed), force(force){

	}
	void update_position(TimeObject time){
		position += speed * time;
	}
	void collision_on() { IsCollisionDo = true; }
	void collision_off() { IsCollisionDo = false;  }


};
#endif /*PhysObjObj*/