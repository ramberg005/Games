// MineSweep.cpp : implementation file
//

#include "stdafx.h"
#include "RDAGames.h"
#include "definitions.h"
#include <atlimage.h>
#include "MineSweep.h"
#include <math.h>
#include "MainFrm.h"
#include "TrackViews.h"


// CMineSweep

IMPLEMENT_DYNCREATE(CMineSweep, CView)

CMineSweep::CMineSweep()
{
	CleanGame();
	LoadImages();
	NewGame();
	CleanPaintArray();
	lbuttondown = false;
	rbuttondown = false;
	HitABomb = false;
	Seven = false;
	Eight = false;
	BombCount = 99;
}

CMineSweep::~CMineSweep()
{
	CTrackViews tv;
	tv.RemoveStatus(MINESWEEPVIEW);
}

BEGIN_MESSAGE_MAP(CMineSweep, CView)
	ON_WM_SIZE()
//	ON_WM_LBUTTONUP()
//	ON_WM_RBUTTONUP()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_COMMAND(ID_APP_DEAL, &CMineSweep::OnAppDeal)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
//	ON_WM_ICONERASEBKGND()
//	ON_WM_UPDATEUISTATE()
END_MESSAGE_MAP()


// CMineSweep drawing

void CMineSweep::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

}


// CMineSweep diagnostics

#ifdef _DEBUG
void CMineSweep::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMineSweep::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMineSweep message handlers
void CMineSweep::LoadImages()
{
	CString imagepath;
	CString imagefile;

	imagepath = ".\\MineSweep\\";

	imagefile = imagepath + "1.png";
	aImages[IMAGEONE].Load(imagefile);

	imagefile = imagepath + "2.png";
	aImages[IMAGETWO].Load(imagefile);

	imagefile = imagepath + "3.png";
	aImages[IMAGETHREE].Load(imagefile);

	imagefile = imagepath + "4.png";
	aImages[IMAGEFOUR].Load(imagefile);

	imagefile = imagepath + "5.png";
	aImages[IMAGEFIVE].Load(imagefile);

	imagefile = imagepath + "6.png";
	aImages[IMAGESIX].Load(imagefile);

	imagefile = imagepath + "7.png";
	aImages[IMAGESEVEN].Load(imagefile);

	imagefile = imagepath + "8.png";
	aImages[IMAGEEIGHT].Load(imagefile);

	imagefile = imagepath + "blank.png";
	aImages[IMAGEBLANK].Load(imagefile);

	imagefile = imagepath + "clickedOnBomb.png";
	aImages[IMAGECLICKEDONBOMB].Load(imagefile);

	imagefile = imagepath + "cover.png";
	aImages[IMAGECOVER].Load(imagefile);

	imagefile = imagepath + "marked.png";
	aImages[IMAGEMARKED].Load(imagefile);

	imagefile = imagepath + "markedBomb.png";
	aImages[IMAGEMARKEDBOMB].Load(imagefile);

	imagefile = imagepath + "unexplodedBomb.png";
	aImages[IMAGEUNEXPLODEDBOMB].Load(imagefile);
	
	imagefile = imagepath + "coverwhileLR.png";
	aImages[IMAGECOVERLRDOWN].Load(imagefile);

}

void CMineSweep::NewGame()
{
	int rndnum;
	int i, j, row, column, bombcount;

	HitABomb = false;
	lbuttondown = false;
	rbuttondown = false;
	Seven = false;
	Eight = false;
	// seed our random number generator
	srand(GetTickCount());

	// put bombs in first
	i = 99;
	while (i > 0)
	{
		rndnum = rand() % (MSCOLUMNS * MSROWS);
		row = (int)rndnum/MSCOLUMNS;
		column = rndnum - (row * MSCOLUMNS);

		if (aGame[column][row] == IMAGEBLANK)
		{
			aGame[column][row] = IMAGEUNEXPLODEDBOMB;
			i--;
		}
	}
	// now set the values for non-bombs
	for (i = 0; i < MSCOLUMNS; i++)
	{
		for(j = 0; j < MSROWS; j++)
		{
			bombcount = 0;
			if (aGame[i][j] != IMAGEUNEXPLODEDBOMB)
			{
				// check left
				if (i != 0)
				{
					if (aGame[i - 1][j] == IMAGEUNEXPLODEDBOMB)
					{
						bombcount++;
					}
				}
				// check top and left
				if ((i != 0) && (j != 0))
				{
					if (aGame[i - 1][j - 1] == IMAGEUNEXPLODEDBOMB)
					{
						bombcount++;
					}
				}
				// check top
				if (j != 0)
				{
					if (aGame[i][j - 1] == IMAGEUNEXPLODEDBOMB)
					{
						bombcount++;
					}
				}
				// check right and top
				if ((i != (MSCOLUMNS - 1)) && (j != 0))
				{
					if (aGame[i + 1][j - 1] == IMAGEUNEXPLODEDBOMB)
					{
						bombcount++;
					}
				}
				// check right
				if (i != (MSCOLUMNS - 1))
				{
					if (aGame[i + 1][j] == IMAGEUNEXPLODEDBOMB)
					{
						bombcount++;
					}
				}
				// check right and bottom
				if ((i != (MSCOLUMNS - 1)) && (j != (MSROWS - 1)))
				{
					if (aGame[i + 1][j + 1] == IMAGEUNEXPLODEDBOMB)
					{
						bombcount++;
					}
				}
				// check bottom
				if (j != (MSROWS - 1))
				{
					if (aGame[i][j + 1] == IMAGEUNEXPLODEDBOMB)
					{
						bombcount++;
					}
				}
				// check bottom and left
				if ((j != (MSROWS - 1)) && (i != 0))
				{
					if (aGame[i - 1][j + 1] == IMAGEUNEXPLODEDBOMB)
					{
						bombcount++;
					}
				}
				switch (bombcount)
				{
				case 1:
					aGame[i][j] = IMAGEONE;
					break;
				case 2:
					aGame[i][j] = IMAGETWO;
					break;
				case 3:
					aGame[i][j] = IMAGETHREE;
					break;
				case 4:
					aGame[i][j] = IMAGEFOUR;
					break;
				case 5:
					aGame[i][j] = IMAGEFIVE;
					break;
				case 6:
					aGame[i][j] = IMAGESIX;
					break;
				case 7:
					aGame[i][j] = IMAGESEVEN;
					Seven = true;
					break;
				case 8:
					aGame[i][j] = IMAGEEIGHT;
					Eight = true;
					break;
				}
			}
		}
	}

}

void CMineSweep::CleanGame()
{
	paintAll = true;
	BombCount = 99;
	GameOver = false;
	for (int i = 0; i < MSCOLUMNS; i++)
	{
		for (int j = 0; j < MSROWS; j++)
		{
			aGame[i][j] = IMAGEBLANK;
			aGameStatus[i][j] = COVERED;
		}
	}
}

void CMineSweep::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	int DrawWidth, DrawHieght;
	int ScoreBox = 100;
	double WidthRatio, HieghtRatio, LineSize;

	defaultImageWidth = aImages[IMAGECOVER].GetWidth();
	defaultImageHeight = aImages[IMAGECOVER].GetHeight();

	xSize = cx;
	ySize = cy;

	LineSize = (double)(defaultImageWidth *.05);
	LineThickness = (int)LineSize;

	DrawWidth = (defaultImageWidth * MSCOLUMNS) + (int)(LineSize * (MSCOLUMNS + 2)) + ScoreBox;
	DrawHieght = (defaultImageHeight * MSROWS) + (int)(LineSize * (MSROWS + 2));

	WidthRatio = (double)xSize/DrawWidth;
	HieghtRatio = (double)ySize/DrawHieght;

	if (WidthRatio > HieghtRatio)
	{
		iStrechFactor = HieghtRatio;
	}
	else
	{
		iStrechFactor = WidthRatio;
	}

	MSwidth = Round(aImages[IMAGECOVER].GetWidth() * iStrechFactor);
	MSheight = Round(aImages[IMAGECOVER].GetHeight() * iStrechFactor);
	MSline = Round(LineThickness * iStrechFactor);

	DrawWidth = (MSwidth * MSCOLUMNS)  + (MSline * (MSCOLUMNS + 2));
	DrawHieght = MSheight;

	ScoreRect.top = DrawHieght;
	ScoreRect.left = DrawWidth;
	ScoreRect.right = DrawWidth + Round(ScoreBox * iStrechFactor);
	ScoreRect.bottom = DrawHieght + Round(ScoreBox * iStrechFactor);

	SevenRect.top = ScoreRect.bottom + MSheight;
	SevenRect.left = DrawWidth;
	SevenRect.right = DrawWidth + MSwidth;
	SevenRect.bottom = SevenRect.top + MSheight;

	EightRect.top = SevenRect.bottom + MSheight;
	EightRect.left = DrawWidth;
	EightRect.right = DrawWidth + MSwidth;
	EightRect.bottom = EightRect.top + MSheight;

	paintAll = true;
}

int CMineSweep::Round(double d)
{
	int i;
	// we sure there won't be a screen that is 65536 bytes wide
	i = (int)floor(d);
	if ((d - i) > .5)
	{
		i++;
	}

	return i;
}

void CMineSweep::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	DoThePaint(&dc);
}

void CMineSweep::DoThePaint(CDC* pDC)
{
	int x, y;
	int imagetype;
	HDC mhDC = pDC->m_hDC;
	if (GameOver == true)
	{
		return;
	}
	
	if (paintAll)
	{
		GetWindowRect(&FCRectColorChanger);
		CBrush BrushBlack(RGB(0, 0, 0));

		// Select the new brush
		pFCOldBrush = pDC->SelectObject(&BrushBlack);

		// Convert the current coordinates from Screen to Client
		ScreenToClient(&FCRectColorChanger);
		// Change the background of the control
		pDC->Rectangle(FCRectColorChanger);
	}

	
	x = MSline;
	for (int i = 0; i < MSCOLUMNS; i++)
	{
		y = MSline;
		for(int j = 0; j < MSROWS; j++)
		{
			if (HitABomb)
			{
				if ((aGameStatus[i][j] == MARKED) && (aGame[i][j] == IMAGEUNEXPLODEDBOMB))
				{
					imagetype = IMAGEMARKEDBOMB;
				}
				else
				{
					if (aGame[i][j] == IMAGEUNEXPLODEDBOMB)
					{
						imagetype = aGame[i][j];
					}
					else
					{
						if (aGame[i][j] == IMAGECLICKEDONBOMB)
						{
							imagetype =IMAGECLICKEDONBOMB;
						}
						else
						{
							switch (aGameStatus[i][j])
							{
							case COVERED:
								imagetype = IMAGECOVER;
								break;
							case UNCOVERED:
								imagetype = aGame[i][j];
								break;
							case MARKED:
								imagetype = IMAGEMARKED;
								break;
							case AFTEREXPLODED:
								imagetype = aGame[i][j];
								break;
							}
						}
					}
				}
			}
			else
			{
				if (rbuttondown &&	lbuttondown)
				{
					imagetype = IMAGECOVERLRDOWN;
				}
				else
				{
					switch (aGameStatus[i][j])
					{
					case COVERED:
						imagetype = IMAGECOVER;
						break;
					case UNCOVERED:
						imagetype = aGame[i][j];
						break;
					case MARKED:
						imagetype = IMAGEMARKED;
						break;
					case AFTEREXPLODED:
						imagetype = aGame[i][j];
						break;
					}
				}
			}
			if ((HitABomb)  || (PaintArray[i][j] != -1) || (paintAll))
			{
				aImages[imagetype].StretchBlt(mhDC,x,y, MSwidth, MSheight);
			}
			y += MSline + MSheight;
		}
		x += MSline + MSwidth;
	}
	if(!(rbuttondown &&	lbuttondown))
	{
		CleanPaintArray();
	}
	if (Seven == true)
	{
		aImages[IMAGESEVEN].StretchBlt(mhDC,SevenRect);
	}
	if (Eight == true)
	{
		aImages[IMAGEEIGHT].StretchBlt(mhDC,EightRect);
	}

	paintAll = false;
	DrawTheBombCount(pDC);
	SeeIfGameIsOver();
}

void CMineSweep::OnAppDeal()
{
	CleanGame();
	NewGame();
	CleanPaintArray();
	paintAll = true;
	Invalidate(false);
}

void CMineSweep::OnLButtonDown(UINT nFlags, CPoint point)
{
	lbuttondown = true;
	

	if (rbuttondown)
	{
		RightAndLeftMouseButtonDown(point);
	}

	CView::OnLButtonDown(nFlags, point);
}

void CMineSweep::UnCoverAroundBlanks(int column, int row)
{
	// check left
	if (column != 0)
	{
		if ((aGame[column - 1][row] <= IMAGEBLANK) && (aGameStatus[column - 1][row] == COVERED))
		{
			aGameStatus[column - 1][row] = UNCOVERED;
			PaintArray[column - 1][row] = 1;
			if (aGame[column - 1][row] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column - 1, row);
			}
		}
	}
	// check top and left
	if ((column != 0) && (row != 0))
	{
		if ((aGame[column - 1][row - 1] <= IMAGEBLANK) && (aGameStatus[column - 1][row - 1] == COVERED))
		{
			aGameStatus[column - 1][row - 1] = UNCOVERED;
			PaintArray[column - 1][row - 1] = 1;
			if (aGame[column - 1][row - 1] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column - 1, row - 1);
			}
		}
	}
	// check top
	if (row != 0)
	{
		if ((aGame[column][row - 1] <= IMAGEBLANK) && (aGameStatus[column][row - 1] == COVERED))
		{
			aGameStatus[column][row - 1] = UNCOVERED;
			PaintArray[column][row - 1] = 1;
			if (aGame[column][row - 1] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column, row - 1);
			}
		}
	}
	// check right and top
	if ((column != (MSCOLUMNS - 1)) && (row != 0))
	{
		if ((aGame[column + 1][row - 1] <= IMAGEBLANK) && (aGameStatus[column + 1][row - 1] == COVERED))
		{
			aGameStatus[column + 1][row - 1] = UNCOVERED;
			PaintArray[column + 1][row - 1] = 1;
			if (aGame[column + 1][row - 1] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column + 1, row - 1);
			}
		}
	}
	// check right
	if (column != (MSCOLUMNS - 1))
	{
		if ((aGame[column + 1][row] <= IMAGEBLANK) && (aGameStatus[column + 1][row] == COVERED))
		{
			aGameStatus[column + 1][row] = UNCOVERED;
			PaintArray[column + 1][row] = 1;
			if (aGame[column + 1][row] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column + 1, row);
			}
		}
	}
	// check right and bottom
	if ((column != (MSCOLUMNS - 1)) && (row != (MSROWS - 1)))
	{
		if ((aGame[column + 1][row + 1] <= IMAGEBLANK) && (aGameStatus[column + 1][row + 1] == COVERED))
		{
			aGameStatus[column + 1][row + 1] = UNCOVERED;
			PaintArray[column + 1][row + 1] = 1;
			if (aGame[column + 1][row + 1] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column + 1, row + 1);
			}
		}
	}
	// check bottom
	if (row != (MSROWS - 1))
	{
		if ((aGame[column][row + 1] <= IMAGEBLANK) && (aGameStatus[column][row + 1] == COVERED))
		{
			aGameStatus[column][row + 1] = UNCOVERED;
			PaintArray[column][row + 1] = 1;
			if (aGame[column][row + 1] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column, row + 1);
			}
		}
	}
	// check bottom and left
	if ((row != (MSROWS - 1)) && (column != 0))
	{
		if ((aGame[column - 1][row + 1] <= IMAGEBLANK) && (aGameStatus[column - 1][row + 1] == COVERED))
		{
			aGameStatus[column - 1][row + 1] = UNCOVERED;
			PaintArray[column - 1][row + 1] = 1;
			if (aGame[column - 1][row + 1] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column - 1, row + 1);
			}
		}
	}
}

void CMineSweep::OnLButtonUp(UINT nFlags, CPoint point)
{
	int column, row;
	bool somethingchanged = false;

	if (rbuttondown && lbuttondown)
	{
		Invalidate(false);
	}
	rbuttondown = false;
	lbuttondown = false;

	if (!HitABomb)
	{
		column = (int)point.x/(MSwidth + MSline);
		row = (int)point.y/(MSheight + MSline);

		if (row >= MSROWS)
		{
			return;
		}
		if (column >= MSCOLUMNS)
		{
			return;
		}

		switch (aGameStatus[column][row])
		{
		case COVERED:
			if (aGame[column][row] == IMAGEUNEXPLODEDBOMB)
			{
				aGame[column][row] = IMAGECLICKEDONBOMB;
				PaintArray[column][row] = 1;
				HitABomb = true;
			}
			if (aGame[column][row] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column, row);
			}
			aGameStatus[column][row] = UNCOVERED;
			PaintArray[column][row] = 1;
			somethingchanged = true;
			break;
		case MARKED:
			//aGameStatus[column][row] = COVERED;
			//PaintArray[column][row] = 1;
			//BombCount++;
			//somethingchanged = true;
			break;
		}
	
		if (somethingchanged)
		{
			Invalidate(false);
		}
	}
	CView::OnLButtonUp(nFlags, point);
}

void CMineSweep::OnRButtonUp(UINT nFlags, CPoint point)
{
	int column,row;
	
	if (rbuttondown && lbuttondown)
	{
		Invalidate(false);
	}
	rbuttondown = false;
	lbuttondown = false;
	
	if (!HitABomb)
	{
		column = (int)point.x/(MSwidth + MSline);
		row = (int)point.y/(MSheight + MSline);

		switch (aGameStatus[column][row])
		{
		case COVERED:
			aGameStatus[column][row] = MARKED;
			PaintArray[column][row] = 1;
			BombCount--;
			break;
		case MARKED:
			aGameStatus[column][row] = COVERED;
			PaintArray[column][row] = 1;
			BombCount++;
			break;
		}
		Invalidate(false);
	}

	CView::OnRButtonUp(nFlags, point);
}

void CMineSweep::OnRButtonDown(UINT nFlags, CPoint point)
{
	rbuttondown = true;
	if (lbuttondown)
	{
		RightAndLeftMouseButtonDown(point);
	}

	CView::OnRButtonDown(nFlags, point);
}
BOOL CMineSweep::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true; //CView::OnEraseBkgnd(pDC);
}

void CMineSweep::RightAndLeftMouseButtonDown(CPoint point)
{
	int column,row, TouchingBombCount, MarkedCount;

	if (!HitABomb)
	{
		column = (int)point.x/(MSwidth + MSline);
		row = (int)point.y/(MSheight + MSline);

		if ((aGameStatus[column][row] != COVERED) && (aGameStatus[column][row] != MARKED))
		{
			TouchingBombCount = aGame[column][row];
			if (TouchingBombCount > IMAGEEIGHT)
			{
				return;
			}
			else
			{
				TouchingBombCount++;
			}
			MarkedCount = GetMarkedCount(column, row);
			if (MarkedCount != TouchingBombCount)
			{
				ShowPressedDownCovers(column, row);
				Invalidate(false);
				return;
			}
			UnCoverUnMarked(column, row);
			lbuttondown = false;
			rbuttondown = false;
			Invalidate(false);
		}
	}
}

void CMineSweep::ShowPressedDownCovers(int column, int row)
{
	if (column != 0)
	{
		if (aGameStatus[column - 1][row] == COVERED)
		{
			PaintArray[column - 1][row] = 1;
		}
	}
	// check top and left
	if ((column != 0) && (row != 0))
	{
		if (aGameStatus[column - 1][row - 1] == COVERED)
		{
			PaintArray[column - 1][row - 1] = 1;
		}
	}
	// check top
	if (row != 0)
	{
		if (aGameStatus[column][row - 1] == COVERED) 
		{
			PaintArray[column][row - 1] = 1;
		}
	}
	// check right and top
	if ((column != (MSCOLUMNS - 1)) && (row != 0))
	{
		if (aGameStatus[column + 1][row - 1] == COVERED)
		{
			PaintArray[column + 1][row - 1] = 1;
		}
	}
	// check right
	if (column != (MSCOLUMNS - 1))
	{
		if (aGameStatus[column + 1][row] == COVERED) 
		{
			PaintArray[column + 1][row] = 1;
		}
	}
	// check right and bottom
	if ((column != (MSCOLUMNS - 1)) && (row != (MSROWS - 1)))
	{
		if (aGameStatus[column + 1][row + 1] == COVERED)
		{
			PaintArray[column + 1][row + 1] = 1;
		}
	}
	// check bottom
	if (row != (MSROWS - 1))
	{
		if (aGameStatus[column][row + 1] == COVERED)
		{
			PaintArray[column][row + 1] = 1;
		}
	}
	// check bottom and left
	if ((row != (MSROWS - 1)) && (column != 0))
	{
		if (aGameStatus[column - 1][row + 1] == COVERED)
		{
			PaintArray[column - 1][row + 1] = 1;
		}
	}
}

int CMineSweep::GetMarkedCount(int column, int row)
{
	int Marked = 0;
	// check left
	if (column != 0)
	{
		if (aGameStatus[column - 1][row] == MARKED)
		{
			Marked++;
		}
	}
	// check top and left
	if ((column != 0) && (row != 0))
	{
		if (aGameStatus[column - 1][row - 1] == MARKED)
		{
			Marked++;
		}
	}
	// check top
	if (row != 0)
	{
		if (aGameStatus[column][row - 1] == MARKED) 
		{
			Marked++;
		}
	}
	// check right and top
	if ((column != (MSCOLUMNS - 1)) && (row != 0))
	{
		if (aGameStatus[column + 1][row - 1] == MARKED)
		{
			Marked++;
		}
	}
	// check right
	if (column != (MSCOLUMNS - 1))
	{
		if (aGameStatus[column + 1][row] == MARKED) 
		{
			Marked++;
		}
	}
	// check right and bottom
	if ((column != (MSCOLUMNS - 1)) && (row != (MSROWS - 1)))
	{
		if (aGameStatus[column + 1][row + 1] == MARKED)
		{
			Marked++;
		}
	}
	// check bottom
	if (row != (MSROWS - 1))
	{
		if (aGameStatus[column][row + 1] == MARKED)
		{
			Marked++;
		}
	}
	// check bottom and left
	if ((row != (MSROWS - 1)) && (column != 0))
	{
		if (aGameStatus[column - 1][row + 1] == MARKED)
		{
			Marked++;
		}
	}
	return Marked;
}

void CMineSweep::UnCoverUnMarked(int column, int row)
{
	if (column != 0)
	{
		if (aGameStatus[column - 1][row] == COVERED)
		{
			if (aGame[column - 1][row] == IMAGEUNEXPLODEDBOMB)
			{
				HitABomb = true;
				aGame[column - 1][row] = IMAGECLICKEDONBOMB;
				PaintArray[column - 1][row] = 1;
				return;
			}
			aGameStatus[column - 1][row] = UNCOVERED;
			PaintArray[column - 1][row] = 1;
			if (aGame[column - 1][row] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column - 1, row);
			}
		}
	}
	// check top and left
	if ((column != 0) && (row != 0))
	{
		if (aGameStatus[column - 1][row - 1] == COVERED)
		{
			if (aGame[column - 1][row - 1] == IMAGEUNEXPLODEDBOMB)
			{
				HitABomb = true;
				aGame[column - 1][row - 1] = IMAGECLICKEDONBOMB;
				PaintArray[column - 1][row - 1] = 1;
				return;
			}
			aGameStatus[column - 1][row - 1] = UNCOVERED;
			PaintArray[column - 1][row - 1] = 1;
			if (aGame[column - 1][row - 1] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column - 1, row - 1);
			}
		}
	}
	// check top
	if (row != 0)
	{
		if (aGameStatus[column][row - 1] == COVERED) 
		{
			if (aGame[column][row - 1] == IMAGEUNEXPLODEDBOMB)
			{
				HitABomb = true;
				aGame[column][row - 1] = IMAGECLICKEDONBOMB;
				PaintArray[column][row - 1] = 1;
				return;
			}
			aGameStatus[column][row - 1] = UNCOVERED;
			PaintArray[column][row - 1] = 1;
			if (aGame[column][row - 1] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column, row - 1);
			}
		}
	}
	// check right and top
	if ((column != (MSCOLUMNS - 1)) && (row != 0))
	{
		if (aGameStatus[column + 1][row - 1] == COVERED)
		{
			if (aGame[column + 1][row - 1] == IMAGEUNEXPLODEDBOMB)
			{
				HitABomb = true;
				aGame[column + 1][row - 1] = IMAGECLICKEDONBOMB;
				PaintArray[column + 1][row - 1] = 1;
				return;
			}
			aGameStatus[column + 1][row - 1] = UNCOVERED;
			PaintArray[column + 1][row - 1] = 1;
			if (aGame[column + 1][row - 1] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column + 1, row - 1);
			}
		}
	}
	// check right
	if (column != (MSCOLUMNS - 1))
	{
		if (aGameStatus[column + 1][row] == COVERED) 
		{
			if (aGame[column + 1][row] == IMAGEUNEXPLODEDBOMB)
			{
				HitABomb = true;
				aGame[column + 1][row] = IMAGECLICKEDONBOMB;
				PaintArray[column + 1][row] = 1;
				return;
			}
			aGameStatus[column + 1][row] = UNCOVERED;
			PaintArray[column + 1][row] = 1;
			if (aGame[column + 1][row] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column + 1, row);
			}
		}
	}
	// check right and bottom
	if ((column != (MSCOLUMNS - 1)) && (row != (MSROWS - 1)))
	{
		if (aGameStatus[column + 1][row + 1] == COVERED)
		{
			if (aGame[column + 1][row + 1] == IMAGEUNEXPLODEDBOMB)
			{
				HitABomb = true;
				aGame[column + 1][row + 1] = IMAGECLICKEDONBOMB;
				PaintArray[column + 1][row + 1] = 1;
				return;
			}
			aGameStatus[column + 1][row + 1] = UNCOVERED;
			PaintArray[column + 1][row + 1] = 1;
			if (aGame[column + 1][row + 1] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column + 1, row + 1);
			}
		}
	}
	// check bottom
	if (row != (MSROWS - 1))
	{
		if (aGameStatus[column][row + 1] == COVERED)
		{
			if (aGame[column][row + 1] == IMAGEUNEXPLODEDBOMB)
			{
				HitABomb = true;
				aGame[column][row + 1] = IMAGECLICKEDONBOMB;
				PaintArray[column][row + 1] = 1;
				return;
			}
			aGameStatus[column][row + 1] = UNCOVERED;
			PaintArray[column][row + 1] = 1;
			if (aGame[column][row + 1] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column, row + 1);
			}
		}
	}
	// check bottom and left
	if ((row != (MSROWS - 1)) && (column != 0))
	{
		if (aGameStatus[column - 1][row + 1] == COVERED)
		{
			if (aGame[column - 1][row + 1] == IMAGEUNEXPLODEDBOMB)
			{
				HitABomb = true;
				aGame[column - 1][row + 1] = IMAGECLICKEDONBOMB;
				PaintArray[column - 1][row + 1] = 1;
				return;
			}
			aGameStatus[column - 1][row + 1] = UNCOVERED;
			PaintArray[column - 1][row + 1] = 1;
			if (aGame[column - 1][row + 1] == IMAGEBLANK)
			{
				UnCoverAroundBlanks(column - 1, row + 1);
			}
		}
	}
}

void CMineSweep::CleanPaintArray()
{
	for (int i = 0; i < MSCOLUMNS; i++)
	{
		for (int j = 0; j < MSROWS; j++)
		{
			PaintArray[i][j] = -1;
		}
	}
}

void CMineSweep::DrawTheBombCount(CDC *dc)
{
	LOGFONT LogFont;
	CFont SizeFont;
	CFont *pFont;

	//delete the old images first
	dc->FillSolidRect(ScoreRect, RGB(255, 255, 128)); //dc->GetBkColor())

	int s;
	char score[128];
	s = BombCount;
	_itoa_s(s,score,128,10);

	int iFontSize = 80;

	LogFont.lfWeight = 0; //(int)(iFontSize * theDrawScreen->CardStretchSize);
	LogFont.lfStrikeOut = 0;
	LogFont.lfUnderline = 0;
	LogFont.lfHeight = (int)(iFontSize * iStrechFactor);  // sets font size
	LogFont.lfEscapement = 0;
	LogFont.lfItalic = FALSE;
	LogFont.lfWidth = 0;
	strcpy_s(LogFont.lfFaceName, "Arial");

	SizeFont.CreateFontIndirect(&LogFont);	
	pFont = dc->SelectObject(&SizeFont);

	if (BombCount == 0)
	{
		// red font
		dc->SetTextColor(RGB(255, 0, 0));
	}
	else
	{
		dc->SetTextColor(RGB(0, 0, 0));
	}
	dc->SetBkColor(RGB(255, 255, 128));
	dc->SetBkMode(OPAQUE);
	dc->DrawText(score,ScoreRect, DT_NOCLIP | DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc->SelectObject(pFont);
	SizeFont.DeleteObject();
}

void CMineSweep::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);
	CMFCRibbonBar *pRibbon;
	CMFCRibbonCategory *pRibbonCategory;

	pRibbon = ((CMainFrame*)AfxGetMainWnd())->GetRibbonBar();
	pRibbonCategory = pRibbon->GetCategory(3);
	pRibbon->SetActiveCategory(pRibbonCategory, true);

	paintAll = true;
	Invalidate(false);
}

void CMineSweep::SeeIfGameIsOver()
{
	if (GameOver == true)
	{
		return;
	}
	for (int i = 0; i < MSCOLUMNS; i++)
	{
		for (int j= 0; j < MSROWS; j++)
		{
			if ((aGameStatus[i][j] != UNCOVERED) && (aGameStatus[i][j] != MARKED))
			{
				return;
			}
		}
	}
	GameOver = true;
	MessageBox("You won the game", "WINNER");
}

