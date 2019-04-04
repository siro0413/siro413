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
	WPARAM wParam, //�ΰ����� �ǹ̰� �ٴٸ�
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


	WNDCLASS wndclass; //����ܰ�
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));//��������ϴ»�
	wndclass.hCursor = LoadIcon(nullptr, IDC_HAND); //Ŀ����� 
	wndclass.hIcon = LoadIcon(nullptr, IDI_ERROR); //�����ܸ��
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = static_cast<WNDPROC> (WndProc);//lpfn = �Լ��� ������
	wndclass.lpszClassName = L"FirstWindow"; //���̵�������?? L ǥ��
	wndclass.lpszMenuName = nullptr;
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //���� ���� �ø��� ���δ� CS =CLASS STYLE
	RegisterClass(&wndclass); //���

	HWND hwnd = CreateWindow //window�� ����´ܰ�
	(
		L"FirstWindow",
		L"Hellow,Window",
		WS_OVERLAPPEDWINDOW, //������ �����츸���� �⺻���õǾ��ִ� �Լ�
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
	ZeroMemory(&message, sizeof(MSG)); //�ξ��������̴�
	while (true)
	{
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
				break;

			TranslateMessage(&message); //����Ű���� �Ű�� �������� ���� (�޽��� ����)
			DispatchMessage(&message); //message�� �����¿�Ȱ 
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
