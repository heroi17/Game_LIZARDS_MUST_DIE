#pragma once
#include <iostream>
#include <vector>
#include "Physics.h"
#include <thread>
class mover {
private:
	PO::Object* moveble;
	std::vector<char>* vec;
	std::thread Mythreed;
	bool is_vorking = false;
public:
	mover(PO::Object* moveble, std::vector<char>* vec);
	void startMove();
	void stopMove();
	void moverloop();
};