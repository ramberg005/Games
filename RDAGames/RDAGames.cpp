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

// RDAGames.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "RDAGames.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "RDAGamesDoc.h"
#include "RDAGamesView.h"
#include "FreeCell.h"
#include "MineSweep.h"
#include "Jewel.h"
#include "TrackViews.h"
#include "MahjongView.h"
#include "Sudoku.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRDAGamesApp

BEGIN_MESSAGE_MAP(CRDAGamesApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CRDAGamesApp::OnAppAbout)
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
//	ON_COMMAND(ID_APP_EXIT, &CRDAGamesApp::OnAppExit)
ON_COMMAND(ID_FILE_NEW, &CRDAGamesApp::OnFileNew)
ON_COMMAND(ID_NEW_ETSOLBUTTON, &CRDAGamesApp::OnNewEtsolbutton)
ON_COMMAND(ID_FREECELL_NEW_BUTTON, &CRDAGamesApp::OnFreecellNewButton)
ON_COMMAND(ID_MINESWEEP_BUTTON, &CRDAGamesApp::OnMineSweepButton)
ON_COMMAND(ID_JEWEL_BUTTON, &CRDAGamesApp::OnJewelButton)
ON_COMMAND(ID_MAHJONGNEW_BUTTON, &CRDAGamesApp::OnMahjongnewButton)
ON_COMMAND(ID_SUDOKUNEW_BUTTON, &CRDAGamesApp::OnSudokunewButton)
END_MESSAGE_MAP()


// CRDAGamesApp construction

CRDAGamesApp::CRDAGamesApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("RDAGames.AppID.NoVersion"));
	CTrackViews tv;
	tv.TVDeleteFile();
}

// The one and only CRDAGamesApp object

CRDAGamesApp theApp;


// CRDAGamesApp initialization

BOOL CRDAGamesApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("RDAFUN"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	//afxAmbientActCtx = FALSE; // <<-- Add this line

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_RDAGamesTYPE,
		RUNTIME_CLASS(CRDAGamesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CRDAGamesView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	CMultiDocTemplate* pDocTemplate1;
	pDocTemplate1 = new CMultiDocTemplate(IDR_RDAFREECELLTYPE,
		RUNTIME_CLASS(CRDAGamesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CFreeCell));
	if (!pDocTemplate1)
		return FALSE;
	AddDocTemplate(pDocTemplate1);

	CMultiDocTemplate* pDocTemplate2;
	pDocTemplate2 = new CMultiDocTemplate(IDR_RDAMINESWEEPTYPE,
		RUNTIME_CLASS(CRDAGamesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CMineSweep));
	if (!pDocTemplate2)
		return FALSE;
	AddDocTemplate(pDocTemplate2);

	CMultiDocTemplate* pDocTemplate3;
	pDocTemplate3 = new CMultiDocTemplate(IDR_RDAJEWELTYPE,
		RUNTIME_CLASS(CRDAGamesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CJewel));
	if (!pDocTemplate3)
		return FALSE;
	AddDocTemplate(pDocTemplate3);

	CMultiDocTemplate* pDocTemplate4;
	pDocTemplate4 = new CMultiDocTemplate(IDR_RDAMAHJONGTYPE,
		RUNTIME_CLASS(CRDAGamesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CMahjongView));
	if (!pDocTemplate4)
		return FALSE;
	AddDocTemplate(pDocTemplate4);

	CMultiDocTemplate* pDocTemplate5;
	pDocTemplate5 = new CMultiDocTemplate(IDR_RDASUDOKUTYPE,
		RUNTIME_CLASS(CRDAGamesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSudoku));
	if (!pDocTemplate5)
		return FALSE;
	AddDocTemplate(pDocTemplate5);

	
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CRDAGamesApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CRDAGamesApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnAppExit();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnAppDeal();
//	afx_msg void OnFileNew();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_ERASEBKGND()
//	ON_COMMAND(ID_APP_EXIT, &CAboutDlg::OnAppExit)
//	ON_WM_TIMER()
//	ON_WM_ERASEBKGND()
//	ON_COMMAND(ID_APP_DEAL, &CAboutDlg::OnAppDeal)
//	ON_COMMAND(ID_FILE_NEW, &CAboutDlg::OnFileNew)
END_MESSAGE_MAP()

// App command to run the dialog
void CRDAGamesApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CRDAGamesApp customization load/save methods

void CRDAGamesApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CRDAGamesApp::LoadCustomState()
{
}

void CRDAGamesApp::SaveCustomState()
{
}

// CRDAGamesApp message handlers




void CRDAGamesApp::OnFileNew()
{
	//CWinAppEx::OnFileNew();

	POSITION docPos;
	CTrackViews tv;

	docPos = GetFirstDocTemplatePosition();
	CDocTemplate* pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	//pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	//pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	//pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	//pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);

	if (tv.GetStatus(ETSOLVIEW) == -1)
	{
		tv.SetStatus(ETSOLVIEW);

		ASSERT(pTemplate != NULL);
		ASSERT_KINDOF(CDocTemplate, pTemplate);

		pTemplate->OpenDocumentFile(NULL);
	}
}


void CRDAGamesApp::OnNewEtsolbutton()
{
	POSITION docPos;
	CTrackViews tv;

	docPos = GetFirstDocTemplatePosition();
	CDocTemplate* pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);

	if (tv.GetStatus(ETSOLVIEW) == -1)
	{
		tv.SetStatus(ETSOLVIEW);

		ASSERT(pTemplate != NULL);
		ASSERT_KINDOF(CDocTemplate, pTemplate);

		pTemplate->OpenDocumentFile(NULL);
	}
}


void CRDAGamesApp::OnFreecellNewButton()
{
	POSITION docPos;
	CTrackViews tv;

	docPos = GetFirstDocTemplatePosition();
	CDocTemplate* pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);

	if (tv.GetStatus(FREECELLVIEW) == -1)
	{
		tv.SetStatus(FREECELLVIEW);

		ASSERT(pTemplate != NULL);
		ASSERT_KINDOF(CDocTemplate, pTemplate);

		pTemplate->OpenDocumentFile(NULL);
	}
}


void CRDAGamesApp::OnMineSweepButton()
{
	POSITION docPos;
	CTrackViews tv;

	docPos = GetFirstDocTemplatePosition();
	CDocTemplate* pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);

	if (tv.GetStatus(MINESWEEPVIEW) == -1)
	{
		tv.SetStatus(MINESWEEPVIEW);

		ASSERT(pTemplate != NULL);
		ASSERT_KINDOF(CDocTemplate, pTemplate);

		pTemplate->OpenDocumentFile(NULL);
	}
}



void CRDAGamesApp::OnJewelButton()
{
	POSITION docPos;
	CTrackViews tv;

	docPos = GetFirstDocTemplatePosition();
	CDocTemplate* pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);

	if (tv.GetStatus(JEWELVIEW) == -1)
	{
		tv.SetStatus(JEWELVIEW);

		ASSERT(pTemplate != NULL);
		ASSERT_KINDOF(CDocTemplate, pTemplate);

		pTemplate->OpenDocumentFile(NULL);
	}
	 
}


void CRDAGamesApp::OnMahjongnewButton()
{
	POSITION docPos;
	CTrackViews tv;

	docPos = GetFirstDocTemplatePosition();
	CDocTemplate* pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);

	if (tv.GetStatus(MAHJONGVIEW) == -1)
	{
		tv.SetStatus(MAHJONGVIEW);

		ASSERT(pTemplate != NULL);
		ASSERT_KINDOF(CDocTemplate, pTemplate);

		pTemplate->OpenDocumentFile(NULL);
	}
}


void CRDAGamesApp::OnSudokunewButton()
{
POSITION docPos;
	CTrackViews tv;

	docPos = GetFirstDocTemplatePosition();
	CDocTemplate* pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);
	pTemplate = (CDocTemplate*)GetNextDocTemplate(docPos);

	if (tv.GetStatus(SUDOKUVIEW) == -1)
	{
		tv.SetStatus(SUDOKUVIEW);

		ASSERT(pTemplate != NULL);
		ASSERT_KINDOF(CDocTemplate, pTemplate);

		pTemplate->OpenDocumentFile(NULL);
	}}
