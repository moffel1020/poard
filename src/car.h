#pragma once
#include "poard.h"
#include "wheel.h"


struct CarData {
    float mass = 1500.0f;   // kg
    float dragConstant = 0.5f;
    float rollConstant = 0.012f * mass * 9.81f;
    float length = 4.0f; // m
    float width = 1.9f; // m
    float height = 1.5f; // m
    float wheelBase = 2.0f; // m, distance between center of front and rear wheels
    float weightRatio = 0.5f; // weight ratio of back wheel (back wheel : front wheel) = (back wheel : 1 - backwheel)
    float finalRatio = 3.46f; // ratio multiplied with gearratio to get the gear ratio from the engine to the wheel
    float gearRatios[7] = { 4.11, 2.32, 1.54, 1.18, 1.00, 0.85, 3.37 }; // 1, 2, 3, 4, 5, 6, reverse
    bool automaticTransmission = true;
    std::vector<float> rpmCurve;
    std::vector<float> torqueCurve;
};


class Car
{
public:
    Car(const CarData& carData);
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

    // in car reference, +x is forward, +z is right
    glm::vec3 accelCar = glm::vec3(0.0f);   // m/s^2
    glm::vec3 velCar = glm::vec3(0.0f);     // m/s

    float weightRear = 0.0f;
    float weightFront = 0.0f;
    float engineRpm = 0.0f;

    float steeringAngle = 0.0f;         // degrees
    float angularAccel = 0.0f;          // rad/s^2
    float angularVel = 0.0f;            // rad/s
    float yaw = 0.0f;                   // radians 

    float slipAngleFront = 0.0f;        // radians
    float slipAngleRear = 0.0f;         // radians

    float latForceFront = 0.0f;         // N
    float latForceRear = 0.0f;          // N

    float angularTorque = 0.0f;         // N m

    glm::vec3 dragForce = glm::vec3(0.0f);
    glm::vec3 rollForce = glm::vec3(0.0f);
    glm::vec3 tractionForce = glm::vec3(0.0f);
    glm::vec3 brakeForce = glm::vec3(0.0f);
    float lateralForce = 0.0f;

    glm::vec3 totalForce = glm::vec3(0.0f);

    CarData data;
    uint32_t selectedGear = 0;

    std::unique_ptr<Model> hullModel;
    std::unique_ptr<Wheel> wheel_fl;
    std::unique_ptr<Wheel> wheel_fr;
    std::unique_ptr<Wheel> wheel_bl;
    std::unique_ptr<Wheel> wheel_br;
};
