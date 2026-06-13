/*
@file SpatialRegistry.hpp
@name Carlos Aguilar
@date 04/27/2026
@brief Declaration of the SpatialRegistry class, which manages a binary search tree (BST)
of SpatialNode objects and provides operations for insertion, searching, and range queries
based on 3D point magnitudes.
*/

#ifndef SpatialRegistry_hpp
#define SpatialRegistry_hpp

#include "SpatialNode.hpp"
#include <vector>

/**
 * @class SpatialRegistry
 * @brief Manages a Binary Search Tree (BST) of SpatialNode objects.
 */
class SpatialRegistry {
private:
    SpatialNode* root_;

    /**
     * @brief Recursive helper for inserting nodes into the BST.
     */
    SpatialNode* insertHelper(SpatialNode* node, const Vector3D& point);

    /**
     * @brief Recursively deletes all nodes in the BST.
     */
    void clearTree(SpatialNode* node);

    /**
     * @brief Helper for range query (frustum search).
     */
    void frustumHelper(SpatialNode* node,
                       double min,
                       double max,
                       std::vector<Vector3D>& result) const;
    
public:
    /**
     * @post Initializes an empty BST.
     */
    SpatialRegistry();

    /**
     * @post Deletes all nodes and frees memory.
     */
    ~SpatialRegistry();

    /**
     * @param point Insert a point into the BST.
     */
    void insert(const Vector3D& point);

    /**
     * @return The point with the smallest magnitude.
     */
    Vector3D findClosest() const;

    /**
     * @param min Minimum magnitude (inclusive)
     * @param max Maximum magnitude (inclusive)
     * @return All points in range sorted by magnitude
     */
    std::vector<Vector3D> getPointsInFrustum(double min, double max) const;
};

#endif
