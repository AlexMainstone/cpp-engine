#pragma once

#include <vector>
#include <queue>

#include "World/Map.hpp"

class DijkstraMap {
    public:
        void generate(Map *map, int x, int y, int range);
    private:
        std::vector<sf::Vector2i> neighbors(int x, int y);
        int src_x, src_y;
        std::vector<std::vector<int>> djk_map;
};