#include "stdafx.h"
#include "Game.h"
#include "Framework/Core/Rect.h"

Game::Game(Graphics * graphics)
	: graphics(graphics)
{
	srand(static_cast<UINT>(time(nullptr)));

	rect = new Rect();
	rect->init(this->graphics, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	class Rect* rectObj[18];
	for (int i = 0; i < 18; i++)
	{
		float r = rand() % 255 + 1;
		float g = rand() % 255 + 1;
		float b = rand() % 255 + 1;

		rectObj[i] = new Rect(this->graphics, D3DXCOLOR(r / 255, g / 255, b / 255, 1.0f));
		rects.push_back(rectObj[i]);
	}

}

Game::~Game()
{
	rects.clear();

	SAFE_DELETE(rect);
}

void Game::Update()
{
	Collision();

	if (rects.size() == 0)
	{
		bCheck = true;
	}

	for (int i = 0; i < rects.size(); i++)
	{
		rects[i]->autoMove();
		rects[i]->Update2();
	}
	
	rect->Update();

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		rect->pos.y += 5;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		rect->pos.y -= 5;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		rect->pos.x -= 5;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		rect->pos.x += 5;
	}



}

void Game::Render()
{
	for (int i = 0; i < rects.size(); i++)
	{
		rects[i]->Render();
	}

	rect->Render();


}

void Game::Collision()
{
	D3DXCOLOR _color;

	for (int i = 0; i < rects.size(); i++)
	{
		if (rect->rectPos.top > rects[i]->rectsPos.bottom &&
			rect->rectPos.bottom < rects[i]->rectsPos.top &&
			rect->rectPos.left < rects[i]->rectsPos.right &&
			rect->rectPos.right > rects[i]->rectsPos.left)
		{
			_color = rects[i]->_color;
			rect->size.x += 10;
			rect->size.y += 10;
			rect->init(this->graphics, _color);
			rects.erase(rects.begin() + i);
		}

	}
}
