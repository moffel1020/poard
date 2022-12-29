#pragma once
#include "core.h"

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:
    Camera(glm::vec3 position=glm::vec3(0.0f, 0.0f, 0.0f), float fov=70.0f, float yaw=-90.0f ,float pitch=0.0f);
    void setPosition(float x, float y, float z);
    void rotate(float yawAngle, float pitchAngle);
    void move(Direction direction, float distance);
    glm::vec3 getPosition() { return position; }
    glm::vec3 getForward() { return forward; }
    glm::vec3 getDirection() { return direction; }
    glm::mat4 getViewMatrix();
    glm::mat4 getProjMatrix();
    void update();
private:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 forward;
    glm::vec3 right;
    float yaw;
    float pitch;
    float fov;
    glm::mat4 viewMatrix;
    glm::mat4 projMatrix;
};