#pragma once
#include "stdafx.h"

namespace window
{
	static HINSTANCE Instance;
	static HWND Handle;

	inline LRESULT CALLBACK WndProc
	(
		HWND handle,
		uint message,
		WPARAM wParam,
		LPARAM lParam
	)
	{
		switch (message)
		{
		case WM_CLOSE:

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(handle, message, wParam, lParam);
		}
		return 0;
	}

	inline void Create(HINSTANCE instance, const uint& width, const uint& height)
	{

		Instance = instance;
		WNDCLASSEX wndClass; //EX�� ���ݴ� Ȯ��ȹ���
		wndClass.cbClsExtra		= 0;
		wndClass.cbWndExtra		= 0;
		wndClass.hbrBackground	= static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wndClass.hCursor		= LoadCursor(nullptr, IDC_ARROW);
		wndClass.hIcon			= LoadIcon(nullptr, IDI_ERROR);
		wndClass.hIconSm		= LoadIcon(nullptr, IDI_ERROR);
		wndClass.hInstance		= instance;
		wndClass.lpfnWndProc	= static_cast<WNDPROC>(WndProc);
		wndClass.lpszClassName	= L"D2DllGame";
		wndClass.lpszMenuName	= nullptr;
		wndClass.style			= CS_HREDRAW | CS_VREDRAW;
		wndClass.cbSize			= sizeof(WNDCLASSEX);

		auto check = RegisterClassEx(&wndClass);
		assert(check != 0);

		Handle = CreateWindowExW
		(

			WS_EX_APPWINDOW,
			L"D2DllGame",
			L"D2DllGame",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<int>(width),
			static_cast<int>(height),
			nullptr,
			nullptr,
			instance,
			nullptr
		);

		assert(Handle != nullptr);


	}

	inline void Show()
	{
		SetForegroundWindow(Handle); //������â�� ���� ������
		SetFocus(Handle);
		ShowCursor(TRUE); //Ŀ���� ���̰�
		ShowWindow(Handle, SW_NORMAL); //������ȭ�� ���̱�
		UpdateWindow(Handle); 
	}

	inline const bool Update()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return msg.message != WM_QUIT;
	}
	
	inline void Destroy()
	{
		DestroyWindow(Handle);
		UnregisterClass(L"D2DllGame", Instance);
	}
	//������ ������ ���̴µ� ���⼭ �Ⱥ��̴����� 
	//�������� ������ ��������
	inline const uint GetWidth()
	{
		RECT rect;
		GetClientRect(Handle, &rect);//&rect �������ּ�
		return static_cast<uint>(rect.right - rect.left);

	}

	inline const uint GetHeight()
	{
		RECT rect;
		GetClientRect(Handle, &rect);//&rect �������ּ�
		return static_cast<uint>(rect.bottom - rect.top);
	}

	inline void Settings()
	{
		Settings::Get().SetwindowInstance(Instance);
		Settings::Get().SetwindowHandle(Handle);
		Settings::Get().SetWidth(static_cast<float>(GetWidth()));
		Settings::Get().SetHeight(static_cast<float>(GetHeight()));
	}
}