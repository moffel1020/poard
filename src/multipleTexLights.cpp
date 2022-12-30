#include "multipleTexLights.h"


void MultipleTexLights::start() {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    this->cubeVao = std::make_unique<VertexArray>();
    this->cubeVbo = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    this->cam = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f), 70.0f);
    this->modelShader = std::make_unique<Shader>("./res/shader/texlights.vert", "./res/shader/texlights.frag");
    this->lightShader = std::make_unique<Shader>("./res/shader/white.vert", "./res/shader/white.frag");
    this->cubeDiff = std::make_unique<Texture>("./res/texture/crate2.png");
    this->cubeSpec = std::make_unique<Texture>("./res/texture/crate2_specular.png");
    
    cubeVao->addBuffer(*cubeVbo, 0, 3, GL_FLOAT, sizeof(float) * 8, (void*)0);
    cubeVao->addBuffer(*cubeVbo, 1, 3, GL_FLOAT, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    cubeVao->addBuffer(*cubeVbo, 2, 2, GL_FLOAT, sizeof(float) * 8, (void*)(sizeof(float) * 6));
}

void MultipleTexLights::update(float dt) {
    const float speed = 2.0f;
    const float sensitivity = 0.1f;

    if (Input::isKeyDown(GLFW_KEY_W))
        cam->move(FORWARD, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_S))
        cam->move(BACKWARD, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_D))
        cam->move(RIGHT, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_A))
        cam->move(LEFT, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_SPACE))
        cam->move(UP, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
        cam->move(DOWN, speed * dt);

    if (Application::get().getWindow()->getLockCursor())
        cam->rotate(Input::getMouseXMovement() * sensitivity, -Input::getMouseYMovement() * sensitivity);
}

void MultipleTexLights::draw() {
    cam->update();

    glm::mat4 view = cam->getViewMatrix();
    glm::mat4 proj = cam->getProjMatrix();

    modelShader->bind();
    modelShader->uploadMat4("uProjection", proj);
    modelShader->uploadMat4("uView", view);

    glm::mat4 model(1.0f);

    modelShader->uploadMat4("uModel", model);
    modelShader->uploadVec3("uCamPos", cam->getPosition());

    glm::vec3 matColor(1.0f, 0.5f, 0.3f);
    modelShader->uploadVec3("material.diffuse", matColor);
    modelShader->uploadVec3("material.specular", 1.0f, 1.0f, 1.0f);
    modelShader->uploadFloat("material.shininess", 32.0f);

    // bind textures to correct slot
    cubeDiff->bind(GL_TEXTURE0);
    cubeSpec->bind(GL_TEXTURE1);

    // dir light
    modelShader->uploadVec3("dirLight.direction", 0.0f, -1.0f, 0.0f);
    modelShader->uploadVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
    modelShader->uploadVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    modelShader->uploadVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

    // point light
    modelShader->uploadVec3("pointLight.position", pLightPos);
    modelShader->uploadVec3("pointLight.ambient", 0.1f, 0.1f, 0.1f);
    modelShader->uploadVec3("pointLight.diffuse", 1.0f, 1.0f, 1.0f);
    modelShader->uploadVec3("pointLight.specular", 0.5f, 0.5f, 0.5f);
    modelShader->uploadFloat("pointLight.constant", 1.0f);
    modelShader->uploadFloat("pointLight.quadratic", 0.05f);
    modelShader->uploadFloat("pointLight.linear", 0.003f);

    // spot light
    modelShader->uploadVec3("spotLight.position", sLightPos);
    modelShader->uploadVec3("spotLight.direction", sLightDir);
    modelShader->uploadVec3("spotLight.ambient", 0.1f, 0.1f, 0.1f);
    modelShader->uploadVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    modelShader->uploadVec3("spotLight.specular", 0.1f, 0.1f, 0.1f);
    modelShader->uploadFloat("spotLight.constant", 1.0f);
    modelShader->uploadFloat("spotLight.quadratic", 0.05f);
    modelShader->uploadFloat("spotLight.linear", 0.003f);
    modelShader->uploadFloat("spotLight.inner", glm::cos(glm::radians(12.0f)));
    modelShader->uploadFloat("spotLight.outer", glm::cos(glm::radians(15.0f)));

    // draw model
    Renderer::drawTriangles(*cubeVao, *modelShader, 36);

    // visualize point light pos
    model = glm::translate(glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)), pLightPos);
    lightShader->bind();
    lightShader->uploadMat4("uProjection", proj);
    lightShader->uploadMat4("uView", view);
    lightShader->uploadMat4("uModel", model);
    Renderer::drawTriangles(*cubeVao, *lightShader, 36);
}

void MultipleTexLights::gui() {
    ImGui::Begin("light");
    ImGui::Text("App: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::SliderFloat3("p position", glm::value_ptr(pLightPos), -10.0f, 10.0f);

    ImGui::SliderFloat3("s position", glm::value_ptr(sLightPos), -10.0f, 10.0f);
    ImGui::SliderFloat3("s dir", glm::value_ptr(sLightDir), -1.0f, 1.0f);

    ImGui::End();
}