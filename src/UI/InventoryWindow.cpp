#include "UI/InventoryWindow.hpp"


InventoryWindow::InventoryWindow() {
    x = 0;
    y = 0;
    
    visible = false;
    dragging = false;

    inv_slot.setFillColor(sf::Color(80, 80, 80, 240));
    inv_slot.setOutlineThickness(2.0f);
    inv_slot.setOutlineColor(sf::Color(100, 100, 100));
    inv_slot.setSize(sf::Vector2f(SLOT_SIZE, SLOT_SIZE));
    
    inv_back.setFillColor(sf::Color(40, 40, 40, 250));
    inv_back.setOutlineThickness(2.0f);
    inv_back.setOutlineColor(sf::Color(0, 0, 0));
    inv_back.setSize(sf::Vector2f(SLOT_MARGIN + ((SLOT_MARGIN + SLOT_SIZE)*INV_WRAP), SLOTS_Y + ((SLOT_MARGIN + SLOT_SIZE) * (INV_SIZE / INV_WRAP))));
    
    inv_bar.setFillColor(sf::Color(50, 50, 50, 250));
    inv_bar.setOutlineThickness(2.0f);
    inv_bar.setOutlineColor(sf::Color(0, 0, 0));
    inv_bar.setSize(sf::Vector2f(SLOT_MARGIN + ((SLOT_MARGIN + SLOT_SIZE)*INV_WRAP), 30));
}

void InventoryWindow::handleEvent(sf::Event e) {
    if(e.type == sf::Event::KeyPressed) {
        if(e.key.code == sf::Keyboard::Tab) {
            visible = !visible;
        }
    } else if(e.type == sf::Event::MouseButtonPressed) {
        if(inv_back.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {
            if(e.mouseButton.y <  y + 30) {
                dragpos.x = e.mouseButton.x - x;
                dragpos.y = e.mouseButton.y - y;
                dragging = true;
            }
        }
    } else if(e.type == sf::Event::MouseButtonReleased) {
        dragging = false;
    } else if(e.type == sf::Event::MouseMoved) {
        if(dragging) {
            // x = e.mouseButton.x - dragpos.x;
            // y = e.mouseButton.y - dragpos.y;
            x = e.mouseMove.x - dragpos.x;
            y = e.mouseMove.y - dragpos.y;
            inv_back.setPosition(x, y);
            inv_bar.setPosition(x, y);
        }
    }
    
}

void InventoryWindow::render(sf::RenderTarget &target) {
    if(!visible) {
        return;
    }
    
    target.draw(inv_back);
    target.draw(inv_bar);

    int y_off = 0;
    int x_off = 0;
    for(int i = 0; i < INV_SIZE; i++) {
        if(x_off == INV_WRAP) {
            y_off++;
            x_off = 0;
        }
        inv_slot.setPosition(x + SLOT_MARGIN + (x_off * (SLOT_SIZE + SLOT_MARGIN)), y + SLOTS_Y + (y_off * (SLOT_SIZE + SLOT_MARGIN)));
        target.draw(inv_slot);
        x_off++;
    }
}