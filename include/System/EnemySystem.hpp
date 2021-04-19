#pragma once

#include <entt/entt.hpp>

#include "World/Map.hpp"
#include "Components/BasicComponents.hpp"

class EnemySystem {
    public:
        EnemySystem(entt::registry &reg, Map *map);
        void update(float dt);
        void takeTurn();
    private:
        entt::registry &reg;
        Map *map;
        
        bool moving;
        float turn_progress;
};