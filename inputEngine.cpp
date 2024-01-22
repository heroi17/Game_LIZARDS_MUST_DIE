#include "inputEngine.h"
inputEngine::inputEngine(std::vector<char>* data) : data(data) {

}
void inputEngine::startEngine() {
	if (not engine_is_working) {
		engine_is_working = true;
		myThread = std::thread(&inputEngine::inputLoop, this);
	}
}

void inputEngine::stopEngine() {
	if (engine_is_working) {
		engine_is_working = false;
		myThread.join();
	}
}
void inputEngine::inputLoop() {
	//just put char into box, thats_all
	while (engine_is_working) {
		this->data->push_back(_getch());
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
bool inputEngine::is_loop() const {
	return engine_is_working;
}
