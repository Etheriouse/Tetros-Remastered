#include "Tetriminos.hpp"


Tetriminos::Tetriminos()
{
    matrix[0] = false;
    matrix[1] = true;
    matrix[2] = true;
    matrix[3] = true;
    matrix[4] = true;
    matrix[5] = false;
    width = 3;
    height = 2;
}

Tetriminos::Tetriminos(TetriType t)
{
    switch (t)
    {
    case TetriType::I:
        matrix[0] = true;
        matrix[1] = true;
        matrix[2] = true;
        matrix[3] = true;
        width = 4;
        height = 1;
        break;

    case TetriType::O:
        matrix[0] = true;
        matrix[1] = true;
        matrix[2] = true;
        matrix[3] = true;
        width = 2;
        height = 2;
        break;

    case TetriType::T:
        matrix[0] = true;
        matrix[1] = true;
        matrix[2] = true;
        matrix[3] = false;
        matrix[4] = true;
        matrix[5] = false;
        width = 3;
        height = 2;
        break;

    case TetriType::L:
        matrix[0] = true;
        matrix[1] = true;
        matrix[2] = true;
        matrix[3] = true;
        matrix[4] = false;
        matrix[5] = false;
        width = 3;
        height = 2;
        break;

    case TetriType::J:
        matrix[0] = true;
        matrix[1] = true;
        matrix[2] = true;
        matrix[3] = false;
        matrix[4] = false;
        matrix[5] = true;
        width = 3;
        height = 2;
        break;

    case TetriType::Z:
        matrix[0] = true;
        matrix[1] = true;
        matrix[2] = false;
        matrix[3] = false;
        matrix[4] = true;
        matrix[5] = true;
        width = 3;
        height = 2;
        break;

    case TetriType::S:
    default:
        matrix[0] = false;
        matrix[1] = true;
        matrix[2] = true;
        matrix[3] = true;
        matrix[4] = true;
        matrix[5] = false;
        width = 3;
        height = 2;
        break;
    }

    color = colors[rand() % 7];
}

Tetriminos::Tetriminos(TetriType t, TetriCell color) : Tetriminos(t) {
    this->color = color;
}
