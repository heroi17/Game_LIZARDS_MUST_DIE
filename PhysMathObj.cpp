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

void Line2D::position_update() { lenth = sqrt(x_lenth * x_lenth + y_lenth * y_lenth); }

Line2D::Line2D(Vec2D A, Vec2D B) : A(A), B(B) {
	x_lenth = B.get_x() - A.get_x();
	y_lenth = B.get_y() - A.get_y();
	position_update();
}