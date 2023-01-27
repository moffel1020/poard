#include "application.h"
#include "modelScene.h"

int main() {
    Application* app = new Application();
    app->addScene(new ModelScene("modelTestScene"));
    app->setScene("modelTestScene");
    app->run();

    delete app;
}