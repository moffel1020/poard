#include "window.h"

class Application
{
public:
    Application();
    void run();
    Window* getWindow() { return window; }
    static Application& getInstance() { return *instance; }
private:
    Window* window;
    static Application* instance;
};
