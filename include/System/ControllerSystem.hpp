#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "Components/BasicComponents.hpp"
#include "World/Map.hpp"

class ControllerSystem {
    public:
        ControllerSystem(entt::registry &reg, Map *map, sf::RenderWindow &window);
        void update(float dt);
        void handleEvent(sf::Event e);
        bool isPlayerTurn();
        void setPlayerTurn(bool turn);
        
        sf::View getView();
    private:
        void move(int x, int y);
        entt::registry &reg;
        
        sf::View game_view;
        
        Map *map;
        
        //TODO: move these to a dedicated class, all entities will need it
        bool moving;
        float turn_progress;
        
        bool player_turn;
};