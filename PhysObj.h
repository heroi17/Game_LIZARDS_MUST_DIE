#pragma once
#ifndef PhysObjObj
#define PhysObjObj
#include "PhysMathObj.h"
#include "PhysMeshObj.h"
namespace PO {
	class Object {
	private:
		bool IsCollisionDo = true;
		PMathO::Vec2D position;
		PMeshO::Mesh mesh;
		friend class StaticObject;
		friend class MovebleObject;
	public:
		Object(PMathO::Vec2D position, PMeshO::Mesh mesh);
		void collision_on();
		void collision_off();
		bool get_IsCollisionDo() const;
		PMathO::Vec2D get_position();
	};

	class StaticObject : public Object {
	public:
		StaticObject(PMathO::Vec2D position, PMeshO::Mesh mesh);
	};

	class MovebleObject : public Object {
	private:
		double last_update_time_sec = 0;
		double mass;
		double Frict;
		PMathO::Vec2D speed;
		PMathO::Vec2D force;
	public:
		MovebleObject(PMathO::Vec2D position, PMeshO::Mesh mesh, double mass, double Frict, PMathO::Vec2D speed, PMathO::Vec2D force);
		
		void update_mechanics_parameters(double to_time_sec);
		void set_last_update_time_sec(double new_time_sec);
	};
}
#endif /*PhysObjObj*/