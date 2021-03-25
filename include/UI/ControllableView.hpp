#pragma once

#include <SFML/Graphics.hpp>

class ControllableView {
    public:
        ControllableView(sf::View v);
        
        void handleEvent(sf::Event e, sf::RenderWindow &window);
        
        sf::View getView();
    private:
        sf::View view;
        bool dragging;
        sf::Vector2f drag_pos;
        
        float zoom;
};