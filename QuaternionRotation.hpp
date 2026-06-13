// Carlos Aguilar

#pragma once

#include "Rotation.hpp"

class QuaternionRotation : public Rotation
{
private:
    double w_;
    double x_;
    double y_;
    double z_;

public:

    QuaternionRotation();

    QuaternionRotation(double w, double x, double y, double z);

    double getW() const;

    double getX() const;

    double getY() const;

    double getZ() const;
};
