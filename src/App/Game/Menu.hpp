#ifndef YUZUENGIN_MENU_HPP
#define YUZUENGIN_MENU_HPP

#include "Global.hpp"
#include "Game.hpp"
#include "ylib.hpp"
#include <cstdint>

class Menu
{

public:
    Menu();
    Menu(bool *running, Game **game);

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

private:
    bool *running;
    Game **game;
};

#endif
