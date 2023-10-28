#pragma once
#ifndef PhysObjObj
#define PhysObjObj
#include "PhysMathObj.h"
#include "PhysColliderObj.h"
namespace PO {
	class Object {
	private:
		char type = 0;
		bool IsCollisionDo = true;
		bool destroy_if_collision = false;
		bool event_if_collision = false; // add funk that if collision then we call function(add in future)
		PMathO::Vec2D position;
		PColliderO::Collider* mesh;
		friend class StaticObject;
		friend class MovebleObject;
	public:
		Object(PMathO::Vec2D position, PColliderO::Collider* mesh);
		void collision_on();
		void collision_off();
		const PColliderO::Collider* get_collider() const;
		void virtual update_mechanics_parameters(double to_time_sec);
		void virtual set_last_update_time_sec(double new_time_sec);
		bool get_IsCollisionDo() const;
		PMathO::Vec2D get_position();
		char get_type() const;
	};

	class StaticObject : public Object {
	public:
		StaticObject(PMathO::Vec2D position, PColliderO::Collider *mesh);
	};

	class MovebleObject : public Object {
	private:
		double last_update_time_sec = 0;
		double mass;
		double FrictCoef;//physic parameter means coefficient of friction(usually betwen two materials, bat here it is frict between MovebleObject and map)

		PMathO::Vec2D speed;
	public:
		MovebleObject(PMathO::Vec2D position, PColliderO::Collider *mesh, double mass, double FrictCoef, PMathO::Vec2D speed);
		void update_mechanics_parameters(double to_time_sec) override final;
		void set_last_update_time_sec(double new_time_sec) override final;
	};
}
#endif /*PhysObjObj*/