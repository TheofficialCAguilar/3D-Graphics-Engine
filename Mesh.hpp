// Carlos Aguilar

#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <vector>
#include <string>

struct Vertex {
    float x, y, z;       
    float nx, ny, nz;    
    float u, v;          
};

class Mesh {
public:
 
    Mesh(const std::string& objPath = "");

    ~Mesh();

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
