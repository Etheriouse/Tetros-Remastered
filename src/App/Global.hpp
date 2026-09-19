#ifndef YUZUENGIN_GLOBAL_HPP
#define YUZUENGIN_GLOBAL_HPP

#include <memory>

class App;

void setGlobal(App *app);

extern App *g_app;

#endif