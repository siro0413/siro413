#include "stdafx.h"
#include "Renderer.h"
#include "../Gameobj/GameObject.h"


void Renderer::Render(GameObject * object)
{
    MoveCursor(object->GetPosition(), object->GetSymbol());
}

void Renderer::Render(const Pos & pos, const char * str)
{
    MoveCursor(pos, str);
    //int a = 10;
    //int b = a;
    //l-value, r-value -> &a, &10
}

void Renderer::MoveCursor(const Pos & pos, const char * str)
{
    COORD coord = { pos.x, pos.y };

    SetConsoleCursorPosition
    (
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );

    std::cout << str;
}
