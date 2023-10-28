#include "PhysColliderObj.h"
#include <iostream>
#include <cmath>
using namespace PColliderO;
Collider::Collider(){}

const double Collider::get_coverage_radious() const { return coverage_radious; }

const int Collider::get_type() const{
	return 0;
}


RectangleCollider::RectangleCollider(double start_width, double start_height) : Collider(){
	width = start_width;
	height = start_height;
	coverage_radious = sqrt((start_width / 2.) * (start_width / 2.) + (start_height / 2.) * (start_height / 2.));
}


const int RectangleCollider::get_type() const {
	return 1;
}



CricleCollider::CricleCollider(double start_radious) : Collider(){
	radious = start_radious;
	coverage_radious = start_radious;
}

const int CricleCollider::get_type() const {
	return 2;
}



