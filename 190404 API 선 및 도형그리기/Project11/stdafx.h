#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <tchar.h>
using namespace std;

extern POINT _mousePoint;
enum  class shape : int
{
	Line, Rect, Ellipse
};
typedef struct tagSelection
{
	int lineStyle, lineThick, lineColor;
	shape shape;
	int polygonPattern, polygonColor;
	RECT size;

}shapeInfo;
