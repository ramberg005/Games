#pragma once


// CMyRibbonBar

class CMyRibbonBar : public CMFCRibbonBar
{
	DECLARE_DYNAMIC(CMyRibbonBar)

public:
	CMyRibbonBar();
	virtual ~CMyRibbonBar();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


