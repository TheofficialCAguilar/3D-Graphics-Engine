// Carlos Aguilar
// 02/25/2026

#include "EulerRotation.hpp"

EulerRotation::EulerRotation()
    : Rotation("EULER"), roll_(0.0), pitch_(0.0), yaw_(0.0) {}

EulerRotation::EulerRotation(double roll, double pitch, double yaw)
    : Rotation("EULER"), roll_(roll), pitch_(pitch), yaw_(yaw) {}

double EulerRotation::getRoll() const
{
    return roll_;
}

double EulerRotation::getPitch() const
{
    return pitch_;
}

double EulerRotation::getYaw() const
{
    return yaw_;
}
