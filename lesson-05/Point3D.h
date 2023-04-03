#pragma once
#include "Point.h"
class Point3D : public Point {
public:
	Point3D* NewLocation(float* vectors) override;
	std::string Location() override;
	explicit Point3D(float x, float y, float z);
private:
	float x;
	float y;
	float z;
};