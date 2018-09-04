// MyRibbonBar.cpp : implementation file
//

#include "stdafx.h"
#include "RDAGames.h"
#include "MyRibbonBar.h"
#include "MainFrm.h"
#include "RDAGamesDoc.h"
#include "TrackViews.h"
#include "definitions.h"

// CMyRibbonBar

IMPLEMENT_DYNAMIC(CMyRibbonBar, CMFCRibbonBar)

CMyRibbonBar::CMyRibbonBar()
{

}

CMyRibbonBar::~CMyRibbonBar()
{
}


BEGIN_MESSAGE_MAP(CMyRibbonBar, CMFCRibbonBar)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMyRibbonBar message handlers




void CMyRibbonBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	CMFCRibbonCategory* pRC;
	CString CategorySelected;
	CString ViewName;
	CTrackViews tv;
	CMFCTabCtrl* pTabCtrl;
	INT_PTR pi;
	int i;

	CMainFrame * pWndMain = (CMainFrame *)AfxGetMainWnd();
	CFrameWnd* pFrame = ((CMDIFrameWnd*)pWndMain)->MDIGetActive();

	try
	{
		pi = (INT_PTR)pWndMain->GetMDITabGroups().GetCount();
	} catch (...) {
		CMFCRibbonBar::OnLButtonUp(nFlags, point);
		return;
	}

	if (pi > 0)
	{
		pTabCtrl = (CMFCTabCtrl*)pWndMain->GetMDITabGroups().GetHead();
		i = 0;
		pRC = GetActiveCategory();
		CategorySelected = pRC->GetName();

		if (CategorySelected == "ETSol")
		{
			i = tv.GetStatus(ETSOLVIEW);
			if (i != -1)
			{
				pTabCtrl->SetActiveTab(i);
			}
		}
		if (CategorySelected == "FreeCell")
		{
			i = tv.GetStatus(FREECELLVIEW);
			if (i != -1)
			{
				pTabCtrl->SetActiveTab(i);
			}
		}
		if (CategorySelected == "Mine Sweep")
		{
			i = tv.GetStatus(MINESWEEPVIEW);
			if (i != -1)
			{
				pTabCtrl->SetActiveTab(i);
			}
		}
		if (CategorySelected == "BeJeweled")
		{
			i = tv.GetStatus(JEWELVIEW);
			if (i != -1)
			{
				pTabCtrl->SetActiveTab(i);
			}
		}
		if (CategorySelected == "Mahjong")
		{
			i = tv.GetStatus(MAHJONGVIEW);
			if (i != -1)
			{
				pTabCtrl->SetActiveTab(i);
			}
		}
		if (CategorySelected == "Sudoku")
		{
			i = tv.GetStatus(SUDOKUVIEW);
			if (i != -1)
			{
				pTabCtrl->SetActiveTab(i);
			}
		}
	}
	CMFCRibbonBar::OnLButtonUp(nFlags, point);
}
