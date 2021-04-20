#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>

struct DialogueItem {
    sf::Color name_color;
    std::string name;
    std::string text;
};

class DialogueWindow {
    public:
        DialogueWindow(sf::RenderWindow &window);

        void handleEvent(sf::Event e);
        
        void addText(std::string name, std::string text, sf::Color name_color = sf::Color::White);
        void addOption(std::string option);
        void jumpToEnd();
        
        void render(sf::RenderTarget &target);
    private:
        sf::RectangleShape background_shape;
        
        sf::Font font;
        sf::Text name_text;
        sf::Text true_text;
        
        std::vector<DialogueItem> dialogue_items;
        std::vector<sf::Text> dialogue_option;
        
        int scroll, height;
};