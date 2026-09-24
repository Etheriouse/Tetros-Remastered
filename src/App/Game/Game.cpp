#include "Game.hpp"
#include <time.h>
#include "Global.hpp"
#include "App.hpp"

#include "Tetriminos.hpp"

const uint64_t lineScores[] = {0, 40, 100, 300, 1200};

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
    for (uint16_t i = 0; i < width * height; i++)
        matrix[i] = TetriCell::Empty;

    head = generateTetriminos();
    next = generateTetriminos();
    posHead.x = 5;
    posHead.y = -1;

    Image blocksImg = LoadImage("assets/Tetriminos/bricksColor/color_bricks.png");
    g_app->assetsManager.put("red_block", loadFromImagePart(blocksImg, {0, 0, 32, 32}));
    g_app->assetsManager.put("green_block", loadFromImagePart(blocksImg, {0, 32, 32, 32}));
    g_app->assetsManager.put("orange_block", loadFromImagePart(blocksImg, {32, 0, 32, 32}));
    g_app->assetsManager.put("cyan_block", loadFromImagePart(blocksImg, {32, 32, 32, 32}));
    g_app->assetsManager.put("yellow_block", loadFromImagePart(blocksImg, {64, 0, 32, 32}));
    g_app->assetsManager.put("blue_block", loadFromImagePart(blocksImg, {64, 32, 32, 32}));
    g_app->assetsManager.put("magenta_block", loadFromImagePart(blocksImg, {96, 0, 32, 32}));
    g_app->assetsManager.put("empty_block", loadFromImagePart(blocksImg, {96, 32, 32, 32}));
    g_app->assetsManager.put("background", LoadTexture("assets/background.png"));
    // load write police
    g_app->assetsManager.loadFont("monocraft", "assets/font/monocraft.ttf");
    
    UnloadImage(blocksImg);
}

Game::~Game()
{
    if (head != nullptr)
        delete head;
    if (next != nullptr)
        delete next;
}

Tetriminos *Game::generateTetriminos()
{
    // return new Tetriminos(TetriType::I, TetriCell::Cyan);
    return new Tetriminos(types[rand() % 7]);
}

bool Game::isCollide()
{
    if (head == nullptr)
        return false;
    if (posHead.y + head->height >= height)
        return true;

    // if(head->height == 1) return matrix[(headPo+1)*width+j] != TetriCell::Empty;

    uint16_t t_w = head->width, t_h = head->height;
    bool result = false;
    for (uint16_t i = posHead.y; i < posHead.y + t_h; i++)
    {
        for (uint16_t j = posHead.x; j < posHead.x + t_w; j++)
        {
            // special case for I
            uint16_t a = j - posHead.x, b = i - posHead.y;
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

    for (uint16_t row = 0; row < head->height; row++)
    {
        uint16_t x = 0;
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
    for (uint16_t row = 0; row < head->height; row++)
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

bool Game::checkSuperposition()
{
    for (uint16_t i = 0; i < head->height; i++)
    {
        for (uint16_t j = 0; j < head->width; j++)
        {
            if (matrix[(posHead.y + i) * width + posHead.x + j] != TetriCell::Empty && head->matrix[i * head->width + j] != TetriCell::Empty)
                return true;
        }
    }
    return false;
}

void Game::fixTetriminos()
{
    uint16_t t_w = head->width, t_h = head->height;
    for (uint16_t j = posHead.x; j < posHead.x + t_w; j++)
    {
        for (uint16_t i = posHead.y; i < posHead.y + t_h; i++)
        {
            uint16_t a = i - posHead.y, b = j - posHead.x;
            matrix[i * width + j] = head->matrix[a * t_w + b] ? head->color : matrix[i * width + j];
        }
    }
}

uint16_t Game::checkClearLines()
{
    uint16_t qtt = 0;
    for (int16_t row = height - 1; row >= 0; row--)
    {
        bool fullline = true;
        for (int16_t j = 0; j < width; j++)
        {
            fullline &= matrix[row * width + j] != TetriCell::Empty;
        }

        if (fullline)
        {
            qtt += moveDownLine(row);
        }
    }
    return qtt;
}

uint16_t Game::moveDownLine(int16_t from)
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
    return checkClearLines() + 1;
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
    {
        head->rotateLeft();
        if (checkSuperposition())
            head->rotateRight();
    }

    if (IsKeyPressed(KEY_X))
    {
        head->rotateRight();
        if (checkSuperposition())
            head->rotateLeft();
    }

    if (posHead.x + head->width >= width)
        posHead.x -= ((posHead.x + head->width) - width);
    if (posHead.x < 0)
        posHead.x = 0;
}

void Game::restartGame()
{
    for (uint16_t i = 0; i < width * height; i++)
        matrix[i] = TetriCell::Empty;
    if (head != nullptr)
        delete head;
    if (next != nullptr)
        delete next;
    head = generateTetriminos();
    next = generateTetriminos();
    score = 0;
    gameOver = false;
    exit = false;
    timeGame = 0;
    acc = 0;
    level = 1;
    clearLine = 0;
    posHead.x = width / 2;
    posHead.y = 0;
}

bool Game::roofTouch()
{
    for (uint16_t j = 0; j < width; j++)
    {
        if (matrix[j] != TetriCell::Empty)
            return true;
    }
    return false;
}

void Game::render(long double delta, uint64_t tick)
{
    unused(delta);
    unused(tick);

    if (!gameOver)
        moveTetriminos(delta);
    else
    {
        if (IsKeyPressed(k_restart))
            restartGame();

        if (IsKeyPressed(k_exit))
            exit = true;
    }

    DrawRectangle(0, 0, width * sizeBlock, height * sizeBlock, GRAY);

    // Draw moving peace
    head->draw(posHead.x, posHead.y, sizeBlock);
    next->draw(12, 1, sizeBlock);

    // DrawRectangleLines(posHead.x * 32, posHead.y * 32, head->width * 32, head->height * 32, RED);

    for (uint16_t j = 0; j < width; j++)
    {
        for (uint16_t i = 0; i < height; i++)
        {
            DrawTexture(Tetriminos::TetriCellToTex(matrix[i * width + j]), j * sizeBlock, i * sizeBlock, WHITE);
        }
    }

    if (!gameOver)
    {
        acc += delta;
        if (acc >= 1.0L)
        {
            timeGame++;
            acc = 0;
        }
    } else {
        DrawText("Game Over", (3*sizeBlock)/2, (20*sizeBlock)/2, 40, BLACK);
    }
    std::string text = "Score: " + std::to_string(score) + "\nLevel: " + std::to_string(level) + "\nTime: " + std::to_string(timeGame) + "s";
    DrawText(text.c_str(), 0, g_app->height * 0.85, 20, BLACK);
    DrawText("R for restart, ESCAPE for exit", 0, g_app->height * 0.75, 20, BLACK);
}

void Game::process(long double delta, uint64_t tick)
{

    if (gameOver)
    {
    }
    else
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
                    next = generateTetriminos();

                    uint16_t nbline = checkClearLines();
                    clearLine += nbline;
                    if (clearLine % 10 == 0 && clearLine != 0) {
                        level++;
                        clearLine-=10;
                    }
                    if (nbline > 4)
                        nbline = 4;
                    score += (level * lineScores[nbline]);
                    posHead.x = width / 2;
                    posHead.y = 0;
                }
                else
                {
                    posHead.y++;
                }
            }
            gameOver = roofTouch();
        }
    }

    unused(delta);
    unused(tick);
}
