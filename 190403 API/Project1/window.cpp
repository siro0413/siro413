#include <Windows.h>

//LPSTR -> char*
//LPCSRT -> const char*
//LPWSRT -> wchar*
//LPCWSRT -> const wchar*

//����1
//__stcall;
//__cdecl
//__thiscall
//__fastcall

LRESULT CALLBACK WndProc
(
	HWND hwnd, //window handel
	UINT message, //unsigend int
	WPARAM wParam, //�ΰ����� �ǹ̰� �ٴٸ�
	LPARAM iParam

);



int APIENTRY WinMain
(
	HINSTANCE hinstance, //�������� �ĺ��� - �ڵ��Էµ�
	HINSTANCE previnstance,
	LPSTR ipszCmdaram, //LP = long point , STR = string ,sz = null������
	int nCmdShow
)
{
	WNDCLASS wndclass; //����ܰ�
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));//��������ϴ»�
	wndclass.hCursor = LoadIcon(nullptr, IDC_HAND); //Ŀ����� 
	wndclass.hIcon = LoadIcon(nullptr, IDI_ERROR); //�����ܸ��
	wndclass.hInstance = hinstance;
	wndclass.lpfnWndProc = static_cast<WNDPROC> (WndProc);//lpfn = �Լ��� ������
	wndclass.lpszClassName = L"FirstWindow"; //���̵������ϋ� L ǥ��
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
		hinstance,
		nullptr
	);

	ShowWindow(hwnd, nCmdShow);
	
	//MSG message = { 0 }; �Ҿ���
	MSG message;
	ZeroMemory(&message, sizeof(MSG)); //�ξ��������̴�

	//while (GetMessage(&message, 0, 0, 0)) //Ű���� ���ö����� ����
	//{
	//	TranslateMessage(&message); //����Ű���� �Ű�� �������� ���� (�޽��� ����)
	//	DispatchMessage(&message); //message�� �����¿�Ȱ 
	//}

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

	UnregisterClass(L"FirstWindow", hinstance);
	return message.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM iParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		MessageBox
		(
			hwnd,
			L"����� �޸��Դϱ�?",
			L"Error",
			MB_OK
		);
		break;
		
	case WM_CLOSE: //window message ����
		//DestroyWindow(hwnd);
		//break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, iParam); //��� �Ѿ�°͵��� def�� ó������
	}

	return 0;
}
