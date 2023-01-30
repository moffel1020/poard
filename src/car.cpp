#include "car.h"
#include "imgui/imgui.h"

#define PI 3.14159265358979323846


float lerp(float min, float max, float t) {
    return (min + max) / t;
}


Car::Car() {
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
    engineRpm = (wheelAngularVel * gearRatios[selectedGear] * gearRatios[0] * 60) / (2 *  PI);
    if (engineRpm < 1000.0f) engineRpm = 1100.0f;

    if (automaticTransmission) {
        if (engineRpm > 7500.0f && selectedGear < 5) {
            selectedGear++;
        } else if (engineRpm < 1200.0f && selectedGear > 0) {
            selectedGear--;
        }
    }

    float engineTorque = lookupTorque(engineRpm);

    float gasInput = Input::isKeyDown(GLFW_KEY_W) ? 1.0f : 0.0f;
    float wheelTorque = engineTorque * gearRatios[selectedGear] * gearRatios[0] * gasInput;
    glm::vec3 fTraction(0.0f);
    fTraction.x = wheelTorque / wheel_bl->getRadius();
    //std::cout << fTraction.x << std::endl;

    glm::vec3 fDrag = glm::length(velCar) * velCar * -dragConstant;
    glm::vec3 fRoll = -rollConstant * velCar; 
    
    glm::vec3 fTotal = fTraction + fDrag + fRoll;
    std::cout << fTotal.x << std::endl;

    accelCar = fTotal / mass;

    // translate back to world coords
    accel.x = cos(glm::radians(-yaw)) * accelCar.x - sin(glm::radians(-yaw)) * accelCar.z;
    accel.y = sin(glm::radians(-yaw)) * accelCar.x + cos(glm::radians(-yaw)) * accelCar.z;

    vel += dt * accel;
    pos += dt * vel;
}


float Car::lookupTorque(float rpm) {
    // curves from:
    // https://www.automobile-catalog.com/curve/2021/2917385/bmw_m2_competition_6-speed.html#gsc.tab=0
    float rpmCurve[] = { 1000.0f, 1500.0f, 2000.0f, 2500.0f, 3000.0f, 3500.0f, 4000.0f, 4500.0f, 5000.0f, 5500.0f, 6000.0f, 6500.0f, 7000.0f, 7500.0f };
    float torqueCurve[] = { 296.0f, 443.9f, 517.9f, 551.0f, 551.0f, 551.0f, 551.0f, 551.0f, 551.0f, 524.0f, 480.6f, 443.7f, 412.0f, 346.1f };
    
    float torque = torqueCurve[0];
    for (uint32_t i = 1; i < 14; i++) {
        if (rpm > rpmCurve[i-1] && rpm < rpmCurve[i]) {
            torque = lerp(torqueCurve[i-1], torqueCurve[i], ((rpm - rpmCurve[i-1]) / (rpmCurve[i] - rpmCurve[i-1])));
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
    ImGui::Text("localVel = %.2f %.2f", velCar.x * 3.6f, velCar.z *3.6f);
    ImGui::SliderFloat("steering", &steeringAngle, -90.0f, 90.0f);
    ImGui::End();

    ImGui::Begin("engine");
    ImGui::Text("rpm = %.0f", engineRpm);
    ImGui::Text("gear = %u", selectedGear + 1);
    if (ImGui::Button("gear up"))
        selectedGear++;

    if (ImGui::Button("gear down"))
        selectedGear--;

    ImGui::End();
}
