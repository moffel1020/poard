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

    Window *window = new Window(720, 720, 144, "poard", false);
    window->Initialize();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize glad";
        glfwTerminate();
        return -1;
    }

    Input::Initialize(window->GLwindow);

    std::cout << "opengl version " << glGetString(GL_VERSION) << "\n" << std::endl;

    

    GLfloat vertices[] = 
    {	//coords				//colors            // texture coords
        -0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        0.5f,  -0.5f, 0.0f,		0.0f, 0.5f, 0.5f,   1.0f, 0.0f,
        0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f,		0.0f, 0.5f, 0.5f,   0.0f, 1.0f
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    glEnable(GL_DEPTH_TEST);
    Shader shader = Shader("../res/shader/vertex.glsl", "../res/shader/fragment.glsl");

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 proj = glm::perspective(glm::radians(70.0f), (float)window->width / (float)window->height, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 

    shader.Activate();
    shader.UploadMat4("model", model);
    shader.UploadMat4("projection", proj);
    shader.UploadMat4("view", view);

    Vao vao = Vao();
    vao.Bind();

    Vbo vbo = Vbo(vertices, sizeof(vertices));
    Ebo ebo = Ebo(indices, sizeof(indices));
    Texture tex = Texture("../res/texture/wood_texture.jpg");

    vao.AddBuffer(vbo, 0, 3, GL_FLOAT, sizeof(float) * 8, (void*)0);
    vao.AddBuffer(vbo, 1, 3, GL_FLOAT, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    vao.AddBuffer(vbo, 2, 2, GL_FLOAT, sizeof(float) * 8, (void*)(sizeof(float) * 6));

    glViewport(0, 0, window->height, window->height);
    while (!glfwWindowShouldClose(window->GLwindow))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Activate();
        tex.Bind();
        vao.Bind();
        ebo.Bind();
        shader.UploadMat4("model", model);
        shader.UploadMat4("projection", proj);
        shader.UploadMat4("view", view);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window->GLwindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}