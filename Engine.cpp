/*
 * @file Engine.cpp
 * @name Carlos Aguilar
 * @brief Main OpenGL engine entry point.
 *
 *  Features:
 *    - SDL2 window + OpenGL 3.3 context
 *    - Phong lighting (ambient + diffuse + specular)
 *    - Texture support (drop any .bmp next to the exe)
 *    - WASD + mouse look camera
 *    - Spinning cube using TransformPipeline math
 *    - SpatialRegistry point cloud rendered as small cubes
 *
 *  Controls:
 *    W/A/S/D       — move camera
 *    Q / E         — move up / down
 *    Mouse         — look around
 *    T             — toggle texture on/off
 *    ESC           — quit
 */

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

#include "Shader.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

// Your existing engine systems
#include "Vector3D.hpp"
#include "Translation.hpp"
#include "Scale.hpp"
#include "TransformPipeline.hpp"
#include "SpatialRegistry.hpp"

// ── Window settings ───────────────────────────
static const int   WIDTH  = 1280;
static const int   HEIGHT = 720;
static const char* TITLE  = "3D Graphics Engine — Carlos Aguilar";

// ── Simple 4x4 matrix helpers ─────────────────
// (until we wire in a full math lib in Phase 3)

static void mat4Identity(float m[16]) {
    memset(m, 0, 64);
    m[0]=m[5]=m[10]=m[15]=1.0f;
}

// Rotate around Y axis (radians) — used for spinning cube
static void mat4RotateY(float m[16], float angle) {
    mat4Identity(m);
    m[0]  =  std::cos(angle);
    m[2]  =  std::sin(angle);
    m[8]  = -std::sin(angle);
    m[10] =  std::cos(angle);
}

// Scale uniformly
static void mat4Scale(float m[16], float s) {
    mat4Identity(m);
    m[0]=m[5]=m[10]=s;
}

// Translate
static void mat4Translate(float m[16], float x, float y, float z) {
    mat4Identity(m);
    m[12]=x; m[13]=y; m[14]=z;
}

// Multiply two 4x4 column-major matrices
static void mat4Mul(const float a[16], const float b[16], float out[16]) {
    for (int col=0; col<4; col++)
        for (int row=0; row<4; row++) {
            out[col*4+row] = 0;
            for (int k=0; k<4; k++)
                out[col*4+row] += a[k*4+row] * b[col*4+k];
        }
}

// ─────────────────────────────────────────────
// Load a BMP texture (SDL2 built-in, no deps)
// Returns 0 if file not found — engine keeps running
// ─────────────────────────────────────────────
static GLuint loadTextureBMP(const char* path)
{
    SDL_Surface* surf = SDL_LoadBMP(path);
    if (!surf) {
        std::cout << "Texture: " << path << " not found or failed to load\n"
                  << "  SDL error: " << SDL_GetError() << "\n"
                  << "  Running without texture.\n";
        return 0;
    }

    // Always convert to RGBA32 — handles BGR, indexed, and any other format
    SDL_Surface* rgba = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(surf);
    if (!rgba) {
        std::cout << "Texture: format conversion failed: " << SDL_GetError() << "\n";
        return 0;
    }

    // Flip vertically — BMP is stored bottom-up, OpenGL expects top-down
    int w = rgba->w, h = rgba->h;
    int pitch = rgba->pitch;
    std::vector<unsigned char> flipped(pitch * h);
    unsigned char* src = (unsigned char*)rgba->pixels;
    for (int row = 0; row < h; row++)
        memcpy(&flipped[row * pitch], src + (h - 1 - row) * pitch, pitch);

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 w, h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, flipped.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(rgba);
    std::cout << "Texture: loaded " << path << "  (" << w << "x" << h << ")\n";
    return tex;
}

// ─────────────────────────────────────────────
int main(int argc, char* argv[])
{
    // ── SDL2 init ─────────────────────────────
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    // Request OpenGL 3.3 Core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window* window = SDL_CreateWindow(
        TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_GLContext glCtx = SDL_GL_CreateContext(window);
    if (!glCtx) {
        std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_GL_SetSwapInterval(1);  // vsync

    // ── GLEW init ─────────────────────────────
    glewExperimental = GL_TRUE;
    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK) {
        std::cerr << "GLEW init failed: " << glewGetErrorString(glewErr) << "\n";
        return 1;
    }

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << "\n";
    std::cout << "GPU:    " << glGetString(GL_RENDERER) << "\n\n";

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, WIDTH, HEIGHT);

    // ── Shader ────────────────────────────────
    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    if (shader.ID == 0) {
        std::cerr << "Failed to load shaders. Make sure shaders/ folder is next to the exe.\n";
        return 1;
    }

    // ── Mesh ──────────────────────────────────
    // Pass a .obj path as command-line argument to load your own mesh:
    //   ./engine mymodel.obj
    // Otherwise falls back to the built-in cube
    std::string objPath = (argc > 1) ? argv[1] : "";
    Mesh mainMesh(objPath);

    // Small cube reused for point cloud dots
    Mesh dotMesh;

    // ── Texture ───────────────────────────────
    GLuint texture = loadTextureBMP("texture.bmp");
    bool useTexture = (texture != 0);

    // ── Camera ────────────────────────────────
    Camera camera(Vector3D(0.0, 0.0, 5.0));
    SDL_SetRelativeMouseMode(SDL_TRUE);   // capture mouse

    // ── SpatialRegistry point cloud ───────────
    // Uses your P6 BST to store scene points,
    // then queries them each frame for frustum culling
    SpatialRegistry pointCloud;
    for (int i = -2; i <= 2; i++)
        for (int j = -2; j <= 2; j++)
            if (!(i==0 && j==0))   // skip center (main cube is there)
                pointCloud.insert(Vector3D(i * 2.5, 0.0, j * 2.5));

    // Light position (orbits around the scene)
    Vector3D lightPos(3.0, 3.0, 3.0);

    // ── State ─────────────────────────────────
    bool    running    = true;
    float   angle      = 0.0f;      // cube rotation
    float   lightAngle = 0.0f;      // light orbit angle
    Uint32  lastTime   = SDL_GetTicks();

    std::cout << "Controls: WASD=move  Q/E=up/down  Mouse=look  T=texture  ESC=quit\n\n";

    // ═════════════════════════════════════════
    // MAIN LOOP
    // ═════════════════════════════════════════
    while (running)
    {
        // ── Delta time ────────────────────────
        Uint32 now = SDL_GetTicks();
        float  dt  = (now - lastTime) / 1000.0f;
        lastTime   = now;

        // ── Events ────────────────────────────
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE: running = false; break;
                    case SDLK_t:      useTexture = !useTexture; break;
                    default: break;
                }
            }

            if (e.type == SDL_MOUSEMOTION) {
                camera.processMouse((float)e.motion.xrel,
                                    (float)e.motion.yrel);
            }
        }

        // ── Keyboard movement (held) ──────────
        const Uint8* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_W]) camera.processKeyboard(FORWARD,  dt);
        if (keys[SDL_SCANCODE_S]) camera.processKeyboard(BACKWARD, dt);
        if (keys[SDL_SCANCODE_A]) camera.processKeyboard(LEFT,     dt);
        if (keys[SDL_SCANCODE_D]) camera.processKeyboard(RIGHT,    dt);
        if (keys[SDL_SCANCODE_Q]) camera.processKeyboard(UP,       dt);
        if (keys[SDL_SCANCODE_E]) camera.processKeyboard(DOWN,     dt);

        // ── Update ────────────────────────────
        angle      += 0.5f * dt;   // cube spins
        lightAngle += 0.8f * dt;   // light orbits

        // Orbit light using your Vector3D trig
        float lx = 4.0f * std::cos(lightAngle);
        float lz = 4.0f * std::sin(lightAngle);
        lightPos = Vector3D(lx, 3.0, lz);

        // ── Render ────────────────────────────
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // Camera matrices
        float view[16], proj[16];
        camera.getViewMatrix(view);
        camera.getProjectionMatrix(proj, (float)WIDTH / HEIGHT);
        shader.setMat4("view", view);
        shader.setMat4("projection", proj);

        // Lighting uniforms
        shader.setVec3("lightPos",
                       (float)lightPos.getX(),
                       (float)lightPos.getY(),
                       (float)lightPos.getZ());
        shader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
        shader.setVec3("viewPos",
                       (float)camera.position.getX(),
                       (float)camera.position.getY(),
                       (float)camera.position.getZ());

        // ── Draw main cube (spins) ────────────
        {
            // Build model = Scale(1.5) * RotateY(angle)
            float mRot[16], mScale[16], mModel[16];
            mat4RotateY(mRot, angle);
            mat4Scale(mScale, 1.5f);
            mat4Mul(mScale, mRot, mModel);  // result goes into mModel, not an input

            shader.setMat4("model", mModel);
            shader.setVec3("baseColor", 0.2f, 0.6f, 1.0f);  // cyan-blue

            // Apply texture if loaded and T is toggled on
            bool applyTex = useTexture && texture != 0;
            shader.setBool("useTexture", applyTex);
            if (applyTex) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture);
                shader.setInt("texture0", 0);
            }
            mainMesh.draw();
        }

        // ── Draw point cloud (SpatialRegistry) ──
        // Query all points and draw a tiny cube at each
        {
            shader.setBool("useTexture", false);
            std::vector<Vector3D> pts = pointCloud.getPointsInFrustum(0.0, 100.0);
            for (const Vector3D& p : pts) {
                float mT[16], mS[16], mM[16];
                mat4Translate(mT, (float)p.getX(), (float)p.getY(), (float)p.getZ());
                mat4Scale(mS, 0.15f);
                mat4Mul(mT, mS, mM);
                shader.setMat4("model", mM);
                shader.setVec3("baseColor", 1.0f, 0.8f, 0.1f);  // gold dots
                dotMesh.draw();
            }
        }

        // ── Draw light indicator (tiny white cube) ──
        {
            shader.setBool("useTexture", false);
            float mT[16], mS[16], mM[16];
            mat4Translate(mT,
                          (float)lightPos.getX(),
                          (float)lightPos.getY(),
                          (float)lightPos.getZ());
            mat4Scale(mS, 0.1f);
            mat4Mul(mT, mS, mM);
            shader.setMat4("model", mM);
            shader.setVec3("baseColor", 1.0f, 1.0f, 1.0f);  // white
            dotMesh.draw();
        }

        SDL_GL_SwapWindow(window);   // present frame
    }

    // ── Cleanup ───────────────────────────────
    if (texture) glDeleteTextures(1, &texture);
    SDL_GL_DeleteContext(glCtx);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}