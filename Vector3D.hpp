// Carlos Aguilar

#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP
 
#include <iostream>
 
class Vector3D {
public:
 
    Vector3D();

    Vector3D(double x, double y, double z);
 
    double getX() const;
    double getY() const;
    double getZ() const;
 
    void setX(double x);
    void setY(double y);
    void setZ(double z);
  
    double calculateMagnitude() const;

    void normalize();

    void display() const;

    Vector3D operator+(const Vector3D& other) const;
 
    Vector3D operator*(double scalar) const;

    bool operator==(const Vector3D& other) const;
 
private:
    double x_, y_, z_;
};
 
#endif 