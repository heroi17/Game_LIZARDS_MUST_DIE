#pragma once
#include <thread>
#include <vector>
#include <conio.h>
#include <future>
#include <iostream>
using namespace std;
class inputEngine {
private:
	vector<char>* data;
	std::thread myThread;
	bool engine_is_working = false;
public:
	inputEngine(std::vector<char>* data);
	void startEngine();
	void stopEngine();
	void inputLoop();
	bool is_loop() const;
};