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
	};

	class StaticObject : public Object {
	
	};

	class MovebleObject : public Object {
	private:
		bool IsCollisionDo;
		double mass;
		double Frict;
		PMathO::Vec2D speed;
		PMathO::Vec2D force;
	public:
		MovebleObject(PMathO::Vec2D position, PMeshO::Mesh mesh, double mass, double Frict, PMathO::Vec2D speed, PMathO::Vec2D force);
		
		void update_position(double time);
	};
}
#endif /*PhysObjObj*/