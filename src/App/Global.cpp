#include <Global.hpp>
#include "App.hpp"

App* g_app;

void setGlobal(App* app) {
    g_app = app;
}
