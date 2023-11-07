#pragma once
#ifndef PhysObjObj
#define PhysObjObj
#include "PhysMathObj.h"
#include "PhysColliderObj.h"
namespace PO {



	class Object {
	protected:
		char type = 0; // 1 if static, 2 if moveble;
		double mass = 1;
		double FrictCoef = 1;//physic parameter means coefficient of friction(usually betwen two materials, bat here it is frict between MovebleObject and map)
		bool IsCollisionDo = true;
		bool destroy_if_collision = false;
		bool event_if_collision = false; // add funk that if collision then we call function(add in future)
		PMathO::Vec2D position;
		PColliderO::Collider* mesh;
		PMathO::Vec2D speed = PMathO::Vec2D(0, 0);
		double last_update_time_sec = 0;
	public:
		/// <summary> pointer on (struct Collision from PhysSimulation.h) </summary>
		void* my_next_collision_pointer = 0;
		Object(PMathO::Vec2D position, PColliderO::Collider* mesh);
		PMathO::Vec2D* get_ptr_speed();
		PMathO::Vec2D get_speed() const;
		PMathO::Vec2D get_acceleration() const;
		void collision_on();
		void collision_off();
		double const get_last_update_time_sec() const;
		const PColliderO::Collider* get_collider() const;
		void virtual update_mechanics_parameters(double to_time_sec);
		void virtual set_last_update_time_sec(double new_time_sec);
		void virtual set_new_speed(PMathO::Vec2D new_speed);
		void set_new_position(PMathO::Vec2D new_position);
		bool get_IsCollisionDo() const;
		const PMathO::Vec2D get_position() const;
		char get_type() const;
		double get_how_time_to_stop();
		PMathO::Vec2D get_position_at_time(double time_sec);
	};

	class StaticObject : public Object {
	public:
		StaticObject(PMathO::Vec2D position, PColliderO::Collider *mesh);
	};

	class MovebleObject : public Object {
	public:
		MovebleObject(PMathO::Vec2D position, PColliderO::Collider *mesh, double mass, double FrictCoef, PMathO::Vec2D StartSpeed);
		void update_mechanics_parameters(double to_time_sec) override final;
		void set_last_update_time_sec(double new_time_sec) override final;
		void set_new_speed(PMathO::Vec2D new_speed) override final;
	};
}
#endif /*PhysObjObj*/