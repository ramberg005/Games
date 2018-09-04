#pragma once
#include "FCDeck.h"
#include "cards.h"

// CFreeCell view

class CFreeCell : public CView
{
	DECLARE_DYNCREATE(CFreeCell)

protected:
	CFreeCell();           // protected constructor used by dynamic creation
	virtual ~CFreeCell();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

struct FCUndo
{
	int MoveID;
	int FromLocation; // WorkArea, Aces or PlayArea
	int FromColumnLocation; 
	int FromCardLocation;
	int ToLocation; // WorkArea, Aces or PlayArea
	int ToColumnLocation; 
	int ToCardLocation;
};


public:
	CFCDeck *pDeck;
	CardImages *pCards;
	double m_CardSizeModifier;

public:
	void CalcSize(int x, int y);
	int Round(double d);
	int GetLastRow(int *arry);
	int HowManyCardsCanPlay(int *arry);
	bool FCSeeIfWeAreDragingCards(CPoint point);
	void CleanCardsDraggingAround();
	bool DoTheDrop(CPoint point);
	void CleanFromLocation();
	bool PlayAllCards();
	void CleanUnDo();
	bool DoAnUnDo();
	//void IsColumnBelowEndOfScreen(int *col, CRect *mrect);
	void FillScreenRects();
	void DoThePaint();

public:
	bool m_bDragging;
	
	CRect FCDragingRect;
	CBitmap m_FCBackBmp;
	CSize FCoffset;
	CImageList m_FCDragImageList;
	CPoint FCStackLocation;
	CPoint FCOldStackLocation;
	FCUndo FCUndoArray[MAXUNDOACTIONS];
	
	int CardWidth;
	int CardHeight;
	int VerticalGapSmall;
	int VerticalGapLarge;
	int HorzGapSmall;
	int HorzGapLarge;
	int CardsDraggingAround[CARDSINSUITE];
	int *CardsDraggedFromLocation;
	int iMoveID;
	int iUndoArrayLocation;
	bool MovedOffAce;
	int LeftOffset;
	int RightOffset;
	int TopOffset;
	int BottomOffset;


public:
	// want to limit what we paint
	bool PaintAll;
	bool PaintWorkArea[WORKAREACOLUMNS];
	bool PaintAcesArea[WORKAREACOLUMNS];
	bool PaintPlayArea[PLAYAREACOLUMNS];
	int ScreenBottom;
	int ScreenRight;
	void CleanWhereToPaint();
	void DeleteImagesInRect(CDC *dc, CRect &RectToDrawBackGround);

private:
	CRect FCRectColorChanger;
	CBrush *pFCOldBrush;
	CFont *pFCFont;




protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnFreecellNewButton();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnXButtonUp(UINT nFlags, UINT nButton, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAppDeal();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnUndoAllButton();
	afx_msg BOOL OnQueryOpen();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};


