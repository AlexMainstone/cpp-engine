#include "Scenes/GameScene.hpp"

GameScene::GameScene(sf::RenderWindow &window) : window(window), tilemanager(16) {
    MapLoader maploader;
    map = maploader.load("../assets/DawnLike/Examples/Dungeon.tmx");

    tilemanager.load("../assets/DawnLike/Characters/Player0.png");
    const auto player = registry.create();
    registry.emplace<position>(player, 5.f, 5.f);
    registry.emplace<render_tile>(player, 10);

    // Zoom
    sf::View v = window.getView();
    v.zoom(0.5);
    v.setCenter(0, 0);
    window.setView(v);
}

void GameScene::handleEvent(sf::Event e) {
    
}

void GameScene::update(float dt) {
    
}

void GameScene::render() {
    map->draw(window);
    
    // Draw all tiles with a position and renderable tile
    auto view = registry.view<const position, const render_tile>();
    for(auto [entity, pos, t] : view.each()) {
        tilemanager.draw(window, t.tile, pos.x * tilemanager.getTileSize(), pos.y * tilemanager.getTileSize());
    }
}