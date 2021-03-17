#include "Resources/TileManager.hpp"

TileManager::TileManager(int tile_size) {
    this->tile_size = tile_size;
}

int TileManager::getTileSize() {
    return tile_size;
}

void TileManager::load(const char *path) {
    sprite_sheets.push_back(SpriteSheet(path, tile_size));
}

void TileManager::draw(sf::RenderTarget &target, int tile, float x, float y) {
    draw(target, tile, sf::Vector2f(x, y));
}

void TileManager::draw(sf::RenderTarget &target, int tile, sf::Vector2f pos) {
    if(tile == 0) {
        return;
    }
    // TMX files count 0 as empty, here we want 0 to be our first sprite
    tile--;

    // Setup our draw sprite
    sf::Sprite draw_sprite;
    draw_sprite.setPosition(pos);

    // iterate through sheets to find the correct one
    for(auto sheet : sprite_sheets) {
        if (tile > sheet.tile_count) {
            // wrong sheet!
            tile -= sheet.tile_count;
        } else {
            // draw sprite & return
            draw_sprite.setTexture(sheet.texture);
            draw_sprite.setTextureRect(sf::IntRect((tile % sheet.tiles_wide) * tile_size, std::floor(tile / sheet.tiles_wide) * tile_size, tile_size, tile_size));
            target.draw(draw_sprite);
            return;
        }
    }
}