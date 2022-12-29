#include "application.h"
#include "cubeScene.h"
#include "lightScene.h"
#include "texLightScene.h"
#include "multipleLights.h"

int main() {
    Application* app = new Application();
    app->addScene(new MultipleLights("LightScene"));
    app->setScene("LightScene");
    app->run();

    delete app;
}