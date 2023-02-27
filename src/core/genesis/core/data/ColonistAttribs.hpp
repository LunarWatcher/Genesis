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

    int strength;
    int intelligence;
    int stamina;
    int agility;
} ColonistGenes;

typedef struct {
    /* Survival {{{*/
    int mining;
    int cooking;
    int hunting;
    int fighting;
    /*}}}*/
    /* Civilisation {{{*/
    int building;
    /*}}}*/
    /* Progress {{{*/
    int crafting;
    int brewing;
    int research;
    /*}}}*/
} ColonistSkills;

}
