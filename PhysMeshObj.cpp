#include "PhysMeshObj.h"
using namespace PMeshO;
Mesh::Mesh(double width = 0., double height = 0.) : width(width), height(height) {}
double Mesh::get_width() const { return width; }
double Mesh::get_height() const { return height; }