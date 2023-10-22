#pragma once
#ifndef PhysObjObj
#define PhysObjObj
#include "PhysMathObj.cpp"
#include "PhysMeshObj.cpp"
namespace PO {
	class Object {
	private:
		PMathO::Vec2D position;
		PMeshO::Mesh mesh;
		friend class StaticObject;
		friend class MovebleObject;
	public:
		Object(PMathO::Vec2D position, PMeshO::Mesh mesh) : position(position), mesh(mesh) {}

	};
	class StaticObject {
	};
	class MovebleObject : public Object {
	private:
		bool IsCollisionDo = true;
		double mass;
		double Frict;
		PMathO::Vec2D speed;
		PMathO::Vec2D force;
	public:
		MovebleObject(PMathO::Vec2D position, PMeshO::Mesh mesh, double mass, double Frict, PMathO::Vec2D speed, PMathO::Vec2D force) : Object(position, mesh), mass(mass), Frict(Frict), speed(speed), force(force) {

		}
		void update_position(double time) {
			position += speed * time;
		}
		void collision_on() { IsCollisionDo = true; }
		void collision_off() { IsCollisionDo = false; }


	};
}
#endif /*PhysObjObj*/