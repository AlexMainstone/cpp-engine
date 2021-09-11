#pragma once

#include <entt/entt.hpp>

#include "World/Map.hpp"

class ChemistrySystem {
    public:
        ChemistrySystem(entt::registry &reg, Map &map);
        void update(float dt);
    private:
        entt::registry &reg;
        Map &map;
    
};