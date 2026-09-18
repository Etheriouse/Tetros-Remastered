#include "Menu.hpp"

Menu::Menu() {}

Menu::Menu(bool *running, Game **game) : running(running), game(game)
{
}

void Menu::render(long double delta, uint64_t tick)
{
    unused(delta);
    unused(tick);
}

void Menu::process(long double delta, uint64_t tick)
{
    unused(delta);
    unused(tick);
}