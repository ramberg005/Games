// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// RDAGamesView.cpp : implementation of the CRDAGamesView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RDAGames.h"
#endif

#include "RDAGamesDoc.h"
#include "RDAGamesView.h"
#include "MainFrm.h"
#include "TrackViews.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRDAGamesView

IMPLEMENT_DYNCREATE(CRDAGamesView, CView)

BEGIN_MESSAGE_MAP(CRDAGamesView, CView)
	//ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_XBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_QUERYOPEN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_APP_DEAL, &CRDAGamesView::OnAppDeal)
	ON_COMMAND(ID_APP_UNDO, &CRDAGamesView::OnAppUndo)
	ON_COMMAND(ID_FILE_SHOWSTATS, &CRDAGamesView::OnFileShowstats)
//	ON_COMMAND(ID_APP_EXIT, &CRDAGamesView::OnAppExit)
ON_COMMAND(ID_APP_EXIT, &CRDAGamesView::OnAppExit)
ON_WM_CREATE()
//ON_WM_UPDATEUISTATE()
ON_WM_SETFOCUS()
END_MESSAGE_MAP()

// CRDAGamesView construction/destruction

CRDAGamesView::CRDAGamesView()
{
}

CRDAGamesView::~CRDAGamesView()
{
	CTrackViews tv;
	tv.RemoveStatus(ETSOLVIEW);
}

BOOL CRDAGamesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRDAGamesView drawing

void CRDAGamesView::OnDraw(CDC* /*pDC*/)
{
	CRDAGamesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CRDAGamesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CRDAGamesView diagnostics

#ifdef _DEBUG
void CRDAGamesView::AssertValid() const
{
	CView::AssertValid();
}

void CRDAGamesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRDAGamesDoc* CRDAGamesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRDAGamesDoc)));
	return (CRDAGamesDoc*)m_pDocument;
}
#endif //_DEBUG


// CRDAGamesView message handlers


void CRDAGamesView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (m_ETSol.theDrawScreen == NULL)
	{
		TRACE("CRDAGamesView::OnPaint OnFileLoadstats\n");
		m_ETSol.OnFileLoadstats(dc);
	}
	TRACE("CRDAGamesView::OnPaint\n");
	m_ETSol.OnPaint(dc);
	// Do not call CView::OnPaint() for painting messages
}


void CRDAGamesView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_ETSol.OnSize(cx, cy);
}


void CRDAGamesView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CPaintDC dc(this);
	if (m_ETSol.OnLButtonUp(dc, point))
	{
		TRACE("CRDAGamesView::OnLButtonUp\n");
		Invalidate(false);
		SendMessage(WM_PAINT);
	}

	CView::OnLButtonUp(nFlags, point);
}


void CRDAGamesView::OnMouseMove(UINT nFlags, CPoint point)
{
	CPaintDC dc(this);
	m_ETSol.OnMouseMove(nFlags, dc, point);

	CView::OnMouseMove(nFlags, point);
}


void CRDAGamesView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_ETSol.OnLButtonDown(point))
	{
		Invalidate(false);
	}

	CView::OnLButtonDown(nFlags, point);
}


void CRDAGamesView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_ETSol.OnRButtonUp(point))
	{
		Invalidate(false);
	}

	CView::OnRButtonUp(nFlags, point);
}


void CRDAGamesView::OnXButtonUp(UINT nFlags, UINT nButton, CPoint point)
{
	if (m_ETSol.OnXButtonUp(nFlags, nButton, point))
	{
		Invalidate(false);
	}

	CView::OnXButtonUp(nFlags, nButton, point);
}


void CRDAGamesView::OnDestroy()
{
	CView::OnDestroy();

	m_ETSol.OnDestroy();
}


BOOL CRDAGamesView::OnQueryOpen()
{
	m_ETSol.OnQueryOpen();

	return CView::OnQueryOpen();
}


BOOL CRDAGamesView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true; //CView::OnEraseBkgnd(pDC);
}


void CRDAGamesView::OnAppDeal()
{
	m_ETSol.OnAppDeal();
	Invalidate(false);
	SendMessage(WM_PAINT);
}


void CRDAGamesView::OnAppUndo()
{
	m_ETSol.OnAppUndo();
	Invalidate(false);
	SendMessage(WM_PAINT);
}


void CRDAGamesView::OnFileShowstats()
{
	m_ETSol.OnFileShowstats();
	Invalidate(false);
	SendMessage(WM_PAINT);
}


void CRDAGamesView::OnAppExit()
{
	AfxGetMainWnd()->PostMessage(WM_CLOSE);
}


int CRDAGamesView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}



void CRDAGamesView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);
	
	CMFCRibbonBar *pRibbon;
	CMFCRibbonCategory *pRibbonCategory;

	pRibbon = ((CMainFrame*)AfxGetMainWnd())->GetRibbonBar();
	pRibbonCategory = pRibbon->GetCategory(1);
	pRibbon->SetActiveCategory(pRibbonCategory, true);

	m_ETSol.OnQueryOpen();
}
