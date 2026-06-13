/*
@file SpatialRegistry.cpp
@name Carlos Aguilar
@date 04/27/2026
@brief Implementation of the SpatialRegistry class, which manages a binary search tree
of SpatialNode objects and supports insertion, querying, and traversal of 3D points
based on their magnitude.
*/

#include "SpatialRegistry.hpp"
#include <cmath>
#include <vector>

// Initializes an empty BST
SpatialRegistry::SpatialRegistry() : root_(nullptr) {}

// Frees all dynamically allocated nodes
SpatialRegistry::~SpatialRegistry() {
    clearTree(root_);
}

void SpatialRegistry::clearTree(SpatialNode* node) {
    if (node == nullptr) return;

    clearTree(node->getLeft());
    clearTree(node->getRight());
    delete node;
}

void SpatialRegistry::insert(const Vector3D& point) {
    root_ = insertHelper(root_, point);
}

SpatialNode* SpatialRegistry::insertHelper(SpatialNode* node, const Vector3D& point) {

    if (node == nullptr) {
        return new SpatialNode(point);
    }

    double mag = std::sqrt(
        point.getX() * point.getX() +
        point.getY() * point.getY() +
        point.getZ() * point.getZ()
    );

    if (mag < node->getMagnitude()) {
        node->setLeft(insertHelper(node->getLeft(), point));
    } else {
        node->setRight(insertHelper(node->getRight(), point));
    }

    return node;
}

Vector3D SpatialRegistry::findClosest() const {

    if (root_ == nullptr) {
        return Vector3D(0, 0, 0);
    }

    SpatialNode* current = root_;

    while (current->getLeft() != nullptr) {
        current = current->getLeft();
    }

    return current->getPoint();
}

std::vector<Vector3D> SpatialRegistry::getPointsInFrustum(double min, double max) const {

    std::vector<Vector3D> result;
    frustumHelper(root_, min, max, result);
    return result;
}

void SpatialRegistry::frustumHelper(SpatialNode* node, double min, double max,std::vector<Vector3D>& result) const {

    if (node == nullptr) return;

    double mag = node->getMagnitude();

    if (mag > min) {
        frustumHelper(node->getLeft(), min, max, result);
    }

    if (mag >= min && mag <= max) {
        result.push_back(node->getPoint());
    }

    if (mag < max) {
        frustumHelper(node->getRight(), min, max, result);
    }
}
