#include "System/ControllerSystem.hpp"

ControllerSystem::ControllerSystem(entt::registry &reg, Map *map, sf::RenderWindow &window) : reg(reg) {
    game_view = window.getView();
    game_view.zoom(0.25);
    
    this->map = map;
    
    moving = false;
    turn_progress = 0;
    player_turn = true;
}

bool ControllerSystem::isPlayerTurn() {
    return player_turn;
}

void ControllerSystem::setPlayerTurn(bool turn) {
    player_turn = turn;
}

void ControllerSystem::update(float dt) {

    
    // TODO: maybe handle the camera & multiple controlled entities
    if(moving) {
        // move progress
        float prev_progress = turn_progress;
        turn_progress += 8 * dt;
        if(turn_progress >= 1) {
            moving = false;
            turn_progress = 1;
            auto view = reg.view<position, const controlled>();
            for(auto [entity, pos, cntrl] : view.each()) {
                game_view.setCenter(pos.x * 16 + 8, pos.y * 16 + 8);
                pos.x -= prev_progress * (float)pos.target_x;
                pos.y -= prev_progress * (float)pos.target_y;
                pos.x += turn_progress * (float)pos.target_x;
                pos.y += turn_progress * (float)pos.target_y;
                pos.x = std::round(pos.x);
                pos.y = std::round(pos.y);
            }
            return;
        }
        
        // Move all controllables and set camera pos
        auto view = reg.view<position, const controlled>();
        for(auto [entity, pos, cntrl] : view.each()) {
            game_view.setCenter(pos.x * 16 + 8, pos.y * 16 + 8);
            pos.x -= prev_progress * (float)pos.target_x;
            pos.y -= prev_progress * (float)pos.target_y;
            pos.x += turn_progress * (float)pos.target_x;
            pos.y += turn_progress * (float)pos.target_y;
        }
    }
}

bool ControllerSystem::solidEntity(int x, int y) {
    auto view = reg.view<position, solid>();
    for(auto [entity, position] : view.each()) {
        if(position.x == x && position.y == y) {
            if(reg.any_of<interactable>(entity)) {
                // TODO interact
            }else if(reg.any_of<enemy>(entity)) {
                auto c = reg.get<creature>(entity);
                c.hp -= 1;
                if(c.hp <= 0) {
                    reg.destroy(entity);
                }
            }
            return true;
        }
    }
    return false;
}

void ControllerSystem::handleEvent(sf::Event e) {
    if(player_turn && e.type == sf::Event::KeyPressed && !moving) {
        if(e.key.code == sf::Keyboard::W) {
            move(0, -1);
        }else if(e.key.code == sf::Keyboard::A) {
            move(-1, 0);
        }else if(e.key.code == sf::Keyboard::S) {
            move(0, 1);
        }else if(e.key.code == sf::Keyboard::D) {
            move(1, 0);
        }
    }
}

void ControllerSystem::move(int x, int y) {
    moving = true;
    player_turn = false; // Sets the player turn to false    
    turn_progress = 0;
    auto view = reg.view<position, const controlled>();
    for(auto [entity, pos, cntrl] : view.each()) {
        if (map->checkCollision(pos.x + x, pos.y + y) | solidEntity(pos.x + x, pos.y + y)) {
            moving = false;
            pos.target_x = 0;
            pos.target_y = 0;
            continue;
        }
        pos.target_x = x;
        pos.target_y = y;
    }
}

sf::View ControllerSystem::getView() {
    return game_view;
}