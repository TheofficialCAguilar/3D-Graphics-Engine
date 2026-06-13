/*
 * @file Mesh.hpp
 * @name Carlos Aguilar
 * @brief Loads a .obj file and uploads it to the GPU as a VAO/VBO.
 *        Supports positions, normals, and UV texture coordinates.
 *        If no .obj is provided, falls back to a built-in cube.
 */

#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <vector>
#include <string>

struct Vertex {
    float x, y, z;       // position
    float nx, ny, nz;    // normal  (for lighting)
    float u, v;          // UV      (for texture)
};

class Mesh {
public:
    /**
     * @brief Constructs a built-in unit cube if no path given,
     *        or loads a .obj file.
     * @param objPath: Path to .obj file, or "" for the default cube.
     */
    Mesh(const std::string& objPath = "");

    ~Mesh();

    /**
     * @brief Draws the mesh using the currently bound shader.
     */
    void draw() const;

private:
    GLuint vao_, vbo_, ebo_;
    GLsizei indexCount_;

    void buildCube();
    bool loadOBJ(const std::string& path);
    void upload(const std::vector<Vertex>& verts,
                const std::vector<unsigned int>& indices);
};

#endif
