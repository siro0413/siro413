#include "stdafx.h"
#include "Pramwork/core/Window.h"
#include "Pramwork/core/engine.h"


int APIENTRY WinMain
(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow

)
{
	window::Create(hInstance, 1280, 720);
	window::Show();
	window::Settings();
	
	Engine* engine = new Engine();

	while (window::Update())
	{
		engine->Update();
		engine->Render();

	}

	SAFE_DELETE(engine);

	window::Destroy();
	return 0;
}