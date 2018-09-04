// Jewel.cpp : implementation file
//

#include "stdafx.h"
#include "RDAGames.h"
#include "definitions.h"
#include <atlimage.h>
#include "Jewel.h"
#include <math.h>
#include "JewelGameOver.h"
#include "MainFrm.h"
#include "TrackViews.h"


// CJewel

IMPLEMENT_DYNCREATE(CJewel, CView)

CJewel::CJewel()
{
	CleanDrawSquare();
	LoadImages();
	NewGame();
	paintAll = true;
	bCleanDrawSquare = true;
	ClickedOneJewel = false;
	TimerHasBeenSet = false;
	Made3InARow = false;
	JewelPauseSeconds = 0;
	Jtime = 0;
	IncrementJtime = false;
	AmountAddedToScore = 0;
}

CJewel::~CJewel()
{
	CTrackViews tv;
	tv.RemoveStatus(JEWELVIEW);
}

BEGIN_MESSAGE_MAP(CJewel, CView)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_APP_DEAL, &CJewel::OnAppDeal)
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// CJewel drawing

void CJewel::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CJewel diagnostics

#ifdef _DEBUG
void CJewel::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CJewel::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

void CJewel::CleanDrawSquare()
{
	for (int i = 0; i < JEWELCOLUMNS; i++)
	{
		for (int j = 0; j < JEWELROWS; j++)
		{
			DrawSquare[i][j] = false;
		}
	}
}

void CJewel::LoadImages()
{
	CString imagepath;
	CString imagefile;

	imagepath = ".\\Jewel\\";

	imagefile = imagepath + "1.bmp";
	JewelImages[JEWELONE].Load(imagefile);

	imagefile = imagepath + "2.bmp";
	JewelImages[JEWELTWO].Load(imagefile);

	imagefile = imagepath + "3.bmp";
	JewelImages[JEWELTHREE].Load(imagefile);

	imagefile = imagepath + "4.bmp";
	JewelImages[JEWELFOUR].Load(imagefile);

	imagefile = imagepath + "5.bmp";
	JewelImages[JEWELFIVE].Load(imagefile);

	imagefile = imagepath + "6.bmp";
	JewelImages[JEWELSIX].Load(imagefile);

	imagefile = imagepath + "7.bmp";
	JewelImages[JEWELSEVEN].Load(imagefile);

	imagefile = imagepath + "cursor.bmp";
	JewelImages[JEWELCURSOR].Load(imagefile);

	imagefile = imagepath + "gameover.bmp";
	JewelImages[JEWELGAMEOVER].Load(imagefile);

	imagefile = imagepath + "logo.png";
	JewelImages[JEWELLOGO].Load(imagefile);

	imagefile = imagepath + "1H.bmp";
	JewelImages[JEWELONECONNECTED].Load(imagefile);

	imagefile = imagepath + "2H.bmp";
	JewelImages[JEWELTWOCONNECTED].Load(imagefile);

	imagefile = imagepath + "3H.bmp";
	JewelImages[JEWELTHREECONNECTED].Load(imagefile);

	imagefile = imagepath + "4H.bmp";
	JewelImages[JEWELFOURCONNECTED].Load(imagefile);

	imagefile = imagepath + "5H.bmp";
	JewelImages[JEWELFIVECONNECTED].Load(imagefile);

	imagefile = imagepath + "6H.bmp";
	JewelImages[JEWELSIXCONNECTED].Load(imagefile);

	imagefile = imagepath + "7H.bmp";
	JewelImages[JEWELSEVENCONNECTED].Load(imagefile);

	imagefile = imagepath + "ScoreBackGround.bmp";
	JewelImages[JEWELSCOREBACKGROUND].Load(imagefile);

	imagefile = imagepath + "Score0.png";
	JewelImages[JEWELSCORE0].Load(imagefile);
	JewelImages[JEWELSCORE0].SetTransparentColor(RGB(255,255,255));

	imagefile = imagepath + "Score1.png";
	JewelImages[JEWELSCORE1].Load(imagefile);
	JewelImages[JEWELSCORE1].SetTransparentColor(RGB(255,255,255));

	imagefile = imagepath + "Score2.png";
	JewelImages[JEWELSCORE2].Load(imagefile);
	JewelImages[JEWELSCORE2].SetTransparentColor(RGB(255,255,255));

	imagefile = imagepath + "Score3.png";
	JewelImages[JEWELSCORE3].Load(imagefile);
	JewelImages[JEWELSCORE3].SetTransparentColor(RGB(255,255,255));

	imagefile = imagepath + "Score4.png";
	JewelImages[JEWELSCORE4].Load(imagefile);
	JewelImages[JEWELSCORE4].SetTransparentColor(RGB(255,255,255));

	imagefile = imagepath + "Score5.png";
	JewelImages[JEWELSCORE5].Load(imagefile);
	JewelImages[JEWELSCORE5].SetTransparentColor(RGB(255,255,255));

	imagefile = imagepath + "Score6.png";
	JewelImages[JEWELSCORE6].Load(imagefile);
	JewelImages[JEWELSCORE6].SetTransparentColor(RGB(255,255,255));

	imagefile = imagepath + "Score7.png";
	JewelImages[JEWELSCORE7].Load(imagefile);
	JewelImages[JEWELSCORE7].SetTransparentColor(RGB(255,255,255));

	imagefile = imagepath + "Score8.png";
	JewelImages[JEWELSCORE8].Load(imagefile);
	JewelImages[JEWELSCORE8].SetTransparentColor(RGB(255,255,255));

	imagefile = imagepath + "Score9.png";
	JewelImages[JEWELSCORE9].Load(imagefile);
	JewelImages[JEWELSCORE9].SetTransparentColor(RGB(255,255,255));

	imagefile = imagepath + "FixBack.png";
	JewelImages[JEWELFIXBACK].Load(imagefile);

}

void CJewel::NewGame()
{
	int JewelValue;

	Score = 0;
	paintAll = true;
	bCleanDrawSquare = true;
	ClickedOneJewel = false;
	Jtime = 0;
	IncrementJtime = false;
	CleanDrawSquare();

	// seed our random number generator
	srand(GetTickCount());

	for (int i = 0; i < JEWELCOLUMNS; i++)
	{
		for (int j = 0; j < JEWELROWS; j++)
		{
			JewelValue = -1;
			while ((JewelValue < 0) || (JewelValue > 6))
			{
				JewelValue = rand() % (7);
			}
			PlayArea[i][j].Jewel = JewelValue;
		}
	}
}

int CJewel::Round(double d)
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

// CJewel message handlers

void CJewel::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	int LogoSize, JewelWidth, JewelHeight, LineSize;;
	int OverallWidth, OverallHeight;
	double WidthRatio, HieghtRatio;
	int h, v;

	LogoSize = JewelImages[JEWELLOGO].GetWidth();
	JewelWidth = JewelImages[0].GetWidth();
	JewelHeight = JewelImages[0].GetHeight();
	LineSize = Round(JewelWidth *.05);

	OverallWidth = LogoSize + (JewelWidth * JEWELCOLUMNS) + (LineSize * JEWELCOLUMNS) + (LineSize * 2);
	OverallHeight = (JewelHeight * JEWELROWS) + (LineSize * JEWELROWS) + (LineSize * 2);

	WidthRatio = (double)cx/OverallWidth;
	HieghtRatio = (double)cy/OverallHeight;

	if (WidthRatio > HieghtRatio)
	{
		StrechRatio = HieghtRatio;
	}
	else
	{
		StrechRatio = WidthRatio;
	}

	JewelWidth = Round(JewelWidth * StrechRatio);
	JewelHeight = Round(JewelHeight * StrechRatio);
	LineSize = Round(LineSize * StrechRatio);

	Logo.left = 0;
	Logo.top = 0;
	Logo.right = Round(JewelImages[JEWELLOGO].GetWidth() * StrechRatio);
	Logo.bottom = Round(JewelImages[JEWELLOGO].GetHeight() * StrechRatio);

	ScoreRect.left = LineSize * 2;
	ScoreRect.right = Logo.right;
	ScoreRect.top = Logo.bottom + Logo.bottom + (LineSize * 2);
	ScoreRect.bottom = ScoreRect.top + 50;

	TimerRect.left = LineSize * 2;
	TimerRect.right = Logo.right;
	TimerRect.top = ScoreRect.bottom + (LineSize * 2);
	TimerRect.bottom = TimerRect.top + 50;
	
	h = Logo.right + (LineSize * 5);
	

	for (int i = 0; i < JEWELCOLUMNS; i++)
	{
		v = LineSize;
		for (int j = 0; j < JEWELROWS; j++)
		{
			PlayArea[i][j].JPRect.left = h;
			PlayArea[i][j].JPRect.right = h + JewelWidth;
			PlayArea[i][j].JPRect.top = v;
			PlayArea[i][j].JPRect.bottom = v + JewelHeight;
			v = v + JewelHeight + LineSize;
		}
		h = h + JewelWidth + LineSize;
	}
}

void CJewel::OnPaint()
{
	CPaintDC dc(this); 
	CRect iRect;
	

	if (paintAll)
	{
		GetWindowRect(&JRectColorChanger);
		CBrush BrushBlack(RGB(255, 255, 128));
		// Select the new brush
		pFCOldBrush = dc.SelectObject(&BrushBlack);

		// Convert the current coordinates from Screen to Client
		ScreenToClient(&JRectColorChanger);
		// Change the background of the control
		dc.Rectangle(JRectColorChanger);

	}
	JewelImages[JEWELLOGO].StretchBlt(dc, Logo);
	DrawTheScoreAndTimer(&dc);
	if (!paintAll)
	{
		iRect = PlayArea[3][3].JPRect;
		iRect.left = iRect.right;
		iRect.right = PlayArea[4][3].JPRect.left;
		JewelImages[JEWELFIXBACK].StretchBlt(dc, iRect);

		iRect = PlayArea[4][3].JPRect;
		iRect.left = iRect.right;
		iRect.right = PlayArea[5][3].JPRect.left;
		JewelImages[JEWELFIXBACK].StretchBlt(dc, iRect);

		iRect = PlayArea[5][3].JPRect;
		iRect.left = iRect.right;
		iRect.right = PlayArea[6][3].JPRect.left;
		JewelImages[JEWELFIXBACK].StretchBlt(dc, iRect);

		iRect = PlayArea[6][3].JPRect;
		iRect.left = iRect.right;
		iRect.right = PlayArea[7][3].JPRect.left;
		JewelImages[JEWELFIXBACK].StretchBlt(dc, iRect);

		iRect = PlayArea[7][3].JPRect;
		iRect.left = iRect.right;
		iRect.right = PlayArea[8][3].JPRect.left;
		JewelImages[JEWELFIXBACK].StretchBlt(dc, iRect);
	}

	for (int i = 0; i < JEWELCOLUMNS; i++)
	{
		for (int j = 0; j < JEWELROWS; j++)
		{
			if ((paintAll == true) || (DrawSquare[i][j] == true))
			{
				JewelImages[PlayArea[i][j].Jewel].StretchBlt(dc,PlayArea[i][j].JPRect); 
			}
		}
	}
	if (AmountAddedToScore > 0)
	{
		int th, h, t, scorewidth;
		bool fth = false;
		bool fh = false;
		
		CRect ScoreLoc;
		th = AmountAddedToScore / 1000;
		AmountAddedToScore = AmountAddedToScore - (th * 1000);
		h = AmountAddedToScore / 100;
		AmountAddedToScore = AmountAddedToScore - (h * 100);
		t = AmountAddedToScore / 10;
		
		DrawSquare[3][3] = true;
		DrawSquare[4][3] = true;
		DrawSquare[5][3] = true;
		DrawSquare[6][3] = true;
		DrawSquare[7][3] = true;
		DrawSquare[8][3] = true;
		ScoreLoc = PlayArea[3][3].JPRect;
		scorewidth = JewelImages[JEWELSCORE0].GetWidth();
		ScoreLoc.right = ScoreLoc.left + scorewidth;

		if (th > 0)
		{
			JewelImages[JEWELSCORE0 + th].TransparentBlt(dc, ScoreLoc);
			ScoreLoc.left = ScoreLoc.right;
			ScoreLoc.right = ScoreLoc.left + scorewidth;
			fth = true;
		}
		if (h > 0 || fth)
		{
			JewelImages[JEWELSCORE0 + h].TransparentBlt(dc, ScoreLoc);
			ScoreLoc.left = ScoreLoc.right;
			ScoreLoc.right = ScoreLoc.left + scorewidth;
			fh = true;
		}
		if (t > 0 || fh)
		{
			JewelImages[JEWELSCORE0 + t].TransparentBlt(dc, ScoreLoc);
			ScoreLoc.left = ScoreLoc.right;
			ScoreLoc.right = ScoreLoc.left + scorewidth;
		}
		JewelImages[JEWELSCORE0].TransparentBlt(dc, ScoreLoc);

		AmountAddedToScore = 0;
	}
	if (bCleanDrawSquare)
	{
		CleanDrawSquare();
	}
	if (!TimerHasBeenSet)
	{
		JSetTimer();
	}
	paintAll = false;
	if (SeeIfGameIsOver())
	{
		// do game over dialog
		CJewelGameOver jgo;
		jgo.DoModal();
		NewGame();
		Invalidate(false);
	}
}

bool CJewel::SeeIfWeMatch3()
{
	bool rtnval = false;
	int newval, oldval, count;
	int newJewel;
	double base = 2;

	// check for vertical
	for (int i = 0; i < JEWELCOLUMNS; i++)
	{
		oldval = -1;
		count = 0;
		for (int j = 0; j < JEWELROWS; j++)
		{
			newval = PlayArea[i][j].Jewel;
			if (oldval == newval)
			{
				count++;
				if (count >= 2)
				{
					DrawSquare[i][j] = true;
					DrawSquare[i][j - 1] = true;
					DrawSquare[i][j - 2] = true;
					newJewel = GetHighlightedJewel(PlayArea[i][j].Jewel);
					PlayArea[i][j].Jewel = newJewel;
					PlayArea[i][j - 1].Jewel = newJewel;
					PlayArea[i][j - 2].Jewel = newJewel;
					rtnval = true;
				}
			}
			else
			{
				if (count >= 2)
				{
					count -= 2;
					if (count == 0)
					{
						AmountAddedToScore = AmountAddedToScore + 10;
						Score = Score + 10;
					}
					else
					{
						AmountAddedToScore = AmountAddedToScore + 10 + (10 * (int)pow(base, count));
						Score = Score + 10 + (10 * (int)pow(base, count));
					}
				}
				count = 0;
				oldval = newval;
			}
			if (j == (JEWELROWS - 1))
			{
				if (count >= 2)
				{
					count -= 2;
					if (count == 0)
					{
						AmountAddedToScore = AmountAddedToScore + 10;
						Score = Score + 10;
					}
					else
					{
						AmountAddedToScore = AmountAddedToScore + 10 + (10 * (int)pow(base, count));
						Score = Score + 10 + (10 * (int)pow(base, count));
					}
				}
			}
		}
	}
	// check for horz.
	for (int j = 0; j < JEWELROWS; j++)
	{
		oldval = -1;
		count = 0;
		for (int i = 0; i < JEWELCOLUMNS; i++)
		{
			newval = PlayArea[i][j].Jewel;
			if (oldval == newval)
			{
				count++;
				if (count >= 2)
				{
					DrawSquare[i][j] = true;
					DrawSquare[i - 1][j] = true;
					DrawSquare[i - 2][j] = true;
					newJewel = GetHighlightedJewel(PlayArea[i][j].Jewel);
					PlayArea[i][j].Jewel = newJewel;
					PlayArea[i - 1][j].Jewel = newJewel;
					PlayArea[i - 2][j].Jewel = newJewel;
					rtnval = true;
				}
			}
			else
			{
				if (count >= 2)
				{
					count -= 2;
					if (count == 0)
					{
						AmountAddedToScore = AmountAddedToScore + 10;
						Score = Score + 10;
					}
					else
					{
						AmountAddedToScore = AmountAddedToScore + 10 + (10 * (int)pow(base, count));
						Score = Score + 10 + (10 * (int)pow(base, count));
					}
				}
				count = 0;
				oldval = newval;
			}
			if (i == (JEWELCOLUMNS - 1))
			{
				if (count >= 2)
				{
					count -= 2;
					if (count == 0)
					{
						AmountAddedToScore = AmountAddedToScore + 10;
						Score = Score + 10;
					}
					else
					{
						AmountAddedToScore = AmountAddedToScore + 10 + (10 * (int)pow(base, count));
						Score = Score + 10 + (10 * (int)pow(base, count));
					}
				}
			}
		}
	}
	return rtnval;
}

void CJewel::SeeIfWeCanMakeAPlay()
{
	if ((JewelPauseSeconds < JEWELPAUSESECONDS) && (Made3InARow))
	{
		JewelPauseSeconds++;
		return;
	}
	if (Made3InARow)
	{
		bCleanDrawSquare = false;
		MoveInNewJewels();
		Made3InARow = SeeIfWeMatch3();
		JewelPauseSeconds = 0;
		Invalidate(false);
	}
}

void CJewel::MoveInNewJewels()
{
	int k;
	for (int i = 0; i < JEWELCOLUMNS; i++)
	{
		for (int j = 0; j < JEWELROWS; j++)
		{
			if ((DrawSquare[i][j]) && (PlayArea[i][j].Jewel >= JEWELONECONNECTED))
			{
				if (j == 0)
				{
					PlayArea[i][0].Jewel = rand() % (7);
					DrawSquare[i][j] = true;
				}
				else
				{
					k = j;
					while (k > 0)
					{
						PlayArea[i][k].Jewel = PlayArea[i][k - 1].Jewel;
						DrawSquare[i][k] = true;
						k--;
					}
					PlayArea[i][0].Jewel = rand() % (7);
					DrawSquare[i][0] = true;
				}
			}
		}
	}
}

void CJewel::OnLButtonUp(UINT nFlags, CPoint point)
{

	if (ClickedOneJewel == true)
	{
		for (int i = 0; i < JEWELCOLUMNS; i++)
		{
			for (int j = 0; j < JEWELROWS; j++)
			{
				if (PlayArea[i][j].JPRect.PtInRect(point))
				{
					if ((i == ClickedJewelColumn) && (j == ClickedJewelRow))
					{
						PlayArea[i][j].Jewel = GetUnHighlightedJewel(PlayArea[i][j].Jewel);
						DrawSquare[i][j] = true;
						ClickedOneJewel = false;
						Invalidate(false);
					}
					else
					{
						PlayArea[ClickedJewelColumn][ClickedJewelRow].Jewel = GetUnHighlightedJewel(PlayArea[ClickedJewelColumn][ClickedJewelRow].Jewel);
						DoSwap(i, j);
						Made3InARow = SeeIfWeMatch3();
						if (Made3InARow)
						{
							bCleanDrawSquare = false;
						}
						ClickedOneJewel = false;
						Invalidate(false);
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < JEWELCOLUMNS; i++)
		{
			for (int j = 0; j < JEWELROWS; j++)
			{
				if (PlayArea[i][j].JPRect.PtInRect(point))
				{
					ClickedJewelColumn = i;
					ClickedJewelRow = j;
					PlayArea[i][j].Jewel = GetHighlightedJewel(PlayArea[i][j].Jewel);
					DrawSquare[i][j] = true;
					ClickedOneJewel = true;
					Invalidate(false);
				}
			}
		}
	}

	CView::OnLButtonUp(nFlags, point);
}

void CJewel::DoSwap(int col, int row)
{
	int jval;
	bool ThenWeCanSwap = false;
	// left
	if (col != 0)
	{
		if (((col - 1) == ClickedJewelColumn) && (row == ClickedJewelRow))
		{
			ThenWeCanSwap = true;
		}
	}
	// left top
	if ((col != 0) && (row != 0) && (ThenWeCanSwap == false))
	{
		if (((col - 1) == ClickedJewelColumn) && ((row - 1) == ClickedJewelRow))
		{
			ThenWeCanSwap = true;
		}
	}
	// top
	if ((row != 0) && (ThenWeCanSwap == false))
	{
		if ((col == ClickedJewelColumn) && ((row - 1) == ClickedJewelRow))
		{
			ThenWeCanSwap = true;
		}
	}
	// top right
	if ((col != (JEWELCOLUMNS - 1)) && (row != 0) && (ThenWeCanSwap == false))
	{
		if (((col + 1) == ClickedJewelColumn) && ((row - 1) == ClickedJewelRow))
		{
			ThenWeCanSwap = true;
		}
	}
	// right
	if ((col != (JEWELCOLUMNS - 1)) && (ThenWeCanSwap == false))
	{
		if ((col + 1) == ClickedJewelColumn) 
		{
			ThenWeCanSwap = true;
		}
	}
	// right bottom
	if ((col != (JEWELCOLUMNS - 1)) && (row != (JEWELROWS - 1)) && (ThenWeCanSwap == false))
	{
		if (((col + 1) == ClickedJewelColumn) && ((row + 1) == ClickedJewelRow))
		{
			ThenWeCanSwap = true;
		}
	}
	// bottom
	if ((row != (JEWELROWS - 1)) && (ThenWeCanSwap == false))
	{
		if ((col == ClickedJewelColumn) && ((row + 1) == ClickedJewelRow))
		{
			ThenWeCanSwap = true;
		}
	}
	// left bottom
	if ((col != 0) && (row != (JEWELROWS - 1)) && (ThenWeCanSwap == false))
	{
		if (((col - 1) == ClickedJewelColumn) && ((row + 1) == ClickedJewelRow))
		{
			ThenWeCanSwap = true;
		}
	}

	if (ThenWeCanSwap)
	{
		jval = PlayArea[col][row].Jewel;
		PlayArea[col][row].Jewel = PlayArea[ClickedJewelColumn][ClickedJewelRow].Jewel;
		PlayArea[ClickedJewelColumn][ClickedJewelRow].Jewel = jval;
		DrawSquare[ClickedJewelColumn][ClickedJewelRow] = true;
		DrawSquare[col][row] = true;
	}
}

int CJewel::GetHighlightedJewel(int oldJewel)
{
	switch (oldJewel)
	{
	case JEWELONE:
		return JEWELONECONNECTED;
	case JEWELTWO:
		return JEWELTWOCONNECTED;
	case JEWELTHREE:
		return JEWELTHREECONNECTED;
	case JEWELFOUR:
		return JEWELFOURCONNECTED;
	case JEWELFIVE:
		return JEWELFIVECONNECTED;
	case JEWELSIX:
		return JEWELSIXCONNECTED;
	case JEWELSEVEN:
		return JEWELSEVENCONNECTED;
	}
	return JEWELONECONNECTED;
}

int CJewel::GetUnHighlightedJewel(int oldJewel)
{
	switch (oldJewel)
	{
	case JEWELONECONNECTED:
		return JEWELONE;
	case JEWELTWOCONNECTED:
		return JEWELTWO;
	case JEWELTHREECONNECTED:
		return JEWELTHREE;
	case JEWELFOURCONNECTED:
		return JEWELFOUR;
	case JEWELFIVECONNECTED:
		return JEWELFIVE;
	case JEWELSIXCONNECTED:
		return JEWELSIX;
	case JEWELSEVENCONNECTED:
		return JEWELSEVEN;
	}
	return JEWELONE;
}

void CJewel::OnTimer(UINT_PTR nIDEvent)
{
	SeeIfWeCanMakeAPlay();
	if (IncrementJtime)
	{
		Jtime++;
		IncrementJtime = false;
		Invalidate(false);
	}
	else
	{
		IncrementJtime = true;
	}

	CView::OnTimer(nIDEvent);
}

void CJewel::JSetTimer()
{
	m_nTimer = SetTimer(IDR_RDAJEWELTYPE, 500, NULL);
	TimerHasBeenSet = true;
}

void CJewel::JStopTimer()
{
	//KillTimer(m_nTimer);
}

void CJewel::DrawTheScoreAndTimer(CPaintDC *dc)
{
	LOGFONT LogFont;
	CFont SizeFont;
	CFont *pFont;

	//delete the old images first
	dc->FillSolidRect(ScoreRect, RGB(255, 255, 128)); 
	dc->FillSolidRect(TimerRect, RGB(255, 255, 128)); 

	CString score;
	score.Format("Score: %d", Score);

	int iFontSize = 30;

	LogFont.lfWeight = 0; //(int)(iFontSize * theDrawScreen->CardStretchSize);
	LogFont.lfStrikeOut = 0;
	LogFont.lfUnderline = 0;
	LogFont.lfHeight = (int)(iFontSize * StrechRatio);  // sets font size
	LogFont.lfEscapement = 0;
	LogFont.lfItalic = FALSE;
	LogFont.lfWidth = 0;
	strcpy_s(LogFont.lfFaceName, "Arial");

	SizeFont.CreateFontIndirect(&LogFont);	
	pFont = dc->SelectObject(&SizeFont);

	if (Score == 0)
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
	dc->SetTextColor(RGB(0, 0, 0));
	score.Format("Time: %d", Jtime);
	dc->DrawText(score,TimerRect, DT_NOCLIP | DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc->SelectObject(pFont);
	SizeFont.DeleteObject();
}

void CJewel::OnDestroy()
{
	CView::OnDestroy();

	JStopTimer();
}

BOOL CJewel::OnEraseBkgnd(CDC* pDC)
{
	paintAll = true;
	return CView::OnEraseBkgnd(pDC);
}

void CJewel::OnAppDeal()
{
	NewGame();
}

void CJewel::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	CMFCRibbonBar *pRibbon;
	CMFCRibbonCategory *pRibbonCategory;

	pRibbon = ((CMainFrame*)AfxGetMainWnd())->GetRibbonBar();
	pRibbonCategory = pRibbon->GetCategory(4);
	pRibbon->SetActiveCategory(pRibbonCategory, true);

	paintAll = true;
	Invalidate(false);
}

bool CJewel::SeeIfGameIsOver()
{
	int jewelval, jcount;
	bool rtnval;

	// check for vertical
	for (int i = 0; i < JEWELCOLUMNS; i++)
	{
		for (int j = 0; j < JEWELROWS; j++)
		{
			jewelval = PlayArea[i][j].Jewel;
			// two above locations have same value
			if (j > 1)
			{
				if ((PlayArea[i][j-1].Jewel == jewelval) && (PlayArea[i][j-2].Jewel == jewelval))
				{
					return false;
				}
			}
			// two below locations have same value
			if (j < (JEWELROWS - 3))
			{
				if ((PlayArea[i][j+1].Jewel == jewelval) && (PlayArea[i][j+2].Jewel == jewelval))
				{
					return false;
				}
			}
			// one above and one below have same value
			if ((j > 0) && (j < (JEWELROWS - 2)))
			{
				if ((PlayArea[i][j-1].Jewel == jewelval) && (PlayArea[i][j+1].Jewel == jewelval))
				{
					return false;
				}
			}
			// two locations to the left have the same value
			if (i > 1)
			{
				if ((PlayArea[i-1][j].Jewel == jewelval) && (PlayArea[i-2][j].Jewel == jewelval))
				{
					return false;
				}
			}
			// two locations to the right have the same value
			if (i < (JEWELCOLUMNS - 3))
			{
				if ((PlayArea[i+1][j].Jewel == jewelval) && (PlayArea[i+2][j].Jewel == jewelval))
				{
					return false;
				}
			}
			// one location to the left and one to the right have the same value
			if ((i > 0) && (i < (JEWELCOLUMNS - 2)))
			{
				if ((PlayArea[i-1][j].Jewel == jewelval) && (PlayArea[i+1][j].Jewel == jewelval))
				{
					return false;
				}
			}
			// 2 locations have the same value in the locations 2 above ,1 left & above, 2 to the left
			if ((i > 1) && (j > 1))
			{
				jcount = 0;
				if (PlayArea[i][j-2].Jewel == jewelval)
				{
					jcount++;;
				}
				if (PlayArea[i-1][j-1].Jewel == jewelval)
				{
					jcount++;;
				}
				if (PlayArea[i-2][j].Jewel == jewelval)
				{
					jcount++;;
				}
				if (jcount > 1)
				{
					return false;
				}
			}
			// 2 locations have the same value in the locations 2 above 1, right & above, 2 to the right
			if ((i < (JEWELCOLUMNS - 3)) && (j > 1))
			{
				jcount = 0;
				if (PlayArea[i][j-2].Jewel == jewelval)
				{
					jcount++;;
				}
				if (PlayArea[i+1][j-1].Jewel == jewelval)
				{
					jcount++;;
				}
				if (PlayArea[i+2][j].Jewel == jewelval)
				{
					jcount++;;
				}
				if (jcount > 1)
				{
					return false;
				}
			}
			// 2 locations have the same value in the locations 2 below 1, left & below, 2 to the left
			if ((i > 1) && (j < (JEWELROWS - 3)))
			{
				jcount = 0;
				if (PlayArea[i][j+2].Jewel == jewelval)
				{
					jcount++;;
				}
				if (PlayArea[i-1][j+1].Jewel == jewelval)
				{
					jcount++;;
				}
				if (PlayArea[i-2][j].Jewel == jewelval)
				{
					jcount++;;
				}
				if (jcount > 1)
				{
					return false;
				}
			}
			// 2 locations have the same value in the locations 2 below 1 right & below, 2 to the right
			if ((i < (JEWELCOLUMNS - 3)) && (j < (JEWELROWS - 3)))
			{
				jcount = 0;
				if (PlayArea[i][j+2].Jewel == jewelval)
				{
					jcount++;;
				}
				if (PlayArea[i+1][j+1].Jewel == jewelval)
				{
					jcount++;;
				}
				if (PlayArea[i+2][j].Jewel == jewelval)
				{
					jcount++;;
				}
				if (jcount > 1)
				{
					return false;
				}
			}
			// if you have 2 in a row vert then if any one touchs has the same value then game not over
			// need to check the three one space beyond the ends too
			if (j < (JEWELROWS - 2))
			{
				if (PlayArea[i][j+1].Jewel == jewelval)
				{
					rtnval = CheckAround2(jewelval, i,j,i,j+1);
					if (rtnval)
					{
						return false;
					}
					// up and down = 1, left and right = 2
					rtnval = CheckAroundSkipOne(jewelval, 1, i, j - 2);
					if (rtnval)
					{
						return false;
					}
					rtnval = CheckAroundSkipOne(jewelval, 1, i, j + 2);
					if (rtnval)
					{
						return false;
					}
				}
			}
			// if you have 2 in a row horz then if any one touchs has the same value then game not over
			// need to check the three one space beyond the ends too
			if (i < (JEWELCOLUMNS - 2))
			{
				if (PlayArea[i+1][j].Jewel == jewelval)
				{
					rtnval = CheckAround2(jewelval, i,j,i+1,j);
					if (rtnval)
					{
						return false;
					}
					// up and down = 1, left and right = 2
					rtnval = CheckAroundSkipOne(jewelval, 2, i - 2, j);
					if (rtnval)
					{
						return false;
					}
					rtnval = CheckAroundSkipOne(jewelval, 2, i + 2, j);
					if (rtnval)
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool CJewel::CheckAroundSkipOne(int jvalue, int direction, int col, int row)
{
	if ((col < 0) || (col >= JEWELCOLUMNS) || (row < 0) || (row >= JEWELROWS))
	{
		return false;
	}
	// up and down = 1, left and right = 2
	switch (direction)
	{
	case 1:
		if ((col - 1) >= 0)
		{
			if (PlayArea[col-1][row].Jewel == jvalue)
			{
				return true;
			}
		}
		if (PlayArea[col][row].Jewel == jvalue)
		{
			return true;
		}
		if ((col + 1) < JEWELCOLUMNS)
		{
			if (PlayArea[col+1][row].Jewel == jvalue)
			{
				return true;
			}
		}
		break;
	case 2:
		if ((row -1) < JEWELROWS)
		{
			if (PlayArea[col][row-1].Jewel == jvalue)
			{
				return true;
			}
		}
		if (PlayArea[col][row].Jewel == jvalue)
		{
			return true;
		}
		if ((row +1) < JEWELROWS)
		{
			if (PlayArea[col][row+1].Jewel == jvalue)
			{
				return true;
			}
		}
		break;
	}
	return false;
}

bool CJewel::CheckAround2(int jvalue, int col1, int row1, int col2, int row2)
{
	int i,j;
	for (i = col1 -1; i <= col1 + 1; i++)
	{
		for(j = row1 - 1; j <= row1 + 1; j++)
		{
			// does count if it is location 1 or location 2
			if (!((j == row1) && (i == col1) || ((j == row2) && (i == col2))))
			{
				if (!(((i < 0) || (i >= JEWELCOLUMNS)) || ((j < 0) || (j >= JEWELROWS))))
				{
					if (PlayArea[i][j].Jewel == jvalue)
					{
						return true;
					}
				}
			}
		}
	}
	for (i = col2 -1; i <= col2 + 1; i++)
	{
		for(j = row2 - 1; j <= row2 + 1; j++)
		{
			// does count if it is location 1 or location 2
			if (!((j == row1) && (i == col1) || ((j == row2) && (i == col2))))
			{
				if (!(((i < 0) || (i >= JEWELCOLUMNS)) || ((j < 0) || (j >= JEWELROWS))))
				{
					if (PlayArea[i][j].Jewel == jvalue)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}