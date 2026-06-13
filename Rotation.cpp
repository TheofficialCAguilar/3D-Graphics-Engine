// Carlos Aguilar

#include "Rotation.hpp"

Rotation::Rotation(const std::string& type)
    : type_(type) {}

std::string Rotation::getType() const
{
    return type_;
}

Rotation::~Rotation() {}


