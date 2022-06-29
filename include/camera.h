#pragma once

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
    Camera(glm::vec3 position=glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 direction=glm::vec3(0.0f, 0.0f, -1.0f), float yaw=-90.0f, float pitch=0.0f, glm::vec3 up=glm::vec3(0.0f, 1.0f, 0.0f));
    void setPosition(float x, float y, float z);
    void rotate(float yawAngle, float pitchAngle);
    void move(Direction direction, float distance);
    glm::mat4 getViewMatrix();
private:
    void update();
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 forward;
    glm::vec3 right;
    float yaw;
    float pitch;
    float fov;
    glm::vec3 up;
    glm::mat4 viewMatrix;
};