#include "application.h"
#include "cubeScene.h"
#include "lightScene.h"

int main() {
    Application* app = new Application();
    app->addScene(new LightScene("LightScene"));
    app->setScene("LightScene");
    app->run();

    delete app;
}