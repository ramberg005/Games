
#pragma once
#include "definitions.h"
#include "DrawScreen.h"



class CETSol
{
public:
	bool m_bDragging;
	CImageList m_cDragImageList;
	CBitmap m_cBackBmp;
// these are the messages we have to support in the view the code to do the work in in this class
	void OnPaint(CPaintDC &dc);
	void OnSize(int cx, int cy);
	bool OnLButtonUp(CPaintDC &dc, CPoint point);
	void OnMouseMove(UINT nFlags, CPaintDC &dc, CPoint point);
	void OnAppDeal();
	bool OnLButtonDown(CPoint point);
	bool OnRButtonUp(CPoint point);
	bool OnXButtonUp(UINT nFlags, UINT nButton, CPoint point);
	void OnAppUndo();
	void OnFileLoadstats(CPaintDC &dc);
	void OnDestroy();
	void OnFileShowstats();
	void OnHelpDebugdump();
	void OnQueryOpen();
	
public:
	CDrawScreen *theDrawScreen;
	CFont SizeFont;
	LOGFONT LogFont;

private:
	CRect RectColorChanger;
	CBrush *pOldBrush;
	CFont *pFont;

private:
	void DrawScore(CPaintDC *dc);


public:
	CETSol();
	~CETSol();
};
