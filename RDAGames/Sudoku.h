#pragma once

#define NOTHIGHLIGHTED	0
#define HIGHILIGHTED	1
#define ROWHIGHLIHTED	2

struct GameDetails 
{
	int CellValue;
	int Highlighted;
	bool DoPaint;
	CRect CellRect;
};

struct UndoDetails
{
	int row;
	int col;
	int oldval;
	int newval;
};

struct RegionCells
{
	int row;
	int column;
};

struct Region
{
	RegionCells Rcells[3][3];
};

// CSudoku view

class CSudoku : public CView
{
	DECLARE_DYNCREATE(CSudoku)

protected:
	CSudoku();           // protected constructor used by dynamic creation
	virtual ~CSudoku();

public:
	

private:
	CRect SRectColorChanger;
	CRect KeyPad[10];
	CRect KeyPadArea;
	CRect PlayLevelRects[3];
	CRect PlayLevelArea;
	CRect PlayArea;

	CBrush *pSOldBrush;
	CFont *pSFont;
	bool PaintAll;
	bool PaintLevels;
	bool PlayAreaSelected;
	bool PaintKeyPad;
	bool IsKeyHighlighted[10];
	bool GameOver;
	bool one, two, three, four, five, six, seven, eight, nine;


	int ScreenBottom;
	int ScreenRight;
	int margin;
	int playrect;
	int thickline;
	int inner_playrect;
	int inner_thickline;
	int PlayLevel;
	int SelectedRow;
	int SelectedCol;
	int PreviousSelectedRow;
	int PreviousSelectedCol;
	int KeySelected;
	int UndoLocation;

	GameDetails SgameDetails[9][9];
	UndoDetails Undo[1024];
	Region Regions[3][3];
	
	CImage numbers[10];
	CImage ynumbers[10];
	CImage znumbers[10];
	CImage PlayLevels[6];
	

public:
	void Init();
	void CalcSize(int x, int y);
	void DrawRect(CPaintDC *dc, GameDetails &GD);
	void LoadImages();
	void UpdatePlayArea();
	void HighlightLikeNumber(int key);
	void SeeIfGameIsWon();
	void SeeIfAllNumberIsPlayed();
	void SetBools(int val);
	void ClearBools();
	void SetupRegions();
	void OldDeal();
	void AddNumberToRegionAndValidate(int RRow, int RCol);
	void IfEasyHighlightRowAndColumn(int RRow, int RCol);
	void ClearEasyHighlightedRowAndColumn();
	
	
	int b[9][9],r[60][2];
	int row, col, icount, mode;
	void generate(int choice);
	int isfixed(int count, int m, int n);
	int checkrow(int m, int n);
	int checkcolumn(int m, int n);
	int check(int m,int n);
	int solve();
	int checkmat(int m, int n);


	bool ClickOnPlayLevel(CPoint point);
	bool ClickOnPlayArea(CPoint point);
	bool ClickOnKeyPad(CPoint point);
	bool ValidateRow(int rownum);
	bool ValidateColumn(int colnum);
	bool ValidateRegion (int RegionRow, int RegionColumn);

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAppDeal();
	afx_msg void OnUndoAllButton();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSudokunewButton();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnXButtonUp(UINT nFlags, UINT nButton, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};


