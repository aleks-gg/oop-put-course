#pragma once
#include <string>
class Point {
public:
	Point() {};
	virtual ~Point() {};
	virtual Point* NewLocation(float* vectors) = 0;
	virtual std::string Location() = 0;
};