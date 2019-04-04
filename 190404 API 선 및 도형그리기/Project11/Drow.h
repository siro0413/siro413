#include "stdafx.h"
#pragma once
class SelectMenu;

class DrawObject
{
public:
	DrawObject();
	~DrawObject() {}

	void setSelectedOptAddress(SelectMenu* ptr) { selectedOpt = ptr; }

	//void dragAndSizeShape(POINT mousePoint);
	void startDraw(POINT mousePoint)
	{
		if (bClicked) return;

		bClicked = true;
		startPoint = mousePoint;
	}
	void makeObject(POINT mousePoint);
	void saveObject();
	void showSavedObject(HDC hdc);
	void showDrawingObject(HDC hdc);
	void drawObject(HDC, shapeInfo);
	void drawObject(HDC);

private:
	SelectMenu* selectedOpt;
	vector<shapeInfo> vObjects;

	POINT startPoint;
	POINT endPoint;
	bool bClicked;

	shapeInfo object;
};

