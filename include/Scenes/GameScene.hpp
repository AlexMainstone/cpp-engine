#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "Components/BasicComponents.hpp"
#include "Resources/TileManager.hpp"
#include "Resources/MapLoader.hpp"
#include "Resources/TextureLoader.hpp"
#include "System/ControllerSystem.hpp"
#include "System/EnemySystem.hpp"

class GameScene {
    public:
        GameScene(sf::RenderWindow &window);
        ~GameScene();
        
        void handleEvent(sf::Event e);
        void update(float dt);
        void render();
    private:
        sf::RenderWindow &window;
        
        entt::registry registry;
        
        TileManager tilemanager;
        
        Map *map;
        
        ControllerSystem *control_system;
        EnemySystem *enemy_system;
        
        texture_cache tcache{};
};