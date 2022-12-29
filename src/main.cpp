#include "application.h"
#include "cubeScene.h"
#include "lightScene.h"
#include "texLightScene.h"
#include "dirLightScene.h"

int main() {
    Application* app = new Application();
    app->addScene(new DirLightScene("LightScene"));
    app->setScene("LightScene");
    app->run();

    delete app;
}