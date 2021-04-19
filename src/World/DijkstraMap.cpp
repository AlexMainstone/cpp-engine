#include "World/DijkstraMap.hpp"

#include<iostream>
void DijkstraMap::generate(Map *map, int x, int y, int range) {
    src_x = x;
    src_y = y;

    // Initialize vector
    djk_map.resize(range * 2 + 1);
    for(auto &i : djk_map) {
        i.resize(range*2 + 1);
        std::fill(i.begin(), i.end(), 10000);
    }
    
    // Get the centre of the 2d array
    int vec_centre = std::ceil((range*2+1)/2);
    djk_map[vec_centre][vec_centre] = 0;
    
    bool changes;
    do{
        changes = false;

        for(int x = 0; x < djk_map.size(); x++) {
            for(int y = 0; y < djk_map[0].size(); y++) {
                //TODO set each cell to one above its smallest neighbor
                // if a change was made set changes to true
            }
        }
        
    }while(changes);
}

std::vector<sf::Vector2i> DijkstraMap::neighbors(int x, int y) {
    std::vector<sf::Vector2i> out;

    out.push_back(sf::Vector2i(x - 1, y - 1));
    out.push_back(sf::Vector2i(x - 1, y + 1));
    out.push_back(sf::Vector2i(x - 1, y));
    
    out.push_back(sf::Vector2i(x, y - 1));
    out.push_back(sf::Vector2i(x, y + 1));

    out.push_back(sf::Vector2i(x + 1, y - 1));
    out.push_back(sf::Vector2i(x + 1, y + 1));
    out.push_back(sf::Vector2i(x + 1, y));

    return out;
}