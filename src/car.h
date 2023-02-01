#pragma once
#include "poard.h"
#include "wheel.h"


float lerp(float min, float max, float t);


struct CarData {
    float mass = 1500.0f;   // kg
    float dragConstant = 0.5f;
    float rollConstant = 0.012f * mass * 9.81f;
    float length = 4.0f; // m
    float width = 1.9f; // m
    float height = 1.5f; // m
    float wheelBase = 2.0f; // m, distance between center of front and rear wheels
    float weightDistribution = 0.5f; // weight ratio of back wheel (back wheel : front wheel) = (back wheel : 1 - backwheel)
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

    // in car reference
    glm::vec3 accelCar = glm::vec3(0.0f);   // m/s^2
    glm::vec3 velCar = glm::vec3(0.0f);     // m/s

    float engineRpm = 0.0f;
    float steeringAngle = 0.0f;         // degrees
    float yaw = 0.0f;                   // degrees
    uint32_t selectedGear = 0;

    CarData data;

    std::unique_ptr<Model> hullModel;
    std::unique_ptr<Wheel> wheel_fl;
    std::unique_ptr<Wheel> wheel_fr;
    std::unique_ptr<Wheel> wheel_bl;
    std::unique_ptr<Wheel> wheel_br;
};
