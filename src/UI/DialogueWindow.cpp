#include "UI/DialogueWindow.hpp"

DialogueWindow::DialogueWindow(sf::RenderWindow &window) {
    background_shape.setSize(sf::Vector2f(500, window.getSize().y));
    background_shape.setPosition(50, 0);
    background_shape.setFillColor(sf::Color(50, 50, 50, 240));
    background_shape.setOutlineColor(sf::Color(20, 20, 20, 225));
    background_shape.setOutlineThickness(8.f);
    
    
    font.loadFromFile("../assets/fonts/Silver.ttf");
    name_text.setFont(font);
    name_text.setCharacterSize(36);
    name_text.setOutlineColor(sf::Color::White);
    name_text.setOutlineThickness(1.f);
    name_text.setStyle(sf::Text::Bold);
    
    true_text.setFont(font);
    true_text.setCharacterSize(34);
    true_text.setLineSpacing(0.75);

    visible = false;
    
    selected = 0;
}

void DialogueWindow::clearOptions() {
    dialogue_option.clear();
}

int DialogueWindow::getSelected() {
    int out = selected;
    selected = 0;
    return out;
}

void DialogueWindow::jumpToEnd() {
    int y = scroll;
    for(auto i : dialogue_items) {
        name_text.setFillColor(i.name_color);
        name_text.setPosition(60, y + 10);
        name_text.setString(i.name + ":");
        
        true_text.setPosition(60, y + 10 + name_text.getGlobalBounds().height + 5);
        true_text.setString(i.text);
        y = true_text.getGlobalBounds().top + true_text.getGlobalBounds().height;
    }
    
    for(auto &i : dialogue_option) {
        i.setPosition(60, y + 10);
        y = i.getGlobalBounds().top + i.getGlobalBounds().height;
    }
    height = y - scroll;
    
    height = y - scroll;
    if(height >= 700) {
        scroll = -height + 700;
        scroll = std::max(std::min(0, scroll), -height + 700);
    } else {
        scroll = 0;
    }
}

void DialogueWindow::resize(int w, int h) {
    background_shape.setSize(sf::Vector2f(500, h));
    //TODO change jumpto position
}

void DialogueWindow::addText(std::string name, std::string text, sf::Color name_color) {
    std::istringstream iss(text);
    std::string ctext = "";
    iss >> ctext;
    do {
        std::string word;
        iss >> word;
        true_text.setString(ctext + " " + word);
        if(true_text.getGlobalBounds().width >= 480) {
            ctext += "\n" + word;
        } else {
            ctext += " " + word;
        }
    }while(iss);
    
    DialogueItem item;
    item.name_color = name_color;
    item.name = name;
    item.text = ctext;
    dialogue_items.push_back(item);
}

void DialogueWindow::addOption(std::string option) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(34);
    text.setFillColor(sf::Color(216, 143, 17));
    text.setLineSpacing(0.75);
    
    // wrap text
    std::istringstream iss(std::to_string(dialogue_option.size() + 1) + ". " + option);
    std::string ctext = "";
    iss >> ctext;
    do {
        std::string word;
        iss >> word;
        text.setString(ctext + " " + word);
        if(text.getGlobalBounds().width >= 480) {
            ctext += "\n" + word;
        } else {
            ctext += " " + word;
        }
    }while(iss);
    text.setString(ctext);

    dialogue_option.push_back(text);
}

void DialogueWindow::setVisible(bool v) {
    visible = v;
}

void DialogueWindow::addTexti(std::string name, std::string text, int r, int g, int b) {
    addText(name, text, sf::Color(r,g,b));
}

void DialogueWindow::handleEvent(sf::Event e) {
    if(!visible) {
        return;
    }

    if(e.type == sf::Event::MouseMoved) {
        for(int i = 0; i < dialogue_option.size(); i++) {
            if(dialogue_option[i].getGlobalBounds().contains(e.mouseMove.x, e.mouseMove.y)) {
                dialogue_option[i].setFillColor(sf::Color(116, 43, 0));
            } else {
                dialogue_option[i].setFillColor(sf::Color(216, 143, 17));
            }
        }
    } else if(e.type == sf::Event::MouseWheelScrolled) {
        if(height >= 700) {
            scroll += 50 * e.mouseWheelScroll.delta;
            scroll = std::max(std::min(0, scroll), -height + 700);
        }
        
    } else if(e.type == sf::Event::MouseButtonPressed) {
        for(int i = 0; i < dialogue_option.size(); i++) {
            if(dialogue_option[i].getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {
                addText("You", dialogue_option[i].getString().substring(3, dialogue_option[i].getString().getSize()), sf::Color(150,150,150));
                jumpToEnd();
                selected = i + 1;
            }
        }
    }
}

void DialogueWindow::render(sf::RenderTarget &target) {
    if(!visible) {
        return;
    }

    target.draw(background_shape);

    int y = scroll;
    for(auto i : dialogue_items) {
        name_text.setFillColor(i.name_color);
        name_text.setPosition(60, y + 10);
        name_text.setString(i.name + ":");
        
        true_text.setPosition(60, y + 10 + name_text.getGlobalBounds().height + 5);
        true_text.setString(i.text);
        
        if(true_text.getGlobalBounds().top + true_text.getGlobalBounds().height > 0) {
            target.draw(name_text);
            target.draw(true_text);
        }
        y = true_text.getGlobalBounds().top + true_text.getGlobalBounds().height;
    }
    
    for(auto &i : dialogue_option) {
        i.setPosition(60, y + 10);
        target.draw(i);
        y = i.getGlobalBounds().top + i.getGlobalBounds().height;
    }
    height = y - scroll;
}