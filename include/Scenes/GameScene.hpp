#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "Components/BasicComponents.hpp"
#include "Resources/TileManager.hpp"
#include "Resources/MapLoader.hpp"
#include "Resources/TextureLoader.hpp"
#include "System/ControllerSystem.hpp"
#include "System/EnemySystem.hpp"

#include "UI/DialogueWindow.hpp"
#include "UI/InventoryWindow.hpp"
#include "Resources/DialogueScript.hpp"

class GameScene {
    public:
        GameScene(sf::RenderWindow &window);
        ~GameScene();
        
        void handleEvent(sf::Event e);
        void update(float dt);
        void render();
        void resize(int w, int h);
    private:
        sf::RenderWindow &window;
        
        entt::registry registry;
        
        TileManager tilemanager;
        
        Map *map;
        
        DialogueWindow *dialogue_window;
        
        ControllerSystem *control_system;
        EnemySystem *enemy_system;
        
        texture_cache tcache{};
        
        sf::View ui_view;
        
        DialogueScript dscript;
        
        InventoryWindow invwindow;
        
};