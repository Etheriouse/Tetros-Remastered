#include <iostream>
#include "App.hpp"
#include "ylib.hpp"

int main(int argc, char const *argv[])
{

    unused(argc);
    unused(argv);

    return App::createInstance().run();
}
