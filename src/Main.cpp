#include <SFML/Graphics.hpp>
#include "Scenes/GameScene.hpp"

void main() {
    //TODO load window settings
    
    // Create Window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "cpp-engine");
    
    // TODO abstract scene class
    GameScene scene(window);
    
    // Clock that counts time between updates
    sf::Clock delta_clock;

    while(window.isOpen()) {
        // Handle Events
        sf::Event e;
        while(window.pollEvent(e)) {
            // Check if window closed
            if(e.type == sf::Event::Closed) {
                window.close();
            }
            
            // Pass Event to scene
            // scene->handleEvent(e);
        }
        
        // Update & restart clock
        // scene->update(delta_clock.restart().asSeconds());
        
        // Render
        window.clear();
        // scene->render();
        window.display();
    }
}