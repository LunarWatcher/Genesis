#pragma once

namespace genesis {

class AI {
public:
    virtual ~AI() = default;

    virtual void tick() = 0;
};

}
