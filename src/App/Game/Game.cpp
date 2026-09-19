#include "Game.hpp"
#include <time.h>
#include "Global.hpp"
#include "App.hpp"

Texture2D loadFromImagePart(Image src, Rectangle dst)
{
    Image cropped = ImageFromImage(src, dst);
    Texture2D tex = LoadTextureFromImage(cropped);
    UnloadImage(cropped);
    return tex;
}

Game::Game()
{
    srand(time(NULL));
    for (uint8_t i = 0; i < width * height; i++)
        matrix[i] = TetriCell::Empty;

    head = chooseNext();
    next = chooseNext();
    posHead.x = 5;
    posHead.y = -1;

    Image blocksImg = LoadImage("assets/Tetriminos/bricksColor/color_bricks.png");
    g_app->textureManager.put("red_block", loadFromImagePart(blocksImg, {0, 0, 32, 32}));
    g_app->textureManager.put("green_block", loadFromImagePart(blocksImg, {0, 32, 32, 32}));
    g_app->textureManager.put("orange_block", loadFromImagePart(blocksImg, {32, 0, 32, 32}));
    g_app->textureManager.put("cyan_block", loadFromImagePart(blocksImg, {32, 32, 32, 32}));
    g_app->textureManager.put("yellow_block", loadFromImagePart(blocksImg, {64, 0, 32, 32}));
    g_app->textureManager.put("blue_block", loadFromImagePart(blocksImg, {64, 32, 32, 32}));
    g_app->textureManager.put("magenta_block", loadFromImagePart(blocksImg, {96, 0, 32, 32}));
    g_app->textureManager.put("empty_block", loadFromImagePart(blocksImg, {96, 32, 32, 32}));
    UnloadImage(blocksImg);
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
    if (head == nullptr)
        return false;
    if (posHead.y + head->height >= height)
        return true;

    // if(head->height == 1) return matrix[(headPo+1)*width+j] != TetriCell::Empty;

    uint8_t t_w = head->width, t_h = head->height;
    bool result = false;
    for (uint8_t i = posHead.y; i < posHead.y + t_h; i++)
    {
        for (uint8_t j = posHead.x; j < posHead.x + t_w; j++)
        {
            // special case for I
            uint8_t a = j - posHead.x, b = i - posHead.y;
            if (head->matrix[b * t_w + a] == TetriCell::Empty)
                continue;
            if (head->height == 1 || b + 1 >= head->height)
                result |= matrix[(i + 1) * width + j] != TetriCell::Empty;
            else
                result |= head->matrix[(b + 1) * t_w + a] == TetriCell::Empty && matrix[(i + 1) * width + j] != TetriCell::Empty;
        }
    }
    return result;
}

bool Game::isLeftCollide()
{

    for (uint8_t row = 0; row < head->height; row++)
    {
        uint8_t x = 0;
        while (x < head->width && head->matrix[row * head->width + x] == TetriCell::Empty)
        {
            x++;
        }
        if (x == head->width)
            continue;
        if (posHead.x + x == 0)
            return true;
        if (matrix[(posHead.y + row) * width + (posHead.x + x - 1)] != TetriCell::Empty)
            return true;
    }

    return false;
}

bool Game::isRightCollide()
{
    for (uint8_t row = 0; row < head->height; row++)
    {
        int8_t x = head->width - 1;
        while (x >= 0 && head->matrix[row * head->width + x] == TetriCell::Empty)
        {
            x--;
        }
        if (x < 0)
            continue;
        if (posHead.x + x + 1 >= width)
            return true;
        if (matrix[(posHead.y + row) * width + (posHead.x + x + 1)] != TetriCell::Empty)
            return true;
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
            matrix[i * width + j] = head->matrix[a * t_w + b] ? head->color : matrix[i * width + j];
        }
    }
    posHead.x = 5;
    posHead.y = -1;
}

void Game::checkClearLines()
{
    for (int16_t row = height - 1; row >= 0; row--)
    {
        bool fullline = true;
        for (int16_t j = 0; j < width; j++)
        {
            fullline &= matrix[row * width + j] != TetriCell::Empty;
        }

        if (fullline)
        {
            moveDownLine(row);
        }
    }
}

void Game::moveDownLine(int16_t from)
{
    for (int16_t row = from; row >= 1; row--)
    {
        // down all line up to from
        for (int16_t j = 0; j < width; j++)
        {
            matrix[row * width + j] = matrix[(row - 1) * width + j];
        }
    }
    for (int16_t j = 0; j < width; j++)
        matrix[j] = TetriCell::Empty;
    checkClearLines();
}

void Game::render(long double delta, uint64_t tick)
{
    unused(delta);
    unused(tick);

    moveTetriminos(delta);

    DrawRectangle(0, 0, width * 32, height * 32, GRAY);

    // DrawTexture(g_app->textureManager.get("square"), posHead.x * 32, posHead.y * 32, WHITE);

    for (uint8_t j = 0; j < head->width; j++)
    {
        for (uint8_t i = 0; i < head->height; i++)
        {
            if (head->matrix[i * head->width + j])
                DrawTexture(TetriCellToTex(head->color), posHead.x * 32 + j * 32, posHead.y * 32 + i * 32, WHITE);
        }
    }
    
    // DrawRectangleLines(posHead.x * 32, posHead.y * 32, head->width * 32, head->height * 32, RED);

    for (uint8_t j = 0; j < width; j++)
    {
        for (uint8_t i = 0; i < height; i++)
        {
            DrawTexture(TetriCellToTex(matrix[i * width + j]), j * 32, i * 32, WHITE);
        }
    }
}

void Game::moveTetriminos(long double delta)
{
    if (head == nullptr)
        return;

    Vector2i direction = {0, 0};
    if (IsKeyDown(KEY_LEFT))
        direction.x = -1;
    if (IsKeyDown(KEY_RIGHT))
        direction.x = 1;

    // check collide side and wall area
    if (posHead.x >= 0 || posHead.x <= width - 1)
        if (!(isLeftCollide() && direction.x == -1))
            if (!(isRightCollide() && direction.x == 1))
                if (!(posHead.x + direction.x >= width || posHead.x + direction.x < 0))
                {
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
                }

    if (IsKeyPressed(KEY_Z))
        head->rotateLeft();
    if (IsKeyPressed(KEY_X))
        head->rotateRight();

    if (posHead.x + head->width >= width)
        posHead.x -= ((posHead.x + head->width) - width);
    if (posHead.x < 0)
        posHead.x = 0;
}

void Game::process(long double delta, uint64_t tick)
{

    uint64_t downFall = g_app->TPS / 4;

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
                head = nullptr;
                head = next;
                next = chooseNext();

                checkClearLines();
            }
            else
            {
                posHead.y++;
            }
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
    default:
        return g_app->textureManager.get("empty_block");
    }
}
