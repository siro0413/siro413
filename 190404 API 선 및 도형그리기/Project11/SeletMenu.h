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
	��������,
	���Ǳ���,
	���ǻ���,
	��������,
	��������,
	��������
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
	wstring MenuName[6]; //������ �޴��� ���� 6�� �迭
	COLORREF Color[5];
	UINT _SelectMenu; // �޴� ����
	int _SelectColor;
	shapeInfo Select;

	shapeInfo shape1;



};

