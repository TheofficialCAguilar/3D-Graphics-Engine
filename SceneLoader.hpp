/*
@file SceneLoader.hpp
@name Carlos Aguilar
@date 03/30/2026
@brief SceneLoader Class Declaration
*/

#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <vector>
#include <string>
#include "Transformation.hpp"

/**
 * @class SceneLoader
 * @brief Loads transformation commands from a CSV file.
 *
 * Reads a file and dynamically creates Transformation objects
 * (Translation or Scale) based on the commands in the file.
 */

class SceneLoader { // class declaration
public:
    
    /**
    * @param filename The path to the CSV file containing transformation commands.
    * @return A vector of pointers to dynamically allocated Transformation objects.
    * @post Reads the file and creates the appropriate transformations.
    * Returns an empty vector if the file cannot be opened.
    */
    
    static std::vector<Transformation*> loadScene(const std::string& filename);
};

#endif
