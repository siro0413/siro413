#include "stdafx.h"
#pragma once
const int numberOfMenus = 6;
const int numberOfOptions = 5;
const POINT menuStart = { 25,25 };
const POINT optionStart = { 150, 30 };
const int menuTitleHeight = 20;
const int optionWidth = 20;



enum class Title : UINT
{
	선의패턴,
	선의굵기,
	선의색상,
	도형종류,
	도형색상,
	도형패턴
};

class SelectMenu
{
public:
	SelectMenu();
	~SelectMenu();

	shapeInfo getShapeInfo() { return shape1; }
	COLORREF* GetColor() { return Color; }

	void ShowMenu(HDC hdc);
	void ShowOption(HDC hdc);
	void selectOptions();



private:
	wstring MenuName[6]; //선택할 메뉴의 종류 6개 배열
	COLORREF Color[5];
	UINT _SelectMenu; // 메뉴 선택
	int _SelectColor;
	shapeInfo Select;

	shapeInfo shape1;



};

