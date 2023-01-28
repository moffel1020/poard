#include "application.h"

Application* Application::instance = nullptr;

Application::Application() {
    Application::instance = this;

    if (!glfwInit())
        std::cout << "Failed to initialize GLFW" << std::endl;

    this->window = new Window(1280, 720, "poard", false, true, true);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize glad" << std::endl;
        glfwTerminate();
    }

    std::cout << "opengl version " << glGetString(GL_VERSION) << "\n" << std::endl;
}


void Application::run() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, window->getWidth(), window->getHeight());

    float lastTime = glfwGetTime();
    Gui gui = Gui();
    Input::init();

    while (!glfwWindowShouldClose(window->getNativeWindow())) {
        Renderer::clear();

        frameTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        accum += frameTime;
        while (accum >= fixedDeltaTime) {
            scenes[activeScene]->update(fixedDeltaTime);
            accum -= fixedDeltaTime;
        }

        scenes[activeScene]->draw();

        gui.begin();
        scenes[activeScene]->gui();
        gui.end();

        Input::update();
        glfwSwapBuffers(window->getNativeWindow());
        glfwPollEvents();
    }

    delete window;
    glfwTerminate();
}


void Application::addScene(Scene* scene) {
    scenes.insert(std::pair<std::string, Scene*>(scene->getName(), scene));
}


void Application::setScene(const std::string& name) {
    if (scenes.find(name) == scenes.end()) {
        std::cout << "scene " << name << " does not exist" << std::endl;
        return;
    }

    if (scenes[activeScene])
        scenes[activeScene]->stop();

    activeScene = name;
    scenes[activeScene]->start();
}