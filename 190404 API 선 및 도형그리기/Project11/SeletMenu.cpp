#include "stdafx.h"
#include "SeletMenu.h"

SelectMenu::SelectMenu()
{
	//메뉴의 종류
	 MenuName[0] = L"선의 패턴";
	 MenuName[1] = L"선의 굵기";
	 MenuName[2] = L"선의 색상";
	 MenuName[3] = L"도형의 종류";
	 MenuName[4] = L"도형의 색상";
	 MenuName[5] = L"도형의 패턴";

	 //색상
	 //Color[0] = RGB(0, 0, 0);		//black
	 Color[0] = RGB(1, 0, 0);		//black
	 Color[1] = RGB(255, 0,0 );		//red
	 Color[2] = RGB(0, 0, 255);		//blue
	 Color[3] = RGB(0, 255, 0);		//green
	 Color[4] = RGB(255, 255, 0);	//yellow

	 ZeroMemory(&Select, sizeof(Select));
	 ZeroMemory(&shape1, sizeof(shape1));

	 _SelectMenu = 0; //처음시작은 0번
	 _SelectColor = 0; // 처음시작은 0번
}

SelectMenu::~SelectMenu()
{
}
void SelectMenu::ShowMenu(HDC hdc)
{
	for (UINT i = 0; i < 6; i++)
	{
		wstring MenuNum;
		MenuNum += to_wstring(i + 1);
		MenuNum += L" ";
		MenuNum += MenuName[i];
		SetTextColor(hdc,RGB(0,0,0));

		if (i == _SelectMenu) SetTextColor(hdc, RGB(255, 0, 0));

		TextOut(hdc, menuStart.x, menuStart.y + i * menuTitleHeight, MenuNum.c_str(), MenuNum.length());

	}
}

void SelectMenu::ShowOption(HDC hdc)
{
	//wstring a;
	//a = L"방향키를 이용하여 옵션을 선택하세요.";
	//TextOut(hdc, 300, 50, a.c_str(), a.length());

	wstring b;
	b = L"Made by OTK";
	TextOut(hdc, 900,0, b.c_str(), b.length());

	//선의 패턴
	HPEN curPen1, oldPen1;
	curPen1 = CreatePen(Select.lineStyle, 1, RGB(0, 0, 0));
	oldPen1 = (HPEN)SelectObject(hdc, curPen1);
	MoveToEx(hdc, optionStart.x, optionStart.y + 0 * menuTitleHeight, NULL);
	//LineTo(hdc, optionStart.x + optionWidth * 2, optionStart.y + 0 * menuTitleHeight);
	SelectObject(hdc, oldPen1);
	DeleteObject(curPen1);

	//선의 굵기
	HPEN curPen2, oldPen2;
	curPen2 = CreatePen(Select.lineStyle, Select.lineThick, RGB(0, 0, 0));
	oldPen2 = (HPEN)SelectObject(hdc, curPen2);
	DeleteObject(oldPen1);
	MoveToEx(hdc, optionStart.x, optionStart.y  +1* menuTitleHeight, NULL);
	//LineTo(hdc, optionStart.x + optionWidth * 3, optionStart.y + 1 * menuTitleHeight);
	SelectObject(hdc, oldPen2);
	DeleteObject(curPen2);


	//선의 색상 
	HPEN curPen3, oldPen3;
	curPen3 = CreatePen(Select.lineStyle, Select.lineThick, Color[Select.lineColor]);
	oldPen3 = (HPEN)SelectObject(hdc, curPen3);
	DeleteObject(oldPen2);
	MoveToEx(hdc, optionStart.x, optionStart.y + 2 * menuTitleHeight, NULL);
	//LineTo(hdc, optionStart.x + optionWidth * 3, optionStart.y + 2 * menuTitleHeight);

	//도형 종류
	if (Select.shape == shape::Line)
	{
		//MoveToEx(hdc, optionStart.x, optionStart.y + 3 * menuTitleHeight, NULL);
		//LineTo(hdc, optionStart.x + optionWidth * 3, optionStart.y + 3 * menuTitleHeight);
	}
	else if (Select.shape == shape::Rect)
	{
		//Rectangle(hdc, optionStart.x, optionStart.y + 3 * menuTitleHeight,
		//	optionStart.x + optionWidth * 3, optionStart.y + 3.5 * menuTitleHeight);
	}
	else
	{
//		Ellipse(hdc, optionStart.x, optionStart.y + 3 * menuTitleHeight,
//			optionStart.x + optionWidth * 3, optionStart.y + 3.5 * menuTitleHeight);
	}

	//도형 색상
	HBRUSH curBrush1, oldBrush1;
	curBrush1 = CreateSolidBrush(Color[Select.polygonColor]);
	oldBrush1 = (HBRUSH)SelectObject(hdc, curBrush1);

	if (Select.shape == shape::Line)
	{
		//MoveToEx(hdc, optionStart.x, optionStart.y + 4 * menuTitleHeight, NULL);
		//LineTo(hdc, optionStart.x + optionWidth * 3, optionStart.y + 4 * menuTitleHeight);
	}
	else if (Select.shape == shape::Rect)
	{
		//Rectangle(hdc, optionStart.x, optionStart.y + 4 * menuTitleHeight,
		//	optionStart.x + optionWidth * 3, optionStart.y + 4.5 * menuTitleHeight);
	}
	else
	{
		//Ellipse(hdc, optionStart.x, optionStart.y + 4 * menuTitleHeight,
		//	optionStart.x + optionWidth * 3, optionStart.y + 4.5 * menuTitleHeight);
	}

	SelectObject(hdc, oldBrush1);
	DeleteObject(curBrush1);

	//도형 패턴
	HBRUSH curBrush2, oldBrush2;
	// 브러시 생성
	if (Select.polygonPattern == 0)
	{
		curBrush2 = CreateSolidBrush(Color[Select.polygonColor]);
	}
	else
	{
		curBrush2 = CreateHatchBrush(Select.polygonPattern, Color[Select.polygonColor]);
	}
	oldBrush2 = (HBRUSH)SelectObject(hdc, curBrush2);
	DeleteObject(oldBrush1);

	//화면에 띄우기
	if (Select.shape == shape::Line)
	{
		//MoveToEx(hdc, optionStart.x, optionStart.y + 5 * menuTitleHeight, NULL);
		//LineTo(hdc, optionStart.x + optionWidth * 3, optionStart.y + 5 * menuTitleHeight);
	}
	else if (Select.shape == shape::Rect)
	{
		//Rectangle(hdc, optionStart.x, optionStart.y + 5 * menuTitleHeight,
		//	optionStart.x + optionWidth * 3, optionStart.y + 5.5 * menuTitleHeight);
	}
	else
	{
		//Ellipse(hdc, optionStart.x, optionStart.y + 5 * menuTitleHeight,
		//	optionStart.x + optionWidth * 3, optionStart.y + 5.5 * menuTitleHeight);
	}

	//사용한 펜 브러시 삭제
	SelectObject(hdc, oldBrush2);
	DeleteObject(curBrush2);
	SelectObject(hdc, oldPen3);
	DeleteObject(curPen3);


}

void SelectMenu::selectOptions()
{
	// 메뉴 선택
	if ((GetAsyncKeyState(VK_UP) & 0x8000) && _SelectMenu > 0)
	{
		_SelectMenu--;
		_SelectColor = 0;
	}
	else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && _SelectMenu < numberOfMenus - 1)
	{
		_SelectMenu++;
		_SelectColor = 0;
	}

	// 옵션 선택
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && _SelectColor > 0)
	{
		_SelectColor--;
	}
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && _SelectColor < numberOfOptions - 1)
	{
		_SelectColor++;
	}

	// 메뉴 옵션 선택 (예외)처리
	switch (_SelectMenu)
	{
	case (UINT)Title::선의패턴:
		Select.lineStyle = _SelectColor;
		break;

	case (UINT)Title::선의굵기:
		if (Select.lineStyle == PS_SOLID) Select.lineThick = _SelectColor;
		else if (Select.lineThick = 1);
		break;

	case (UINT)Title::선의색상:
		Select.lineColor = _SelectColor;
		break;

	case (UINT)Title::도형종류:
		Select.shape = static_cast<shape>(_SelectColor);
		break;

	case (UINT)Title::도형색상:
		if (Select.shape != shape::Line) Select.polygonColor = _SelectColor;
		break;

	case (UINT)Title::도형패턴:
		if (Select.shape != shape::Line) Select.polygonPattern = _SelectColor;
		break;
	}

	shape1 = Select;

}

