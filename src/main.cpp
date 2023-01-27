#include "application.h"
#include "carScene.h"

int main() {
    Application* app = new Application();
    app->addScene(new CarScene("carScene"));
    app->setScene("carScene");
    app->run();

    delete app;
}