#pragma once
#ifndef PhysObjObj
#define PhysObjObj
#include "PhysMathObj.h"
#include "PhysColliderObj.h"
namespace PO {
	class Object {
	protected:
		char type = 0; // 1 if static, 2 if moveble;
		bool IsCollisionDo = true;
		bool destroy_if_collision = false;
		bool event_if_collision = false; // add funk that if collision then we call function(add in future)
		PMathO::Vec2D position;
		PColliderO::Collider* mesh;
		PMathO::Vec2D speed = PMathO::Vec2D(0, 0);
	public:
		Object(PMathO::Vec2D position, PColliderO::Collider* mesh);
		PMathO::Vec2D* get_ptr_speed();
		void collision_on();
		void collision_off();
		const PColliderO::Collider* get_collider() const;
		void virtual update_mechanics_parameters(double to_time_sec);
		void virtual set_last_update_time_sec(double new_time_sec);
		bool get_IsCollisionDo() const;
		const PMathO::Vec2D get_position() const;
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
	public:
		MovebleObject(PMathO::Vec2D position, PColliderO::Collider *mesh, double mass, double FrictCoef, PMathO::Vec2D StartSpeed);
		void update_mechanics_parameters(double to_time_sec) override final;
		void set_last_update_time_sec(double new_time_sec) override final;
	};
}
#endif /*PhysObjObj*/