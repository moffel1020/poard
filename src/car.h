#pragma once
#include "poard.h"
#include "wheel.h"

class Car
{
public:
    Car();
    void update(float dt);
    void draw(Shader& shader);
    void gui();

    float getYaw() { return yaw; }
    glm::vec3& getPosition() { return pos; }
    glm::vec3& getVelocity() { return vel; }
private:
    glm::vec3 pos = glm::vec3(0.0);    // m
    glm::vec3 vel = glm::vec3(0.0);    // m/s
    glm::vec3 accel = glm::vec3(0.0);  // m/s^2

    float yaw = 0.0f;                   // degrees
    float angularVel = 0.0f;            // rad/s
    float mass = 1632.933f;             // kg
    float steeringAngle = 0.0f;         // degrees
    float wheelRadius = 0.0f;           // m

    std::unique_ptr<Model> hullModel;
    
    std::unique_ptr<Wheel> wheel_fl;
    std::unique_ptr<Wheel> wheel_fr;
    std::unique_ptr<Wheel> wheel_bl;
    std::unique_ptr<Wheel> wheel_br;
};
