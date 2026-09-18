#include <Global.hpp>
#include "App.hpp"

std::unique_ptr<App> g_app;


void setGlobal(std::unique_ptr<App> app) {
    g_app = std::move(app);
}
