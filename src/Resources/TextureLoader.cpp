#include "Resources/TextureLoader.hpp"

void TextureKey::addKey(int start, entt::hashed_string hash) {
    key_vec.push_back(KeyItem(start, hash));
}

KeyItem TextureKey::getHash(int tile) {
    entt::hashed_string hash;
    for(int i = 1; i < key_vec.size(); i++) {
        if(tile < key_vec[i].start) {
            return key_vec[i-1];
        }
    }
    
    return key_vec.back();
}