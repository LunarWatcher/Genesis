#pragma once

#include "genesis/core/data/DataLoader.hpp"
#include "genesis/core/data/DataHelper.hpp"

namespace genesis {

static inline struct Context {
    DataLoader loader;
    DataHelper* generator = DataHelper::getInstance();
} GlobalCtx;

}
