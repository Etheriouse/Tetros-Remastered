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
    ~Game();

    uint8_t width = 10, height = 20;
    TetriCell matrix[10 * 20];

    Tetriminos *head = nullptr, *next = nullptr;
    Vector2i posHead;

    double moveTime = 0.0;
    const double moveInteraval = 0.20;

    Tetriminos *chooseNext();

    bool isCollide();
    bool isLeftCollide();
    bool isRightCollide();

    void fixTetriminos();

    void checkClearLines();
    void moveDownLine(int16_t from);



    /**
     * render the game or the actual things used at the screen
     * @param delta time between last frame
     * @param tick number tick elapsed from the launch of app
     */
    void render(long double delta, uint64_t tick);

    void moveTetriminos(long double delta);

    /**
     * Process the game if a game is in court
     * @param delta time between last frame
     * @param tick number tick elapsed from the launch of app
     */
    void process(long double delta, uint64_t tick);

    Texture2D TetriCellToTex(TetriCell t);
};

#endif