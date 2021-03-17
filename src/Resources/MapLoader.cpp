#include "Resources/MapLoader.hpp"

#include<iostream>
Map *MapLoader::load(std::string path) {
    // Calculate working directory
    std::string working_dir = path;
    working_dir.erase(working_dir.rfind("/")+1, working_dir.size());
    std::cout << "Working Dir: " << working_dir << std::endl;

    // Load TMX from path
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());
    
    // Get list of resources
    tinyxml2::XMLElement *map = doc.FirstChildElement("map");
    
    // Load all tilesets
    TileManager *manager = new TileManager(16);
    
    // Iterate through tilesets & load
    for(tinyxml2::XMLElement *child = map->FirstChildElement("tileset"); child != NULL; child = child->NextSiblingElement("tileset")) {
        std::string load_path = working_dir + std::string(child->FirstChildElement("image")->Attribute("source"));
        std::cout << "TILESET LOADED: " << load_path << std::endl;
        manager->load(load_path.c_str());
    }
    
    // Iterate through layers
    Map *game_map = new Map(manager);
    for(tinyxml2::XMLElement *child = map->FirstChildElement("layer"); child != NULL; child = child->NextSiblingElement("layer")) {
        // Width & Height of layer
        int width = child->IntAttribute("width");
        int height = child->IntAttribute("height");

        // get tile data
        std::string raw_tile_data = child->FirstChildElement("data")->GetText();

        // Load data into layer
        std::vector<std::vector<int>> tile_data(width, std::vector<int> (height, 0));
        std::stringstream s_stream(raw_tile_data);

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
        
        game_map->addLayer(tile_data);
    }
    return game_map;
}