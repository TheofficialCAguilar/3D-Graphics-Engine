/*
@file SceneLoader.cpp
@name Carlos Aguilar
@date 03/30/2026
@brief SceneLoader Class Initialization
*/

#include "SceneLoader.hpp"
#include "Translation.hpp"
#include "Scale.hpp"

#include <fstream>
#include <sstream>

/**
 * @brief Loads a scene from a CSV file and creates transformation objects.
 * @param filename The file containing transformation commands.
 * @return A vector of Transformation pointers.
 */

std::vector<Transformation*> SceneLoader::loadScene(const std::string& filename) {

    std::vector<Transformation*> transformations;

    std::ifstream file(filename);

    if (!file.is_open()) {
        return transformations;
    }

    std::string line;

    while (getline(file, line)) {

        std::stringstream ss(line);
        std::string command;

        getline(ss, command, ',');

        if (command == "TRANSLATE") {

            double x, y, z;
            std::string temp;

            getline(ss, temp, ',');
            x = stod(temp);

            getline(ss, temp, ',');
            y = stod(temp);

            getline(ss, temp, ',');
            z = stod(temp);

            transformations.push_back(new Translation(x,y,z));
        }

        else if (command == "SCALE") {

            double factor;
            std::string temp;

            getline(ss, temp, ',');
            factor = stod(temp);

            transformations.push_back(new Scale(factor));
        }
    }

    return transformations;
}
