// Carlos Aguilar

#pragma once

#include "ArrayBag.hpp"
#include "Rotation.hpp"
#include "QuaternionRotation.hpp"
#include "AxisAngleRotation.hpp"

class RotationRegistry : public ArrayBag<Rotation*>
{
public:
    
       RotationRegistry();

       bool addRotation(Rotation* rotation);

       int countQuaternions() const;

       double getAverageMagnitude() const;
   };
    

 