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

    pointLights.emplace_back(glm::vec3(1.0f, 2.0f, 0.0f));
    pointLights.emplace_back(glm::vec3(-4.0f, 1.0f, 3.0f));
    pointLights.emplace_back(glm::vec3(2.0f, 1.0f, -5.0f));

    spotLights.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), 15.0f, 12.0f);
    spotLights.emplace_back(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 35.0f);
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
    glm::mat4 model(1.0f);

    modelShader->bind();
    modelShader->uploadMat4("uProjection", proj);
    modelShader->uploadMat4("uView", view);
    modelShader->uploadMat4("uModel", model);
    modelShader->uploadVec3("uCamPos", cam->getPosition());
    modelShader->uploadFloat("uPointLightCount", pointLights.size());
    modelShader->uploadFloat("uSpotLightCount", spotLights.size());

    glm::vec3 matColor(1.0f, 0.5f, 0.3f);
    modelShader->uploadVec3("material.diffuse", matColor);
    modelShader->uploadVec3("material.specular", 1.0f, 1.0f, 1.0f);
    modelShader->uploadFloat("material.shininess", 32.0f);

    cubeDiff->bind(GL_TEXTURE0);
    cubeSpec->bind(GL_TEXTURE1);

    DirLight dirLight = DirLight(glm::vec3(0.0f, -1.0f, 0.0f));
    dirLight.upload(*modelShader);

    for (uint32_t i = 0; i < pointLights.size(); i++)
        pointLights[i].upload(*modelShader, i);

    for (uint32_t i = 0; i < spotLights.size(); i++)
        spotLights[i].upload(*modelShader, i);

    Renderer::drawTriangles(*cubeVao, *modelShader, 36);

    // visualize point light pos
    lightShader->bind();
    lightShader->uploadMat4("uProjection", proj);
    lightShader->uploadMat4("uView", view);
    lightShader->uploadMat4("uModel", model);
    for (int i = 0; i < pointLights.size(); i++) {
        glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), pointLights[i].getPosition()), glm::vec3(0.3f));
        lightShader->uploadMat4("uModel", model);
        Renderer::drawTriangles(*cubeVao, *lightShader, 36);
    }
}

void MultipleTexLights::gui() {
    ImGui::Begin("performance");
    ImGui::Text("App: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Begin("light");
    static float pos[3] = { 0.0f, 0.0f, 0.0f };
    static float linear = 0.05f;
    static float quadratic = 0.003f;
    ImGui::SliderFloat3("position", pos, -10.0f, 10.0f);
    ImGui::SliderFloat("quadratic", &quadratic, -2.0f, 2.0f);
    ImGui::SliderFloat("linear", &linear, -2.0f, 2.0f);

    pointLights[0].setPosition(glm::vec3(pos[0], pos[1], pos[2]));
    pointLights[0].setLinear(linear);
    pointLights[0].setQuadratic(quadratic);
    ImGui::End();
}