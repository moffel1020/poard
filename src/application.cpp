#include "application.h"
#include "core.h"
#include "shader.h"
#include "window.h"
#include "input.h"
#include "buffers.h"
#include "texture.h"
#include "camera.h"
#include "math.h"


Application* Application::instance = nullptr;

Application::Application()
{
    Application::instance = this;

    if (!glfwInit())
        std::cout << "Failed to initialize GLFW\n" << std::endl;

    this->window = new Window(1280, 720, "poard", false, true, false);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize glad";
        glfwTerminate();
    }

    std::cout << "opengl version " << glGetString(GL_VERSION) << "\n" << std::endl;
    this->input = Input();
    this->renderer = Renderer();
}


void Application::run()
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
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


    Shader shader = Shader("./res/shader/default.vert", "./res/shader/default.frag");
    shader.bind();

    glm::mat4 model = glm::mat4(1.0f);

    Camera cam = Camera(glm::vec3(0.0f, 0.0f, 0.0f), 70.0f);
    float speed = 1.0f;
    float sensitivity = 0.1f;

    Texture tex = Texture("./res/texture/crate.jpg");

    VertexArray vao = VertexArray();
    VertexBuffer vbo = VertexBuffer(vertices, sizeof(vertices));
    IndexBuffer ibo = IndexBuffer(indices, sizeof(indices));

    vao.addBuffer(vbo, 0, 3, GL_FLOAT, sizeof(float) * 5, (void*)0);                    // positions
    vao.addBuffer(vbo, 1, 2, GL_FLOAT, sizeof(float) * 5, (void*)(sizeof(float) * 3));  // texture coordinates

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
    glViewport(0, 0, window->getWidth(), window->getHeight());

    float lastTime = glfwGetTime();
    float lastXPos = input.getMouseXPos();
    float lastYPos = input.getMouseYPos();

    while (!glfwWindowShouldClose(window->getNativeWindow()))
    {
        renderer.clear();

        float deltaTime = glfwGetTime() - lastTime;
        float xMouseMovement = input.getMouseXPos() - lastXPos;
        float yMouseMovement = input.getMouseYPos() - lastYPos;
        lastTime = glfwGetTime();
        lastXPos = input.getMouseXPos();
        lastYPos = input.getMouseYPos();

        if (input.isKeyDown(GLFW_KEY_W))
            cam.move(FORWARD, speed * deltaTime);
        if (input.isKeyDown(GLFW_KEY_S))
            cam.move(BACKWARD, speed * deltaTime);
        if (input.isKeyDown(GLFW_KEY_D))
            cam.move(RIGHT, speed * deltaTime);
        if (input.isKeyDown(GLFW_KEY_A))
            cam.move(LEFT, speed * deltaTime);
        if (input.isKeyDown(GLFW_KEY_SPACE))
            cam.move(UP, speed * deltaTime);
        if (input.isKeyDown(GLFW_KEY_LEFT_SHIFT))
            cam.move(DOWN, speed * deltaTime);

        cam.rotate(xMouseMovement * sensitivity, -yMouseMovement * sensitivity);
        cam.update();

        tex.bind();

        shader.bind();
        glm::mat4 view = cam.getViewMatrix();
        glm::mat4 proj = cam.getProjMatrix();
        shader.uploadMat4("uModel", model);
        shader.uploadMat4("uProjection", proj);
        shader.uploadMat4("uView", view);

        renderer.draw(vao, ibo, shader);

        glfwSwapBuffers(window->getNativeWindow());
        glfwPollEvents();
    }

    glfwTerminate();
}
