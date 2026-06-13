// Carlos Aguilar

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vector3D.hpp"
#include <cmath>

enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

class Camera {
public:
    Vector3D position;

    float yaw;   
    float pitch; 

    float moveSpeed;
    float mouseSensitivity;
    float fov;      
    float nearPlane;
    float farPlane;

    Camera(Vector3D startPos = Vector3D(0.0, 0.0, 3.0));

    void processKeyboard(CameraMovement direction, float deltaTime);

    void processMouse(float xOffset, float yOffset);

    void getViewMatrix(float out[16]) const;

    void getProjectionMatrix(float out[16], float aspectRatio) const;

private:
    Vector3D front_;
    Vector3D right_;
    Vector3D up_;

    void updateVectors();

    static float toRad(float deg) { return deg * 3.14159265f / 180.0f; }
    static void  mat4Multiply(const float a[16], const float b[16], float out[16]);
};

#endif
 