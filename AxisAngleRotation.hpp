// Carlos Aguilar

#pragma once

#include "Rotation.hpp"
#include "Vector3D.hpp"

class AxisAngleRotation : public Rotation
{
private:
    Vector3D axis_;
    double angle_;

public:

    AxisAngleRotation();

    AxisAngleRotation(const Vector3D& axis, double angle);

    Vector3D getAxis() const;

    double getAngle() const;
};
 