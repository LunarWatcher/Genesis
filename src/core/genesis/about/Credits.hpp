#pragma once

#include <string>
#include <vector>

namespace genesis {

enum class ProductCategory {
    FONT,
    LIBARY,
    OTHER
};

typedef struct {
    const std::string productName;
    const std::string license;
    const std::string url;
    const std::string author;

    const ProductCategory category;
} ProductEntry;

typedef struct {
    const std::string person;
    // Some optional URL for identification purposes
    const std::string url;
    // Free-form input describing what they did
    const std::string role;
} PersonEntry;

static inline std::vector<ProductEntry> assets {
    {
        "GamePixies",
        "freeware",
        "https://www.fontspace.com/gamepixies-font-f42493",
        "Heaven Castro Studios",
        ProductCategory::FONT
    },
    // TODO: populate with libraries
};

// Primarily intended for code/asset contributions
static inline std::vector<PersonEntry> contributors {
    {
        "Olivia (LunarWatcher)",
        "https://github.com/LunarWatcher",
        "Lead everything"
    },
};

// Non-code/asset contributors; prolific bug hunters (lmao, like I'll ever have the community for that),
// some people who write stuff that helps, some people I just feel like thanking, idk, this is my game,
// I can thank whoever I want :p
static inline std::vector<PersonEntry> honorableMentions {
};

}
