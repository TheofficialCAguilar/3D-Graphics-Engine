// Carlos Aguilar

#ifndef TRANSLATION_HPP
#define TRANSLATION_HPP

#include "Transformation.hpp"
#include <string>

class Translation : public Transformation {
public:

    Translation(double tx, double ty, double tz);

    Vector3D apply(const Vector3D& point) const override;
    
    std::string getType() const override;

private:
    Vector3D offset_;
};

#endif