#pragma once

#include <map>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace genesis {

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
