#include "AssetsManager.hpp"

AssetsManager::AssetsManager()
{
}

void AssetsManager::run()
{
    _default = LoadTexture(defaultTexturePath);
}

void AssetsManager::exit()
{
    UnloadTexture(_default);
    for (auto [name, tex] : this->textureLoaded)
    {
        UnloadTexture(tex);
    }
    for (auto [name, tex] : this->fontLoaded)
    {
        UnloadFont(tex);
    }
    for (auto [name, tex] : this->musicLoaded)
    {
        UnloadMusicStream(tex);
    }
    for (auto [name, tex] : this->soundLoaded)
    {
        UnloadSound(tex);
    }
}

Texture2D AssetsManager::get(std::string tex)
{
    auto _tex = textureLoaded.find(tex);
    if (_tex == textureLoaded.end())
        return _default;
    else
        return _tex->second;
}

void AssetsManager::put(std::string tex, std::string path)
{
    textureLoaded[tex] = LoadTexture(path.c_str());
}

void AssetsManager::put(std::string tex, Texture2D t)
{
    textureLoaded[tex] = t;
}

void AssetsManager::loadFont(std::string font, std::string path) {
    fontLoaded[font] = LoadFont(path.c_str());
}
void AssetsManager::loadSound(std::string sound, std::string path) {
    soundLoaded[sound] = LoadSound(path.c_str());
}
void AssetsManager::loadMusic(std::string music, std::string path) {
    musicLoaded[music] = LoadMusicStream(path.c_str());
}
