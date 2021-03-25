#include "Resources/TextureLoader.hpp"

std::shared_ptr<texture> texture_loader::load(const char *path) const {
    return std::shared_ptr<texture>(new texture(path));
}
