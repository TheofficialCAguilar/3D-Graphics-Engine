// Carlos Aguilar
// 02/25/2026

#pragma once

#include <string>

class Rotation

{
    
protected:
    std::string type_;  // The rotation type ("EULER", "AXIS_ANGLE", or "QUATERNION")

public:

    /**
     * @param type: The rotation type
     * @post: Initializes type_ to the provided value
     */
    Rotation(const std::string& type);

    /**
     * @return: The value of type_
     * @note: This function should be marked const!
     */
    std::string getType() const;

    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~Rotation();
};

