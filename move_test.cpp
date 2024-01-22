#include "move_test.h"

mover::mover(PO::Object* moveble, std::vector<char>* vec): vec(vec), moveble(moveble){

}
void mover::startMove() {
	if (not is_vorking) {
		is_vorking = true;
		Mythreed = std::thread(&mover::moverloop, this);
	}
}
void mover::stopMove() {
	if (is_vorking) {
		is_vorking = false;
		Mythreed.join();
	}
}
void mover::moverloop() {
	double speed = 100.;
	while (is_vorking) {
		for (const char el : *vec) {
			if (el == 'W' or el == 'w') moveble->set_new_speed(PMathO::Vec2D(0., -speed));
			else if (el == 'a' or el == 'A') moveble->set_new_speed(PMathO::Vec2D(-speed, 0.));
			else if (el == 's' or el == 'S') moveble->set_new_speed(PMathO::Vec2D(0., speed));
			else if (el == 'd' or el == 'D') moveble->set_new_speed(PMathO::Vec2D(speed, 0.));
		}
		vec->clear();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		
	}
}