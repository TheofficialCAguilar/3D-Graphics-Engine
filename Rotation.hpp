// Carlos Aguilar

#pragma once

#include <string>

class Rotation

{
    
protected:
    std::string type_;  

public:

    Rotation(const std::string& type);

    std::string getType() const;

    virtual ~Rotation();
};

 