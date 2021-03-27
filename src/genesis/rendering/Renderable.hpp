#pragma once

class Renderable {
public:
    virtual ~Renderable() = default;
    virtual void render() = 0;
    //For future use (if necessary)
    //virtual void tick() = 0;
};
