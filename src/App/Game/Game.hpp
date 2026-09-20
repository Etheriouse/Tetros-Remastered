#ifndef YUZUENGIN_GAME_HPP
#define YUZUENGIN_GAME_HPP

#include "Global.hpp"
#include "ylib.hpp"

#define __width 10
#define __height 20

#include <raylib.h>
#include <cstdint>

class Tetriminos;
enum TetriCell : uint8_t;

typedef struct
{
    int x, y;
} Vector2i;

class Game
{

public:
    Game();
    ~Game();

    uint16_t width = __width, height = __height;
    TetriCell matrix[__width * __height];

    Tetriminos *head = nullptr, *next = nullptr;
    Vector2i posHead;

    const double moveInteraval = 0.15;
    const float sizeBlock = 32.0f;

    bool gameOver = false, exit = false;
    uint64_t score = 0, level = 1, clearLine = 0, timeGame = 0;
    long double acc = 0, moveTime = 0.0;

    KeyboardKey k_restart = KEY_R, k_exit = KEY_ESCAPE;

    Tetriminos *generateTetriminos();

    bool isCollide();
    bool isLeftCollide();
    bool isRightCollide();
    bool checkSuperposition();
    bool roofTouch();

    void fixTetriminos();
    void moveTetriminos(long double delta);
    void restartGame();

    uint16_t checkClearLines();
    uint16_t moveDownLine(int16_t from);

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