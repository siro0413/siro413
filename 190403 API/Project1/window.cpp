#include <Windows.h>

//LPSTR -> char*
//LPCSRT -> const char*
//LPWSRT -> wchar*
//LPCWSRT -> const wchar*

//과제1
//__stcall;
//__cdecl
//__thiscall
//__fastcall

LRESULT CALLBACK WndProc
(
	HWND hwnd, //window handel
	UINT message, //unsigend int
	WPARAM wParam, //부가정보 의미가 다다름
	LPARAM iParam

);



int APIENTRY WinMain
(
	HINSTANCE hinstance, //윈도우의 식별자 - 자동입력됨
	HINSTANCE previnstance,
	LPSTR ipszCmdaram, //LP = long point , STR = string ,sz = null문자형
	int nCmdShow
)
{
	WNDCLASS wndclass; //설계단계
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));//배경을정하는색
	wndclass.hCursor = LoadIcon(nullptr, IDC_HAND); //커서모양 
	wndclass.hIcon = LoadIcon(nullptr, IDI_ERROR); //아이콘모양
	wndclass.hInstance = hinstance;
	wndclass.lpfnWndProc = static_cast<WNDPROC> (WndProc);//lpfn = 함수의 포인터
	wndclass.lpszClassName = L"FirstWindow"; //와이드차형일떈 L 표시
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
		hinstance,
		nullptr
	);

	ShowWindow(hwnd, nCmdShow);
	
	//MSG message = { 0 }; 불안정
	MSG message;
	ZeroMemory(&message, sizeof(MSG)); //훨씬안정적이다

	//while (GetMessage(&message, 0, 0, 0)) //키값이 들어올때까지 멈춤
	//{
	//	TranslateMessage(&message); //문자키들을 어떤키를 눌렀는지 번역 (메시지 번역)
	//	DispatchMessage(&message); //message로 보내는역활 
	//}

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
			L"당신은 휴먼입니까?",
			L"Error",
			MB_OK
		);
		break;
		
	case WM_CLOSE: //window message 약자
		//DestroyWindow(hwnd);
		//break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, iParam); //없어서 넘어가는것들은 def가 처리해줌
	}

	return 0;
}
