#include <math.h>
#include "core.h"
#include "camera.h"

Camera::Camera(float fov, glm::vec3 position, glm::vec3 direction, float yaw, float pitch, glm::vec3 up)
{
    this->position = position; 
    this->direction = direction;
    this->fov = fov;
    this->yaw = yaw;
    this-> pitch = pitch;
    this-> up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::rotate(float yawAngle, float pitchAngle)
{
    yaw += yawAngle;
    pitch += pitchAngle;

    if (pitch > 89.9f) pitch = 89.9f;
    else if (pitch < -89.9f) pitch = -89.9f;
    update();
}

void Camera::move(Direction dir, float distance)
{
    switch (dir) {
        case FORWARD:
            position += direction * distance;
            break;
        case BACKWARD:
            position -= direction * distance;
            break;
        case RIGHT:
            position += right * distance;
            break;
        case LEFT:
            position -= right * distance;
            break;
    }

    update();
}

void Camera::setPosition(float x, float y, float z)
{
    position.x += x;
    position.y += y;
    position.z += z;
    update();
}

void Camera::update()
{
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    direction = glm::normalize(direction);
    right = glm::normalize(glm::cross(direction, up));

    viewMatrix = glm::lookAt(position, position + direction, up);
}