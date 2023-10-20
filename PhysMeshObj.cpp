struct mesh {
private:
	double width;
	double height;
public:
	mesh(double width=0., double height=0.): width(width), height(height){}
	double get_width() const { return width; }
	double get_height() const { return height; }
	
};