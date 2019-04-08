#include "stdafx.h"
#include "Paramwork/core/Window.h"
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

	while (window::Update())
	{

	}

	window::Destroy();
	return 0;
}