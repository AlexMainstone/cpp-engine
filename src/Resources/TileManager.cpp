#include "Resources/TileManager.hpp"

TileManager::TileManager(int tile_size) {
    this->tile_size = tile_size;
}

void TileManager::load(const char *path) {
    sprite_sheets.push_back(SpriteSheet(path, tile_size));
}

void TileManager::draw(sf::RenderTarget &target, int tile, float x, float y) {
    draw(target, tile, sf::Vector2f(x, y));
}

void TileManager::draw(sf::RenderTarget &target, int tile, sf::Vector2f pos) {
    sf::Sprite draw_sprite;
    draw_sprite.setPosition(pos);

    for(auto sheet : sprite_sheets) {
        if (tile > sheet.tile_count) {
            tile -= sheet.tile_count;
        } else {
            draw_sprite.setTexture(sheet.texture);
            draw_sprite.setTextureRect(sf::IntRect((tile % sheet.tiles_wide) * tile_size, std::floor(tile / sheet.tiles_wide) * tile_size, tile_size, tile_size));
            target.draw(draw_sprite);
            return;
        }
    }
}