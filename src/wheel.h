#pragma once
#include "poard.h"

class Wheel
{
public:
    Wheel(const std::string& modelPath, const glm::vec3& position);
    void draw(Shader& shader, const glm::mat4& baseTransform);
    void update(float dt);

    float getSteeringAngle() { return steeringAngle; }
    float getAngularVel() { return angularVel; }
    float getRadius() { return radius; }
    void setAngularVel(float vel) { angularVel = vel; }
    void setSteeringAngle(float angle) { steeringAngle = angle; }
    void setWeight(float w) { weight = w; }

private:
    float radius = 0.4826f;      // m
    float angularVel = 0.0f;    // rad/s
    float weight = 3678.0f;      // m * g, set by car
    float steeringAngle = 0.0f; // degrees
    float rot = 0.0f;           // degrees rotation to make the tires roll

    std::unique_ptr<Model> wheelModel;
    glm::vec3 position;
};
