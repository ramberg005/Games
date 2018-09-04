#pragma once
#include "definitions.h"


class CDragStack
{
public:
	CDragStack();
	~CDragStack();

public:
	CPoint StackLocation;
	CPoint OldStackLocation;
	CSize StackSize;
	int CardsInStack[CARDSINSUITE];

public:
	CSize MouseOffset;

public:
	bool CalculateNewCornersAfterMouseMove(CPoint point);
	void SetStackInfoWhenMoveStarts(CRect StackRect,  CPoint point);
	void InitDragStack();
};