#include "Game.hpp"
#include <time.h>
#include "Global.hpp"
#include "App.hpp"

Game::Game()
{
    srand(time(NULL));
    for (uint8_t i = 0; i < width * height; i++)
        matrix[i] = TetriCell::Empty;

    head = chooseNext();
    next = chooseNext();
    posHead.x = 5;
    posHead.y = 0;

    Image blocksImg = LoadImage("assets/Tetriminos/bricksColor/color_bricks.png");
    g_app->textureManager.put("red_block", LoadTextureFromImage(ImageFromImage(blocksImg, {0, 0, 32, 32})));
    g_app->textureManager.put("green_block", LoadTextureFromImage(ImageFromImage(blocksImg, {0, 32, 32, 32})));
    g_app->textureManager.put("orange_block", LoadTextureFromImage(ImageFromImage(blocksImg, {32, 0, 32, 32})));
    g_app->textureManager.put("cyan_block", LoadTextureFromImage(ImageFromImage(blocksImg, {32, 32, 32, 32})));
    g_app->textureManager.put("yellow_block", LoadTextureFromImage(ImageFromImage(blocksImg, {64, 0, 32, 32})));
    g_app->textureManager.put("blue_block", LoadTextureFromImage(ImageFromImage(blocksImg, {64, 32, 32, 32})));
    g_app->textureManager.put("magenta_block", LoadTextureFromImage(ImageFromImage(blocksImg, {96, 0, 32, 32})));
    g_app->textureManager.put("empty_block", LoadTextureFromImage(ImageFromImage(blocksImg, {96, 32, 32, 32})));
}

Game::~Game()
{
    if (head != nullptr)
        delete head;
    if (next != nullptr)
        delete next;
}

Tetriminos *Game::chooseNext()
{
    return new Tetriminos(types[rand() % 7]);
}

bool Game::isCollide()
{
    uint8_t t_w = head->width, t_h = head->height;

    for (uint8_t j = posHead.x; j < posHead.x + t_w; j++)
    {
        uint8_t looking = posHead.y + t_h;
        return (looking + 1 >= height) || (matrix[(looking + 1) * width + j] != TetriCell::Empty && head->matrix[j + ((t_h - 1) * t_w)]);
    }
    return false;
}

void Game::fixTetriminos()
{
    uint8_t t_w = head->width, t_h = head->height;
    for (uint8_t j = posHead.x; j < posHead.x + t_w; j++)
    {
        for (uint8_t i = posHead.y; i < posHead.y + t_h; i++)
        {
            uint8_t a = i - posHead.y, b = j - posHead.x;
            matrix[i * width + j] = head->matrix[a * t_w + b] ? head->color : TetriCell::Empty;
        }
    }
    posHead.x = 5;
    posHead.y = 0;
}

void Game::render(long double delta, uint64_t tick)
{
    unused(delta);
    unused(tick);

    Vector2i direction = {0, 0};
    if (IsKeyDown(KEY_LEFT))
        direction.x = -1;
    if (IsKeyDown(KEY_RIGHT))
        direction.x = 1;


    // check collide side and wall area    

    if (direction.x != 0)
    {
        moveTime -= delta;
        if (moveTime <= 0.0)
        {
            posHead.x += direction.x;
            moveTime += moveInteraval;
        }
    }
    else
    {
        moveTime = 0.0;
    }

    // DrawTexture(g_app->textureManager.get("square"), posHead.x * 32, posHead.y * 32, WHITE);

    for (uint8_t j = 0; j < head->width; j++)
    {
        for (uint8_t i = 0; i < head->height; i++)
        {
            if(head->matrix[i*head->width+j]) DrawTexture(TetriCellToTex(head->color), posHead.x*32 + j * 32, posHead.y*32 + i * 32, WHITE);
        }
    }

    for (uint8_t j = 0; j < width; j++)
    {
        for (uint8_t i = 0; i < height; i++)
        {
            DrawTexture(TetriCellToTex(matrix[i * width + j]), j * 32, i * 32, WHITE);
        }
    }
}

void Game::process(long double delta, uint64_t tick)
{

    uint64_t downFall = g_app->TPS;

    if (IsKeyDown(KEY_DOWN))
        downFall *= 0.5;

    if (((tick + 1) % downFall) == 0)
    {
        if (head != nullptr)
        {
            if (isCollide())
            {
                fixTetriminos();
                delete head;
                head = next;
                next = chooseNext();
            }
            posHead.y++;
        }
    }

    unused(delta);
    unused(tick);
}

Texture2D Game::TetriCellToTex(TetriCell t)
{
    switch (t)
    {
    case TetriCell::Red:
        return g_app->textureManager.get("red_block");
    case TetriCell::Blue:
        return g_app->textureManager.get("blue_block");
    case TetriCell::Green:
        return g_app->textureManager.get("green_block");
    case TetriCell::Cyan:
        return g_app->textureManager.get("cyan_block");
    case TetriCell::Yellow:
        return g_app->textureManager.get("yellow_block");
    case TetriCell::Magenta:
        return g_app->textureManager.get("magenta_block");
    case TetriCell::Orange:
        return g_app->textureManager.get("orange_block");
    case TetriCell::Empty:
        return g_app->textureManager.get("empty_block");
    }
}
