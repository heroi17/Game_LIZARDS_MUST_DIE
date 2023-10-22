#pragma once
#ifndef PhysMathObj
#define PhysMathObj
#include <cmath>
struct Vec2D
{
private:
	double x;
	double y;
	double radian_angle;
	double lenth;
	void update_lenth() {lenth = sqrt(x * x + y * y);}
public:
	Vec2D(double x, double y) : x(x), y(y) {
		radian_angle = 5.;
		update_lenth();
	}

	double get_x() { return x; }
	double get_y() { return y; }
	double get_lenth() { return lenth; }
	void add_vec(Vec2D vector) {
		this->x += vector.x;
		this->y += vector.y;
		update_lenth();
	}
	Vec2D operator+(const Vec2D& other) const {
		return Vec2D(this->x + other.x, this->y + other.y);
	}
	Vec2D operator-(const Vec2D& other) const {
		return Vec2D(this->x - other.x, this->y - other.y);
	}
	Vec2D operator*(const double& other) const {
		return Vec2D(this->x * other, this->y * other);
	}
	Vec2D operator+=(const Vec2D& other){
		this->x += other.x;
		this->y += other.y;
		update_lenth();
		return *this;
	}

};

struct Line2D
{
private:
	Vec2D A;
	Vec2D B;
	double x_lenth;
	double y_lenth;
	double lenth;
	void position_update() { lenth = sqrt(x_lenth * x_lenth + y_lenth * y_lenth); }
public:
	Line2D(Vec2D A, Vec2D B) : A(A), B(B) {
		x_lenth = B.get_x() - A.get_x();
		y_lenth = B.get_y() - A.get_y();
		position_update();
	}
};
#endif /* PhysMathObj */