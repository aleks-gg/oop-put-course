#pragma once
#include "Point.h"
#include <string>
#include <iostream>

class MassCenter {
public:
	MassCenter(std::string shape, Point *location);
	void PrintLocation();
	void Move(float* v);
private:
	std::string shape;
	Point *location;
};