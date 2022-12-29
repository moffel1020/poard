#include "application.h"
#include "cubeScene.h"
#include "lightScene.h"
#include "texLightScene.h"
#include "multipleLights.h"
#include "multipleTexLights.h"

int main() {
    Application* app = new Application();
    app->addScene(new MultipleTexLights("LightScene"));
    app->setScene("LightScene");
    app->run();

    delete app;
}