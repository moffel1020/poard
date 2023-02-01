#include "car.h"
#include "imgui/imgui.h"

#define PI 3.14159265358979323846


float lerp(float min, float max, float t) {
    return min + (max - min) * t;
}


Car::Car(const CarData& carData) {
    this->data = carData;
    this->hullModel= std::make_unique<Model>("./res/models/car/hull.obj");

    glm::vec3 flWheelPos = glm::vec3(-2.05f, 0.5f, 1.1f);
    glm::vec3 frWheelPos = glm::vec3(-2.05f, 0.5f, -1.1f);
    glm::vec3 blWheelPos = glm::vec3(1.75f, 0.5f, 1.1f);
    glm::vec3 brWheelPos = glm::vec3(1.75f, 0.5f, -1.1f);

    this->wheel_fl = std::make_unique<Wheel>("./res/models/car/wheel_l.obj", flWheelPos);
    this->wheel_fr = std::make_unique<Wheel>("./res/models/car/wheel_r.obj", frWheelPos);
    this->wheel_bl = std::make_unique<Wheel>("./res/models/car/wheel_l.obj", blWheelPos);
    this->wheel_br = std::make_unique<Wheel>("./res/models/car/wheel_r.obj", brWheelPos);
}

void Car::draw(Shader& shader) {
    glm::mat4 carTransform(1.0f);
    carTransform = glm::translate(carTransform, pos);
    carTransform = glm::scale(carTransform, glm::vec3(0.7196245f));     // convert from model size to metres
    carTransform = glm::rotate(carTransform, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));    // car model is flipped, so we flip it back to point in the +x axis
    carTransform = glm::rotate(carTransform, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    hullModel->draw(shader, carTransform);

    wheel_fr->draw(shader, carTransform);
    wheel_fl->draw(shader, carTransform);
    wheel_br->draw(shader, carTransform);
    wheel_bl->draw(shader, carTransform);
}


void Car::update(float dt) {
    wheel_fr->setSteeringAngle(steeringAngle);
    wheel_fl->setSteeringAngle(steeringAngle);

    // get velocity in local car coordinates from world coords
    velCar.x = cos(glm::radians(-yaw)) * vel.x + sin(glm::radians(-yaw)) * vel.z;
    velCar.z = cos(glm::radians(-yaw)) * vel.z - sin(glm::radians(-yaw)) * vel.x;

    float wheelAngularVel = velCar.x / wheel_bl->getRadius();   // only works if there is no slip
    wheel_bl->setAngularVel(wheelAngularVel);
    wheel_fl->setAngularVel(wheelAngularVel);
    wheel_br->setAngularVel(wheelAngularVel);
    wheel_fr->setAngularVel(wheelAngularVel);

    wheel_bl->update(dt);
    wheel_fl->update(dt);
    wheel_br->update(dt);
    wheel_fr->update(dt);

    engineRpm = (wheelAngularVel * data.gearRatios[selectedGear] * data.finalRatio * 60) / (2 *  PI);
    if (engineRpm < 1000.0f) engineRpm = 1000.0f;
    if (engineRpm > 7500.0f) engineRpm = 7500.0f;

    if (data.automaticTransmission) {
        if (engineRpm >= 7500.0f && selectedGear < 5) {
            selectedGear++;
        } else if (engineRpm <= 1200.0f && selectedGear > 0) {
            selectedGear--;
        }
    }

    float engineTorque = lookupTorque(engineRpm);

    float gasInput = Input::isKeyDown(GLFW_KEY_W) ? 1.0f : 0.0f;
    float wheelTorque = engineTorque * data.gearRatios[selectedGear] * data.finalRatio * gasInput;

    glm::vec3 fTraction(0.0f);
    fTraction.x = wheelTorque / wheel_bl->getRadius() * gasInput;;
    glm::vec3 fDrag = glm::length(velCar) * velCar * -data.dragConstant;
    glm::vec3 fRoll = velCar * -data.rollConstant; 

    glm::vec3 fTotal = fTraction + fDrag + fRoll;

    accelCar = fTotal / data.mass;

    // translate back to world coords
    accel.x = cos(glm::radians(-yaw)) * accelCar.x - sin(glm::radians(-yaw)) * accelCar.z;
    accel.y = sin(glm::radians(-yaw)) * accelCar.x + cos(glm::radians(-yaw)) * accelCar.z;

    vel += dt * accel;
    pos += dt * vel;
}


float Car::lookupTorque(float rpm) {
    // curves from:
    float torque = data.torqueCurve[0];
    for (uint32_t i = 1; i < 14; i++) {
        if (rpm > data.rpmCurve[i-1] && rpm < data.rpmCurve[i]) {
            torque = lerp(data.torqueCurve[i-1], data.torqueCurve[i], ((rpm - data.rpmCurve[i-1]) / (data.rpmCurve[i] - data.rpmCurve[i-1])));
        }
    }

    return torque;
}


void Car::gui() {
    ImGui::Begin("car");
    ImGui::Text("accel =  %.2f %.2f %.2f ", accel.x, accel.y, accel.z);
    ImGui::Text("vel =  %.2f %.2f %.2f ", vel.x, vel.y, vel.z);
    ImGui::Text("pos =  %.2f %.2f %.2f ", pos.x, pos.y, pos.z);
    ImGui::NewLine();
    ImGui::Text("localAccel = %.2f %.2f", accelCar.x, accelCar.z);
    ImGui::Text("localVel = %.2f %.2f", velCar.x, velCar.z);
    ImGui::SliderFloat("steering", &steeringAngle, -90.0f, 90.0f);
    ImGui::End();

    ImGui::Begin("engine");
    ImGui::Text("rpm = %.0f", engineRpm);
    ImGui::Text("gear = %u", selectedGear + 1);

    ImGui::End();
}
