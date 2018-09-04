#pragma once



// CMineSweep view

class CMineSweep : public CView
{
	DECLARE_DYNCREATE(CMineSweep)

protected:
	CMineSweep();           // protected constructor used by dynamic creation
	virtual ~CMineSweep();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	bool paintAll;
	int aGame[MSCOLUMNS][MSROWS];
	int aGameStatus[MSCOLUMNS][MSROWS];
	int PaintArray[MSCOLUMNS][MSROWS];
	CImage aImages[15];
	int xSize;
	int ySize;
	double iStrechFactor;
	int LineThickness;
	int defaultImageWidth;
	int defaultImageHeight;
	bool lbuttondown;
	bool rbuttondown;
	bool HitABomb;
	int MSline;
	int MSwidth;
	int MSheight;
	int BombCount;
	CRect ScoreRect;
	CRect EightRect;
	CRect SevenRect;
	bool GameOver;
	bool Eight;
	bool Seven;


public:
	void NewGame();
	void CleanGame();
	void LoadImages();
	int Round(double d);
	void UnCoverAroundBlanks(int column, int row);
	void RightAndLeftMouseButtonDown(CPoint point);
	int GetMarkedCount(int column, int row);
	void UnCoverUnMarked(int column, int row);
	void CleanPaintArray();
	void ShowPressedDownCovers(int column, int row);
	void DrawTheBombCount(CDC *dc);
	void SeeIfGameIsOver();
	void DoThePaint(CDC* pDC);

private:
	CRect FCRectColorChanger;
	CBrush *pFCOldBrush;


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnAppDeal();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
//	afx_msg void OnIconEraseBkgnd(CDC* pDC);
//	afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
};


