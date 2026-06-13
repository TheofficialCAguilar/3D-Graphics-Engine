//
//  RotationRegistry.hpp
//  Rotation project 3
//
//  Created by Carlos Aguilar on 3/11/26.
//

#pragma once

#include "ArrayBag.hpp"
#include "Rotation.hpp"
#include "QuaternionRotation.hpp"
#include "AxisAngleRotation.hpp"

class RotationRegistry : public ArrayBag<Rotation*>
{
public:
    
    /**
       * @post: Initializes the RotationRegistry as an empty ArrayBag of Rotation pointers.
       */
       RotationRegistry();

       /**
       * @param rotation: A pointer to a Rotation object.
       * @return: True if the rotation was successfully added, false otherwise.
       * @post: Adds a rotation to the registry.
       */
       bool addRotation(Rotation* rotation);

       /**
       * @return: The count of QuaternionRotation objects in the registry.
       */
       int countQuaternions() const;

       /**
       * @return: The average magnitude of the axes in all AxisAngleRotation objects in the registry.
       * Returns 0.0 if no AxisAngleRotations exist.
       */
       double getAverageMagnitude() const;
   };
    

