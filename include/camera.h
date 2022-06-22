#pragma once

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera(float fov=90.0f, glm::vec3 position=glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 direction=glm::vec3(0.0f, 0.0f, -1.0f), float yaw=-90.0f, float pitch=0.0f, glm::vec3 up=glm::vec3(0.0f, 1.0f, 0.0f));
    void setPosition(float x, float y, float z);
    void Rotate(float yawAngle, float pitchAngle);
    void Move(Direction direction, float distance);
    glm::mat4 viewMatrix;
private:
    void Update();
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 right;
    float yaw;
    float pitch;
    float fov;
    glm::vec3 up;
};