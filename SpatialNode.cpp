// Carlos Aguilar

#include "SpatialNode.hpp"
#include <cmath>

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


