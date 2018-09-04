#include "stdafx.h"
#include "DragStack.h"

CDragStack::CDragStack()
{
}

CDragStack::~CDragStack()
{
}

void CDragStack::SetStackInfoWhenMoveStarts(CRect StackRect,  CPoint point)
{
	CSize ImageSize(StackRect.right - StackRect.left, StackRect.bottom - StackRect.top);

	OldStackLocation.x = StackLocation.x;
	OldStackLocation.y = StackLocation.y;

	StackLocation.x = StackRect.left;
	StackLocation.y = StackRect.top;
	StackSize = ImageSize;

	MouseOffset = point - StackLocation;
}

bool CDragStack::CalculateNewCornersAfterMouseMove(CPoint point)
{
	CPoint MousePoint(point);
	StackLocation = MousePoint - MouseOffset;
	return true;
}

void CDragStack::InitDragStack()
{
	StackLocation.x = -1;
	StackLocation.y = -1;
	OldStackLocation.x = -1;
	OldStackLocation.y = -1;
	StackSize.cx = 0;
	StackSize.cy = 0;
	MouseOffset.cx = -1;
	MouseOffset.cy = -1;

	for (int i = 0; i < CARDSINSUITE; i++)
	{
		CardsInStack[i] = -1;
	}
}