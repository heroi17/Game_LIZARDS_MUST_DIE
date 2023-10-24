#pragma once
#ifndef PhysMeshObj
#define PhysMeshObj
namespace PMeshO {
	struct Mesh {
	private:
		double width;
		double height;
	public:
		Mesh(double width, double height);
		double get_width() const;
		double get_height() const;
	};
}
#endif