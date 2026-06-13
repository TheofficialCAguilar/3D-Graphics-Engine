/*
 * @file Camera.cpp
 * @name Carlos Aguilar
 */

#include "Camera.hpp"
#include <cstring>
#include <cmath>

Camera::Camera(Vector3D startPos)
    : position(startPos),
      yaw(-90.0f), pitch(0.0f),
      moveSpeed(2.5f), mouseSensitivity(0.1f),
      fov(45.0f), nearPlane(0.1f), farPlane(100.0f),
      front_(Vector3D(0,0,-1)), right_(Vector3D(1,0,0)), up_(Vector3D(0,1,0))
{
    updateVectors();
}

void Camera::processKeyboard(CameraMovement dir, float dt)
{
    float v = moveSpeed * dt;
    if (dir == FORWARD)  position = position + front_ * v;
    if (dir == BACKWARD) position = position + front_ * (-v);
    if (dir == LEFT)     position = position + right_ * (-v);
    if (dir == RIGHT)    position = position + right_ * v;
    if (dir == UP)       position = position + up_ * v;
    if (dir == DOWN)     position = position + up_ * (-v);
}

void Camera::processMouse(float xOff, float yOff)
{
    yaw   += xOff * mouseSensitivity;
    pitch -= yOff * mouseSensitivity;
    if (pitch >  89.0f) pitch =  89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    updateVectors();
}

void Camera::updateVectors()
{
    float r   = toRad(yaw);
    float p   = toRad(pitch);
    float fx  = std::cos(r) * std::cos(p);
    float fy  = std::sin(p);
    float fz  = std::sin(r) * std::cos(p);
    front_ = Vector3D(fx, fy, fz);
    front_.normalize();

    // right = front x worldUp
    Vector3D worldUp(0, 1, 0);
    float rx = front_.getY() * worldUp.getZ() - front_.getZ() * worldUp.getY();
    float ry = front_.getZ() * worldUp.getX() - front_.getX() * worldUp.getZ();
    float rz = front_.getX() * worldUp.getY() - front_.getY() * worldUp.getX();
    right_ = Vector3D(rx, ry, rz);
    right_.normalize();

    // up = right x front
    float ux = right_.getY() * front_.getZ() - right_.getZ() * front_.getY();
    float uy = right_.getZ() * front_.getX() - right_.getX() * front_.getZ();
    float uz = right_.getX() * front_.getY() - right_.getY() * front_.getX();
    up_ = Vector3D(ux, uy, uz);
    up_.normalize();
}

// ── View matrix (lookAt) ──────────────────────────────────
void Camera::getViewMatrix(float out[16]) const
{
    // eye = position,  center = position + front,  up = up_
    float ex = (float)position.getX(), ey = (float)position.getY(), ez = (float)position.getZ();
    float fx = (float)front_.getX(),   fy = (float)front_.getY(),   fz = (float)front_.getZ();
    float rx = (float)right_.getX(),   ry = (float)right_.getY(),   rz = (float)right_.getZ();
    float ux = (float)up_.getX(),      uy = (float)up_.getY(),      uz = (float)up_.getZ();

    // column-major
    out[ 0]=rx; out[ 1]=ux; out[ 2]=-fx; out[ 3]=0;
    out[ 4]=ry; out[ 5]=uy; out[ 6]=-fy; out[ 7]=0;
    out[ 8]=rz; out[ 9]=uz; out[10]=-fz; out[11]=0;
    out[12]=-(rx*ex+ry*ey+rz*ez);
    out[13]=-(ux*ex+uy*ey+uz*ez);
    out[14]= (fx*ex+fy*ey+fz*ez);
    out[15]=1;
}

// ── Perspective projection matrix ────────────────────────
void Camera::getProjectionMatrix(float out[16], float aspect) const
{
    float f   = 1.0f / std::tan(toRad(fov) * 0.5f);
    float n   = nearPlane, fa = farPlane;
    memset(out, 0, 16 * sizeof(float));
    out[ 0] = f / aspect;
    out[ 5] = f;
    out[10] = -(fa + n) / (fa - n);
    out[11] = -1.0f;
    out[14] = -(2.0f * fa * n) / (fa - n);
}
