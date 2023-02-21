#pragma once

namespace genesis {

class MouseHandler {
public:
    virtual ~MouseHandler() = default;

    virtual bool onMouseMoved(double x, double y) = 0;
    virtual bool onMousePressed(int button, int action, int mods) = 0;
};

}
