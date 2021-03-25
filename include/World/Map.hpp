#pragma once

#include <vector>
#include "Resources/TextureLoader.hpp"

//NOTE: look into OPENGL map rendering on the GPU: https://old.reddit.com/r/gamedev/comments/3y1va8/sdl2_c_tile_map_most_efficient_way_to_render_lots/cy9yyin/

class Map { //NOTE: maybe should implement some kind of chunk system for larger maps
    public:
        Map(TextureKey texturekey, texture_cache &tcache);
        ~Map();
        void addLayer(std::vector<std::vector<int>> layer);

        void setCollisionMap(std::vector<std::vector<bool>> map);
        bool checkCollision(int x, int y);
        
        void drawTiles(sf::RenderTarget &target);
        
        void updateTextures();
        void draw(sf::RenderTarget &target);
        
        void drawCollisionMap(sf::RenderTarget &target);
    private:
        // Layer - Column - Row
        std::vector<std::vector<std::vector<int>>> map_data;
        std::vector<std::vector<bool>> collision_map;
        
        std::vector<sf::Texture> map_textures;
        
        TextureKey texturekey;
        texture_cache &tcache;
};