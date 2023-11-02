#pragma once
#ifndef PhysMathObj
#define PhysMathObj
namespace PMathO {
	const double PI = 3.1415926535897932384626433832795028841971;

	void solve3(double * ptr, double A, double B, double C, double D);
	void solve2(double * ptr, double A, double B, double C);
	void solve1(double* ptr, double A, double B);
	double croot(double x);
	struct Vec2D {
	private:
		double x;
		double y;
		double radian_angle;
		double lenth;
		void update_lenth();
	public:
		Vec2D(double x, double y);
		double get_x() const;
		double get_y() const;
		double get_lenth() const;
		void add_vec(Vec2D vector);
		Vec2D operator+(const Vec2D& other) const;
		Vec2D operator-(const Vec2D& other) const;
		Vec2D operator*(const double& other) const;
		Vec2D operator/(const double& other) const;
		Vec2D operator*=(const double& other);
		Vec2D operator+=(const Vec2D& other);
		Vec2D operator-=(const Vec2D& other);
		Vec2D operator*=(const Vec2D& other);

	};
	struct Section2D {
	private:
		Vec2D A;
		Vec2D B;
		double x_lenth;
		double y_lenth;
		double lenth;
		void position_update();
	public:
		Section2D(Vec2D A, Vec2D B);
		double get_distance_to_point(Vec2D point);
	};
}
#endif /* PhysMathObj */