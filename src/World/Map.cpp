#include "World/Map.hpp"

Map::Map(TileManager *manager) {
    this->tile_manager = manager;
}

void Map::addLayer(std::vector<std::vector<int>> layer) {
    map_data.push_back(layer);
}

void Map::draw(sf::RenderTarget &target) {
    for(int z = 0; z < map_data.size(); z++) {
        for(int x = 0; x < map_data[z].size(); x++) {
            for(int y = 0; y < map_data[z][x].size(); y++) {
                tile_manager->draw(target, map_data[z][x][y], x*16, y*16);
            }
        }
    }
}