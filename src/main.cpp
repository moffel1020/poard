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
        printf("failed to initialize GLFW\n");
        return -1;
    }

    Window *window = new Window(1080, 720, "poard", false, true);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize glad";
        glfwTerminate();
        return -1;
    }

    std::cout << "opengl version " << glGetString(GL_VERSION) << "\n" << std::endl;
    Input::initialize(window->GLwindow);
    glEnable(GL_DEPTH_TEST);

    
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    Shader shader = Shader("../res/shader/vertex.glsl", "../res/shader/fragment.glsl");

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 proj = glm::perspective(glm::radians(70.0f), (float)window->width / (float)window->height, 0.1f, 100.0f);

    Camera cam = Camera();
    float speed = 0.001f;
    float sensitivity = 0.1f;

    shader.activate();
    Texture tex = Texture("../res/texture/crate.jpg");

    VertexArray vao = VertexArray();
    VertexBuffer vbo = VertexBuffer(vertices, sizeof(vertices));

    vao.addBuffer(vbo, 0, 3, GL_FLOAT, sizeof(float) * 5, (void*)0);
    vao.addBuffer(vbo, 1, 2, GL_FLOAT, sizeof(float) * 5, (void*)(sizeof(float) * 3));


    int framecount = 0;
    float previousTime = glfwGetTime();

    glClearColor(0.1f, 0.5f, 0.5f, 1.0f);
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

        cam.rotate(Input::getMouseXOffset() * sensitivity, Input::getMouseYOffset() * sensitivity);

        shader.activate();
        tex.bind();
        vao.bind();

        shader.uploadMat4("uModel", model);
        shader.uploadMat4("uProjection", proj);
        shader.uploadMat4("uView", cam.viewMatrix);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glfwSwapBuffers(window->GLwindow);
        glfwPollEvents();

        framecount += 1;
        float time = glfwGetTime();
        if (time - previousTime >= 1) {
            window->changeTitle("poard | fps: " + std::to_string(framecount));
            previousTime = time;
            framecount = 0;
        }
    }

    glfwTerminate();
    return 0;
}