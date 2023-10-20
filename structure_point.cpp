#include <cmath>
struct Point2D
{
private:
	double x = 0.;
	double y = 0.;
public:
	Point2D(double x=0., double y=0.): x(x), y(y) {
	}
	double float_get_x() const { return x; }
	double float_get_y() const { return y; }
	Point2D operator+(const Point2D & other) const {
		return Point2D(this->x + other.x, this->y + other.y);
	}
	Point2D operator-(const Point2D& other) const {
		return Point2D(this->x - other.x, this->y - other.y);
	}
};
struct Vec2D
{
private:
	double x;
	double y;
	double radian_angle;
	double lenth;
public:
	Vec2D(double x, double y) : x(x), y(y) {
		radian_angle = 5.;
		lenth = sqrt(x * x + y * y);
	}

	double get_x() { return x; }
	double get_y() { return y; }
	double get_lenth() { return lenth; }
	void add_vec(Vec2D vector) {
		this->x += vector.x;
		this->y += vector.y;
		lenth = sqrt(x * x + y * y);
	}
};

struct Line2D
{
private:
	Point2D A;
	Point2D B;
	double lenth;
public:
	Line2D(Point2D A, Point2D B) : A(A), B(B) {
	}
};