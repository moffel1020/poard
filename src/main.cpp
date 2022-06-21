#include "core.h"
#include "shader.h"
#include "window.h"
#include "input.h"
#include "buffers.h"
#include "texture.h"


int main()
{
    if (!glfwInit())
    {
        printf("failed to initialize GLFW\n");
        return -1;
    }

    Window *window = new Window(1080, 720, "poard", false);
    window->Initialize();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize glad";
        glfwTerminate();
        return -1;
    }

    std::cout << "opengl version " << glGetString(GL_VERSION) << "\n" << std::endl;
    Input::Initialize(window->GLwindow);
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
    glm::mat4 view = glm::mat4(1.0f);

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 

    shader.Activate();
    shader.UploadMat4("model", model);
    shader.UploadMat4("projection", proj);
    shader.UploadMat4("view", view);

    Vao vao = Vao();
    vao.Bind();

    Vbo vbo = Vbo(vertices, sizeof(vertices));
    Texture tex = Texture("../res/texture/wood_texture.jpg");

    vao.AddBuffer(vbo, 0, 3, GL_FLOAT, sizeof(float) * 5, (void*)0);
    vao.AddBuffer(vbo, 1, 2, GL_FLOAT, sizeof(float) * 5, (void*)(sizeof(float) * 3));

    float angle;

    glViewport(0, 0, window->width, window->height);
    while (!glfwWindowShouldClose(window->GLwindow))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Activate();
        tex.Bind();
        vao.Bind();

        if (Input::isKeyDown(GLFW_KEY_W))
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.001f));
        if (Input::isKeyDown(GLFW_KEY_S))
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.001f));

        if (Input::isKeyDown(GLFW_KEY_LEFT))
            model = glm::rotate(model, glm::radians(-0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
        if (Input::isKeyDown(GLFW_KEY_RIGHT))
            model = glm::rotate(model, glm::radians(0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
        if (Input::isKeyDown(GLFW_KEY_UP))
            model = glm::rotate(model, glm::radians(-0.05f), glm::vec3(1.0f, 0.0f, 0.0f));
        if (Input::isKeyDown(GLFW_KEY_DOWN))
            model = glm::rotate(model, glm::radians(0.05f), glm::vec3(1.0f, 0.0f, 0.0f));


        angle = glfwGetTime() * 0.01f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 0.0f));

        shader.UploadMat4("model", model);
        shader.UploadMat4("projection", proj);
        shader.UploadMat4("view", view);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window->GLwindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}