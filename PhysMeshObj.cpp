#include "PhysMeshObj.h"
using namespace PMeshO;
Mesh::Mesh(int start_type = 0, double start_width = 0., double start_height = 0.) : width(start_width), height(start_width), type(start_type) {
	switch (start_type)
	{
	case 0://cricle
		radious = start_width;//just radious of cricle
		break;
	case 1://rectangle
		radious = sqrt((start_width / 2.) * (start_width / 2.) + (start_height / 2.) * (start_height / 2.));
		break;
	default:
		type = 0; //if we don't find right type then our type is 0 - cricle
		radious = start_width;
		break;
	}
}
double Mesh::get_width() const { return width; }

double Mesh::get_height() const { return height; }