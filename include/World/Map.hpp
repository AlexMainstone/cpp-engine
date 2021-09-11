#pragma once

#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <utility>
#include <map>

#include "Resources/TextureLoader.hpp"

//NOTE: look into OPENGL map rendering on the GPU: https://old.reddit.com/r/gamedev/comments/3y1va8/sdl2_c_tile_map_most_efficient_way_to_render_lots/cy9yyin/

struct Node {
    Node *parent;
    int x, y;
    float f, g, h;
    
    Node(int x, int y, float g, float h, Node *parent = nullptr) : x(x), y(y), g(g), h(h), parent(parent) {
        f = g + h;
    }
};

class Map { //NOTE: maybe should implement some kind of chunk system for larger maps
    public:
        Map(TextureKey texturekey, texture_cache &tcache);
        ~Map();
        void addLayer(std::vector<std::vector<int>> layer);

        void setCollisionMap(std::vector<std::vector<int>> map);
        int checkCollision(int x, int y);
        
        void updateTextures();
        void draw(sf::RenderTarget &target, const sf::RenderStates &states = sf::RenderStates::Default);
        
        void drawCollisionMap(sf::RenderTarget &target);
        
        std::list<sf::Vector2i> astar(sf::Vector2i start, sf::Vector2i end);
        bool raycast(int startx, int starty, int endx, int endy);
    private:
        float heuristic(sf::Vector2i start, sf::Vector2i end);
        std::vector<sf::Vector2i> neighbors(int x, int y);
        // Layer - Column - Row
        std::vector<std::vector<std::vector<int>>> map_data;
        std::vector<std::vector<int>> collision_map;
        
        std::vector<sf::Texture> map_textures;
        
        TextureKey texturekey;
        texture_cache &tcache;
};