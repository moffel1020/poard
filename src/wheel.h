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
    float getAngularVel() { return angularVel; }
    float getRadius() { return radius; }
    void setAngularVel(float vel) { angularVel = vel; }

private:
    float radius = 0.4826;      // m
    float angularVel = 0.0f;    // rad/s

    std::unique_ptr<Model> wheelModel;
    glm::vec3 position;
    float rot = 0.0f;
    float steeringAngle = 0.0f; // degrees
};
