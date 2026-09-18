#ifndef YUZUENGIN_TEXTUREMANAGER_HPP
#define YUZUENGIN_TEXTUREMANAGER_HPP

#include <raylib.h>
#include <map>
#include <string>

class TextureManager
{
public:
    TextureManager();

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

private:
    const char *defaultTexturePath = "assets/default/default.png";
    Texture2D _default;

    std::map<std::string, Texture2D> loaded;
};

#endif
