//
//  RotationRegistry.cpp
//  Rotation project 3
//
//  Created by Carlos Aguilar on 3/11/26.
//


#include "RotationRegistry.hpp"
#include <vector>

RotationRegistry::RotationRegistry() : ArrayBag<Rotation *>() {}

bool RotationRegistry::addRotation(Rotation* rotation) {
    return add(rotation);
}

int RotationRegistry::countQuaternions() const {
    int count = 0;
    std:: vector<Rotation*> items = toVector();
    for (Rotation* r : items) {
        if (dynamic_cast<QuaternionRotation*>(r) != nullptr) {
            count++;
        }
    }
    
    return count;
}

double RotationRegistry::getAverageMagnitude()const {
    std:: vector<Rotation*> items = toVector();
    
    double totalMagnitude = 0.0;
    int count = 0;
    
    for (Rotation* r : items) {
        AxisAngleRotation* axisAngle = dynamic_cast<AxisAngleRotation*>(r);
        
        if (axisAngle != nullptr) {
            totalMagnitude += axisAngle->getAxis().calculateMagnitude();
            count++;
        }
    }
    
    if (count == 0) 
    {
        return 0.0;
    }
    return totalMagnitude / count;
}
