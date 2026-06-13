// Carlos Aguilar

#include "Mesh.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

Mesh::Mesh(const std::string& objPath)
    : vao_(0), vbo_(0), ebo_(0), indexCount_(0)
{
    if (objPath.empty() || !loadOBJ(objPath))
        buildCube();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
}

void Mesh::draw() const
{
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, indexCount_, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::buildCube()
{
    std::vector<Vertex> verts = {

        {-1,-1, 1,  0, 0, 1,  0,0},
        { 1,-1, 1,  0, 0, 1,  1,0},
        { 1, 1, 1,  0, 0, 1,  1,1},
        {-1, 1, 1,  0, 0, 1,  0,1},
        { 1,-1,-1,  0, 0,-1,  0,0},
        {-1,-1,-1,  0, 0,-1,  1,0},
        {-1, 1,-1,  0, 0,-1,  1,1},
        { 1, 1,-1,  0, 0,-1,  0,1},
        {-1,-1,-1, -1, 0, 0,  0,0},
        {-1,-1, 1, -1, 0, 0,  1,0},
        {-1, 1, 1, -1, 0, 0,  1,1},
        {-1, 1,-1, -1, 0, 0,  0,1},
        { 1,-1, 1,  1, 0, 0,  0,0},
        { 1,-1,-1,  1, 0, 0,  1,0},
        { 1, 1,-1,  1, 0, 0,  1,1},
        { 1, 1, 1,  1, 0, 0,  0,1},
        {-1, 1, 1,  0, 1, 0,  0,0},
        { 1, 1, 1,  0, 1, 0,  1,0},
        { 1, 1,-1,  0, 1, 0,  1,1},
        {-1, 1,-1,  0, 1, 0,  0,1},
        {-1,-1,-1,  0,-1, 0,  0,0},
        { 1,-1,-1,  0,-1, 0,  1,0},
        { 1,-1, 1,  0,-1, 0,  1,1},
        {-1,-1, 1,  0,-1, 0,  0,1},
    };

    std::vector<unsigned int> idx;
    for (int f = 0; f < 6; f++) {
        unsigned int b = f * 4;
        idx.insert(idx.end(), {b,b+1,b+2, b,b+2,b+3});
    }

    upload(verts, idx);
}

bool Mesh::loadOBJ(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Mesh: could not open " << path << " — using cube\n";
        return false;
    }

    std::vector<float> posData, normData, uvData;
    std::vector<Vertex> verts;
    std::vector<unsigned int> indices;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;
        ss >> token;

        if (token == "v") {
            float x,y,z; ss>>x>>y>>z;
            posData.insert(posData.end(),{x,y,z});
        } else if (token == "vn") {
            float x,y,z; ss>>x>>y>>z;
            normData.insert(normData.end(),{x,y,z});
        } else if (token == "vt") {
            float u,v; ss>>u>>v;
            uvData.insert(uvData.end(),{u,v});
        } else if (token == "f") {
            std::vector<std::string> faceTokens;
            std::string t;
            while (ss >> t) faceTokens.push_back(t);

            auto parseIdx = [](const std::string& tok,
                                int& pi, int& ti, int& ni) {
                pi = ti = ni = 0;
                std::replace(const_cast<char*>(tok.c_str()),
                             const_cast<char*>(tok.c_str()) + tok.size(),
                             '/', ' ');
                std::istringstream s(tok);
                std::string a,b,c;
                s>>a;
                try { pi = std::stoi(a)-1; } catch(...) {}
                if(s>>b && !b.empty()) try { ti = std::stoi(b)-1; } catch(...) {}
                if(s>>c) try { ni = std::stoi(c)-1; } catch(...) {}
            };

            for (int i = 1; i+1 < (int)faceTokens.size(); i++) {
                int pIdx[3], tIdx[3], nIdx[3];
                std::string corners[3] = {faceTokens[0], faceTokens[i], faceTokens[i+1]};
                for (int k = 0; k < 3; k++) {
                    std::string tok = corners[k];
                    for (char& ch : tok) if (ch == '/') ch = ' ';
                    std::istringstream ts(tok);
                    std::string a,b,c;
                    ts>>a; pIdx[k] = a.empty() ? 0 : std::stoi(a)-1;
                    ts>>b; tIdx[k] = b.empty() ? 0 : std::stoi(b)-1;
                    ts>>c; nIdx[k] = c.empty() ? 0 : std::stoi(c)-1;
                }
                for (int k = 0; k < 3; k++) {
                    Vertex vx{};
                    if (pIdx[k]*3+2 < (int)posData.size()) {
                        vx.x=posData[pIdx[k]*3];
                        vx.y=posData[pIdx[k]*3+1];
                        vx.z=posData[pIdx[k]*3+2];
                    }
                    if (!normData.empty() && nIdx[k]*3+2 < (int)normData.size()) {
                        vx.nx=normData[nIdx[k]*3];
                        vx.ny=normData[nIdx[k]*3+1];
                        vx.nz=normData[nIdx[k]*3+2];
                    }
                    if (!uvData.empty() && tIdx[k]*2+1 < (int)uvData.size()) {
                        vx.u=uvData[tIdx[k]*2];
                        vx.v=uvData[tIdx[k]*2+1];
                    }
                    indices.push_back((unsigned int)verts.size());
                    verts.push_back(vx);
                }
            }
        }
    }

    if (verts.empty()) return false;
    upload(verts, indices);
    std::cout << "Mesh: loaded " << path
              << "  (" << verts.size() << " verts)\n";
    return true;
}

void Mesh::upload(const std::vector<Vertex>& verts,
                  const std::vector<unsigned int>& indices)
{
    indexCount_ = (GLsizei)indices.size();

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 verts.size() * sizeof(Vertex),
                 verts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, x));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, nx));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, u));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}
 