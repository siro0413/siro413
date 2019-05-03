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
	//auto�� �����ϸ� �����ʿ䰡����
	//�˾Ƽ� nullptr�� �ʱ�ȭ�ϱ⋚���� �ʱ�ȭ�� �ʿ䰡����

	Window::Input_proc = Input::MouseProc;
	Window::Editor_proc = ImGui_ImplWin32_WndProcHandler;
	Window::Resize = [&editor](const uint& width,const uint& height)
	{
		if (editor)
			editor->Resize(width, height);
	};

	// [����ĸó](�Ķ����)->����Ÿ�� {�Լ� ������}(�ѱ� ����)
	// ����ĸó: ���� �Լ����� ����ϴ� �ܺκ���
	// = �� ������ �ش��Լ��� ��� �������
	// & �� ������ ��� ������ ������ ����
	// ����θ� �ƹ��͵� �Ⱦ�
	// ���������� ĸó�� �ʿ����

	//�Ķ���� : �Լ����� ��������
	//����Ÿ�� : �Լ��� ��ȯ�� / ���ϰ��� void�� ��������
	//�Լ������� : �Լ���ü
	//�ѱ����� : ȣ���ϴ� �Լ��� �Ѱ��ٰ�


    while (Window::Update())
    {
		editor->Update();
		editor->Render();
    }

    Window::Destroy();
    return 0;
}