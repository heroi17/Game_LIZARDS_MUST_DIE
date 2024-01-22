#pragma once
#ifndef PhysMeshObj
#define PhysMeshObj
#include <cmath>
namespace PColliderO {
	class Collider {
	private:
		double coverage_radious=0.;
		double width = 0;
		double height = 0;
		double radious = 0;
		friend class CricleCollider;
		friend class RectangleCollider;
	public:
		Collider();
		/// <summary>
		/// 2 is cricle collider
		/// 1 is rectngle collider
		/// </summary>
		/// <returns></returns>
		const virtual int get_type() const;
		const double get_coverage_radious() const;
		const double get_width() const { return width; }
		const double get_height() const { return height; }
		const double get_radious() const { return radious; }
	};

	class CricleCollider : public Collider{
	public:
		CricleCollider(double start_radious=10.);
		const int get_type() const final;
	};

	class RectangleCollider : public Collider {
	public:
		RectangleCollider(double start_width=10., double start_height=10.);
		const int get_type() const final;
	};
}
#endif