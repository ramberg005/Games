#pragma once

struct JEWELPLAY
{
	CRect JPRect;
	int Jewel;
};

// CJewel view

class CJewel : public CView
{
	DECLARE_DYNCREATE(CJewel)

protected:
	CJewel();           // protected constructor used by dynamic creation
	virtual ~CJewel();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


public:
	bool DrawSquare[JEWELCOLUMNS][JEWELROWS];
	JEWELPLAY PlayArea[JEWELCOLUMNS][JEWELROWS];
	CImage JewelImages[JEWELFIXBACK + 1];

	bool paintAll;
	bool bCleanDrawSquare;
	bool ClickedOneJewel;
	bool TimerHasBeenSet;
	bool Made3InARow;
	bool IncrementJtime;
	
	CRect Logo;
	CRect JRectColorChanger;
	CRect ScoreRect;
	CRect TimerRect;
	CBrush *pFCOldBrush;
	UINT_PTR m_nTimer;

	int Score;
	int AmountAddedToScore;
	int ClickedJewelColumn;
	int	ClickedJewelRow;
	int Jtime;
	int JewelPauseSeconds;

	double StrechRatio;

public:
	int Round(double d);
	int GetHighlightedJewel(int oldJewel);
	int GetUnHighlightedJewel(int oldJewel);

	bool SeeIfWeMatch3();
	bool SeeIfGameIsOver();
	bool CheckAround2(int jvalue, int col1, int row1, int col2, int row2);
	bool CheckAroundSkipOne(int jvalue, int direction, int col, int row);

	void CleanDrawSquare();
	void LoadImages();
	void NewGame();
	void SeeIfWeCanMakeAPlay();
	void MoveInNewJewels();
	void DoSwap(int col, int row);
	void JSetTimer();
	void JStopTimer();
	void DrawTheScoreAndTimer(CPaintDC *dc);
	

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAppDeal();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};


