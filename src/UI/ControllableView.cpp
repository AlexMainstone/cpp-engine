#include "UI/ControllableView.hpp"

ControllableView::ControllableView(sf::View v) {
    view.setCenter(v.getCenter());
    view.setSize(v.getSize());
    dragging = false;
}

void ControllableView::handleEvent(sf::Event e, sf::RenderWindow &window) {
    if(e.type == sf::Event::MouseButtonPressed) {
        if(e.mouseButton.button == sf::Mouse::Middle) {
            dragging = true;
            drag_pos = window.mapPixelToCoords(sf::Vector2i(e.mouseButton.x, e.mouseButton.y), view);
        }
    } else if(e.type == sf::Event::MouseButtonReleased) {
        if(e.mouseButton.button == sf::Mouse::Middle) {
            dragging = false;
        }
    } else if(e.type == sf::Event::MouseMoved) {
        sf::Vector2i cursorpos;
        cursorpos.x = e.mouseMove.x;
        cursorpos.y = e.mouseMove.y;
        if(dragging) {
            sf::Vector2f world_cursor = window.mapPixelToCoords(cursorpos, view);
            view.setCenter(view.getCenter() + (drag_pos - world_cursor));
        }
    } else if(e.type == sf::Event::MouseWheelScrolled) {
        view.zoom(1 + (0.1 * e.mouseWheelScroll.delta));
    }
}

sf::View ControllableView::getView() {
    return view;
}