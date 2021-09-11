#pragma once

#include<SFML/Graphics.hpp>

const int INV_SIZE = 32;
const int INV_WRAP = 8;

struct Item {
    int tile;
};

class InventoryWindow {
    public:
        InventoryWindow();
        void handleEvent(sf::Event e);
        void render(sf::RenderTarget &target);
    private:
        int x, y;
        
        sf::RectangleShape inv_back;
        sf::RectangleShape inv_bar;

        const int SLOT_SIZE = 44;
        const int SLOT_MARGIN = 8;
        const int SLOTS_Y = 100;
        sf::RectangleShape inv_slot;
        Item *items[INV_SIZE];
        
        bool visible;
        sf::Vector2i dragpos;
        bool dragging;
        
};