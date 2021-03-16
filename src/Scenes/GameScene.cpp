#include "Scenes/GameScene.hpp"


GameScene::GameScene(sf::RenderWindow &window) : window(window), tilemanager(16) {
    tilemanager.load("../assets/images/Characters/Player0.png");
    const auto player = registry.create();
    registry.emplace<position>(player, 5.f, 5.f);
    registry.emplace<render_tile>(player, 10);

}

void GameScene::handleEvent(sf::Event e) {
    
}

void GameScene::update(float dt) {
    
}

#include <iostream>
void GameScene::render() {
    
    // Draw all tiles with a position and renderable tile
    auto view = registry.view<const position, const render_tile>();
    for(auto [entity, pos, t] : view.each()) {
        tilemanager.draw(window, t.tile, pos.x, pos.y);
    }
}