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

// RDAGames.h : main header file for the RDAGames application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRDAGamesApp:
// See RDAGames.cpp for the implementation of this class
//

class CRDAGamesApp : public CWinAppEx
{
public:
	CRDAGamesApp();

public:

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
//	afx_msg void OnAppExit();
	afx_msg void OnFileNew();
	afx_msg void OnNewEtsolbutton();
	afx_msg void OnFreecellNewButton();
	afx_msg void OnMineSweepButton();
	afx_msg void OnJewelButton();
	afx_msg void OnMahjongnewButton();
	afx_msg void OnSudokunewButton();
};

extern CRDAGamesApp theApp;
