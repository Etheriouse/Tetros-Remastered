#ifndef YUZUENGIN_GLOBAL_HPP
#define YUZUENGIN_GLOBAL_HPP

#include <memory>

class App;

void setGlobal(std::unique_ptr<App> app);

extern std::unique_ptr<App> g_app;

#endif