#pragma once
#include "poard.h"

class Wheel
{
public:
    Wheel(const std::string& modelPath, const glm::vec3& position);
    void draw(Shader& shader, const glm::mat4& baseTransform);
    void update(float dt);
    void setSteeringAngle(float angle) { steeringAngle = angle; }
    float getSteeringAngle() { return steeringAngle; }

private:
    float angulerVel = 0.0f; // rad/s
    float radius; // m
    float steeringAngle = 0.0f; // degrees

    std::unique_ptr<Model> wheelModel;
    glm::vec3 position;
};
