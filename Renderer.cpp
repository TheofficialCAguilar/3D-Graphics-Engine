// Carlos Aguilar

#include "Renderer.hpp"
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iostream>


Renderer::Renderer(int width, int height)
    : width_(width), height_(height)
{
    pixels_ = new Color[width_ * height_];
    clear();
}

Renderer::~Renderer()
{
    delete[] pixels_;
}


void Renderer::clear()
{
    for (int i = 0; i < width_ * height_; i++)
        pixels_[i] = Color(15, 15, 25);  
}

void Renderer::drawPixel(int x, int y, Color color)
{
    if (x < 0 || x >= width_ || y < 0 || y >= height_) return;
    pixels_[y * width_ + x] = color;
}


void Renderer::drawLine(int x0, int y0, int x1, int y1, Color color)
{
    int dx =  std::abs(x1 - x0);
    int dy = -std::abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (true) {
        drawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

bool Renderer::projectPoint(const Vector3D& point,
                             double fov, double camZ,
                             int& screenX, int& screenY) const
{
    double z = point.getZ() + camZ;
    if (z <= 0.0) return false;  

    double px = (point.getX() / z) * fov + width_  / 2.0;
    double py = (point.getY() / z) * fov + height_ / 2.0;

    screenX = static_cast<int>(px);
    screenY = static_cast<int>(py);
    return true;
}


Mesh Renderer::makeCube()
{
    Mesh m;
    m.vertices = {
        Vector3D(-1, -1, -1),  
        Vector3D( 1, -1, -1),  
        Vector3D( 1,  1, -1),  
        Vector3D(-1,  1, -1),  
        Vector3D(-1, -1,  1),  
        Vector3D( 1, -1,  1),  
        Vector3D( 1,  1,  1),  
        Vector3D(-1,  1,  1),  
    };
    m.edges = {
        {0,1},{1,2},{2,3},{3,0},
        {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}
    };
    return m;
}


Mesh Renderer::transformMesh(const Mesh& mesh, TransformPipeline& pipeline)
{
    Mesh result;
    result.edges = mesh.edges;   
    for (const Vector3D& v : mesh.vertices) {
        Vector3D transformed = v;
        pipeline.runFullPipeline(transformed);
        result.vertices.push_back(transformed);
    }
    return result;
}

void Renderer::drawWireframe(const Mesh& mesh, Color color,
                              double fov, double camZ)
{
    for (const Edge& e : mesh.edges) {
        const Vector3D& va = mesh.vertices[e.a];
        const Vector3D& vb = mesh.vertices[e.b];

        int ax, ay, bx, by;
        bool okA = projectPoint(va, fov, camZ, ax, ay);
        bool okB = projectPoint(vb, fov, camZ, bx, by);

        if (okA && okB)
            drawLine(ax, ay, bx, by, color);
    }
}

void Renderer::drawSpatialPoints(SpatialRegistry& registry,
                                  double minMag, double maxMag, Color color)
{
    std::vector<Vector3D> points = registry.getPointsInFrustum(minMag, maxMag);
    for (const Vector3D& p : points) {
        int sx, sy;
        if (projectPoint(p, 400.0, 5.0, sx, sy)) {
            drawLine(sx - 3, sy,     sx + 3, sy,     color);
            drawLine(sx,     sy - 3, sx,     sy + 3, color);
        }
    }
}

bool Renderer::writePPM(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Renderer: could not open " << filename << "\n";
        return false;
    }

    file << "P3\n" << width_ << " " << height_ << "\n255\n";

    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            const Color& c = pixels_[y * width_ + x];
            // clamp to [0, 255]
            file << std::max(0, std::min(255, c.r)) << " "
                 << std::max(0, std::min(255, c.g)) << " "
                 << std::max(0, std::min(255, c.b)) << "  ";
        }
        file << "\n";
    }

    file.close();
    std::cout << "Renderer: wrote " << filename
              << "  (" << width_ << "x" << height_ << ")\n";
    return true;
}
