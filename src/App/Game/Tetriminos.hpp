#ifndef TETROS_TETRIMINOS_HPP
#define TETROS_TETRIMINOS_HPP

#include <cstdint>
#include <cstdlib>

#include "Global.hpp"
#include "App.hpp"

enum TetriCell : uint8_t
{
    Empty,

    Red,
    Blue,
    Green,

    Cyan,
    Yellow,
    Magenta,

    Orange,
};

enum TetriType : uint8_t
{
    I,
    O,
    T,
    J,
    L,
    S,
    Z
};

constexpr TetriCell colors[] = {Red, Blue, Green, Cyan, Yellow, Magenta, Orange};
constexpr TetriType types[] = {I, O, T, J, L, S, Z};

class Tetriminos
{

public:
    ~Tetriminos() { free(matrix); }
    Tetriminos();
    Tetriminos(TetriType t);
    Tetriminos(TetriType t, TetriCell color);

    void rotateLeft();
    void rotateRight();

    void draw(int x, int y, float sizeBlock);
    
    bool *matrix = (bool *)(malloc(sizeof(bool) * 8));
    uint8_t width, height;
    TetriCell color;

    static Tetriminos I()
    {
        return Tetriminos(TetriType::I, TetriCell::Cyan);
    }
    static Tetriminos O()
    {
        return Tetriminos(TetriType::O, TetriCell::Yellow);
    }
    static Tetriminos T()
    {
        return Tetriminos(TetriType::T, TetriCell::Magenta);
    }
    static Tetriminos J()
    {
        return Tetriminos(TetriType::J, TetriCell::Blue);
    }
    static Tetriminos L()
    {
        return Tetriminos(TetriType::L, TetriCell::Orange);
    }
    static Tetriminos S()
    {
        return Tetriminos(TetriType::S, TetriCell::Green);
    }
    static Tetriminos Z()
    {
        return Tetriminos(TetriType::Z, TetriCell::Red);
    }

    static Texture2D TetriCellToTex(TetriCell t)
    {
        switch (t)
        {
        case TetriCell::Red:
            return g_app->assetsManager.get("red_block");
        case TetriCell::Blue:
            return g_app->assetsManager.get("blue_block");
        case TetriCell::Green:
            return g_app->assetsManager.get("green_block");
        case TetriCell::Cyan:
            return g_app->assetsManager.get("cyan_block");
        case TetriCell::Yellow:
            return g_app->assetsManager.get("yellow_block");
        case TetriCell::Magenta:
            return g_app->assetsManager.get("magenta_block");
        case TetriCell::Orange:
            return g_app->assetsManager.get("orange_block");
        case TetriCell::Empty:
        default:
            return g_app->assetsManager.get("empty_block");
        }
    }
};

#endif