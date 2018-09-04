// MahjongView.cpp : implementation file
//

#include "stdafx.h"
#include "RDAGames.h"
#include "MahjongView.h"
#include "TrackViews.h"
#include "MainFrm.h"

int MJTileArray [] = {BAMBOO1_PNG, BAMBOO2_PNG, BAMBOO3_PNG, BAMBOO4_PNG, BAMBOO5_PNG, BAMBOO6_PNG, BAMBOO7_PNG, BAMBOO8_PNG, BAMBOO9_PNG, CIRCLE1_PNG, CIRCLE2_PNG, CIRCLE3_PNG, CIRCLE4_PNG, CIRCLE5_PNG,
CIRCLE6_PNg, CIRCLE7_PNG, CIRCLE8_PNG, CIRCLE9_PNG, DRAGON1_PNG, DRAGON2_PNG, DRAGON3_PNG, WAN1_PNG, WAN2_PNG, WAN3_PNG, WAN4_PNG, WAN5_PNG, WAN6_PNG, WAN7_PNG, WAN8_PNG, WAN9_PNG, EAST_PNG,
NORTH_PNG, SOUTH_PNG, WEST_PNG, CHRYSANTHEMUM_PNG, ORCHID_PNG, PLUM_PNG, BAMBOO_PNG, SPRING_PNG, SUMMER_PNG, WINTER_PNG, FALL_PNG, BAMBOO1_PNG, BAMBOO2_PNG, BAMBOO3_PNG, BAMBOO4_PNG, BAMBOO5_PNG,
BAMBOO6_PNG, BAMBOO7_PNG, BAMBOO8_PNG, BAMBOO9_PNG, CIRCLE1_PNG, CIRCLE2_PNG, CIRCLE3_PNG, CIRCLE4_PNG, CIRCLE5_PNG, CIRCLE6_PNg, CIRCLE7_PNG, CIRCLE8_PNG, CIRCLE9_PNG, DRAGON1_PNG,
DRAGON2_PNG, DRAGON3_PNG, WAN1_PNG, WAN2_PNG, WAN3_PNG, WAN4_PNG, WAN5_PNG, WAN6_PNG, WAN7_PNG, WAN8_PNG, WAN9_PNG, EAST_PNG, NORTH_PNG, SOUTH_PNG, WEST_PNG, CHRYSANTHEMUM_PNG, ORCHID_PNG,
PLUM_PNG, BAMBOO_PNG, SPRING_PNG, SUMMER_PNG, WINTER_PNG, FALL_PNG, BAMBOO1_PNG, BAMBOO2_PNG, BAMBOO3_PNG, BAMBOO4_PNG, BAMBOO5_PNG, BAMBOO6_PNG, BAMBOO7_PNG, BAMBOO8_PNG, BAMBOO9_PNG, CIRCLE1_PNG,
CIRCLE2_PNG, CIRCLE3_PNG, CIRCLE4_PNG, CIRCLE5_PNG, CIRCLE6_PNg, CIRCLE7_PNG, CIRCLE8_PNG, CIRCLE9_PNG, DRAGON1_PNG, DRAGON2_PNG, DRAGON3_PNG, WAN1_PNG, WAN2_PNG, WAN3_PNG, WAN4_PNG, WAN5_PNG,
WAN6_PNG, WAN7_PNG, WAN8_PNG, WAN9_PNG, BAMBOO1_PNG, BAMBOO2_PNG, BAMBOO3_PNG, BAMBOO4_PNG, BAMBOO5_PNG, BAMBOO6_PNG, BAMBOO7_PNG, BAMBOO8_PNG, BAMBOO9_PNG, CIRCLE1_PNG, CIRCLE2_PNG, CIRCLE3_PNG,
CIRCLE4_PNG, CIRCLE5_PNG, CIRCLE6_PNg, CIRCLE7_PNG, CIRCLE8_PNG, CIRCLE9_PNG, DRAGON1_PNG, DRAGON2_PNG, DRAGON3_PNG, WAN1_PNG, WAN2_PNG, WAN3_PNG, WAN4_PNG, WAN5_PNG, WAN6_PNG, WAN7_PNG, WAN8_PNG, WAN9_PNG};


// CMahjongView

IMPLEMENT_DYNCREATE(CMahjongView, CView)

CMahjongView::CMahjongView()
{
	MahjongImages.LoadImages();
	CleanTileSpecifics();
	LonghornLayout.SetAdjancentIDs();
	LonghornLayout.SetupData();
	FillTileSpecifics();
	paintAll = true;
	HighlightedTile = -1;
	deleteRects = false;
	UndoLoc = 0;
}

CMahjongView::~CMahjongView()
{
	CTrackViews tv;
	tv.RemoveStatus(MAHJONGVIEW);
}

BEGIN_MESSAGE_MAP(CMahjongView, CView)
	ON_WM_PAINT()
	ON_WM_SIZE()
//	ON_COMMAND(ID_MAHJONGNEW_BUTTON, &CMahjongView::OnMahjongnewButton)
ON_COMMAND(ID_APP_DEAL, &CMahjongView::OnAppDeal)
ON_WM_SETFOCUS()
ON_WM_LBUTTONUP()
ON_WM_XBUTTONUP()
END_MESSAGE_MAP()


// CMahjongView drawing

void CMahjongView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CMahjongView diagnostics

#ifdef _DEBUG
void CMahjongView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMahjongView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMahjongView message handlers


void CMahjongView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	

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
	if (deleteRects)
	{
		MahjongImages.MJImagesMask[BLANK_PNG].StretchBlt(dc, rect1, SRCAND);
		MahjongImages.MJImages[BLANK_PNG].StretchBlt(dc, rect1, SRCPAINT);
		MahjongImages.MJImagesMask[BLANK_PNG].StretchBlt(dc, rect2, SRCAND);
		MahjongImages.MJImages[BLANK_PNG].StretchBlt(dc, rect2, SRCPAINT);
	}

	for (int i = 0; i < MAHJONGTILES; i++)
	{
		if (LonghornLayout.LHRectDefinition[i].Draw == true || paintAll == true)
		{
			MahjongImages.MJImagesMask[LonghornLayout.LHRectDefinition[i].TileID].StretchBlt(dc, LonghornLayout.LHRectDefinition[i].ScreenLocation, SRCAND);
			if (LonghornLayout.LHRectDefinition[i].TileSelected == false)
			{
				MahjongImages.MJImages[LonghornLayout.LHRectDefinition[i].TileID].StretchBlt(dc, LonghornLayout.LHRectDefinition[i].ScreenLocation, SRCPAINT);
			}
			else
			{
				MahjongImages.MJImagesHighLighted[LonghornLayout.LHRectDefinition[i].TileID].StretchBlt(dc, LonghornLayout.LHRectDefinition[i].ScreenLocation, SRCPAINT);
			}
		}
		LonghornLayout.LHRectDefinition[i].Draw = false;
	}
	paintAll = false;
	deleteRects = false;
	if (SeeIfGameIsOver())
	{
		MessageBox("Game over", "Game over", 0);
	}
}

void CMahjongView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	double width, height;

	SizeX = cx;
	SizeY = cy;
	if ((cx > 0) && (cy > 0))
	{
		width = (double)cx/DEFAULTSCREENWIDTH;
		height = (double)cy/DEFAULTSCREENHEIGHT;

		if (width > height)
		{
			stretchval = height;
		}
		else
		{
			stretchval = width;
		}
		LonghornLayout.SetSize(stretchval);
		SetTopTilesToDraw();
	}
	paintAll = true;
	Invalidate(false);
}

void CMahjongView::FillTileSpecifics()
{
	int rndnum;
	int i;
	int tilearray[MAHJONGTILES];

	srand(GetTickCount());
	for (i = 0; i < MAHJONGTILES; i++)
	{
		tilearray[i] = -1;
	}
	while (tilearray[MAHJONGTILES - 1] == -1)
	{
		rndnum = rand() % MAHJONGTILES;
		for (i = 1; i < MAHJONGTILES; i++)
		{
			if (tilearray[i] == -1)
			{
				tilearray[i] = rndnum;
				break;
			}
			if (tilearray[i] == rndnum)
			{
				break;
			}
		}
	}

	for (int i = 0; i < MAHJONGTILES; i++)
	{
		LonghornLayout.LHRectDefinition[i].TileID = MJTileArray[tilearray[i]];
	}
}

void CMahjongView::CleanTileSpecifics()
{

	for (int i = 0; i < MAHJONGTILES; i++)
	{
		LonghornLayout.LHRectDefinition[i].Draw = false;
		LonghornLayout.LHRectDefinition[i].TileID = -1;
		LonghornLayout.LHRectDefinition[i].TileSelected = false;
		LonghornLayout.LHRectDefinition[i].Played = false;
	}
}

void CMahjongView::OnAppDeal()
{
	CleanTileSpecifics();
	FillTileSpecifics();
	SetTopTilesToDraw();
	UndoLoc = 0;
	Invalidate(false);
}

void CMahjongView::SetTopTilesToDraw()
{
	int id;
	for (int i = 0; i < MAHJONGTILES; i++)
	{
		id = LonghornLayout.LHRectDefinition[i].adjancentIDs.aboveID;
		if (id != -1)
		{
			if (LonghornLayout.LHRectDefinition[id].Played == true)
			{
				if (LonghornLayout.LHRectDefinition[i].Played == false)
				{
					LonghornLayout.LHRectDefinition[i].Draw = true;
				}
			}
		}
		else
		{
			if (LonghornLayout.LHRectDefinition[i].Played == false)
			{
					LonghornLayout.LHRectDefinition[i].Draw = true;
			}
		}
	}
}

void CMahjongView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	CMFCRibbonBar *pRibbon;
	CMFCRibbonCategory *pRibbonCategory;

	pRibbon = ((CMainFrame*)AfxGetMainWnd())->GetRibbonBar();
	pRibbonCategory = pRibbon->GetCategory(5);
	pRibbon->SetActiveCategory(pRibbonCategory, true);

	Invalidate(false);
}

void CMahjongView::OnLButtonUp(UINT nFlags, CPoint point)
{
	for (int i = MAHJONGTILES - 1; i >= 0; i--)
	{
		if (LonghornLayout.LHRectDefinition[i].ScreenLocation.PtInRect(point))
		{
			if (i == HighlightedTile)
			{
				HighlightedTile = -1;
				LonghornLayout.LHRectDefinition[i].Draw = true;
				LonghornLayout.LHRectDefinition[i].TileSelected = false;
				break;
			}
			else
			{
				if (LonghornLayout.LHRectDefinition[i].Played == false)
				{
					if (IsTilePlayable(i))
					{
						if (HighlightedTile == -1)
						{
							LonghornLayout.LHRectDefinition[i].Draw = true;
							if (LonghornLayout.LHRectDefinition[i].TileSelected == true)
							{
								LonghornLayout.LHRectDefinition[i].TileSelected = false;
								HighlightedTile = -1;
							}
							else
							{
								LonghornLayout.LHRectDefinition[i].TileSelected = true;
								HighlightedTile = i;
							}
						}
						else
						{
							if (DoTilesPlay(i, HighlightedTile))
							{
								LonghornLayout.LHRectDefinition[i].Played = true;
								LonghornLayout.LHRectDefinition[i].TileSelected = false;
								LonghornLayout.LHRectDefinition[HighlightedTile].Played = true;
								LonghornLayout.LHRectDefinition[HighlightedTile].TileSelected = false;

								deleteRects = true;
								rect1 = LonghornLayout.LHRectDefinition[HighlightedTile].ScreenLocation;
								rect2 = LonghornLayout.LHRectDefinition[i].ScreenLocation;
								UNDO[UndoLoc].tile1 = i;
								UNDO[UndoLoc].tile2 = HighlightedTile;
								UndoLoc++;
								SetDrawOfTilesAround(i, HighlightedTile);
								HighlightedTile = -1;
							}
						}
					}
				}
			}
		}
	}
	Invalidate(false);
	CView::OnLButtonUp(nFlags, point);
}

void CMahjongView::SetDrawOfTilesAround(int tile1, int tile2)
{
	int id, id2;

	id = LonghornLayout.LHRectDefinition[tile1].adjancentIDs.belowID;
	if (id != -1)
	{
		if (LonghornLayout.LHRectDefinition[id].Played == false)
		{
			LonghornLayout.LHRectDefinition[id].Draw = true;
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.leftID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}	
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.rightID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}	
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.topID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}	
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.bottomID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}	
	}
	id = LonghornLayout.LHRectDefinition[tile1].adjancentIDs.leftID;
	if (id != -1)
	{
		if (LonghornLayout.LHRectDefinition[id].Played == false)
		{
			LonghornLayout.LHRectDefinition[id].Draw = true;
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.aboveID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.belowID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
	}	
	id = LonghornLayout.LHRectDefinition[tile1].adjancentIDs.rightID;
	if (id != -1)
	{
		if (LonghornLayout.LHRectDefinition[id].Played == false)
		{
			LonghornLayout.LHRectDefinition[id].Draw = true;
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.aboveID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.belowID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
	}	
	id = LonghornLayout.LHRectDefinition[tile1].adjancentIDs.topID;
	if (id != -1)
	{
		if (LonghornLayout.LHRectDefinition[id].Played == false)
		{
			LonghornLayout.LHRectDefinition[id].Draw = true;
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.aboveID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.belowID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
	}	
	id = LonghornLayout.LHRectDefinition[tile1].adjancentIDs.bottomID;
	if (id != -1)
	{
		if (LonghornLayout.LHRectDefinition[id].Played == false)
		{
			LonghornLayout.LHRectDefinition[id].Draw = true;
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.aboveID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.belowID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
	}	
	
	
	
	id = LonghornLayout.LHRectDefinition[tile2].adjancentIDs.belowID;
	if (id != -1)
	{
		if (LonghornLayout.LHRectDefinition[id].Played == false)
		{
			LonghornLayout.LHRectDefinition[id].Draw = true;
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.leftID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}	
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.rightID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}	
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.topID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}	
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.bottomID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}	
	}
	id = LonghornLayout.LHRectDefinition[tile2].adjancentIDs.leftID;
	if (id != -1)
	{
		if (LonghornLayout.LHRectDefinition[id].Played == false)
		{
			LonghornLayout.LHRectDefinition[id].Draw = true;
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.aboveID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.belowID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
	}	
	id = LonghornLayout.LHRectDefinition[tile2].adjancentIDs.rightID;
	if (id != -1)
	{
		if (LonghornLayout.LHRectDefinition[id].Played == false)
		{
			LonghornLayout.LHRectDefinition[id].Draw = true;
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.aboveID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.belowID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
	}	
	id = LonghornLayout.LHRectDefinition[tile2].adjancentIDs.topID;
	if (id != -1)
	{
		if (LonghornLayout.LHRectDefinition[id].Played == false)
		{
			LonghornLayout.LHRectDefinition[id].Draw = true;
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.aboveID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.belowID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
	}	
	id = LonghornLayout.LHRectDefinition[tile2].adjancentIDs.bottomID;
	if (id != -1)
	{
		if (LonghornLayout.LHRectDefinition[id].Played == false)
		{
			LonghornLayout.LHRectDefinition[id].Draw = true;
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.aboveID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
		id2 = LonghornLayout.LHRectDefinition[id].adjancentIDs.belowID;
		if (id2 != -1)
		{
			if (LonghornLayout.LHRectDefinition[id2].Played == false)
			{
				LonghornLayout.LHRectDefinition[id2].Draw = true;
			}
		}
	}	
	
}

bool CMahjongView::DoTilesPlay(int tile1, int tile2)
{
	if (tile1 == tile2)
	{
		return false;
	}
	if (LonghornLayout.LHRectDefinition[tile1].TileID == LonghornLayout.LHRectDefinition[tile2].TileID)
	{
		return true;
	}
	return false;
}

bool CMahjongView::IsTilePlayable(int locationid)
{
	int id;

	id = LonghornLayout.LHRectDefinition[locationid].adjancentIDs.aboveID;

	if ((id == -1) || (LonghornLayout.LHRectDefinition[id].Played == true))
	{
		id = LonghornLayout.LHRectDefinition[locationid].adjancentIDs.leftID;
		if ((id == -1) || (LonghornLayout.LHRectDefinition[id].Played == true))
		{
			return true;
		}
		id = LonghornLayout.LHRectDefinition[locationid].adjancentIDs.rightID;
		if ((id == -1) || (LonghornLayout.LHRectDefinition[id].Played == true))
		{
			return true;
		}
	}

	return false;
}

void CMahjongView::OnXButtonUp(UINT nFlags, UINT nButton, CPoint point)
{
	if (UndoLoc > 0)
	{
		UndoLoc--;
		LonghornLayout.LHRectDefinition[UNDO[UndoLoc].tile1].Played = false;
		LonghornLayout.LHRectDefinition[UNDO[UndoLoc].tile1].Draw = true;
		LonghornLayout.LHRectDefinition[UNDO[UndoLoc].tile1].TileSelected = false;
		
		LonghornLayout.LHRectDefinition[UNDO[UndoLoc].tile2].Played = false;
		LonghornLayout.LHRectDefinition[UNDO[UndoLoc].tile2].Draw = true;
		LonghornLayout.LHRectDefinition[UNDO[UndoLoc].tile2].TileSelected = false;
		
		deleteRects = true;
		rect1 = LonghornLayout.LHRectDefinition[UNDO[UndoLoc].tile1].ScreenLocation;
		rect2 = LonghornLayout.LHRectDefinition[UNDO[UndoLoc].tile2].ScreenLocation;
		SetDrawOfTilesAround(UNDO[UndoLoc].tile1, UNDO[UndoLoc].tile2);
		HighlightedTile = -1;
		Invalidate(false);
	}

	CView::OnXButtonUp(nFlags, nButton, point);
}

bool CMahjongView::SeeIfGameIsOver()
{
	int ids[MAHJONGTILES];
	int foundid = 0;

	for (int i = 0; i < MAHJONGTILES; i++)
	{
		if ((LonghornLayout.LHRectDefinition[i].Played == false) &&
			(((LonghornLayout.LHRectDefinition[i].adjancentIDs.leftID == -1) || (LonghornLayout.LHRectDefinition[LonghornLayout.LHRectDefinition[i].adjancentIDs.leftID].Played == true)) ||
			((LonghornLayout.LHRectDefinition[i].adjancentIDs.rightID == -1) || (LonghornLayout.LHRectDefinition[LonghornLayout.LHRectDefinition[i].adjancentIDs.rightID].Played == true))))
		{
			for (int j = 0; j < foundid; j++)
			{
				if (ids[j] == LonghornLayout.LHRectDefinition[i].TileID)
				{
					return false;
				}
			}
			ids[foundid] = LonghornLayout.LHRectDefinition[i].TileID;
			foundid++;
		}
	}
	return true;
}