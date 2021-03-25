#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

using texture_cache = entt::resource_cache<texture>;

struct texture { 
    sf::Texture value;
    texture(const char *path) {
        value.loadFromFile(path);
    }
};

class texture_loader final: entt::resource_loader<texture_loader, texture> {
    public:
        std::shared_ptr<texture> load(const char *path) const;
};