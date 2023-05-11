#pragma once

#include "genesis/game/util/Name.hpp"
#include "Traits.hpp"

#include "nlohmann/detail/macro_scope.hpp"
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
    bool isSpriteSheet = false;
    std::string rowSelector = "", colSelector = "";
};



/**
 * Key structure for defining a class of species.
 */
// This feels a bit too memory-intensive for subspecies. Not right now, but as the amount of data grows,
// there's going to be a lot to keep track of, particularly for subspecies that don't override everything.
// All the data has to be duplicated a few too many times for my taste.
// On the other hand, I doubt this will ever use so much RAM that it matters. Future me problem
struct SpeciesInfo {
    /**
     * Backreference to the species ID. This isn't provided as part of the object itself, but is sourced
     * from the species key.
     *
     * This ID is primarily used for internal management.
     * This ID cannot be overridden in the JSON itself. It is always set to the key.
     * This detail will lead to conflicts on species with the same ID, but the solution to that is fairly simple:
     * prefix the ID with a namespace if it's outside the vanilla namespace.
     */
    std::string _id;
    /**
     * Only defined for subspecies; name of the parent species.
     */
    std::string _parentId;

    Name name;
    AIInfo aiDetails;

    // May only be defined in subspecies, if relevant.
    AttributeInfo biologicalAttribBias;
    GraphicsInfo graphics;

    BehaviourTraits behaviourTraits;
    PhysicalTraits physicalTraits;
    std::vector<std::shared_ptr<SpeciesInfo>> subspecies;

    void parent(const SpeciesInfo& p) {
        this->_parentId = p._id;
        this->aiDetails = p.aiDetails;
        this->biologicalAttribBias = p.biologicalAttribBias;
        this->behaviourTraits = p.behaviourTraits;
        this->physicalTraits = p.physicalTraits;
    }

};

extern void from_json(const nlohmann::json& j, SpeciesInfo& r);
extern void from_json(const nlohmann::json& j, AttributeInfo& r);
extern void from_json(const nlohmann::json& j, AIInfo& r);
extern void from_json(const nlohmann::json& j, GraphicsInfo& r);

NLOHMANN_JSON_SERIALIZE_ENUM(ReproductionType, {
    {ReproductionType::MAMMALIAN, "mammalian"},
});

}
