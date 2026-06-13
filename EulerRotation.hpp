// Carlos Aguilar

#pragma once

#include "Rotation.hpp"

class EulerRotation : public Rotation
{
private:
    double roll_;
    double pitch_;
    double yaw_;

public:

    EulerRotation();

    EulerRotation(double roll, double pitch, double yaw);

    double getRoll() const;

    double getPitch() const;

    double getYaw() const;
};
