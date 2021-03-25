#include "World/Map.hpp"

Map::Map(TileManager *manager) {
    this->tile_manager = manager;
}

Map::~Map() {
    delete tile_manager;
}

void Map::addLayer(std::vector<std::vector<int>> layer) {
    map_data.push_back(layer);
    map_textures.push_back(sf::Texture());
    updateTextures();
}

void Map::setCollisionMap(std::vector<std::vector<bool>> map) {
    collision_map = map;
}

bool Map::checkCollision(int x, int y) {
    return collision_map[x][y];
}

void Map::drawCollisionMap(sf::RenderTarget &target) {
    sf::RectangleShape shape;
    shape.setOutlineThickness(2.0);
    shape.setOutlineColor(sf::Color(255, 255, 255, 50));
    shape.setFillColor(sf::Color::Transparent);
    shape.setSize(sf::Vector2f(8,8));
    for(int x = 0; x < collision_map.size(); x++) {
        for(int y = 0; y < collision_map[x].size(); y++) {
            if(collision_map[x][y] != 0) {continue;}
            shape.setPosition(x*16 + 4,y*16 + 4);
            target.draw(shape);
        }
    }

}

void Map::updateTextures() {
    for(int z = 0; z < map_data.size(); z++) {
        sf::RenderTexture rtex;
        rtex.create(map_data[z].size() * 16, map_data[z][0].size() * 16);
        for(int x = 0; x < map_data[z].size(); x++) {
            for(int y = 0; y < map_data[z][x].size(); y++) {
                tile_manager->draw(rtex, map_data[z][x][y], x*16, y*16);
            }
        }
        
        rtex.display();
        map_textures[z] = rtex.getTexture();
    }
}

void Map::draw(sf::RenderTarget &target)  {
    sf::Sprite map_sprite;
    for(auto t : map_textures) {
        map_sprite.setTexture(t);
        target.draw(map_sprite);
    }
}

void Map::drawTiles(sf::RenderTarget &target) {
    for(int z = 0; z < map_data.size(); z++) {
        for(int x = 0; x < map_data[z].size(); x++) {
            for(int y = 0; y < map_data[z][x].size(); y++) {
                tile_manager->draw(target, map_data[z][x][y], x*16, y*16);
            }
        }
    }
}