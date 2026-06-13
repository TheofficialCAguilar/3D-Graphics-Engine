// Carlos Aguilar

#include "Scale.hpp"

Scale::Scale(double factor) : factor_(factor) {}

Vector3D Scale::apply(const Vector3D& point) const {
    return point * factor_; 
}

std::string Scale::getType() const {
    return "SCALE";
}