#include "wheel.h"

Wheel::Wheel(const std::string& modelPath, const glm::vec3& position) 
    : position(position) { 
    this->wheelModel = std::make_unique<Model>(modelPath);
}


void Wheel::draw(Shader& shader, const glm::mat4& baseTransform) {
    glm::mat4 wheelTransform = glm::translate(baseTransform, position);
    wheelTransform = glm::rotate(wheelTransform, glm::radians(steeringAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    wheelModel->draw(shader, wheelTransform);
}


void Wheel::update(float dt) { }
