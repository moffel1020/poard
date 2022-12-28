#include "application.h"
#include "cubeScene.h"
#include "lightScene.h"
#include "texLightScene.h"

int main() {
    Application* app = new Application();
    app->addScene(new TexLightScene("LightScene"));
    app->setScene("LightScene");
    app->run();

    delete app;
}