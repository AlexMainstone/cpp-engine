#include "Resources/MapLoader.hpp"

#include<iostream>
Map *MapLoader::load(std::string path, texture_cache &tcache) {
    // Calculate working directory
    std::string working_dir = path;
    working_dir.erase(working_dir.rfind("/")+1, working_dir.size());
    std::cout << "Working Dir: " << working_dir << std::endl;

    // Load TMX from path
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());
    
    // Get list of resources
    tinyxml2::XMLElement *map = doc.FirstChildElement("map");
    
    // Iterate through tilesets & load
    TextureKey texturekey;
    for(tinyxml2::XMLElement *child = map->FirstChildElement("tileset"); child != NULL; child = child->NextSiblingElement("tileset")) {
        // New loader
        std::string load_path = working_dir + std::string(child->FirstChildElement("image")->Attribute("source"));
        tcache.load<texture_loader>(entt::hashed_string{child->Attribute("name")}, load_path.c_str());
        texturekey.addKey(child->IntAttribute("firstgid"), entt::hashed_string{child->Attribute("name")});
        std::cout << "TILESET LOADED (" << child->Attribute("name") << "): " << load_path << std::endl;
    }
    
    // Iterate through layers
    Map *game_map = new Map(texturekey, tcache);
    for(tinyxml2::XMLElement *child = map->FirstChildElement("layer"); child != NULL; child = child->NextSiblingElement("layer")) {
        // Width & Height of layer
        int width = child->IntAttribute("width");
        int height = child->IntAttribute("height");

        // get tile data
        std::string raw_tile_data = child->FirstChildElement("data")->GetText();

        // Load data into layer
        std::vector<std::vector<int>> tile_data(width, std::vector<int> (height, 0));
        std::stringstream s_stream(raw_tile_data);

        //TODO: Speed this up 
        int x = 0; 
        int y = 0;
        while(s_stream.good()) {
            std::string substr;
            std::getline(s_stream, substr, ',');
            tile_data[x][y] = std::stoi(substr);
            
            x++;
            if(x >= width) {
                x = 0;
                y++;
                if(y >= height) {
                    break;
                }
            }
        }

        //TODO: this could be done better
        // if collision layer
        std::cout << "Loaded Layer: " << child->Attribute("name") << std::endl;
        if(!std::strcmp(child->Attribute("name"), "Collision")) {
        std::vector<std::vector<int>> collision_map;
            for(auto x : tile_data) {
                std::vector<int> row;
                for(auto y : x) {
                    if(y == 1037) {
                        row.push_back(1);
                    } else if(y == 35) {
                        row.push_back(2);
                    } else {
                        row.push_back(0);
                    }
                }
                collision_map.push_back(row);
            }
            game_map->setCollisionMap(collision_map);
            continue;
        }
        
        game_map->addLayer(tile_data);
    }
    
    game_map->updateTextures();

    return game_map;
}