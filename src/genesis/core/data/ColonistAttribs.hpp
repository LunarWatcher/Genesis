#pragma once

#define SPECIES_NUM 5

namespace genesis {

enum class Species {
    GREY_WOLF,
    ARCTIC_WOLF,

    RED_FOX,
    ARCTIC_FOX,
    SILVER_FOX,

};

typedef struct {
    Species s;
} ColonistGenes;
}
