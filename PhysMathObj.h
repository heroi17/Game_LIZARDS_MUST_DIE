#pragma once
#ifndef PhysMathObj
#define PhysMathObj
namespace PMathO {
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
		Vec2D operator+=(const Vec2D& other);

	};
	struct Line2D {
	private:
		Vec2D A;
		Vec2D B;
		double x_lenth;
		double y_lenth;
		double lenth;
		void position_update();
	public:
		Line2D(Vec2D A, Vec2D B);
	};
}
#endif /* PhysMathObj */