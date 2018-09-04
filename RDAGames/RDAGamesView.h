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

// RDAGamesView.h : interface of the CRDAGamesView class
//

#pragma once
#include "ETSOL.h"

class CRDAGamesView : public CView
{
protected: // create from serialization only
	CRDAGamesView();
	DECLARE_DYNCREATE(CRDAGamesView)

// Attributes
public:
	CRDAGamesDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	CETSol m_ETSol;

// Implementation
public:
	virtual ~CRDAGamesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnXButtonUp(UINT nFlags, UINT nButton, CPoint point);
	afx_msg void OnDestroy();
	afx_msg BOOL OnQueryOpen();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAppDeal();
	afx_msg void OnAppUndo();
	afx_msg void OnFileShowstats();
//	afx_msg void OnAppExit();
	afx_msg void OnAppExit();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};

#ifndef _DEBUG  // debug version in RDAGamesView.cpp
inline CRDAGamesDoc* CRDAGamesView::GetDocument() const
   { return reinterpret_cast<CRDAGamesDoc*>(m_pDocument); }
#endif

