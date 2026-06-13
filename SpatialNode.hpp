/*
@file SpatialNode.hpp
@name Carlos Aguilar
@date 04/27/2026
@brief Declaration of the SpatialNode class, which represents a node in a binary search tree
storing a 3D point, its precomputed magnitude, and pointers to left and right children.
*/

#ifndef SpatialNode_hpp
#define SpatialNode_hpp

#include "Vector3D.hpp"

/**
 * @class SpatialNode
 * @brief Node used in a BST storing 3D points ordered by magnitude.
 */

class SpatialNode {
private:
    Vector3D point_;
    double magnitude_;
    SpatialNode* left_;
    SpatialNode* right_;

public:
    /**
     * @param pt The 3D point to store in this node.
     * @post Initializes point, computes magnitude, sets children to nullptr.
     */
    SpatialNode(const Vector3D& pt);

    /**
     * @return The stored 3D point.
     */
    Vector3D getPoint() const;

    /**
     * @return The precomputed magnitude of the point.
     */
    double getMagnitude() const;

    /**
     * @return Pointer to left child.
     */
    SpatialNode* getLeft() const;

    /**
     * @return Pointer to right child.
     */
    SpatialNode* getRight() const;

    /**
     * @param left Pointer to new left child.
     * @post Updates left child pointer.
     */
    void setLeft(SpatialNode* left);

    /**
     * @param right Pointer to new right child.
     * @post Updates right child pointer.
     */
    void setRight(SpatialNode* right);
};

#endif
