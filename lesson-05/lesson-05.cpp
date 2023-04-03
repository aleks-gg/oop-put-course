// lesson-05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include "Point2D.h"
#include "Point3D.h"
#include "MassCenter.h"

using namespace std;

Point2D::Point2D(float x, float y) {
    this->x = x;
    this->y = y;
}

string Point2D::Location() {
    stringstream stream;
    stream << "X: " << fixed << setprecision(2) << x << " Y: " << fixed << setprecision(2) << y << "\n";
    string str = stream.str();
    return str;
}
Point2D* Point2D::NewLocation(float *vectors) {
    Point2D* p = new Point2D(x + vectors[0], y + vectors[1]);
    return p;
}

Point3D::Point3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

string Point3D::Location() {
    stringstream stream;
    stream << "X: " << fixed << setprecision(2) << x << " Y: " << fixed << setprecision(2) << y << " Z: " << fixed << setprecision(2) << z << "\n";
    string str = stream.str();
    return str;
}
Point3D* Point3D::NewLocation(float* vectors) {
    Point3D* p = new Point3D(x + vectors[0], y + vectors[1], z + vectors[2]);
    return p;
}

MassCenter::MassCenter(string shape, Point* location) {
    this->shape = shape;
    this->location = location;
};

void MassCenter::PrintLocation() {
    cout << "I am the center mass of a " << this->shape << " and I am located at " << this->location->Location() << "\n";
}

void MassCenter::Move(float* v) {
    this->location = this->location->NewLocation(v);
}

int main()
{
    Point *p1 = new Point2D(10.0f, 87.0f);
    MassCenter *c1 = new MassCenter("Square", p1);

    c1->PrintLocation();

    float v1[2] {7.2, 4.5};
    c1->Move(v1);

    c1->PrintLocation();

    Point* p2 = new Point3D(2.0f, 212.0f, 64.0f);
    MassCenter* c2 = new MassCenter("Sphere", p2);

    c2->PrintLocation();

    float v2[3]{ 4.1, 4.0, 555.1 };
    c2->Move(v2);

    c2->PrintLocation();
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
