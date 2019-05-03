#include "stdafx.h"
#include "Editor.h"
#include "Core/Window.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain
(
    HINSTANCE hInstance,
    HINSTANCE prevInstance,
    LPSTR lpszCmdParam,
    int nCmdShow
)
{
    Window::Create(hInstance, 1280, 720);
    Window::Show();
    Window::Settings();

	//std::unique_ptr<Editor> editor = std::make_unique<Editor>();
	auto  editor = std::make_unique<Editor>();
	//auto로 가능하며 지울필요가없다
	//알아서 nullptr로 초기화하기떄문에 초기화할 필요가없다

	Window::Input_proc = Input::MouseProc;
	Window::Editor_proc = ImGui_ImplWin32_WndProcHandler;
	Window::Resize = [&editor](const uint& width,const uint& height)
	{
		if (editor)
			editor->Resize(width, height);
	};

	// [변수캡처](파라미터)->리턴타입 {함수 구현부}(넘길 인자)
	// 변수캡처: 현재 함수에서 사용하는 외부변수
	// = 을 넣으면 해당함수의 모든 변수사용
	// & 을 넣으면 모든 변수를 참조로 받음
	// 비워두면 아무것도 안씀
	// 전역변수는 캡처할 필요없음

	//파라미터 : 함수에서 받을인자
	//리턴타입 : 함수의 반환형 / 리턴값이 void면 생략가능
	//함수구현부 : 함수몸체
	//넘길인자 : 호출하는 함수에 넘겨줄값


    while (Window::Update())
    {
		editor->Update();
		editor->Render();
    }

    Window::Destroy();
    return 0;
}