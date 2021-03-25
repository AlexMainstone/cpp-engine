#pragma once

#include <tinyxml2.h>

#include <string>
#include <sstream>
#include <vector>

#include "Resources/TileManager.hpp"
#include "Resources/TextureLoader.hpp"
#include "World/Map.hpp"
    
class MapLoader {
    public:
        Map *load(std::string path, texture_cache &tcache);
};