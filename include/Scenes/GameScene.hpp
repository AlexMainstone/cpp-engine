#pragma once

#include <SFML/Graphics.hpp>
// #include <entt/entt.hpp>

class GameScene {
    public:
        GameScene(sf::RenderWindow &window);
        
        void handleEvent(sf::Event e);
        void update(float dt);
        void render();
    private:
        sf::RenderWindow &window;
};