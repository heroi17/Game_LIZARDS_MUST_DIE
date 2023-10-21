#include "PhysMathObj.cpp"
#include "PhysMeshObj.cpp"
class object {
private:
	Point2D position;
	Mesh mesh;
	double mass;
	Vec2D speed;
	Vec2D force;
public:
	object(Point2D position) : position(position) {}

};
class static_object {
};
class moveble_object {

};