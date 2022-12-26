#include "application.h"
#include "cubeScene.h"

int main() {
    Application* app = new Application();
    app->addScene(new CubeScene("CubeScene"));
    app->setScene("CubeScene");
    app->run();

    delete app;
}