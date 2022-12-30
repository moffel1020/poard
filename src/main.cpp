#include "application.h"
#include "multipleTexLights.h"

int main() {
    Application* app = new Application();
    app->addScene(new MultipleTexLights("LightScene"));
    app->setScene("LightScene");
    app->run();

    delete app;
}