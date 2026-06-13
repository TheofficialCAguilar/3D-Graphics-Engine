// Carlos Aguilar

#ifndef SpatialRegistry_hpp
#define SpatialRegistry_hpp

#include "SpatialNode.hpp"
#include <vector>

class SpatialRegistry {
private:
    SpatialNode* root_;

    SpatialNode* insertHelper(SpatialNode* node, const Vector3D& point);

    void clearTree(SpatialNode* node);

    void frustumHelper(SpatialNode* node,
                       double min,
                       double max,
                       std::vector<Vector3D>& result) const;
    
public:

    SpatialRegistry();

    ~SpatialRegistry();

    void insert(const Vector3D& point);

    Vector3D findClosest() const;

    std::vector<Vector3D> getPointsInFrustum(double min, double max) const;
};

#endif
