#include "genesis/game/Species.hpp"

namespace genesis {

void from_json(const nlohmann::json& j, SpeciesInfo& r) {
    j.at("name").get_to(r.name);
    j.at("_id").get_to(r._id);

    if (j.contains("graphics")) {
        j.at("graphics").get_to(r.graphics);
    }
    if (j.contains("attributes")) {
        j.at("attributes").get_to(r.biologicalAttribBias);
    }
    if (j.contains("ai")) {
        j.at("ai").get_to(r.aiDetails);
    }
    if (j.contains("behaviourTraits")) {
        j.at("behaviourTraits").get_to(r.behaviourTraits);
    }
    if (j.contains("physicalTraits")) {
        j.at("behaviourTraits").get_to(r.physicalTraits);
    }
    // NOTE: this must always be last. obj->parent() depends on all parent init
    // being done prior to the function call. Or at least the parts of the data
    // that get copied
    if (j.contains("subspecies")) {
        for (auto& species : j.at("subspecies")) {
            auto obj = std::make_shared<SpeciesInfo>();
            obj->parent(r);

            species.get_to(*obj);
            obj->_parentId = r._id;
            r.subspecies.push_back(obj);
        }
    }

}

void from_json(const nlohmann::json& j, GraphicsInfo& r) {
    if (j.contains("static")) {
        r.isStatic = true;
        j.at("static").get_to(r.source);
    } else {
        r.isStatic = j.value("isStatic", false);
        j.at("source").get_to(r.source);
    }
}

void from_json(const nlohmann::json& j, AttributeInfo& r) {
    // TODO: figure out if 0 as the default value makes sense
    r.stealth = j.value("stealth", 0);
    r.intelligence = j.value("intelligence", 0);
    r.agility = j.value("agility", 0);
    
}

void from_json(const nlohmann::json& j, AIInfo& r) {
    j.at("aggressive").get_to(r.isAggressive);
    j.at("intelligent").get_to(r.isIntelligent);
}

}
