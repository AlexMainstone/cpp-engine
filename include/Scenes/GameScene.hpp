#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "Components/BasicComponents.hpp"
#include "Resources/TileManager.hpp"

class GameScene {
    public:
        GameScene(sf::RenderWindow &window);
        
        void handleEvent(sf::Event e);
        void update(float dt);
        void render();
    private:
        sf::RenderWindow &window;
        
        entt::registry registry;
        
        TileManager tilemanager;
};