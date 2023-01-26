#pragma once
#include "core.h"
#include "camera.h"

class Scene
{
public:
    Scene(const std::string& name) { this->name = name; }
    virtual void start() { }
    virtual ~Scene() { }
    virtual void update(float dt) { }
    virtual void draw() { }
    virtual void gui() { }
    virtual void stop() { }
    std::string& getName() { return name; }
    void setActiveCam(Camera* camera) { activeCam = camera; }
    Camera* getActiveCam() { return activeCam; }
protected:
    std::string name;
    Camera* activeCam;
};