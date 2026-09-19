#include "TextureManager.hpp"

TextureManager::TextureManager()
{
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

Texture2D TextureManager::get(std::string tex)
{
    auto _tex = loaded.find(tex);
    if (_tex == loaded.end())
        return _default;
    else
        return _tex->second;
}

void TextureManager::put(std::string tex, std::string path)
{
    loaded[tex] = LoadTexture(path.c_str());
}

void TextureManager::put(std::string tex, Texture2D t)
{
    loaded[tex] = t;
}
