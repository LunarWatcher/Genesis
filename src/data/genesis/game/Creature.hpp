#pragma once

#include <map>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace genesis {

enum class Gender {
    /**
     * Primarily intended for gender-less species
     */
    NONE,

    // Currently unused {{{
    // Classic binary {{{
    FEMALE,
    MALE,
    // }}}
    
    TRANS_MASC,
    TRANS_FEM,

    NON_BINARY,
    INTERSEX,
    // There are more categories that could be added,
    // but it heavily depends on how deep down the rabbit hole of mood I go.
    // (DF calls it emotions, and (strange) mood is exclusively the thing used for generating artefacts,
    // but that's kinda dumb). Not sure how I wanna do artefact generation yet though. Future me problem
    // Might just leave it to RNGesus
    // ---
    //
    // Could potentially incorporate a mechanic to get rid of reproductive complications,
    // which would indeed make mood the only affected component.
    // Might just treat them biologically as the correct gender to simplify stuff. Something something
    // magic world?
    //
    // There's already sentient canines, it isn't that much of a stretch.
    // 
    // }}}
};

enum class ReproductionType {
    MAMMALIAN,
};

struct AIInfo {
    bool isIntelligent;
    bool isAggressive;

};

struct BreedingInfo {
    bool infertile;
    std::vector<std::string> compatibleCreatures;

    bool agender = true;
};

struct AttributeInfo {
    int stealth;
    int agility;
    int intelligence;

};

struct GraphicsInfo {
    std::string source;

    /**
     * Whether or not the image is static.
     *
     * If true, `source` must be a reference to a valid image in a sprite sheet.
     * Otherwise, the source must be a spritesheet.
     *
     * The shorthand here is `"static": "imgref"` is equivalent to `"isStatic": true, "source": "imgref"`
     * Specifying just `source` implies `isStatic = false`
     */
    bool isStatic;
};

/**
 * Key structure for defining a class of species.
 */
struct CreatureInfo {
    std::string name;
    std::string plural;
    std::string adjective;

    BreedingInfo breedingInfo;
    AttributeInfo biologicalAttribBias;
    AIInfo aiDetails;
    GraphicsInfo graphics;
};

extern void from_json(const nlohmann::json& j, CreatureInfo& r);
extern void from_json(const nlohmann::json& j, ReproductionType& r);
extern void from_json(const nlohmann::json& j, BreedingInfo& r);
extern void from_json(const nlohmann::json& j, AttributeInfo& r);
extern void from_json(const nlohmann::json& j, AIInfo& r);
extern void from_json(const nlohmann::json& j, GraphicsInfo& r);


}
