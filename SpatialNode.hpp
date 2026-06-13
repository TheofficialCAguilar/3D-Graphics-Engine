// Carlos Aguilar

#ifndef SpatialNode_hpp
#define SpatialNode_hpp

#include "Vector3D.hpp"


class SpatialNode {
private:
    Vector3D point_;
    double magnitude_;
    SpatialNode* left_;
    SpatialNode* right_;

public:

    SpatialNode(const Vector3D& pt);

    Vector3D getPoint() const;

    double getMagnitude() const;

    SpatialNode* getLeft() const;

    SpatialNode* getRight() const;

    void setLeft(SpatialNode* left);


    void setRight(SpatialNode* right);
};

#endif
