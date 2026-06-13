/*
@file SpatialNode.cpp
@name Carlos Aguilar
@date 04/27/2026
@brief Implementation of the SpatialNode class, which represents a node in a binary search tree
storing a 3D point and its precomputed magnitude, along with pointers to left and right children.
*/

#include "SpatialNode.hpp"
#include <cmath>

// Initializes point, children, and computes magnitude
SpatialNode::SpatialNode(const Vector3D& pt)
: point_(pt), left_(nullptr), right_(nullptr) {
    
    magnitude_ = std::sqrt(
    pt.getX() * pt.getX() +
    pt.getY() * pt.getY() +
    pt.getZ() * pt.getZ()
    );
    
}

Vector3D SpatialNode::getPoint() const {
    return point_;
}

double SpatialNode::getMagnitude() const {
    return magnitude_;
}

SpatialNode* SpatialNode::getLeft()const {
    return left_;
}

SpatialNode* SpatialNode::getRight()const{
    return right_;
}

void SpatialNode::setLeft(SpatialNode* left) {
    left_ = left;
}

void SpatialNode::setRight(SpatialNode* right) {
    right_ = right;
}


