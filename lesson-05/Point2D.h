#pragma once
#include "Point.h"
class Point2D : public Point {
public:
	Point2D* NewLocation(float *vectors) override;
	std::string Location() override;
	explicit Point2D(float x, float y);
private:
	float x;
	float y;
};