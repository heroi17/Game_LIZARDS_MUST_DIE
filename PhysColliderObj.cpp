#include "PhysColliderObj.h"
#include <iostream>
#include <cmath>
using namespace PColliderO;
Collider::Collider(){}

const double Collider::get_coverage_radious() const { return coverage_radious; }

void Collider::test() {
	std::cout << "collider" << std::endl;
}


RectangleCollider::RectangleCollider(double start_width, double start_height) : Collider(), width(start_width), height(start_height){
	coverage_radious = sqrt((start_width / 2.) * (start_width / 2.) + (start_height / 2.) * (start_height / 2.));
}


void RectangleCollider::test(){
	std::cout << "I'am rect" << std::endl;
}



CricleCollider::CricleCollider(double start_radious) : Collider(), radious(start_radious){
	coverage_radious = start_radious;
}

void CricleCollider::test(){
	std::cout << "I'am cricle" << std::endl;
}



