#include <Windows.h>
#include <string>
using namespace std;
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


bool Intersect(const RECT& lhs,const RECT& rhs) //left hand size , right hand size
{
	bool bCheck = true;
	bCheck &= lhs.left <= rhs.right;
	bCheck &= lhs.right >= rhs.left;
	bCheck &= lhs.top <= rhs.bottom;
	bCheck &= lhs.bottom >= rhs.top;

	return bCheck;

}

bool Interscect(OUT RECT* outRect, IN const RECT& lhs, IN const RECT& rhs)//*c �� ��ȯ���̵��� * //&lhs��rhs�� ������
{
	outRect->left = max(lhs.left, rhs.left); //���� ��ū��
	outRect->top = max(lhs.top, rhs.top);
	outRect->right = min(lhs.right, rhs.right);
	outRect->bottom = min(lhs.bottom, rhs.bottom);
	//�̰� ��������
	bool bCheck = false;
	bCheck |= (outRect->right - outRect->left) < 1; //1�̻󳪿��� �浹�Ǿ���
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
#pragma region �޽����ڽ�
		//	case WM_LBUTTONDOWN:
		//		MessageBox
		//		(
		//			hwnd,
		//			L"����� �޸��Դϱ�?",
		//			L"Error",
		//			MB_OK
		//		);
		//		break;
#pragma endregion

#pragma region �ؽ�Ʈ
	//case WM_LBUTTONDOWN: //ȭ���� �������� ������
	//{
	//	wstring str = L"��� ����";
	//	HDC hdc = GetDC(hwnd); //DC : Device Context
	//	TextOut(hdc, 200, 200, str.c_str(), str.length());//TextOut�� ���
	//	ReleaseDC(hwnd, hdc);
	//}


	//		break;
	//case WM_PAINT: //���ۺ��� ȣ��
	//{
	//	wstring str = L"WM_PAINT �޽��� �߻�";
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hwnd, &ps); //DC�� ������ �ΰ��� ���
	//	TextOut(hdc, 200, 400, str.c_str(), str.length());
	//	EndPaint(hwnd, &ps); //BeginPaint �� EndPaint �� ��Ʈ   �����ִ� ��Ȱ

	//}
	//	break;
#pragma endregion

#pragma region �ؽ�Ʈ move
	//case WM_KEYDOWN:
	//	if (wParam == VK_UP) //wParam �Ű�� ������ Ȯ�����ִ� �Լ�
	//		position.y -= 10;
	//	else if (wParam == VK_DOWN)
	//		position.y += 10;

	//	if (wParam == VK_LEFT)
	//		position.x -= 10;		
	//	if (wParam == VK_RIGHT)
	//		position.x += 10;
	//	//�̴�θ� �ϸ� �������� �ʴ´� WM_PAINT �� �ѹ��� ȣ��Ǳ⿡

	//	InvalidateRect(hwnd, nullptr, TRUE); //FALSE�Ͻ� �ܻ��� ���� ������ WM_PAINT�� ȣ���ϴ��Լ�
	//	//TRUE�� �ִ������� API�� �ҹ��ڰ� ������
	//	break;

	//case WM_PAINT: //key�� �������� �������Ҽ��ִ°�
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hwnd, &ps);
	//	TextOut(hdc, position.x, position.y, L"��", 1);
	//	EndPaint(hwnd, &ps);
	//}
	//	break;
#pragma endregion

#pragma region ���콺��ǥ
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

#pragma region �׸���
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

#pragma region ���� �׸���
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

#pragma region ���� �׸���
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

#pragma region �浹

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

		Rectangle(hdc, rect1.left, rect1.top, rect1.right, rect1.bottom); //�����׷������� �浹�� �ڷΰ�
		Rectangle(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);

		if (bIntersect)
		{
			//wstring str = L"�����ϸ�Ʈ �����Ŵ�";
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
