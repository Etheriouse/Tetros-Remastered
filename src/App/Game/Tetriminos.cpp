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
    for (uint8_t i = 0; i < 8; i++)
        matrix[i] = false;
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
        matrix[4] = true;
        width = 3;
        height = 2;
        break;

    case TetriType::L:
        matrix[0] = true;
        matrix[1] = true;
        matrix[2] = true;
        matrix[3] = true;
        width = 3;
        height = 2;
        break;

    case TetriType::J:
        matrix[0] = true;
        matrix[1] = true;
        matrix[2] = true;
        matrix[5] = true;
        width = 3;
        height = 2;
        break;

    case TetriType::Z:
        matrix[0] = true;
        matrix[1] = true;
        matrix[4] = true;
        matrix[5] = true;
        width = 3;
        height = 2;
        break;

    case TetriType::S:
    default:
        matrix[1] = true;
        matrix[2] = true;
        matrix[3] = true;
        matrix[4] = true;
        width = 3;
        height = 2;
        break;
    }

    color = colors[rand() % 7];
}

Tetriminos::Tetriminos(TetriType t, TetriCell color) : Tetriminos(t)
{
    this->color = color;
}

void Tetriminos::rotateLeft()
{
    uint8_t nw = height, nh = width;
    bool *next = (bool *)malloc(sizeof(bool) * 8);
    for (uint8_t i = 0; i < nh; i++)
    {
        for (uint8_t j = 0; j < nw; j++)
        {
            next[i * nw + j] = matrix[j * width + (width - i - 1)];
        }
    }

    bool *previous = this->matrix;
    matrix = next;
    free(previous);
    width = nw;
    height = nh;
}

void Tetriminos::rotateRight()
{
    uint8_t nw = height, nh = width;
    bool *next = (bool *)malloc(sizeof(bool) * 8);

    for (uint8_t i = 0; i < nh; i++)
    {
        for (uint8_t j = 0; j < nw; j++)
        {
            next[i * nw + j] =
                matrix[(height - j - 1) * width + i];
        }
    }
    bool *previous = this->matrix;
    matrix = next;
    free(previous);
    width = nw;
    height = nh;
}