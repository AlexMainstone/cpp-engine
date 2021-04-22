#include "Scenes/GameScene.hpp"

GameScene::GameScene(sf::RenderWindow &window) : window(window), dialogue_window(new DialogueWindow(window)), tilemanager(16), dscript(dialogue_window) {
    // tcache.load<texture_loader>(entt::hashed_string{"name"}, "/path");
    
    MapLoader maploader;
    map = maploader.load("../assets/DawnLike/Examples/Dungeon.tmx", tcache);
    map->astar(sf::Vector2i(2, 2), sf::Vector2i(11, 11));
    map->raycast(1, 1, 8, 11);
    
    control_system = new ControllerSystem(registry, map, window);

    tilemanager.load("../assets/DawnLike/Characters/Player0.png");
    const auto player = registry.create();
    registry.emplace<position>(player, 3.f, 3.f, 0, 0);
    registry.emplace<render_tile>(player, 10);
    registry.emplace<controlled>(player);
    
    enemy_system = new EnemySystem(registry, map);
    
    const auto enmy = registry.create();
    registry.emplace<position>(enmy, 11.0f, 13.0f, 0, 0);
    registry.emplace<render_tile>(enmy, 11);
    registry.emplace<enemy>(enmy);
    registry.emplace<creature>(enmy, 1, 1);
    registry.emplace<solid>(enmy);
    
    ui_view = window.getView();

    dscript.load("../assets/scripts/test.lua");
}

GameScene::~GameScene() {
    delete map;
    delete control_system;
    delete enemy_system;
}

void GameScene::handleEvent(sf::Event e) {
    control_system->handleEvent(e);
    dialogue_window->handleEvent(e);
}

void GameScene::update(float dt) {
    control_system->update(dt);
    
    if(!control_system->isPlayerTurn()) {
        enemy_system->takeTurn();
        control_system->setPlayerTurn(true);
    }
    enemy_system->update(dt);
    
    dscript.update(dt);
}

void GameScene::render() {
    window.setView(control_system->getView());
    map->draw(window);
    
    // Draw all tiles with a position and renderable tile
    auto view = registry.view<const position, const render_tile>();
    for(auto [entity, pos, t] : view.each()) {
        tilemanager.draw(window, t.tile, pos.x * tilemanager.getTileSize(), pos.y * tilemanager.getTileSize());
    }
    
    window.setView(ui_view);
    dialogue_window->render(window);
}