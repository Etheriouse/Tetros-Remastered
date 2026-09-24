#ifndef YUZUENGIN_TEXTUREMANAGER_HPP
#define YUZUENGIN_TEXTUREMANAGER_HPP

#include <raylib.h>
#include <map>
#include <string>

class AssetsManager
{
public:
    AssetsManager();

    /**
     * Preapare and setup the texture gesionnary after the initilization of the opengl context
     * @note this function need to be call AFTER InitWindow
     */
    void run();

    /**
     * Unload all texture loaded before closing the window
     * @note this function need to be call BEFORE CloseWindow
     */
    void exit();

    Texture2D get(std::string tex);
    void put(std::string tex, std::string path);
    void put(std::string tex, Texture2D t);

    void loadFont(std::string font, std::string path);
    void loadSound(std::string sound, std::string path);
    void loadMusic(std::string music, std::string path);

private:
    const char *defaultTexturePath = "assets/default/default.png";
    Texture2D _default;

    std::map<std::string, Texture2D> textureLoaded;
    std::map<std::string, Font> fontLoaded;
    std::map<std::string, Sound> soundLoaded;
    std::map<std::string, Music> musicLoaded;
    
    
};

#endif
