#include "core.h"
#include "shader.h"
#include "window.h"
#include "input.h"
#include "buffers.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


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
    {	//coords				//colors
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


    Shader shader = Shader("../res/shader/vertex.glsl", "../res/shader/fragment.glsl");

    Vao vao = Vao();
    vao.Bind();
    Vbo vbo = Vbo(vertices, sizeof(vertices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * 8, (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    Ebo ebo = Ebo(indices, sizeof(indices));
    ebo.Bind();

    glm::mat4 trans = glm::mat4(1.0f);
    shader.Activate();
    shader.UploadMat4("transform", trans);
    

    // textures
    // load texture TODO: check to see if image is not null
    int width, height, nrChannels;
    unsigned char* image_data = stbi_load("../res/texture/wood_texture.jpg", &width, &height, &nrChannels, 0);

    // gen buffers
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // create texture and mipmap
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // free texture
    stbi_image_free(image_data);

    // link
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(float) * 8, (void*)(sizeof(float) * 6));

    // use texture
    glBindTexture(GL_TEXTURE_2D, texture);

    glViewport(0, 0, window->height, window->height);
    while (!glfwWindowShouldClose(window->GLwindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        vao.Bind();
        ebo.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        shader.UploadMat4("transform", trans);

        glfwSwapBuffers(window->GLwindow);
        glfwPollEvents();
    }

    shader.Delete();

    window->Destroy();
    glfwTerminate();
    return 0;
}