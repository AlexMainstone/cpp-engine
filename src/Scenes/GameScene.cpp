#include "Scenes/GameScene.hpp"

GameScene::GameScene(sf::RenderWindow &window) : window(window), tilemanager(16) {
    // tcache.load<texture_loader>(entt::hashed_string{"name"}, "/path");

    MapLoader maploader;
    map = maploader.load("../assets/DawnLike/Examples/Dungeon.tmx", tcache);
    
    control_system = new ControllerSystem(registry, map, window);

    tilemanager.load("../assets/DawnLike/Characters/Player0.png");
    const auto player = registry.create();
    registry.emplace<position>(player, 3.f, 3.f, 0, 0);
    registry.emplace<render_tile>(player, 10);
    registry.emplace<controlled>(player);
    
}

GameScene::~GameScene() {
    delete map;
    delete control_system;
}

void GameScene::handleEvent(sf::Event e) {
    control_system->handleEvent(e);
}

void GameScene::update(float dt) {
    control_system->update(dt);
}

void GameScene::render() {
    window.setView(control_system->getView());
    map->draw(window);
    map->drawCollisionMap(window);
    
    // Draw all tiles with a position and renderable tile
    auto view = registry.view<const position, const render_tile>();
    for(auto [entity, pos, t] : view.each()) {
        tilemanager.draw(window, t.tile, pos.x * tilemanager.getTileSize(), pos.y * tilemanager.getTileSize());
    }
}