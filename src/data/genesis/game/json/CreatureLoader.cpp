#include "genesis/game/Creature.hpp"

namespace genesis {

void from_json(const nlohmann::json& j, CreatureInfo& r) {
    j.at("name").get_to(r.name);
    j.at("plural").get_to(r.plural);
    r.adjective = j.value("adjective", r.name);

    j.at("graphics").get_to(r.graphics);
    j.at("ai").get_to(r.aiDetails);
    j.at("breeding").get_to(r.breedingInfo);
    j.at("attributes").get_to(r.biologicalSkillBias);
}

void from_json(const nlohmann::json& j, ReproductionType& r) {
    auto string = j.get<std::string>();
    if (string == "mammalian") {
        r = ReproductionType::MAMMALIAN;
    } else {
        throw std::runtime_error("Invalid reproduction type: " + string);
    }
}

void from_json(const nlohmann::json& j, BreedingInfo& r) {
    if (j.is_null()) {
        r.infertile = false;
        r.agender = true;
        return;
    }
    r.compatibleCreatures = j.value("compatibleWith", std::vector<std::string>{});
    j.at("infertile").get_to(r.infertile);
    r.agender = j.value("agender", true);
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

void from_json(const nlohmann::json& j, SkillInfo& r) {
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
