#pragma once
#ifndef PhysMeshObj
#define PhysMeshObj
#include <cmath>
namespace PColliderO {
	class Collider {
	private:
		double coverage_radious=0.;
		friend class CricleCollider;
		friend class RectangleCollider;
	public:
		Collider();
		virtual void test();
		const double get_coverage_radious() const;
	};

	class CricleCollider : public Collider{
	protected:
		double radious;
	public:
		CricleCollider(double start_radious=10.);
		void test() final;
	};

	class RectangleCollider : public Collider {
	protected:
		double width;
		double height;
	public:
		RectangleCollider(double start_width=10., double start_height=10.);
		void test() final;
	};
}
#endif