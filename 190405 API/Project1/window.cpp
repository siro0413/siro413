#include <Windows.h>
#include <string>
using namespace std;
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


bool Intersect(const RECT& lhs,const RECT& rhs) //left hand size , right hand size
{
	bool bCheck = true;
	bCheck &= lhs.left <= rhs.right;
	bCheck &= lhs.right >= rhs.left;
	bCheck &= lhs.top <= rhs.bottom;
	bCheck &= lhs.bottom >= rhs.top;

	return bCheck;

}

bool Interscect(OUT RECT* outRect, IN const RECT& lhs, IN const RECT& rhs)//*c 는 반환값이들어가서 * //&lhs와rhs는 변수값
{
	outRect->left = max(lhs.left, rhs.left); //둘중 더큰값
	outRect->top = max(lhs.top, rhs.top);
	outRect->right = min(lhs.right, rhs.right);
	outRect->bottom = min(lhs.bottom, rhs.bottom);
	//이게 곂쳐진값
	bool bCheck = false;
	bCheck |= (outRect->right - outRect->left) < 1; //1이상나오면 충돌되었다
	bCheck |= (outRect->bottom - outRect->top) < 1; 

	if (bCheck)
	{
		outRect->left = 0;
		outRect->top = 0;
		outRect->right = 0;
		outRect->bottom = 0;
		return false;
	}
	return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM iParam)
{
	//static POINT position;
	//static POINT start;
	//static POINT end;
	//static BOOL bClicked = FALSE;

	static RECT rect1 = { 100,100,200,200 };
	static RECT rect2 = { 500,500,700,700 };
	static RECT c = { 0,0,0,0 };

	static bool bIntersect = false;


	switch (message)
	{
#pragma region 메시지박스
		//	case WM_LBUTTONDOWN:
		//		MessageBox
		//		(
		//			hwnd,
		//			L"당신은 휴먼입니까?",
		//			L"Error",
		//			MB_OK
		//		);
		//		break;
#pragma endregion

#pragma region 텍스트
	//case WM_LBUTTONDOWN: //화면이 가려질때 지워짐
	//{
	//	wstring str = L"어딜 만져";
	//	HDC hdc = GetDC(hwnd); //DC : Device Context
	//	TextOut(hdc, 200, 200, str.c_str(), str.length());//TextOut로 출력
	//	ReleaseDC(hwnd, hdc);
	//}


	//		break;
	//case WM_PAINT: //시작부터 호출
	//{
	//	wstring str = L"WM_PAINT 메시지 발생";
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hwnd, &ps); //DC를 얻어오는 두가지 방법
	//	TextOut(hdc, 200, 400, str.c_str(), str.length());
	//	EndPaint(hwnd, &ps); //BeginPaint 와 EndPaint 는 세트   지워주는 역활

	//}
	//	break;
#pragma endregion

#pragma region 텍스트 move
	//case WM_KEYDOWN:
	//	if (wParam == VK_UP) //wParam 어떤키가 들어가는지 확인해주는 함수
	//		position.y -= 10;
	//	else if (wParam == VK_DOWN)
	//		position.y += 10;

	//	if (wParam == VK_LEFT)
	//		position.x -= 10;		
	//	if (wParam == VK_RIGHT)
	//		position.x += 10;
	//	//이대로만 하면 움직이지 않는다 WM_PAINT 가 한번만 호출되기에

	//	InvalidateRect(hwnd, nullptr, TRUE); //FALSE일시 잔상이 남음 강제로 WM_PAINT를 호출하는함수
	//	//TRUE를 넣는이유는 API는 소문자가 없었음
	//	break;

	//case WM_PAINT: //key가 가려져도 렌더링할수있는곳
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hwnd, &ps);
	//	TextOut(hdc, position.x, position.y, L"◎", 1);
	//	EndPaint(hwnd, &ps);
	//}
	//	break;
#pragma endregion

#pragma region 마우스좌표
	//case WM_MOUSEMOVE:
	//	position.x = LOWORD(iParam);
	//	position.y = HIWORD(iParam);
	//	InvalidateRect(hwnd, nullptr, TRUE);
	//	break;

	//case WM_PAINT:
	//{
	//	wstring str = L"";
	//	str += to_wstring(position.x); //10->"10"
	//	str += L", ";
	//	str += to_wstring(position.y);
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hwnd, &ps);
	//	TextOut(hdc, position.x +10, position.y+10, str.c_str(), str.length());

	//	//Line
	//	MoveToEx(hdc, 300, 300, nullptr);
	//	LineTo(hdc, 500, 500);


	//	EndPaint(hwnd, &ps);
	//}
	//	break;
#pragma endregion

#pragma region 그림판
	//case WM_LBUTTONDOWN:
	//	position.x = LOWORD(iParam);
	//	position.y = HIWORD(iParam);
	//	bClicked = TRUE;
	//	
	//	break;

	//case WM_MOUSEMOVE:
	//	if (bClicked)
	//	{
	//		HDC hdc = GetDC(hwnd);

	//		MoveToEx(hdc, position.x, position.y, nullptr);

	//		position.x = LOWORD(iParam);
	//		position.y = HIWORD(iParam);

	//		LineTo(hdc, position.x, position.y);
	//		ReleaseDC(hwnd, hdc);
	//	}
	//	break;

	//case WM_LBUTTONUP:
	//	bClicked = FALSE;

	//	break;
#pragma endregion

#pragma region 도형 그리기
	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hwnd, &ps);
	//	Rectangle(hdc, 100, 100, 500, 500);
	//	Ellipse(hdc, 100, 100, 500, 500);


	//	EndPaint(hwnd, &ps);
	//}

	//	break;
#pragma endregion

#pragma region 도형 그림판
	//case WM_LBUTTONDOWN:
	//	start.x = LOWORD(iParam);
	//	start.y = HIWORD(iParam);
	//	bClicked = TRUE;
	//	
	//	break;

	//case WM_MOUSEMOVE:
	//	if (bClicked)
	//	{
	//		end.x = LOWORD(iParam);
	//		end.y = HIWORD(iParam);
	//		InvalidateRect(hwnd, nullptr, FALSE);


	//	}
	//	break;

	//case WM_LBUTTONUP:
	//	bClicked = FALSE;
	//	break;

	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hwnd, &ps);

	//	//Bursh
	//	//HBRUSH curBrush = CreateSolidBrush(RGB(0, 255, 255));
	//	HBRUSH curBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(215, 225, 255));
	//	HBRUSH oldBrush =static_cast<HBRUSH>(SelectObject(hdc, curBrush));
	//	//Pen
	//	HPEN curPen = CreatePen(PS_SOLID, 2, (RGB(130, 100, 154)));
	//	HPEN oldPen = static_cast<HPEN>(SelectObject(hdc, curPen));

	//	Rectangle(hdc, start.x, start.y,end.x , end.y);
	//	SelectObject(hdc, oldPen);
	//	DeleteObject(curPen);
	//	EndPaint(hwnd, &ps);
	//}
	//	break;
#pragma endregion

#pragma region 충돌

	case WM_KEYDOWN:
		if (wParam == VK_UP)
		{
			rect1.top -= 10;
			rect1.bottom -= 10;

		}

		else if (wParam == VK_DOWN)
		{
			rect1.top += 10;
			rect1.bottom += 10;
			
		}		

		if (wParam == VK_LEFT)
		{
			rect1.left -= 10;
			rect1.right -= 10;

		}

		else if (wParam == VK_RIGHT)
		{
			rect1.left += 10;
			rect1.right += 10;

		}

		bIntersect = Interscect(&c, rect1, rect2);

		InvalidateRect(hwnd, nullptr, TRUE);
		break;


	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		Rectangle(hdc, rect1.left, rect1.top, rect1.right, rect1.bottom); //먼저그려진것이 충돌시 뒤로감
		Rectangle(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);

		if (bIntersect)
		{
			//wstring str = L"라인하르트 나가신다";
			//TextOut(hdc, 500, 300, str.c_str(), str.length());

			HBRUSH curBrush = CreateSolidBrush(RGB(255, 255, 0));
			HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(hdc, curBrush));
			
			Rectangle(hdc, c.left, c.top, c.right, c.bottom);

			SelectObject(hdc, oldBrush);
			DeleteObject(curBrush);

		}

		EndPaint(hwnd, &ps);
	}
		break;


#pragma endregion 

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
