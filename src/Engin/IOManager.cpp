#include "IOManager.hpp"

IOManager::IOManager()
{
}

void IOManager::getTextEnter(std::string &text)
{
    int key = GetCharPressed();
    while (key > 0)
    {
        if (key >= 32 && key <= 125)
            text += static_cast<char>(key);

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !text.empty())
        text.pop_back();
}

YuzuEnginIO::KeyState IOManager::getKey(KeyboardKey k)
{
    return {
        IsKeyDown(k),
        IsKeyPressed(k),
        IsKeyPressedRepeat(k),
        IsKeyReleased(k),
        IsKeyUp(k)};
}

YuzuEnginIO::MouseState IOManager::getMouse(MouseButton m)
{
    return {
        IsMouseButtonDown(m),
        IsMouseButtonPressed(m),
        IsMouseButtonReleased(m),
        IsMouseButtonUp(m),
        GetMouseDelta(),
        GetMousePosition(),
        GetMouseWheelMoveV(),
        GetMouseWheelMove()
    };
}

bool IOManager::isDragged(MouseButton m)
{
    Vector2 v = GetMouseDelta();
    return (v.x != 0 || v.y != 0) && IsMouseButtonPressed(m);
}
