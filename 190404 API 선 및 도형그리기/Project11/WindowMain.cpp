#include "stdafx.h"
#include "Drow.h"
#include "SeletMenu.h"
SelectMenu* a;
DrawObject* b;
POINT _mousePoint;



LRESULT CALLBACK WndProc
(
	HWND hwnd, //window handel
	UINT message, //unsigend int
	WPARAM wParam, //부가정보 의미가 다다름
	LPARAM lParam

);

int APIENTRY WinMain
(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow
)
{

	a = new SelectMenu;
	b = new DrawObject;
	b->setSelectedOptAddress(a);


	WNDCLASS wndclass; //설계단계
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));//배경을정하는색
	wndclass.hCursor = LoadIcon(nullptr, IDC_HAND); //커서모양 
	wndclass.hIcon = LoadIcon(nullptr, IDI_ERROR); //아이콘모양
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = static_cast<WNDPROC> (WndProc);//lpfn = 함수의 포인터
	wndclass.lpszClassName = L"FirstWindow"; //와이드차형일?? L 표시
	wndclass.lpszMenuName = nullptr;
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //수직 수평 늘리고 줄인다 CS =CLASS STYLE
	RegisterClass(&wndclass); //등록

	HWND hwnd = CreateWindow //window를 만드는단계
	(
		L"FirstWindow",
		L"Hellow,Window",
		WS_OVERLAPPEDWINDOW, //간단한 윈도우만들라면 기본세팅되어있는 함수
		0,
		0,
		1024,
		720,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	ShowWindow(hwnd, nCmdShow);
	MSG message;
	ZeroMemory(&message, sizeof(MSG)); //훨씬안정적이다
	while (true)
	{
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
				break;

			TranslateMessage(&message); //문자키들을 어떤키를 눌렀는지 번역 (메시지 번역)
			DispatchMessage(&message); //message로 보내는역활 
		}
	}
	DestroyWindow(hwnd);

	UnregisterClass(L"FirstWindow", hInstance);
	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;



	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
	{
		a->selectOptions();

		InvalidateRect(hwnd, NULL, true);
	}
	return 0;
	case WM_LBUTTONDOWN:
	{
		b->startDraw(_mousePoint);

		InvalidateRect(hwnd, NULL, true);
	}
	return 0;
	case WM_LBUTTONUP:
	{
		b->saveObject();
		InvalidateRect(hwnd, NULL, true);
	}
	return 0;
	case WM_MOUSEMOVE:
	{
		_mousePoint.x = LOWORD(lParam);
		_mousePoint.y = HIWORD(lParam);
		b->makeObject(_mousePoint);

		//InvalidateRect(hwnd, NULL, true);
	}
	return 0;

	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);

		a->ShowMenu(hdc);
		a->ShowOption(hdc);
		b->showDrawingObject(hdc);
		b->showSavedObject(hdc);

	}
	return 0;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);

	}

}
