#pragma once

class Scene
{
public:
    Scene(const std::string& name) { this->name = name; }
    virtual void start() { }
    virtual ~Scene() { }
    virtual void update(float dt) { }
    virtual void draw() { }
    virtual void stop() { }
    std::string& getName() { return name; }
private:
    std::string name;
};