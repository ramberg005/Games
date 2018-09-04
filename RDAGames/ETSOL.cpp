#include "stdafx.h"
#include "ETSOL.h"

CETSol::CETSol()
{
	TRACE("CETSol::CETSol\n");
	theDrawScreen = NULL;
	m_bDragging = false;
	pOldBrush = NULL;
	pFont = NULL;
}

CETSol::~CETSol()
{
	if (theDrawScreen != NULL)
	{
		delete theDrawScreen;
	}
}

void CETSol::DrawScore(CPaintDC *dc)
{
	if (theDrawScreen->Paint_All == true || theDrawScreen->Paint_Score == true)
	{
		if (theDrawScreen->Paint_All != true)
		{
			// delete the old images first
			theDrawScreen->DeleteImagesInRect(dc, theDrawScreen->ScoreLocation);
		}
		int s;
		//char score[128];
		CString score;
		score.Format("%i",theDrawScreen->TheCurrentScore);

		//s = (theDrawScreen->TheCurrentScore<0)?(theDrawScreen->TheCurrentScore*-1):(theDrawScreen->TheCurrentScore);
		//_itoa_s(s,score,128,10);

		int iFontSize = 80;
		if (strlen(score) > 5)
		{
			iFontSize = 60;
		}
		LogFont.lfWeight = 0; //(int)(iFontSize * theDrawScreen->CardStretchSize);
		LogFont.lfStrikeOut = 0;
		LogFont.lfUnderline = 0;
		LogFont.lfHeight = (int)(iFontSize * theDrawScreen->CardStretchSize);  // sets font size
		LogFont.lfEscapement = 0;
		LogFont.lfItalic = FALSE;
		LogFont.lfWidth = 0;
		strcpy_s(LogFont.lfFaceName, "Arial");

		SizeFont.CreateFontIndirect(&LogFont);	
		pFont = dc->SelectObject(&SizeFont);

		if (theDrawScreen->TheCurrentScore < 0)
		{
			// red font
			dc->SetTextColor(RGB(255, 0, 0));
		}
		else
		{
			dc->SetTextColor(RGB(0, 0, 0));
		}
		dc->SetBkColor(RGB(255, 255, 128));
		dc->SetBkMode(OPAQUE);
		s = dc->DrawText(score,theDrawScreen->ScoreLocation, DT_NOCLIP | DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		dc->SelectObject(pFont);
		SizeFont.DeleteObject();
	}
}

void CETSol::OnPaint(CPaintDC &dc) 
{
	TRACE("CETSol::OnPaint\n");
	//CPaintDC dc(this); // device context for painting
	if (theDrawScreen->Paint_All == true)
	{
		// Get the location and dimensions of the control
		CWnd *My_this;
		My_this = dc.GetWindow();
		My_this->GetWindowRect(&RectColorChanger);
		CBrush BrushETYellow(RGB(255, 255, 128));

		// Select the new brush
		pOldBrush = dc.SelectObject(&BrushETYellow);

		// Convert the current coordinates from Screen to Client
		My_this->ScreenToClient(&RectColorChanger);
		// Change the background of the control
		dc.Rectangle(RectColorChanger);
		
		// Restore the old brush
		//dc.SelectObject(pOldBrush);
	}
	DrawScore(&dc);
	theDrawScreen->DrawTheScreen(&dc);
	theDrawScreen->InitPaintValues();

}

void CETSol::OnSize(int cx, int cy)
{
	TRACE("CETSol::OnSize\n");

	if (theDrawScreen != NULL)
	{
		theDrawScreen->ScreenWidth = cx;
		theDrawScreen->ScreenHeight = cy;
		theDrawScreen->Paint_All = true;

			if (cx > 0)
		{
			theDrawScreen->SizeTheCards();
		}
	}
}

bool CETSol::OnLButtonUp(CPaintDC &dc, CPoint point)
{
	TRACE("CETSol::OnLButtonUp\n");
	bool SomethingChanged = false;
	int ColumnID;
	CWnd * My_this;
	My_this = dc.GetWindow();
	
	::ReleaseCapture();
	if (m_bDragging)
	{
		CImageList::DragLeave(My_this);	
		CImageList::EndDrag();
		m_cDragImageList.DeleteImageList();		
	}

	ColumnID = theDrawScreen->SetupRowColumnInformation(point);
	if (m_bDragging)
	{
		SomethingChanged = theDrawScreen->DropDragAroundStack(point);
	}
	else if (ColumnID == UNPLAYEDFACEDOWNCARDSCOLUMNID)
	{
		SomethingChanged = theDrawScreen->NextThreeCards();
		if (SomethingChanged == true)
		{
			theDrawScreen->Paint_UNPLAYEDFACEDOWNCARDSCOLUMNID = true;
			theDrawScreen->Paint_UNPLAYEDFACEUPCARDSCOLUMNID = true;
		}
	}
	else if (ColumnID == LONGHORNCOLUMNID)
	{
		theDrawScreen->TheCurrentScore += 100;
		theDrawScreen->Paint_Score = true;
		SomethingChanged = true;
	}

	m_bDragging = false;
	theDrawScreen->theDragStack->InitDragStack();
	if (theDrawScreen->DoubleSpaceCard.ColumnID != -1 && theDrawScreen->DoubleSpaceCard.RowID != -1)
	{
		theDrawScreen->SetPaintBasedOnColumnID(theDrawScreen->DoubleSpaceCard.ColumnID);
		SomethingChanged = true;
	}
	theDrawScreen->DoubleSpaceCard.ColumnID = -1;
	theDrawScreen->DoubleSpaceCard.RowID = -1;
	if (SomethingChanged)
	{
		TRACE("CETSol::OnLButtonUp SomethingChanged\n");
		return true;
	}
	return false;
}

void CETSol::OnMouseMove(UINT nFlags, CPaintDC &dc, CPoint point)
{
	//TRACE("CETSol::OnMouseMove\n");
	CRect rcClient;
	CWnd * my_this;
	LPRECT lpRect;
	RECT myRect;
	lpRect = &myRect;
	my_this = dc.GetWindow();
	//CRect DragingRect;

	// if the left mouse button is down
	if (MK_LBUTTON & nFlags)
	{
		if(!m_bDragging)
		{
			theDrawScreen->SeeIfWeAreDragingCards(point);
			theDrawScreen->DragingRect = theDrawScreen->GetDragImageRectangle(point);
			//my_this->GetClientRect(&myRect);
			GetClientRect(my_this->m_hWnd, &myRect);
			rcClient.top = lpRect->top;
			rcClient.bottom = lpRect->bottom;
			rcClient.left = lpRect->left;
			rcClient.right = lpRect->right;
			if (theDrawScreen->DragingRect.PtInRect(point) )
			{
				m_bDragging = TRUE;
				if(GetCapture() != my_this->m_hWnd)
				{
					SetCapture(my_this->m_hWnd);
				}

				CDC cMemDC;
				CBitmap bmpMemDrag, *pcBmpOldMemDrag, *pcBmpOldBack;
				CDC *pcDC = my_this->GetDC();


				cMemDC.CreateCompatibleDC(pcDC);
				bmpMemDrag.CreateCompatibleBitmap(pcDC, theDrawScreen->DragingRect.Width(), theDrawScreen->DragingRect.Height());
				
				
				pcBmpOldMemDrag = cMemDC.SelectObject(&bmpMemDrag);
				pcBmpOldBack = 	pcDC->SelectObject(&m_cBackBmp);	
				
				theDrawScreen->offset = point - theDrawScreen->theDragStack->StackLocation;
				cMemDC.BitBlt(0, 0, theDrawScreen->DragingRect.Width(), theDrawScreen->DragingRect.Height(), pcDC, theDrawScreen->theDragStack->StackLocation.x, theDrawScreen->theDragStack->StackLocation.y, SRCCOPY);
				
				cMemDC.SelectObject(&pcBmpOldMemDrag);
				cMemDC.DeleteDC();
				pcDC->SelectObject(pcBmpOldBack);
				my_this->ReleaseDC(pcDC);
					
				m_cDragImageList.Create(theDrawScreen->DragingRect.Width(), theDrawScreen->DragingRect.Height(), ILC_COLOR32 | ILC_MASK, 1, 1);
				m_cDragImageList.Add(&bmpMemDrag, RGB(255,255,255));

				CRect wRect;
				//GetWindowRect(my_this->m_hWnd, wRect);
				GetWindowRect(my_this->m_hWnd, &myRect);
				m_cDragImageList.BeginDrag(0, CPoint(myRect.left,myRect.top) + CPoint(theDrawScreen->offset.cx, theDrawScreen->offset.cy)); //CPoint(offset.cx, offset.cy) );
				//m_cDragImageList.BeginDrag(0, CPoint(wRect.left,wRect.top) + CPoint(theDrawScreen->offset.cx, theDrawScreen->offset.cy)); //CPoint(offset.cx, offset.cy) );
				POINT ptDest = point;
				ClientToScreen(my_this->m_hWnd, &ptDest);
				CImageList::DragEnter(my_this, ptDest);
				
			}
		}
		else
		{
			if (m_bDragging)
			{
				POINT ptDest = point;
				my_this->ClientToScreen(&ptDest);
				CImageList::DragMove(ptDest);			
			}
		}
	}
}

void CETSol::OnAppDeal()
{
	TRACE("CETSol::OnAppDeal\n");
	theDrawScreen->theDragStack->InitDragStack();
	theDrawScreen->theDeck->Deal();
	theDrawScreen->theUndoStack->InitUndoStack();
	theDrawScreen->DealInit();
	theDrawScreen->Paint_All = true;
	theDrawScreen->BaseScore -= 52;
	theDrawScreen->GamesPlayed++;

	//Invalidate(false);
}

bool CETSol::OnLButtonDown(CPoint point)
{
	TRACE("CETSol::OnLButtonDown\n");
	if (theDrawScreen->SetupDoubleSpaceView(point))
	{
		theDrawScreen->SetPaintBasedOnColumnID(theDrawScreen->DoubleSpaceCard.ColumnID);
		return true;
	}
	return false;
}

bool CETSol::OnRButtonUp(CPoint point)
{
	TRACE("CETSol::OnRButtonUp\n");
	if (theDrawScreen->PlayWhatYouCanOnRightButtonClick())
	{
		return true;
	}
	return false;
}

bool CETSol::OnXButtonUp(UINT nFlags, UINT nButton, CPoint point)
{
	TRACE("CETSol::OnXButtonUp\n");
	bool DoInvalidate = false;
	//if (nButton == 1)
	//{
		// do an undo
		DoInvalidate = theDrawScreen->DoAnUnDo();
	//}
	//else
	//{
	//	// do a deal
	//	theDrawScreen->theDragStack->InitDragStack();
	//	theDrawScreen->theDeck->Deal();
	//	theDrawScreen->theUndoStack->InitUndoStack();
	//	theDrawScreen->DealInit();
	//	DoInvalidate = true;
	//}
	if (DoInvalidate)
	{
		return true;
	}
	return false;
}

void CETSol::OnAppUndo()
{
	TRACE("CETSol::OnAppUndo\n");
	if (theDrawScreen->DoAnUnDo())
	{
		//Invalidate(false);
	}
}

void CETSol::OnFileLoadstats(CPaintDC &dc)
{
	TRACE("CETSol::OnFileLoadstats\n");
	if (theDrawScreen == NULL)
	{
		// frist time we need to setup our screen info then deal
		CRect rect;
		RECT myrect;
		HWND hWnd;
		hWnd = dc.GetWindow()->m_hWnd;
		GetClientRect(hWnd, &myrect);
		rect = myrect;

		theDrawScreen = new CDrawScreen();
		theDrawScreen->ScreenWidth = rect.Width();
		theDrawScreen->ScreenHeight = rect.Height();
		theDrawScreen->SizeTheCards();
		theDrawScreen->DealInit();

		if (theDrawScreen->LoadData() == true)
		{
			//Invalidate(false);
		}
		theDrawScreen->Paint_All = true;
	}
}

void CETSol::OnDestroy()
{
	TRACE("CETSol::OnDestroy\n");

	theDrawScreen->SaveData();
}

void CETSol::OnFileShowstats()
{
	//TRACE("CETSol::OnFileShowstats\n");
	//ETSolStats StatsDlg;
	//StatsDlg.BaseScore = theDrawScreen->BaseScore;
	//StatsDlg.GamesWon = theDrawScreen->GamesWon;
	//StatsDlg.GamesPlayed = theDrawScreen->GamesPlayed;

	//StatsDlg.DoModal();
	return;

}

void CETSol::OnHelpDebugdump()
{
	// debug the undo
	theDrawScreen->DumpUndo();
}

void CETSol::OnQueryOpen()
{
	if (theDrawScreen != NULL)
	{
		theDrawScreen->Paint_All = true;
	}
}
