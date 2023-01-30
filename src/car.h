#pragma once
#include "poard.h"
#include "wheel.h"


float lerp(float min, float max, float t);


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
    float lookupTorque(float rpm);

    // in world reference
    glm::vec3 pos = glm::vec3(0.0);    // m
    glm::vec3 vel = glm::vec3(0.0);    // m/s
    glm::vec3 accel = glm::vec3(0.0);  // m/s^2

    glm::vec3 accelCar = glm::vec3(0.0f); // m/s^2, car reference
    glm::vec3 velCar = glm::vec3(0.0f); // m/s, car reference
                                        //
    float engineRpm = 0.0f;
    float yaw = 0.0f;                   // degrees
    float mass = 1632.933f;             // kg
    float steeringAngle = 0.0f;         // degrees

    float dragConstant = 0.4257f;
    float rollConstant = 0.12f * mass * 9.81;

    uint32_t selectedGear = 0;
    bool automaticTransmission = false;

    const float finalRatio = 3.46f;
    const float gearRatios[7] = {
        4.11f,  // 1
        2.32f,  // 2
        1.54f,  // 3
        1.18f,  // 4
        1.00f,  // 5
        0.85f,  // 6
        3.73f,  // reverse
    };

    std::unique_ptr<Model> hullModel;
    
    std::unique_ptr<Wheel> wheel_fl;
    std::unique_ptr<Wheel> wheel_fr;
    std::unique_ptr<Wheel> wheel_bl;
    std::unique_ptr<Wheel> wheel_br;
};
