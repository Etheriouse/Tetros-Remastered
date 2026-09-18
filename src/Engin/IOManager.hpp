#ifndef YUZUENGIN_IOMANAGER_HPP
#define YUZUENGIN_IOMANAGER_HPP

#include <raylib.h>
#include <string>

namespace YuzuEnginIO
{
    typedef struct
    {
        bool down, pressed, pressedRepeat, release, up;
    } KeyState;

    typedef struct
    {
        bool down, pressed, release, up;
        Vector2 delta, pos, wheelXY;
        float wheel;
    } MouseState;
};

class IOManager
{

public:
    IOManager();
    // function of this object is to
    // read and write save file
    // read user input ( keyboard mouse )
    // read game file like map of dungeon
    // other things

    void getTextEnter(std::string &text);
    YuzuEnginIO::KeyState getKey(KeyboardKey k);
    YuzuEnginIO::MouseState getMouse(MouseButton m);
    bool isDragged(MouseButton m);

    // GameIO::MouseState getMouse(MouseCursor m);
};

#endif