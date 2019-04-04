#include "stdafx.h"
#include "Drow.h"
#include "SeletMenu.h"



DrawObject::DrawObject()
{
	startPoint = { 0,0 };
	endPoint = { 0,0 };
	bClicked = false;

	ZeroMemory(&object, sizeof(object));
}

void DrawObject::makeObject(POINT mousePoint)
{
	if (!bClicked) return;

	object = selectedOpt->getShapeInfo();

	endPoint = mousePoint;
	// 오브젝트 사이즈 대입
	object.size.left = startPoint.x;
	object.size.top = startPoint.y;
	object.size.right = endPoint.x;
	object.size.bottom = endPoint.y;
}


void DrawObject::saveObject()
{
	if (!bClicked) return;

	vObjects.push_back(object);
	bClicked = false;
	ZeroMemory(&object, sizeof(object));

}

void DrawObject::showSavedObject(HDC hdc)
{
	for (auto object : vObjects)
	{
		drawObject(hdc, object);
	}
}

void DrawObject::showDrawingObject(HDC hdc)
{
	drawObject(hdc);
}

void DrawObject::drawObject(HDC hdc, shapeInfo object1)
{
	HPEN curPen, oldPen;
	HBRUSH curBrush, oldBrush;

	// 직선은 공통
	curPen = CreatePen(object1.lineStyle, object1.lineThick, selectedOpt->GetColor()[object1.lineColor]);
	oldPen = (HPEN)SelectObject(hdc, curPen);

	if (object1.shape == shape::Line)
	{
		MoveToEx(hdc, object1.size.left, object1.size.top, NULL);
		LineTo(hdc, object1.size.right, object1.size.bottom);
	}
	else
	{
		// 브러쉬 종류 선택
		// solidBrush
		if (object1.polygonPattern == 0) curBrush = CreateSolidBrush(selectedOpt->GetColor()[object1.polygonColor]);
		// hatchBrush
		else curBrush = CreateHatchBrush(object1.polygonPattern, selectedOpt->GetColor()[object1.polygonColor]);

		oldBrush = (HBRUSH)SelectObject(hdc, curBrush);

		if (object1.shape == shape::Rect)
		{
			// 사각형 그리기
			Rectangle(hdc, object1.size.left, object1.size.top, object1.size.right, object1.size.bottom);
		}
		else
		{
			// 타원 그리기
			Ellipse(hdc, object1.size.left, object1.size.top, object1.size.right, object1.size.bottom);
		}
		// 사용한 브러쉬 펜 삭제
		SelectObject(hdc, oldBrush);
		DeleteObject(curBrush);
	}
	SelectObject(hdc, oldPen);
	DeleteObject(curPen);
}

void DrawObject::drawObject(HDC hdc)
{
	HPEN curPen, oldPen;
	HBRUSH curBrush, oldBrush;

	// 직선은 공통
	curPen = CreatePen(object.lineStyle, object.lineThick, selectedOpt->GetColor()[object.lineColor]);
	oldPen = (HPEN)SelectObject(hdc, curPen);

	if (object.shape == shape::Line)
	{
		MoveToEx(hdc, object.size.left, object.size.top, NULL);
		LineTo(hdc, object.size.right, object.size.bottom);
	}
	else
	{
		// 브러쉬 종류 선택
		// solidBrush
		if (object.polygonPattern == 0) curBrush = CreateSolidBrush(selectedOpt->GetColor()[object.polygonColor]);
		// hatchBrush
		else curBrush = CreateHatchBrush(object.polygonPattern,selectedOpt->GetColor()[object.polygonColor]);

		oldBrush = (HBRUSH)SelectObject(hdc, curBrush);

		if (object.shape == shape::Rect)
		{
			// 사각형 그리기
			Rectangle(hdc, object.size.left, object.size.top, object.size.right, object.size.bottom);
		}
		else
		{
			// 타원 그리기
			Ellipse(hdc, object.size.left, object.size.top, object.size.right, object.size.bottom);
		}
		// 사용한 브러쉬 펜 삭제
		SelectObject(hdc, oldBrush);
		DeleteObject(curBrush);
	}
	SelectObject(hdc, oldPen);
	DeleteObject(curPen);

}
