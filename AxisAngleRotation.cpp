// Carlos Aguilar

#include "AxisAngleRotation.hpp"

AxisAngleRotation::AxisAngleRotation()
    : Rotation("AXIS_ANGLE"), axis_(0.0, 0.0, 0.0), angle_(0.0) {}

AxisAngleRotation::AxisAngleRotation(const Vector3D& axis, double angle)
    : Rotation("AXIS_ANGLE"), axis_(axis), angle_(angle) {}

Vector3D AxisAngleRotation::getAxis() const
{
    return axis_;
}

double AxisAngleRotation::getAngle() const
{
    return angle_;
}
