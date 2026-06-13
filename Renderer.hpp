/*
 * @file Renderer.hpp
 * @name Carlos Aguilar
 * @brief A software PPM renderer. Projects 3D points onto a 2D canvas
 *        and writes the result to a .ppm image file (open with Mac Preview).
 *
 *        Uses your existing Vector3D, TransformPipeline, and SpatialRegistry.
 *
 *        Phase 1 of the visual engine — no external dependencies.
 *        Future phases will replace this with OpenGL + SDL2.
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Vector3D.hpp"
#include "TransformPipeline.hpp"
#include "SpatialRegistry.hpp"
#include <vector>
#include <string>

// ── Simple RGB pixel ──────────────────────────────────────
struct Color {
    int r, g, b;
    Color(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {}
};

// ── A 3D edge: two vertex indices into a vertex list ──────
struct Edge {
    int a, b;
    Edge(int a, int b) : a(a), b(b) {}
};

// ── A 3D mesh: vertices + edges for wireframe drawing ─────
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
