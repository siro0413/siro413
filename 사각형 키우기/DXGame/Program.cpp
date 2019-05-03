#include "stdafx.h"
#include "Framework/Core/Window.h"
#include "Framework/Core/Rect.h"
#include "Framework/Core/Game.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	Window::Create(hInstance, 1280, 720);
	Window::Show();
	Window::Settings();

	Graphics* graphics = new Graphics();
	graphics->Initialize();

	Game* game = new Game(graphics);
	//Rect* rect = new Rect(graphics);

	while (Window::Update())
	{
		game->Update();

		graphics->BeginScene();
		{

			game->Render();

		}
		graphics->EndScene();
	}

	SAFE_DELETE(game);
	SAFE_DELETE(graphics);

	Window::Destroy();

	return 0;
}