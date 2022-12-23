#include "application.h"

Application* Application::instance = nullptr;

Application::Application() {
    Application::instance = this;

    if (!glfwInit())
        std::cout << "Failed to initialize GLFW\n" << std::endl;

    this->window = new Window(1280, 720, "poard", false, true, false);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize glad";
        glfwTerminate();
    }

    std::cout << "opengl version " << glGetString(GL_VERSION) << "\n" << std::endl;
}


void Application::run() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
    glViewport(0, 0, window->getWidth(), window->getHeight());

    float lastTime = glfwGetTime();

    CubeScene scene = CubeScene();

    while (!glfwWindowShouldClose(window->getNativeWindow())) {
        Renderer::clear();

        float deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        scene.update(deltaTime);
        scene.draw();

        Input::update();

        glfwSwapBuffers(window->getNativeWindow());
        glfwPollEvents();
    }

    glfwTerminate();
}
