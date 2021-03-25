#pragma once

#include <vector>

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>


struct texture { 
    sf::Texture value;
    texture(const char *path) {
        value.loadFromFile(path);
    }
};

using texture_cache = entt::resource_cache<texture>;

struct texture_loader final: entt::resource_loader<texture_loader, texture> {
    std::shared_ptr<texture> load(const char *path) const {
        return std::shared_ptr<texture>(new texture(path));
    }
};

struct KeyItem {
    int start;
    entt::hashed_string hash;

    KeyItem(int start, entt::hashed_string hash) : start(start), hash(hash) {}
};

class TextureKey {
    public:
        void addKey(int start, entt::hashed_string hash);
        KeyItem getHash(int tile);
    private:
        std::vector<KeyItem> key_vec;
};