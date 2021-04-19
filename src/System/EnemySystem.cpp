#include "System/EnemySystem.hpp"

EnemySystem::EnemySystem(entt::registry &reg, Map *map) : reg(reg), map(map) {
    moving = false; 
    turn_progress = 0.0f;
}

void EnemySystem::update(float dt) {
    if(moving) {
        // move progress
        float prev_progress = turn_progress;
        turn_progress += 8 * dt;
        if(turn_progress >= 1) {
            moving = false;
            turn_progress = 1;
            auto view = reg.view<position, const enemy>();
            for(auto [entity, pos, enemy] : view.each()) {
                pos.x -= prev_progress * (float)pos.target_x;
                pos.y -= prev_progress * (float)pos.target_y;
                pos.x += turn_progress * (float)pos.target_x;
                pos.y += turn_progress * (float)pos.target_y;
                pos.x = std::round(pos.x);
                pos.y = std::round(pos.y);
            }
            return;
        }
        
        // Move all controllables 
        auto view = reg.view<position, const enemy>();
        for(auto [entity, pos, enemy] : view.each()) {
            pos.x -= prev_progress * (float)pos.target_x;
            pos.y -= prev_progress * (float)pos.target_y;
            pos.x += turn_progress * (float)pos.target_x;
            pos.y += turn_progress * (float)pos.target_y;
        }
    }
}

void EnemySystem::takeTurn() {

    auto view = reg.view<position, enemy>();
    auto cntrlview = reg.view<position, const controlled>();
    for(auto [entity, position, enemy] : view.each()) {
        for(auto [cntrlEntity, cntrlPosition, cntrl] : cntrlview.each()) {
            int truepos_x = std::round(cntrlPosition.x) + cntrlPosition.target_x;
            int truepos_y = std::round(cntrlPosition.y) + cntrlPosition.target_y;
            if(!map->raycast(position.x, position.y, truepos_x, truepos_y)) { //Check if a controlled entity is spottedr
                enemy.state = ENEMY_STATE::SPOTTED;
                enemy.spotted_x = truepos_x;
                enemy.spotted_y = truepos_y;
                break;
            } else if(enemy.state == ENEMY_STATE::SPOTTED) { // If can't spot entity anymore
                enemy.state = ENEMY_STATE::LAST_KNOWN;
            }
        }
        
        if(enemy.state == ENEMY_STATE::IDLE) {
            // TODO the enemy probably should do something while idling
            continue;
        }
        
        // Pathfind to target
        auto target_path = map->astar(sf::Vector2i(position.x, position.y), sf::Vector2i(enemy.spotted_x, enemy.spotted_y));
        if((target_path.size() <= 2 && enemy.state == ENEMY_STATE::SPOTTED) || (target_path.size() <= 1 && enemy.state == ENEMY_STATE::LAST_KNOWN)) { // if there are 2 items in the list, then there is only the start and end node.
            continue;
        }
        target_path.pop_front(); // remove start node
        position.target_x = target_path.front().x - position.x;
        position.target_y = target_path.front().y - position.y;
        moving = true;
        turn_progress = 0.0f;
    }
}