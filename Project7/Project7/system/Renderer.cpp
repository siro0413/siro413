#include "stdafx.h"
#include "Renderer.h"

void Renderer::Render(status * status)
{
	MoveCursor(status->GetPosition(), status->GetSymbol());
}

void Renderer::Render(const Pos & pos, const char * str)
{
	MoveCursor(pos, str);

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
