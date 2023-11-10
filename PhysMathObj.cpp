#include <cmath>
#include "PhysMathObj.h"
using namespace PMathO;


void Vec2D::update_lenth() { lenth = sqrt(x * x + y * y); }

Vec2D::Vec2D(double x, double y) : x(x), y(y) {
	radian_angle = 5.;
	update_lenth();
}

double Vec2D::get_x() const{ return x; }

double Vec2D::get_y() const { return y; }

double Vec2D::get_lenth() const { return lenth; }

void Vec2D::add_vec(Vec2D vector) {
	this->x += vector.x;
	this->y += vector.y;
	update_lenth();
}

Vec2D Vec2D::operator+(const Vec2D& other) const {
	return Vec2D(this->x + other.x, this->y + other.y);
}

Vec2D Vec2D::operator-(const Vec2D& other) const {
	return Vec2D(this->x - other.x, this->y - other.y);
}

Vec2D Vec2D::operator*(const double& other) const {
	return Vec2D(this->x * other, this->y * other);
}

Vec2D Vec2D::operator/(const double& other) const {
	if (other != 0)
		return Vec2D(this->x / other, this->y / other);
	else 
		return Vec2D(this->x, this->y);
}

Vec2D Vec2D::operator*=(const double& other){
	this->x *= other;
	this->y *= other;
	update_lenth();
	return *this;
}

Vec2D Vec2D::operator+=(const Vec2D& other) {
	this->x += other.x;
	this->y += other.y;
	update_lenth();
	return *this;
}

Vec2D Vec2D::operator-=(const Vec2D& other) {
	this->x -= other.x;
	this->y -= other.y;
	update_lenth();
	return *this;
}

Vec2D Vec2D::operator*=(const Vec2D& other) {
	this->x *= other.x;
	this->y *= other.y;
	update_lenth();
	return *this;
}

void Section2D::position_update() { lenth = sqrt(x_lenth * x_lenth + y_lenth * y_lenth); }

Section2D::Section2D(Vec2D A, Vec2D B) : A(A), B(B) {
	x_lenth = B.get_x() - A.get_x();
	y_lenth = B.get_y() - A.get_y();
	position_update();
}


double Section2D::get_distance_to_point(Vec2D C) {
	double lenthAC = Section2D(A, C).lenth;
	double lenthBC = Section2D(B, C).lenth;
	double lenthAB = lenth;
	double alfa, beta, gama;
	alfa = acos((pow(lenthAC, 2) + pow(lenthAB, 2) - pow(lenthBC, 2)) / (2 * lenthAC * lenthAB));
	beta = acos((pow(lenthBC, 2) + pow(lenthAB, 2) - pow(lenthAC, 2)) / (2 * lenthBC * lenthAB));
	gama = acos((pow(lenthBC, 2) + pow(lenthAC, 2) - pow(lenthAB, 2)) / (2 * lenthBC * lenthAC));
	if (beta > PI/2) return lenthBC;
	else if (alfa > PI/2) return lenthAC;
	else return lenthBC * sin(beta);
	return 0;
}

