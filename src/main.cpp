#include "core.h"
#include "shader.h"
#include "window.h"
#include "input.h"
#include "buffers.h"
#include "texture.h"
#include "camera.h"
#include "math.h"


int main() 
{
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW\n" << std::endl;
        return -1;
    }

    Window *window = new Window(1920, 1080, "poard", false, true);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize glad";
        glfwTerminate();
        return -1;
    }

    std::cout << "opengl version " << glGetString(GL_VERSION) << "\n" << std::endl;
    Input::initialize(window->GLwindow);

 
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


    Shader shader = Shader("../res/shader/default.vert", "../res/shader/default.frag");
    shader.activate();

    float fov = 90.0f;
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 proj = glm::perspective(glm::radians(fov), (float)window->width / (float)window->height, 0.1f, 100.0f);

    Camera cam = Camera();
    float speed = 0.001f;
    float sensitivity = 0.1f;

    Texture tex = Texture("../res/texture/crate.jpg");

    VertexArray vao = VertexArray();
    VertexBuffer vbo = VertexBuffer(vertices, sizeof(vertices));
    IndexBuffer ibo = IndexBuffer(indices, sizeof(indices));

    vao.addBuffer(vbo, 0, 3, GL_FLOAT, sizeof(float) * 5, (void*)0);                    // positions
    vao.addBuffer(vbo, 1, 2, GL_FLOAT, sizeof(float) * 5, (void*)(sizeof(float) * 3));  // texture coordinates


    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glViewport(0, 0, window->width, window->height);


    while (!glfwWindowShouldClose(window->GLwindow))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (Input::isKeyDown(GLFW_KEY_W))
            cam.move(FORWARD, speed);
        if (Input::isKeyDown(GLFW_KEY_S))
            cam.move(BACKWARD, speed);
        if (Input::isKeyDown(GLFW_KEY_D))
            cam.move(RIGHT, speed);
        if (Input::isKeyDown(GLFW_KEY_A))
            cam.move(LEFT, speed);
        if (Input::isKeyDown(GLFW_KEY_SPACE))
            cam.move(UP, speed);
        if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
            cam.move(DOWN, speed);

        cam.rotate(Input::getMouseXOffset() * sensitivity, Input::getMouseYOffset() * sensitivity);

        shader.activate();
        tex.bind();
        vao.bind();

        glm::mat4 view = cam.getViewMatrix();
        shader.uploadMat4("uModel", model);
        shader.uploadMat4("uProjection", proj);
        shader.uploadMat4("uView", view);
        
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);

        glfwSwapBuffers(window->GLwindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}