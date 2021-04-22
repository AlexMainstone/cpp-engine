#include "World/Map.hpp"

Map::Map(TextureKey texturekey, texture_cache &tcache) : tcache(tcache) {
    this->texturekey = texturekey;
}

Map::~Map() {

}

void Map::addLayer(std::vector<std::vector<int>> layer) {
    map_data.push_back(layer);
    map_textures.push_back(sf::Texture());
}

void Map::setCollisionMap(std::vector<std::vector<bool>> map) {
    collision_map = map;
}

bool Map::checkCollision(int x, int y) {
    return collision_map[x][y];
}

void Map::drawCollisionMap(sf::RenderTarget &target) {
    sf::RectangleShape shape;
    shape.setOutlineThickness(2.0);
    shape.setOutlineColor(sf::Color(255, 255, 255, 50));
    shape.setFillColor(sf::Color::Transparent);
    shape.setSize(sf::Vector2f(8,8));
    for(int x = 0; x < collision_map.size(); x++) {
        for(int y = 0; y < collision_map[x].size(); y++) {
            if(collision_map[x][y] != 0) {continue;}
            shape.setPosition(x*16 + 4,y*16 + 4);
            target.draw(shape);
        }
    }

}

#include<iostream>
void Map::updateTextures() {
    sf::Sprite drawsprite;
    for(int z = 0; z < map_data.size(); z++) {
        sf::RenderTexture rtex;
        rtex.create(map_data[z].size() * 16, map_data[z][0].size() * 16);
        for(int x = 0; x < map_data[z].size(); x++) {
            for(int y = 0; y < map_data[z][x].size(); y++) {
                // TODO: This could use speeding up now, a lot of tileset metadata could be stored before hand
                KeyItem itm =  texturekey.getHash(map_data[z][x][y]);
                auto handle = tcache.handle(itm.hash);
                int tile = map_data[z][x][y] - itm.start;
                if(tile == -1) continue;
                
                drawsprite.setTexture(handle->value);
                drawsprite.setPosition(x * 16, y * 16);
                int tiles_wide = (handle->value.getSize().x / 16);
                drawsprite.setTextureRect(sf::IntRect((tile % tiles_wide) * 16, std::floor(tile / tiles_wide) * 16, 16, 16));
                rtex.draw(drawsprite);
            }
        }
        if(z == 0) {
            drawCollisionMap(rtex);
        }
        
        rtex.display();
        map_textures[z] = rtex.getTexture();
    }
}

void Map::draw(sf::RenderTarget &target)  {
    sf::Sprite map_sprite;
    for(auto t : map_textures) {
        map_sprite.setTexture(t);
        target.draw(map_sprite);
    }
}

std::list<sf::Vector2i> Map::astar(sf::Vector2i start, sf::Vector2i end) {
    Node *current_node = new Node(start.x, start.y, 0, heuristic(start, end));
    
    std::list<Node*> open;
    open.push_back(current_node);

    std::list<Node*> closed;

    while(!open.empty()) {
        // Sort open set;
        open.sort([](const Node *lhs, const Node *rhs) { return lhs->f < rhs->f; });
        
        // Set current node
        current_node = open.front();
        
        // Move to closed set
        open.pop_front();
        closed.push_back(current_node);
        
        // is this the goal?
        if(end.x == current_node->x && end.y == current_node->y) {
            break;
        }

        for(auto n : neighbors(current_node->x, current_node->y)) {
            
            if(collision_map[n.x][n.y]) {
                continue;
            }

            // Check if this node is in the closed set
            bool inSet = false;
            for(auto c : closed) {
                if(c->x == n.x && c->y == n.y) {
                    inSet = true;
                    break;
                }
            }
            if(inSet) { continue; }
            
            float g_score = current_node->g + 1;
            
            // Check if in open set
            for(auto o : open) {
                if(o->x == n.x && o->y == n.y) {
                    if(g_score >= o->g) {
                        inSet = true;
                    }
                    break;
                }
            }
            if(!inSet) {
                Node *node = new Node(n.x, n.y, g_score, heuristic(n, end), current_node);
                open.push_back(node);
            }
        }
    }
    
    std::list<sf::Vector2i> out;
    while(current_node != nullptr) {
        out.push_front(sf::Vector2i(current_node->x, current_node->y));
        current_node = current_node->parent;
    }

    return out;
}

float Map::heuristic(sf::Vector2i start, sf::Vector2i end) {
    return std::sqrt(std::pow(start.x - end.x, 2) + std::pow(start.y - end.y, 2) * 1.0);
}

// Bresenham's line algorithm adapted from rosetta code
bool Map::raycast(int startx, int starty, int endx, int endy) {
    const bool steep = (std::abs(endy - starty) > std::abs(endx - startx));
    
    // Check that the points are in the correct order
    if(steep) {
        std::swap(startx, starty);
        std::swap(endx, endy);
    }
    
    if(startx > endx) {
        std::swap(startx, endx);
        std::swap(starty, endy);
    }
    
    const float dx = endx - startx;
    const float dy = std::fabs(endy - starty);
    
    float error = dx / 2.0f;
    const int ystep = (starty < endy) ? 1 : -1;
    int y = starty;
    
    const int maxX = endx;
    
    for(int x = startx; x <= maxX; x++) {
        if(steep) {
            if(collision_map[y][x]) return true;
        } else {
            if(collision_map[x][y]) return true;
        }
        
        error -= dy;
        if(error < 0) {
            y += ystep;
            error += dx;
        }
    }
    
    // no collision
    return false;
}

std::vector<sf::Vector2i> Map::neighbors(int x, int y) {
    std::vector<sf::Vector2i> out;
    
    out.push_back(sf::Vector2i(x-1,y));
    out.push_back(sf::Vector2i(x+1,y));

    out.push_back(sf::Vector2i(x,y-1));
    // out.push_back(sf::Vector2i(x-1,y-1));
    // out.push_back(sf::Vector2i(x+1,y-1));

    out.push_back(sf::Vector2i(x,y+1));
    // out.push_back(sf::Vector2i(x-1,y+1));
    // out.push_back(sf::Vector2i(x+1,y+1));

    return out;
}