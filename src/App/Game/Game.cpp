#include "Game.hpp"
#include <time.h>
#include "Global.hpp"
#include "App.hpp"

Game::Game()
{
    srand(time(NULL));
    for (uint8_t i = 0; i < width * height; i++)
        matrix[i] = TetriCell::Empty;
}

Tetriminos Game::chooseNext()
{
    return Tetriminos(types[rand() % 7]);
}

bool Game::isCollide()
{
    uint8_t t_w = head.width, t_h = head.height;

    for (uint8_t j = posHead.x; j < posHead.x + t_w; j++)
    {
        uint8_t looking = posHead.y + t_h;
        return (looking + 1 >= height) || (matrix[(looking + 1) * width + j] != TetriCell::Empty && head.matrix[j + ((t_h - 1) * t_w)]);
    }
    return false;
}

void Game::fixTetriminos()
{
    uint8_t t_w = head.width, t_h = head.height;
    for (uint8_t j = posHead.x; j < posHead.x + t_w; j++)
    {
        for (uint8_t i = posHead.y; i < posHead.y + t_h; i++)
        {
            uint8_t a = i-posHead.y, b = j-posHead.x;
            matrix[i * width + j] = head.matrix[a*t_w + b] ? head.color : TetriCell::Empty;
        }
    }
}

void Game::render(long double delta, uint64_t tick)
{
    unused(delta);
    unused(tick);
}

void Game::process(long double delta, uint64_t tick)
{

    uint64_t TPS = g_app.get()->TPS;

    if (tick % TPS == 0)
    {
        posHead.y++;
        if (isCollide())
        {
            fixTetriminos();
            head = next;
            next = chooseNext();
        }
    }
    unused(delta);
    unused(tick);
}