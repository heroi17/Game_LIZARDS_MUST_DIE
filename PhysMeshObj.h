#pragma once
#ifndef PhysMeshObj
#define PhysMeshObj
#include <cmath>
namespace PMeshO {
	struct Mesh {
	private:
		double width; 
		double height;
		double radious; // if mesh is cricle then it is his radious elif mesh is rect then it is radius of the circumscribed circle
		int type; // 0 if cricle, 1 if rectangle
	public:
		Mesh(int type, double width, double height);
		double get_width() const;
		double get_height() const;
	};
}
#endif