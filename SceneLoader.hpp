// Carlos Aguilar

#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <vector>
#include <string>
#include "Transformation.hpp"

class SceneLoader { 
public:
    
    static std::vector<Transformation*> loadScene(const std::string& filename);
};

#endif
