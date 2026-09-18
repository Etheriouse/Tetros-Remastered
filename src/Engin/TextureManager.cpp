#include "TextureManager.hpp"

TextureManager::TextureManager() {

}

void TextureManager::run()
{
    _default = LoadTexture(defaultTexturePath);
}

void TextureManager::exit()
{
    UnloadTexture(_default);
    for (auto [name, tex] : this->loaded)
    {
        UnloadTexture(tex);
    }
}