#include "car.h"


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
    carTransform = glm::scale(carTransform, glm::vec3(0.7196245f)); // convert from model size to metres
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

    accel = glm::vec3(-1.0f, 0.0f, 0.0f);
    vel += dt * accel;
    pos += dt * vel;
}


void Car::gui() {
    ImGui::Begin("car");
    ImGui::Text("accel:  %.2f %.2f %.2f ", accel.x, accel.y, accel.z);
    ImGui::Text("vel:  %.2f %.2f %.2f ", vel.x, vel.y, vel.z);
    ImGui::Text("pos:  %.2f %.2f %.2f ", pos.x, pos.y, pos.z);
    ImGui::SliderFloat("steering angle:", &steeringAngle, -90.0f, 90.0f);
    ImGui::End();
}
