#pragma once

namespace genesis {

class Action {
private:

public:

    enum ActionType {
        DEFEND = -2,
        ATTACK = DEFEND + 1,
        EAT_OR_DRINK = 0,
        SLEEP = 1,
        DEMOLISH = 2,
        CONSTRUCT = DEMOLISH + 1,

    };

};

}
