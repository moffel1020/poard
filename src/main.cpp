#include "core.h"
#include "shader.h"
#include "window.h"
#include "input.h"
#include "buffers.h"
#include "texture.h"

#include "math.h"


int main() 
{
    if (!glfwInit()) {
        printf("failed to initialize GLFW\n");
        return -1;
    }

    Window *window = new Window(1080, 720, "poard", false);
    window->Initialize();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
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
    glm::mat4 view;
    glm::vec3 camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    shader.Activate();
    Texture tex = Texture("D:/Users/thomas schaap/Pictures/aids/matss.png");

    Vao vao = Vao();
    vao.Bind();

    Vbo vbo = Vbo(vertices, sizeof(vertices));

    vao.AddBuffer(vbo, 0, 3, GL_FLOAT, sizeof(float) * 5, (void*)0);
    vao.AddBuffer(vbo, 1, 2, GL_FLOAT, sizeof(float) * 5, (void*)(sizeof(float) * 3));


    int framecount = 0;
    float previousTime = glfwGetTime();
    glClearColor(0.1f, 0.5f, 0.5f, 1.0f);
    glViewport(0, 0, window->width, window->height);
    while (!glfwWindowShouldClose(window->GLwindow))
    {
        float time1 = glfwGetTime();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = glm::lookAt(glm::vec3(cos(glfwGetTime()) * 2.0f, 1.0f, sin(glfwGetTime()) * 2.0f), camTarget, up);

        shader.Activate();
        tex.Bind();
        vao.Bind();

        shader.UploadMat4("uModel", model);
        shader.UploadMat4("uProjection", proj);
        shader.UploadMat4("uView", view);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glfwSwapBuffers(window->GLwindow);
        glfwPollEvents();


        framecount += 1;
        float time = glfwGetTime();
        if (time - previousTime >= 1) {
            window->ChangeTitle("poard | fps: " + std::to_string(framecount));
            previousTime = time;
            framecount = 0;
        }
    }

    glfwTerminate();
    return 0;
}