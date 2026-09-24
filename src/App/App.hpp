#ifndef YUZUENGIN_APP_HPP
#define YUZUENGIN_APP_HPP

#include <cstdint>

#include "ylib.hpp"
#include "AssetsManager.hpp"
#include "IOManager.hpp"

#include "Menu.hpp"
#include "Game.hpp"
#include "Global.hpp"

class App
{

    App();
    App(uint32_t width, uint32_t height, const char *name);

    /**
     * render the game or the actual things used at the screen
     * @param delta time between last frame
     * @param tick number tick elapsed from the launch of app
     */
    void render(long double delta, uint64_t tick);

    /**
     * Process the game if a game is in court
     * @param delta time between last frame
     * @param tick number tick elapsed from the launch of app
     */
    void process(long double delta, uint64_t tick);

public:
    ~App();

    /**
     * Return if the app is closing
     */
    bool appIsClosing();

    /** Width of the app */
    uint16_t width;
    /** Height of the app */
    uint16_t height;

    uint64_t FPS = 0, TPS = 0;

    AssetsManager assetsManager;
    IOManager ioManager;

    static inline App createInstance()
    {
        return App(1600, 900, "Tetros");
    }

    int run();

private:
    uint64_t _tps = 0, _fps = 0;
    long double TICK_TIME = 1;    

    const char *name;

    /**
     * Value who manage the life of the app
     */
    bool running = true;

    /**
     * Pointer to a Game object, if nullptr, there is no Game in cours
     */
    Game *game = nullptr;

    /**
     * Object for using menu
     */
    Menu menu;
};

#endif