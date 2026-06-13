
/*
 * @file Vector3D.hpp
 * @name Carlos Aguilar
 * @brief Merged Vector3D — combines all functionality from Projects 1–5.
 *        P1: calculateMagnitude, normalize, display
 *        P5: operator+, operator*, operator==
 */
 
#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP
 
#include <iostream>
 
class Vector3D {
public:
    /**
     * @post: Initializes x_, y_, and z_ to 0.0.
     */
    Vector3D();
 
    /**
     * @param x: The value to set for x_ component.
     * @param y: The value to set for y_ component.
     * @param z: The value to set for z_ component.
     * @post: Initializes x_, y_, and z_ to the provided values.
     */
    Vector3D(double x, double y, double z);
 
    double getX() const;
    double getY() const;
    double getZ() const;
 
    void setX(double x);
    void setY(double y);
    void setZ(double z);
  
    /**
     * @return: The Euclidean magnitude: sqrt(x^2 + y^2 + z^2).
     */
    double calculateMagnitude() const;
 
    /**
     * @post: Divides each component by the magnitude to produce a unit vector.
     *        Does nothing if magnitude is 0.
     */
    void normalize();
 
    /**
     * @post: Prints the vector as  Vector[x.xx, y.yy, z.zz]  with a newline.
     */
    void display() const;
  
    /**
     * @brief Adds two vectors component-wise.
     * @param other The vector to add.
     * @return A new Vector3D representing the sum.
     */
    Vector3D operator+(const Vector3D& other) const;
 
    /**
     * @brief Multiplies every component by a scalar.
     * @param scalar The factor to scale by.
     * @return A new Vector3D representing the scaled vector.
     */
    Vector3D operator*(double scalar) const;
 
    /**
     * @brief Equality check with a small epsilon tolerance (0.001).
     */
    bool operator==(const Vector3D& other) const;
 
private:
    double x_, y_, z_;
};
 
#endif