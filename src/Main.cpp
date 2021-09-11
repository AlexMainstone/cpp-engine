#include <SFML/Graphics.hpp>
#include "Scenes/GameScene.hpp"

void main() {
    //TODO load window settings
    
    // Create Window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "cpp-engine");
    bool fullscreen = false;
    
    // TODO abstract scene class
    GameScene *scene = new GameScene(window);
    
    // Clock that counts time between updates
    sf::Clock delta_clock;

    while(window.isOpen()) {
        // Handle Events
        sf::Event e;
        while(window.pollEvent(e)) {
            // Check if window closed
            if(e.type == sf::Event::Closed) {
                window.close();
            } if(e.type == sf::Event::KeyPressed) {
                if(e.key.code == sf::Keyboard::Enter && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    if(fullscreen) {
                        window.create(sf::VideoMode::getDesktopMode(), "cpp-engine");
                        scene->resize(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
                    } else {
                        window.create(sf::VideoMode::getFullscreenModes()[0], "cpp-engine", sf::Style::Fullscreen);
                        scene->resize(sf::VideoMode::getFullscreenModes()[0].width, sf::VideoMode::getFullscreenModes()[0].height);
                    }
                    fullscreen =  !fullscreen;
                }
            }
            // Pass Event to scene
            scene->handleEvent(e);
        }
        
        // Update & restart clock
        scene->update(delta_clock.restart().asSeconds());
        
        // Render
        window.clear(sf::Color(20,12,28));
        scene->render();
        window.display();
    }
    
    delete scene;
}