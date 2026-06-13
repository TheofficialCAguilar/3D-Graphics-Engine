/*
 * @file Camera.hpp
 * @name Carlos Aguilar
 * @brief First-person camera with WASD movement and mouse look.
 *        Builds view and projection matrices for OpenGL.
 *        Uses Vector3D internally for position and direction.
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vector3D.hpp"
#include <cmath>

// Movement directions passed from SDL key events
enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

class Camera {
public:
    // World position
    Vector3D position;

    // Euler angles (degrees)
    float yaw;    // left/right — starts facing -Z
    float pitch;  // up/down

    // Settings
    float moveSpeed;
    float mouseSensitivity;
    float fov;      // degrees
    float nearPlane;
    float farPlane;

    /**
     * @param startPos: Initial camera position in world space.
     */
    Camera(Vector3D startPos = Vector3D(0.0, 0.0, 3.0));

    /**
     * @brief Moves the camera in the given direction by deltaTime * moveSpeed.
     */
    void processKeyboard(CameraMovement direction, float deltaTime);

    /**
     * @brief Rotates the camera based on mouse delta.
     * @param xOffset: Mouse delta X (pixels).
     * @param yOffset: Mouse delta Y (pixels).
     */
    void processMouse(float xOffset, float yOffset);

    /**
     * @brief Writes a 4x4 view matrix (column-major, OpenGL convention) into out[16].
     */
    void getViewMatrix(float out[16]) const;

    /**
     * @brief Writes a 4x4 perspective projection matrix into out[16].
     * @param aspectRatio: width / height of the viewport.
     */
    void getProjectionMatrix(float out[16], float aspectRatio) const;

private:
    // Derived direction vectors — updated by updateVectors()
    Vector3D front_;
    Vector3D right_;
    Vector3D up_;

    void updateVectors();

    // Math helpers
    static float toRad(float deg) { return deg * 3.14159265f / 180.0f; }
    static void  mat4Multiply(const float a[16], const float b[16], float out[16]);
};

#endif
