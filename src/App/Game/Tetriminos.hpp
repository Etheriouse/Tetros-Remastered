#ifndef TETROS_TETRIMINOS_HPP
#define TETROS_TETRIMINOS_HPP

#include <cstdint>
#include <cstdlib>


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
    Tetriminos();
    Tetriminos(TetriType t);
    Tetriminos(TetriType t, TetriCell color);
    bool *matrix = (bool *)(malloc(sizeof(bool) * 4));
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
};

#endif