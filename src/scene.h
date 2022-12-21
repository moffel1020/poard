#pragma once

class Scene
{
public:
    Scene() { }
    virtual ~Scene() { }
    virtual void update(float dt) { }
    virtual void draw() { }
};