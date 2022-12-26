#include "cubeScene.h"


void CubeScene::start() {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    };

    uint32_t indices[] = {
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 13, 14,
        12, 14, 15,
        16, 17, 18,
        16, 18, 19,
        20, 21, 22,
        20, 22, 23
    };


    this->vao = std::make_unique<VertexArray>();
    this->vbo = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    this->ibo = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));
    this->cam = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f), 70.0f);
    this->shader = std::make_unique<Shader>("./res/shader/texcolor.vert", "./res/shader/texcolor.frag");
    this->tex = std::make_unique<Texture>("./res/texture/crate.jpg");
    this->whiteTex = std::make_unique<Texture>(1, 1);

    uint32_t whiteData = 0xffffffff;
    whiteTex->setData(&whiteData, sizeof(uint32_t));
    
    vao->addBuffer(*vbo, 0, 3, GL_FLOAT, sizeof(float) * 9, (void*)0);                    // positions
    vao->addBuffer(*vbo, 1, 2, GL_FLOAT, sizeof(float) * 9, (void*)(sizeof(float) * 3));  // texture coordinates
    vao->addBuffer(*vbo, 2, 4, GL_FLOAT, sizeof(float) * 9, (void*)(sizeof(float) * 5));  // colors 
}

void CubeScene::update(float dt) {
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

void CubeScene::draw() {
    cam->update();

    tex->bind();
    shader->bind();
    glm::mat4 view = cam->getViewMatrix();
    glm::mat4 proj = cam->getProjMatrix();
    shader->uploadMat4("uProjection", proj);
    shader->uploadMat4("uView", view);

    shader->uploadMat4("uModel", model);
    Renderer::draw(*vao, *ibo, *shader);

    whiteTex->bind();
    for (int i = 1; i < 5; i++) {
        glm::mat4 model2 = glm::translate(glm::mat4(1.0f), glm::vec3(i*2, 0.0f, 0.0f));
        shader->uploadMat4("uModel", model2);
        Renderer::draw(*vao, *ibo, *shader);
    }
}

void CubeScene::gui() {
    static float x = 0.0f;
    static float y = 0.0f;
    static float z = 0.0f;

    static float rotX = 0.0f;
    static float rotY = 0.0f;
    static float rotZ = 0.0f;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("position");
    ImGui::SliderFloat("x", &x, -1.0f, 1.0f);
    ImGui::SliderFloat("y", &y, -1.0f, 1.0f);
    ImGui::SliderFloat("z", &z, -1.0f, 1.0f);

    ImGui::Text("rotation");
    ImGui::SliderFloat("rx", &rotX, -100.0f, 100.0f);
    ImGui::SliderFloat("ry", &rotY, -100.0f, 100.0f);
    ImGui::SliderFloat("rz", &rotZ, -100.0f, 100.0f);

    model[3][0] = x;
    model[3][1] = y;
    model[3][2] = z;

    const float dt = Application::get().getDeltaTime();
    model = model *
        glm::rotate(glm::mat4(1.0f), glm::radians(rotX * dt), glm::vec3(1.0f, 0.0f, 0.0f)) * 
        glm::rotate(glm::mat4(1.0f), glm::radians(rotY * dt), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(rotZ * dt), glm::vec3(0.0f, 0.0f, 1.0f));

    ImGui::NewLine();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}