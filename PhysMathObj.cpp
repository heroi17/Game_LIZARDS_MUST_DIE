#include <cmath>
#include "PhysMathObj.h"
using namespace PMathO;

double PMathO::croot(double x) {
	if (x < 0)
		return -pow(-x, 1.0 / 3.0);
	return pow(x, 1.0 / 3.0);
}



/// <summary>
/// Solves a polynomial of the 3rd degree.
/// Put solves in double massive, ptr[0] = how many valid solutions. ptr[1-3] - solves.
/// </summary>
/// <param name="ptr">: pointer on solution lst.</param>
/// <param name="A">: The coefficient at the 3rd degree.</param>
/// <param name="B">: The coefficient at the 2rd degree.</param>
/// <param name="C">: The coefficient at the 1rd degree.</param>
/// <param name="D">: The free coefficient.</param>
/// <returns>Void.</returns>
void PMathO::solve3(double* ptr, double A, double B, double C, double D){
	if (A == 0) {
		return solve2(ptr, B, C, D);
	}
	double p = (3.0 * A * C - B * B) / (3.0 * A * A);
	double q = (2.0 * B * B * B - 9.0 * A * B * C + 27.0 * A * A * D) / (27.0 * A * A * A);
	double S = (q * q / 4.0) + (p * p * p / 27.0);
	double F;
	if (q == 0)
		F = PI / 2.0;
	if (q < 0)
		F = atan(-2.0 * sqrt(-S) / q);
	if (q > 0)
		F = atan(-2.0 * sqrt(-S) / q) + PI;
	if (S < 0) {
		ptr[0] = 3;
		ptr[1] = 2.0 * sqrt(-p / 3.0) * cos(F / 3.0) - B / (3.0 * A);
		ptr[2] = 2.0 * sqrt(-p / 3.0) * cos((F / 3.0) + 2.0 * PI / 3.0) - B / (3.0 * A);
		ptr[3] = 2.0 * sqrt(-p / 3.0) * cos((F / 3.0) + 4.0 * PI / 3.0) - B / (3.0 * A);
	}
	if (S == 0) {
		ptr[0] = 2;
		ptr[1] = 2.0 * croot(-q / 2.0) - B / (3.0 * A);
		ptr[2] = -croot(-q / 2.0) - B / (3.0 * A);
	}
	if (S > 0) {
		ptr[0] = 1;
		ptr[1] = croot((-q / 2.0) + sqrt(S)) + croot((-q / 2.0) - sqrt(S)) - B / (3.0 * A);
	}
}

void PMathO::solve2(double* ptr, double A, double B, double C) {
	if (A == 0) {
		return solve1(ptr, A, C);
	}
	double Dis = B * B - 4. * A * C;
	if (Dis < 0.) {
		*ptr = 0.;
	}
	else if (Dis > 0.) {
		*ptr = 2.;
		ptr[1] = (-B - sqrt(Dis)) / (2. * A);
		ptr[2] = (-B + sqrt(Dis)) / (2. * A);
	}
	else {
		*ptr = 1;
		ptr[1] = -B / (2. * A);
	}
}

void PMathO::solve1(double* ptr, double A, double B) {
	if (A == 0. and B == 0.) {
		*ptr = 1.;
		ptr[1] = 0.;
	}
	else if (A==0.){
		*ptr = 0.;
	}
	else if (B == 0.) {
		*ptr = 1.;
		ptr[1] = 0.;
	}
	else {
		*ptr = 1.;
		ptr[1] = -B / A;
	}
}





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

