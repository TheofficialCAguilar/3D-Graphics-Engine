// Carlos Aguilar
// 02/25/2026

#include "QuaternionRotation.hpp"

QuaternionRotation::QuaternionRotation()
    : Rotation("QUATERNION"), w_(0.0), x_(0.0), y_(0.0), z_(0.0) {}

QuaternionRotation::QuaternionRotation(double w, double x, double y, double z)
    : Rotation("QUATERNION"), w_(w), x_(x), y_(y), z_(z) {}

double QuaternionRotation::getW() const
{
    return w_;
}

double QuaternionRotation::getX() const
{
    return x_;
}

double QuaternionRotation::getY() const
{
    return y_;
}

double QuaternionRotation::getZ() const
{
    return z_;
}
