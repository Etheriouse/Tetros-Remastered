#ifndef YUZUENGIN_GAME_HPP
#define YUZUENGIN_GAME_HPP

#include "Global.hpp"
#include "ylib.hpp"
#include "Tetriminos.hpp"

#include <raylib.h>
#include <cstdint>

const Tetriminos basicsTetriminos[] = {Tetriminos::I(), Tetriminos::O(), Tetriminos::T(), Tetriminos::L(), Tetriminos::J(), Tetriminos::Z(), Tetriminos::S()};

typedef struct
{
    int x, y;
} Vector2i;

class Game
{

public:
    Game();

    uint8_t width = 10, height = 20;
    TetriCell matrix[10 * 20];

    Tetriminos head, next;
    Vector2i posHead;

    Tetriminos chooseNext();

    bool isCollide();
    void fixTetriminos();

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
};

#endif