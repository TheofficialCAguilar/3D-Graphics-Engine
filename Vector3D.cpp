/*
 * @file Vector3D.cpp
 * @name Carlos Aguilar
 * @brief Merged Vector3D implementation — combines all functionality from Projects 1–5.
 *        P1: calculateMagnitude, normalize, display
 *        P5: operator+, operator*, operator==
 */
 
#include "Vector3D.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
 
 
Vector3D::Vector3D() : x_(0.0), y_(0.0), z_(0.0) {}
 
Vector3D::Vector3D(double x, double y, double z) : x_(x), y_(y), z_(z) {}
 
double Vector3D::getX() const { return x_; }
double Vector3D::getY() const { return y_; }
double Vector3D::getZ() const { return z_; }
  
void Vector3D::setX(double x) { x_ = x; }
void Vector3D::setY(double y) { y_ = y; }
void Vector3D::setZ(double z) { z_ = z; }
 
 
/**
 * @return: The Euclidean magnitude of the vector.
 */

double Vector3D::calculateMagnitude() const
{
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}
 
/**
 * @post: Normalizes the vector in place. No-op if magnitude is 0.
 */
void Vector3D::normalize()
{
    double magnitude = calculateMagnitude();
    if (magnitude > 0.0)
    {
        x_ /= magnitude;
        y_ /= magnitude;
        z_ /= magnitude;
    }
}
 
/**
 * @post: Prints  Vector[x.xx, y.yy, z.zz]  followed by a newline.
 */
void Vector3D::display() const
{
    std::cout << std::fixed << std::setprecision(2)
              << "Vector[" << x_ << ", " << y_ << ", " << z_ << "]\n";
}
  
/**
 * @brief Adds two vectors component-wise.
 */
Vector3D Vector3D::operator+(const Vector3D& other) const
{
    return Vector3D(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}
 
/**
 * @brief Multiplies every component by a scalar.
 */
Vector3D Vector3D::operator*(double scalar) const
{
    return Vector3D(x_ * scalar, y_ * scalar, z_ * scalar);
}
 
/**
 * @brief Returns true if both vectors are equal within an epsilon of 0.001.
 */
bool Vector3D::operator==(const Vector3D& other) const
{
    const double epsilon = 0.001;
    return std::abs(x_ - other.x_) < epsilon &&
           std::abs(y_ - other.y_) < epsilon &&
           std::abs(z_ - other.z_) < epsilon;
}
