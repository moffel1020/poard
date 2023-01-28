#include "car.h"


Car::Car() {
    this->hullModel= std::make_unique<Model>("./res/models/car/hull.obj");
    this->rightWheelModel= std::make_unique<Model>("./res/models/car/wheel_r.obj");
    this->leftWheelModel= std::make_unique<Model>("./res/models/car/wheel_l.obj");
}


void Car::draw(Shader& shader) {
    glm::mat4 carTransform(1.0f);
    carTransform = glm::translate(carTransform, pos);
    carTransform = glm::scale(carTransform, glm::vec3(0.7196245f)); // convert from model size to metres
    carTransform = glm::rotate(carTransform, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    hullModel->draw(shader, carTransform);


    glm::mat4 wheelTransform = glm::translate(carTransform, flWheelPos);
    wheelTransform = glm::rotate(wheelTransform, glm::radians(steeringAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    leftWheelModel->draw(shader, wheelTransform);

    wheelTransform = glm::translate(carTransform, frWheelPos);
    wheelTransform = glm::rotate(wheelTransform, glm::radians(steeringAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    rightWheelModel->draw(shader, wheelTransform);

    wheelTransform = glm::translate(carTransform, blWheelPos);
    leftWheelModel->draw(shader, wheelTransform);

    wheelTransform = glm::translate(carTransform, brWheelPos);
    rightWheelModel->draw(shader, wheelTransform);
}


void Car::update(float dt) {
    accel = glm::vec3(-1.0f, 0.0f, -1.0f);
    vel += dt * accel;
    pos += dt * vel;
}


void Car::gui() {
    ImGui::Begin("car");
    ImGui::Text("accel:  %.2f %.2f %.2f ", accel.x, accel.y, accel.z);
    ImGui::Text("vel:  %.2f %.2f %.2f ", vel.x, vel.y, vel.z);
    ImGui::Text("pos:  %.2f %.2f %.2f ", pos.x, pos.y, pos.z);
    ImGui::SliderFloat("steering angle:", &steeringAngle, -90.0f, 90.0f);
    // ImGui::SliderFloat("car angle:", &yaw, 0.0f, 360.0f);
    ImGui::End();
}