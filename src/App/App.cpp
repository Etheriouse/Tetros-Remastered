#include "App.hpp"
#include <memory>

App::App()
{
}

App::App(uint32_t width, uint32_t height, const char *name) : width(width), height(height), name(name)
{
}

App::~App()
{
    if (game != nullptr)
        delete game;
}

/**
 * ========================= Main function =========================
 */

int App::run()
{
    setGlobal(this);

    FPS = 100;
    TPS = 70;
    TICK_TIME = 1.0 / ((double)TPS);

    InitWindow(width, height, name);
    textureManager.run();

    menu = Menu(&running, &game);
    game = new Game();

    long double delta = 0, acc_s = 0, acc_ds = 0, acc_p = 0;
    uint64_t tick = 0, fps = 0, tick_s = 0, tmp = 0, last = yLib::time::getNanoSecondes();

    SetTargetFPS(FPS);

    while (running && !appIsClosing())
    {
        tmp = yLib::time::getNanoSecondes();
        delta = static_cast<long double>(tmp - last) / yLib::time::OneBillion;
        last = tmp;

        // delta caper a 250ms
        // evite de faire 150000 calcule dans une loop
        if (delta > 0.25L)
            delta = 0.25L;

        acc_p += delta;

        while (acc_p >= TICK_TIME)
        {
            process(delta, tick);
            acc_p -= TICK_TIME;

            tick++;
            tick_s++;
        }

        render(delta, tick);
        fps++;

        acc_s += delta;
        if (acc_s >= 1.0L)
        {
            _tps = tick_s;
            // std::cout << "process tick: " << tick_s << std::endl;
            tick_s = 0;
            acc_s -= 1.0L;
        }

        acc_ds += delta;
        if (acc_ds >= 1.0L)
        {
            _fps = fps;
            // std::cout << "fps: " << fps*2 << std::endl;
            fps = 0;
            acc_ds -= 1.0L;
        }
    }

    textureManager.exit();

    CloseWindow();

    return 0;
}

void App::render(long double delta, uint64_t tick)
{

    unused(delta);
    unused(tick);

    BeginDrawing();
    ClearBackground(WHITE);

    if (game != nullptr)
    {
        game->render(delta, tick);
    }
    else
    {
        menu.render(delta, tick);
    }

    std::ostringstream ss;
    ss << "FPS: " << _fps << "\nTPS: " << _tps;
    DrawText(ss.str().c_str(), 0, 0, 20, BLACK);
    EndDrawing();
}

void App::process(long double delta, uint64_t tick)
{
    unused(delta);
    unused(tick);

    if (game != nullptr)
    {
        game->process(delta, tick);
    }
    else
    {
        menu.process(delta, tick);
    }
}

/**
 * ========================= Getter function =========================
 */

bool App::appIsClosing()
{
    //  std::cout << "not is key down escape : " <<  !IsKeyDown(KEY_ESCAPE) <<  " full condition : " << (WindowShouldClose() && !IsKeyDown(KEY_ESCAPE)) << std::endl;
    return WindowShouldClose() && !IsKeyDown(KEY_ESCAPE);
}