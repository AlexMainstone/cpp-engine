#pragma once

#include <vector>
#include "Resources/TileManager.hpp"

class Map {
    public:
        Map(TileManager *manager);
        void addLayer(std::vector<std::vector<int>> layer);
        
        void draw(sf::RenderTarget &target);
    private:
        // Layer - Column - Row
        std::vector<std::vector<std::vector<int>>> map_data;
        
        TileManager *tile_manager;
};