#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

struct SpriteSheet {
    int tile_count;
    int tiles_wide;
    sf::Texture texture;
    
    SpriteSheet(const char *path, int tile_size) {
        texture.loadFromFile(path);
        this->tile_count = (texture.getSize().x / tile_size) * (texture.getSize().y / tile_size);
        this->tiles_wide = texture.getSize().x / tile_size;
    }
};

class TileManager {
    public: 
        TileManager(int tile_size);

        int getTileSize();
        void load(const char *path);
        
        void draw(sf::RenderTarget &target, int tile, float x, float y);
        void draw(sf::RenderTarget &target, int tile, sf::Vector2f pos);
    private:
        std::vector<SpriteSheet> sprite_sheets;

        int tile_size;
        int tiles_wide;
};