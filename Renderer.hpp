// Carlos Aguilar

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Vector3D.hpp"
#include "TransformPipeline.hpp"
#include "SpatialRegistry.hpp"
#include <vector>
#include <string>

struct Color {
    int r, g, b;
    Color(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {}
};

struct Edge {
    int a, b;
    Edge(int a, int b) : a(a), b(b) {}
};

struct Mesh {
    std::vector<Vector3D> vertices;
    std::vector<Edge>     edges;
};

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();

    void clear();
    void drawPixel(int x, int y, Color color);
    void drawLine(int x0, int y0, int x1, int y1, Color color);

    bool projectPoint(const Vector3D& point,
                      double fov, double camZ,
                      int& screenX, int& screenY) const;

    static Mesh makeCube();
    static Mesh transformMesh(const Mesh& mesh, TransformPipeline& pipeline);

    void drawWireframe(const Mesh& mesh, Color color,
                       double fov = 400.0, double camZ = 5.0);

    void drawSpatialPoints(SpatialRegistry& registry,
                           double minMag, double maxMag, Color color);

    bool writePPM(const std::string& filename) const;

private:
    int    width_;
    int    height_;
    Color* pixels_;
};

#endif
 