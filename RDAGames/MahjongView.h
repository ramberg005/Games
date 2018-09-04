#pragma once

#include "MahJongImages.h"
#include "definitions.h"
#include "MJLonghorn.h"

struct UndoStruct
{
	int tile1;
	int tile2;
};

// CMahjongView view

class CMahjongView : public CView
{
	DECLARE_DYNCREATE(CMahjongView)

protected:
	CMahjongView();           // protected constructor used by dynamic creation
	virtual ~CMahjongView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CMahJongImages MahjongImages;
	CBrush *pFCOldBrush;
	CRect JRectColorChanger;
	CMJLonghorn LonghornLayout;
	UndoStruct UNDO[100];
	int UndoLoc;

	//MahjongControl TileSpecifics;

	int SizeX;
	int SizeY;
	double stretchval;
	bool paintAll;
	int HighlightedTile;
	bool deleteRects;
	CRect rect1;
	CRect rect2;


public:
	void FillTileSpecifics();
	void CleanTileSpecifics();
	void SetTopTilesToDraw();
	bool IsTilePlayable(int locationid);
	bool DoTilesPlay(int tile1, int tile2);
	void SetDrawOfTilesAround(int tile1, int tile2);
	bool SeeIfGameIsOver();

	
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnMahjongnewButton();
	afx_msg void OnAppDeal();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnXButtonUp(UINT nFlags, UINT nButton, CPoint point);
};


