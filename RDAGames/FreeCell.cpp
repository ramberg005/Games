// FreeCell.cpp : implementation file
//

#include "stdafx.h"
#include "RDAGames.h"
#include "FreeCell.h"
#include <math.h>
#include "MainFrm.h"
#include "TrackViews.h"

// CFreeCell

IMPLEMENT_DYNCREATE(CFreeCell, CView)

CFreeCell::CFreeCell()
{
	pDeck = new CFCDeck;
	pDeck->CleanDeck();
	pDeck->Shuffle();
	pDeck->Deal();
	pCards = new CardImages;
	pCards->init();
	m_bDragging = false;
	CleanUnDo();
	CleanWhereToPaint();
	PaintAll = true;
	MovedOffAce = false;
			
	LeftOffset = -1;
	RightOffset = -1;
	TopOffset = -1;
	BottomOffset = -1;
}

CFreeCell::~CFreeCell()
{
	CTrackViews tv;
	tv.RemoveStatus(FREECELLVIEW);
}

BEGIN_MESSAGE_MAP(CFreeCell, CView)
//	ON_COMMAND(ID_FREECELL_NEW_BUTTON, &CFreeCell::OnFreecellNewButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_XBUTTONUP()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_APP_DEAL, &CFreeCell::OnAppDeal)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_UNDO_ALL_BUTTON, &CFreeCell::OnUndoAllButton)
	ON_WM_QUERYOPEN()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// CFreeCell drawing

void CFreeCell::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	//PaintAll = true;
	//Invalidate();
	//DoThePaint();
	// TODO: add draw code here
}


// CFreeCell diagnostics

#ifdef _DEBUG
void CFreeCell::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CFreeCell::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

void CFreeCell::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACE("CChildView::OnMouseMove\n");
	CRect rcClient;

	// if the left mouse button is down
	if (MK_LBUTTON & nFlags)
	{
		if(!m_bDragging)
		{
			LeftOffset = -1;
			RightOffset = -1;
			TopOffset = -1;
			BottomOffset = -1;

			if (FCSeeIfWeAreDragingCards(point))
			{
				GetClientRect(rcClient);
				if (FCDragingRect.PtInRect(point) )
				{
					m_bDragging = TRUE;
					if(GetCapture() != this)
					{
						SetCapture();
					}

					CDC cMemDC;
					CBitmap bmpMemDrag, *pcBmpOldMemDrag, *pcBmpOldBack;
					CDC* pcDC = GetDC();	


					cMemDC.CreateCompatibleDC(pcDC);
					bmpMemDrag.CreateCompatibleBitmap(pcDC, FCDragingRect.Width(), FCDragingRect.Height());
				
				
					pcBmpOldMemDrag = cMemDC.SelectObject(&bmpMemDrag);
					pcBmpOldBack = 	pcDC->SelectObject(&m_FCBackBmp);	
				
					FCStackLocation.x = FCDragingRect.left;
					FCStackLocation.y = FCDragingRect.top;

					FCoffset = point - FCStackLocation;
					cMemDC.BitBlt(0, 0, FCDragingRect.Width(), FCDragingRect.Height(), pcDC, FCStackLocation.x, FCStackLocation.y, SRCCOPY);
				
					cMemDC.SelectObject(&pcBmpOldMemDrag);
					cMemDC.DeleteDC();
					pcDC->SelectObject(pcBmpOldBack);
					ReleaseDC(pcDC);
					
					m_FCDragImageList.Create(FCDragingRect.Width(), FCDragingRect.Height(), ILC_COLOR32 | ILC_MASK, 1, 1);
					m_FCDragImageList.Add(&bmpMemDrag, RGB(255,255,255));

					CRect wRect;
					GetWindowRect(wRect);
					m_FCDragImageList.BeginDrag(0, CPoint(wRect.left,wRect.top) + CPoint(FCoffset.cx, FCoffset.cy)); //CPoint(offset.cx, offset.cy) );
					POINT ptDest = point;
					ClientToScreen(&ptDest);
					CImageList::DragEnter(this, ptDest);
				
				}
			}
		}
		else
		{
			POINT ptDest = point;
			ClientToScreen(&ptDest);
			CImageList::DragMove(ptDest);			
		}
	}

	CView::OnMouseMove(nFlags, point);
}

void CFreeCell::CleanCardsDraggingAround()
{
	for (int i = 0; i < CARDSINSUITE; i++)
	{
		CardsDraggingAround[i] = -1;
	}
}

bool CFreeCell::FCSeeIfWeAreDragingCards(CPoint point)
{
	int i, j,k, CardsCanPlay,LastCard, EmptyWorkAreaSpots, EmptyPlayAreaSpots, MaxCardThatCanMove ,MovingToEmptyPlayArea;
	CRect testRect;

	EmptyWorkAreaSpots = 0;
	EmptyPlayAreaSpots = 0;
	for (i = 0; i < PLAYAREACOLUMNS; i++)
	{
		if (pDeck->PlayArea[i][0] == -1)
		{
			EmptyPlayAreaSpots++;
		}
	}
	// see if mouse is in work area
	for (i = 0; i < WORKAREACOLUMNS; i++)
	{
		if (pDeck->WorkLocation[i][0] == -1)
		{
			EmptyWorkAreaSpots++;
		} 
		if ((pDeck->WorkLocationRect[i].PtInRect(point)) && (pDeck->WorkLocation[i][0] != -1))
		{
			FCDragingRect = pDeck->WorkLocationRect[i];
			CleanCardsDraggingAround();
			CardsDraggingAround[0] = pDeck->WorkLocation[i][0];
			CardsDraggedFromLocation = pDeck->WorkLocation[i];
			// have to do the undo setup before we do the drop
			FCUndoArray[iUndoArrayLocation].FromCardLocation = 0;
			FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
			FCUndoArray[iUndoArrayLocation].FromLocation = FCWORKAREA;
			PaintWorkArea[i] = true;
			
			LeftOffset = FCDragingRect.left - point.x;
			RightOffset = FCDragingRect.right - point.x;
			TopOffset = FCDragingRect.top - point.y;
			BottomOffset = FCDragingRect.bottom - point.y;

			return true;
		}
	}

	// now do the Aces
	for (i = 0; i < WORKAREACOLUMNS; i++)
	{
		if ((pDeck->ACESRect[i].PtInRect(point)) && (pDeck->ACES[i][0] != -1))
		{
			FCDragingRect = pDeck->ACESRect[i];
			CleanCardsDraggingAround();
			CardsDraggingAround[0] = pDeck->ACES[i][GetLastRow(pDeck->ACES[i])];
			CardsDraggedFromLocation = pDeck->ACES[i];
			// have to do the undo setup before we do the drop 
			FCUndoArray[iUndoArrayLocation].FromCardLocation = GetLastRow(pDeck->ACES[i]);
			FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
			FCUndoArray[iUndoArrayLocation].FromLocation = FCACESAREA;
			PaintAcesArea[i] = true;
			
			LeftOffset = FCDragingRect.left - point.x;
			RightOffset = FCDragingRect.right - point.x;
			TopOffset = FCDragingRect.top - point.y;
			BottomOffset = FCDragingRect.bottom - point.y;

			return true;
		}
	}

	// now do the PlayArea
	for (i=0; i< PLAYAREACOLUMNS; i++)
	{
		LastCard = GetLastRow(pDeck->PlayArea[i]);
		// if true then only the bottom card is selected
		if (pDeck->PlayAreaRect[i][LastCard].PtInRect(point)  && (pDeck->PlayArea[i][LastCard] != -1))
		{
			FCDragingRect = pDeck->PlayAreaRect[i][LastCard];
			CleanCardsDraggingAround();
			CardsDraggingAround[0] = pDeck->PlayArea[i][LastCard];
			CardsDraggedFromLocation = pDeck->PlayArea[i];
			// have to do the undo setup before we do the drop
			FCUndoArray[iUndoArrayLocation].FromCardLocation = LastCard;
			FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
			FCUndoArray[iUndoArrayLocation].FromLocation = FCPLAYAREA;
			PaintPlayArea[i] = true;
			
			LeftOffset = FCDragingRect.left - point.x;
			RightOffset = FCDragingRect.right - point.x;
			TopOffset = FCDragingRect.top - point.y;
			BottomOffset = FCDragingRect.bottom - point.y;

			return true;
		}

		// now walk up the column and see if we can play
		CardsCanPlay = HowManyCardsCanPlay(pDeck->PlayArea[i]);
		j = CardsCanPlay;
		k = LastCard;
		testRect = pDeck->PlayAreaRect[i][k];
		while (j > 0)
		{
			j--;
			k--;
			testRect.top = pDeck->PlayAreaRect[i][k].top;
			if (testRect.PtInRect(point))
			{
				if (EmptyWorkAreaSpots == 0)
				{
					MaxCardThatCanMove = EmptyPlayAreaSpots * 2;
				}
				else
				{
					MovingToEmptyPlayArea = 0;
					if (pDeck->PlayArea[i][0] == -1)
					{
						// then we are moving to a empty play area;
						MovingToEmptyPlayArea = 1;
					}
					switch (EmptyPlayAreaSpots)
					{
					case 0:
						MaxCardThatCanMove = EmptyWorkAreaSpots + 1;
						break;
					default:
						MaxCardThatCanMove = (EmptyWorkAreaSpots + 1) + ((EmptyPlayAreaSpots - MovingToEmptyPlayArea) * EmptyWorkAreaSpots) + ((EmptyPlayAreaSpots - MovingToEmptyPlayArea) * 1);
						break;
					}
				}
				FCDragingRect = testRect;
				CleanCardsDraggingAround();
				// have to do the undo setup before we do the drop 
				FCUndoArray[iUndoArrayLocation].FromCardLocation = LastCard - (CardsCanPlay - j);
				FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
				FCUndoArray[iUndoArrayLocation].FromLocation = FCPLAYAREA;
				PaintPlayArea[i] = true;
				CardsCanPlay = CardsCanPlay - j;
				j = 0;
				while ((CardsCanPlay >= 0) && (MaxCardThatCanMove > CardsCanPlay))
				{
					CardsDraggingAround[j] = pDeck->PlayArea[i][LastCard - CardsCanPlay];
					CardsCanPlay--;
					j++;
				}
				CardsDraggedFromLocation = pDeck->PlayArea[i];
			
				LeftOffset = FCDragingRect.left - point.x;
				RightOffset = FCDragingRect.right - point.x;
				TopOffset = FCDragingRect.top - point.y;
				BottomOffset = FCDragingRect.bottom - point.y;

				return true;
			}
		}
	}

	return false;
}

//bool CFreeCell::FCSeeIfWeAreDragingCards(CPoint point)
//{
//	int HorzLoc;
//	int VerticalLoc;
//	int VerticalLocBottom;
//	int i, j, CardsCanPlay,LastCard, EmptyWorkAreaSpots, EmptyPlayAreaSpots, MaxCardThatCanMove ,MovingToEmptyPlayArea;
//	CRect testRect;
//
//	EmptyWorkAreaSpots = 0;
//	EmptyPlayAreaSpots = 0;
//	for (i = 0; i < PLAYAREACOLUMNS; i++)
//	{
//		if (pDeck->PlayArea[i][0] == -1)
//		{
//			EmptyPlayAreaSpots++;
//		}
//	}
//	HorzLoc = HorzGapSmall;
//	VerticalLoc = VerticalGapSmall;
//	// see if mouse is in work area
//	for (i = 0; i < WORKAREACOLUMNS; i++)
//	{
//		if (pDeck->WorkLocation[i][0] == -1)
//		{
//			EmptyWorkAreaSpots++;
//		} 
//		testRect.left = HorzLoc;
//		testRect.top = VerticalLoc;
//		testRect.bottom = VerticalLoc + CardHeight;
//		testRect.right = HorzLoc + CardWidth;
//		if ((testRect.PtInRect(point)) && (pDeck->WorkLocation[i][0] != -1))
//		{
//			FCDragingRect = testRect;
//			CleanCardsDraggingAround();
//			CardsDraggingAround[0] = pDeck->WorkLocation[i][0];
//			CardsDraggedFromLocation = pDeck->WorkLocation[i];
//			// have to do the undo setup before we do the drop
//			FCUndoArray[iUndoArrayLocation].FromCardLocation = 0;
//			FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
//			FCUndoArray[iUndoArrayLocation].FromLocation = FCWORKAREA;
//			PaintWorkArea[i] = true;
//			return true;
//		}
//		HorzLoc += (HorzGapSmall + CardWidth);
//	}
//
//	// now do the Aces
//	HorzLoc += HorzGapLarge;
//	for (i = 0; i < WORKAREACOLUMNS; i++)
//	{
//
//		testRect.left = HorzLoc;
//		testRect.top = VerticalLoc;
//		testRect.bottom = VerticalLoc + CardHeight;
//		testRect.right = HorzLoc + CardWidth;
//		if ((testRect.PtInRect(point)) && (pDeck->ACES[i][0] != -1))
//		{
//			FCDragingRect = testRect;
//			CleanCardsDraggingAround();
//			CardsDraggingAround[0] = pDeck->ACES[i][GetLastRow(pDeck->ACES[i])];
//			CardsDraggedFromLocation = pDeck->ACES[i];
//			// have to do the undo setup before we do the drop 
//			FCUndoArray[iUndoArrayLocation].FromCardLocation = GetLastRow(pDeck->ACES[i]);
//			FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
//			FCUndoArray[iUndoArrayLocation].FromLocation = FCACESAREA;
//			PaintAcesArea[i] = true;
//			return true;
//		}
//		HorzLoc += (HorzGapSmall + CardWidth);
//	}
//
//	// now do the PlayArea
//	HorzLoc = HorzGapSmall;
//
//	for (i=0; i< PLAYAREACOLUMNS; i++)
//	{
//		LastCard = GetLastRow(pDeck->PlayArea[i]);
//		// VertialLoc = (Top of Row) + (number of gaps)
//		VerticalLoc = (VerticalGapSmall + VerticalGapSmall + CardHeight) + (LastCard * VerticalGapLarge);
//		VerticalLocBottom = VerticalLoc + CardHeight;
//
//		testRect.left = HorzLoc;
//		testRect.top = VerticalLoc;
//		testRect.bottom = ScreenBottom;
//		testRect.right = HorzLoc + CardWidth;
//
//		// if true then only the bottom card is selected
//		if (testRect.PtInRect(point))
//		{
//			FCDragingRect = testRect;
//			if (VerticalLocBottom < ScreenBottom)
//			{
//				FCDragingRect.bottom = VerticalLocBottom;
//			}
//			CleanCardsDraggingAround();
//			CardsDraggingAround[0] = pDeck->PlayArea[i][LastCard];
//			CardsDraggedFromLocation = pDeck->PlayArea[i];
//			// have to do the undo setup before we do the drop
//			FCUndoArray[iUndoArrayLocation].FromCardLocation = LastCard;
//			FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
//			FCUndoArray[iUndoArrayLocation].FromLocation = FCPLAYAREA;
//			PaintPlayArea[i] = true;
//			return true;
//		}
//
//		// now walk up the column and see if we can play
//		CardsCanPlay = HowManyCardsCanPlay(pDeck->PlayArea[i]);
//		j = CardsCanPlay;
//		while (j > 0)
//		{
//			j--;
//			VerticalLoc -= VerticalGapLarge;
//			testRect.top = VerticalLoc;
//			if (testRect.PtInRect(point))
//			{
//				if (EmptyWorkAreaSpots == 0)
//				{
//					MaxCardThatCanMove = EmptyPlayAreaSpots * 2;
//				}
//				else
//				{
//					MovingToEmptyPlayArea = 0;
//					if (pDeck->PlayArea[i][0] == -1)
//					{
//						// then we are moving to a empty play area;
//						MovingToEmptyPlayArea = 1;
//					}
//					switch (EmptyPlayAreaSpots)
//					{
//					case 0:
//						MaxCardThatCanMove = EmptyWorkAreaSpots + 1;
//						break;
//					default:
//						MaxCardThatCanMove = (EmptyWorkAreaSpots + 1) + ((EmptyPlayAreaSpots - MovingToEmptyPlayArea) * EmptyWorkAreaSpots) + ((EmptyPlayAreaSpots - MovingToEmptyPlayArea) * 1);
//						break;
//					}
//				}
//				FCDragingRect = testRect;
//				if (VerticalLocBottom < ScreenBottom)
//				{
//					FCDragingRect.bottom = VerticalLocBottom;
//				}
//
//				CleanCardsDraggingAround();
//				// have to do the undo setup before we do the drop 
//				FCUndoArray[iUndoArrayLocation].FromCardLocation = LastCard - (CardsCanPlay - j);
//				FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
//				FCUndoArray[iUndoArrayLocation].FromLocation = FCPLAYAREA;
//				PaintPlayArea[i] = true;
//				CardsCanPlay = CardsCanPlay - j;
//				j = 0;
//				while ((CardsCanPlay >= 0) && (MaxCardThatCanMove > CardsCanPlay))
//				{
//					CardsDraggingAround[j] = pDeck->PlayArea[i][LastCard - CardsCanPlay];
//					CardsCanPlay--;
//					j++;
//				}
//				CardsDraggedFromLocation = pDeck->PlayArea[i];
//				return true;
//			}
//		}
//		HorzLoc += (HorzGapSmall + CardWidth);
//	}
//
//	return false;
//}


int CFreeCell::HowManyCardsCanPlay(int *arry)
{
	int LastCard;
	int lc;
	bool b = true;
	LastCard = GetLastRow(arry);
	lc = LastCard;
	while ((lc > 0) && b)
	{
		if((pCards->iaCanCardPlay[arry[lc - 1]][0] == arry[lc]) || (pCards->iaCanCardPlay[arry[lc - 1]][1] == arry[lc]))
		{
			lc--;
		}
		else
		{
			b = false;
		}
	}
	return LastCard - lc;
}

void CFreeCell::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);
}

void CFreeCell::OnLButtonUp(UINT nFlags, CPoint point)
{
	TRACE("CFreeCell::OnLButtonUp\n");
	bool SomethingChanged = false;
	::ReleaseCapture();
	if (m_bDragging)
	{
		CImageList::DragLeave(this);	
		CImageList::EndDrag();
		m_FCDragImageList.DeleteImageList();
	}

	SomethingChanged = DoTheDrop(point);
	CleanCardsDraggingAround();

	m_bDragging = false;
	if (SomethingChanged)
	{
		if (!MovedOffAce)
		{
			PlayAllCards();
		}
		MovedOffAce = false;
		Invalidate(false);
	}

	CView::OnLButtonUp(nFlags, point);
}

bool CFreeCell::DoTheDrop(CPoint point)
{
	int i, j, LastCardDragAround, LastCard, EmptyWorkAreaSpots, EmptyPlayAreaSpots, MaxCardThatCanMove,MaxCardThatCanMoveToEmptyPlayArea;
	CRect testRect;
	CPoint TopLeft;
	CPoint TopRight;
	CPoint BottomLeft;
	CPoint BottomRight;

	TopLeft.x = point.x + LeftOffset;
	TopLeft.y = point.y + TopOffset;
		
	TopRight.x = point.x + RightOffset;
	TopRight.y = point.y + TopOffset;
		
	BottomLeft.x = point.x + LeftOffset;
	BottomLeft.y = point.y + BottomOffset;
		
	BottomRight.x = point.x + RightOffset;
	BottomRight.y = point.y + BottomOffset;

	// see if mouse is in work area
	EmptyWorkAreaSpots = 0;
	for (i = 0; i < WORKAREACOLUMNS; i++)
	{
		if (pDeck->WorkLocation[i][0] == -1)
		{
			EmptyWorkAreaSpots++;
		}
		if ((pDeck->WorkLocationRect[i].PtInRect(TopLeft) || pDeck->WorkLocationRect[i].PtInRect(TopRight) || pDeck->WorkLocationRect[i].PtInRect(BottomLeft) || pDeck->WorkLocationRect[i].PtInRect(BottomRight)) && (pDeck->WorkLocation[i][0] == -1))
		{
			if (CardsDraggingAround[1] == -1)
			{
				pDeck->WorkLocation[i][0] = CardsDraggingAround[0];
			// have to do the undo setup before we do the drop don't know card location for play area
				FCUndoArray[iUndoArrayLocation].ToCardLocation = 0;
				FCUndoArray[iUndoArrayLocation].ToColumnLocation = i;
				FCUndoArray[iUndoArrayLocation].ToLocation = FCWORKAREA;
				PaintWorkArea[i] = true;
				FCUndoArray[iUndoArrayLocation].MoveID = iMoveID;
				if (FCUndoArray[iUndoArrayLocation].FromLocation == FCACESAREA)
				{
					MovedOffAce = true;
				}
				iUndoArrayLocation++;
				iMoveID++;
				CleanFromLocation();
				CleanCardsDraggingAround();
				return true;
			}
			else 
			{
				return false;
			}
		}
	}

	// now do the Aces
	for (i = 0; i < WORKAREACOLUMNS; i++)
	{
		if (pDeck->ACESRect[i].PtInRect(TopLeft) || pDeck->ACESRect[i].PtInRect(TopRight) || pDeck->ACESRect[i].PtInRect(BottomLeft) || pDeck->ACESRect[i].PtInRect(BottomRight))
		{
			LastCard = GetLastRow(pDeck->ACES[i]);
			
			if ((CardsDraggingAround[0] - 1) == pDeck->ACES[i][LastCard])
			{
				pDeck->ACES[i][LastCard + 1] = CardsDraggingAround[0];
				FCUndoArray[iUndoArrayLocation].ToCardLocation = LastCard + 1;
				FCUndoArray[iUndoArrayLocation].ToColumnLocation = i;
				FCUndoArray[iUndoArrayLocation].ToLocation = FCACESAREA;
				PaintAcesArea[i] = true;
				FCUndoArray[iUndoArrayLocation].MoveID = iMoveID;
				iUndoArrayLocation++;
				iMoveID++;
				CleanFromLocation();
				CleanCardsDraggingAround();
				return true;
			}
			else 
			{
				return false;
			}
		}
	}

	// now do the PlayArea RDAHERE
	EmptyPlayAreaSpots = 0;
	for (i = 0; i < PLAYAREACOLUMNS; i++)
	{
		if (pDeck->PlayArea[i][0] == -1)
		{
			EmptyPlayAreaSpots++;
		}
	}

	MaxCardThatCanMove = (EmptyPlayAreaSpots + 1) *(EmptyWorkAreaSpots + 1);
	MaxCardThatCanMoveToEmptyPlayArea =(EmptyPlayAreaSpots) *(EmptyWorkAreaSpots + 1);
	if ((EmptyPlayAreaSpots == 0) && (EmptyWorkAreaSpots == 0))
	{
		MaxCardThatCanMove = 1;
		MaxCardThatCanMoveToEmptyPlayArea = 1;
	}
	else
	{
		if (EmptyPlayAreaSpots == 0)
		{
			MaxCardThatCanMoveToEmptyPlayArea = MaxCardThatCanMove;
		}
	}
	LastCardDragAround = GetLastRow(CardsDraggingAround) + 1;
	for (i = 0; i < PLAYAREACOLUMNS; i++)
	{
		// build a rect the whole size of the column

		testRect.left = pDeck->PlayAreaRect[i][0].left;
		testRect.top = pDeck->PlayAreaRect[i][0].top;
		testRect.bottom = ScreenBottom;
		testRect.right = pDeck->PlayAreaRect[i][0].right;

		LastCard = GetLastRow(pDeck->PlayArea[i]);

		if ((testRect.PtInRect(TopLeft) || testRect.PtInRect(TopRight) || testRect.PtInRect(BottomLeft) || testRect.PtInRect(BottomRight)) && ((pCards->iaCanCardPlay[pDeck->PlayArea[i][LastCard]][0] == CardsDraggingAround[0]) ||
											(pCards->iaCanCardPlay[pDeck->PlayArea[i][LastCard]][1] == CardsDraggingAround[0]) ||
											((LastCard == 0) && (pDeck->PlayArea[i][LastCard] == -1))))
		{
			j = 0;
			// see if it is too many cards to play
			if (pDeck->PlayArea[i][0] == -1)
			{
				if (LastCardDragAround > MaxCardThatCanMoveToEmptyPlayArea)
				{
					return false;
				}
			}
			else
			{
				if (LastCardDragAround > MaxCardThatCanMove)
				{
					return false;
				}
			}
			while (CardsDraggingAround[j] != -1)
			{
				if ((LastCard == 0) && (pDeck->PlayArea[i][LastCard] == -1))
				{
					; // do nothing
				}
				else
				{
					LastCard++;
				}
				FCUndoArray[iUndoArrayLocation].ToCardLocation = LastCard;
				FCUndoArray[iUndoArrayLocation].ToColumnLocation = i;
				FCUndoArray[iUndoArrayLocation].ToLocation = FCPLAYAREA;
				PaintPlayArea[i] = true;
				FCUndoArray[iUndoArrayLocation].MoveID = iMoveID;
				if (FCUndoArray[iUndoArrayLocation].FromLocation == FCACESAREA)
				{
					MovedOffAce = true;
				}
				iUndoArrayLocation++;

				FCUndoArray[iUndoArrayLocation].FromColumnLocation = FCUndoArray[iUndoArrayLocation - 1].FromColumnLocation;
				FCUndoArray[iUndoArrayLocation].FromCardLocation = FCUndoArray[iUndoArrayLocation - 1].FromCardLocation + 1;
				FCUndoArray[iUndoArrayLocation].FromLocation = FCUndoArray[iUndoArrayLocation - 1].FromLocation;

				pDeck->PlayArea[i][LastCard] = CardsDraggingAround[j];
				j++;
			}
			iMoveID++;
			CleanFromLocation();
			CleanCardsDraggingAround();
			FillScreenRects();
			return true;
		}
	}


	return false;
}

void CFreeCell::CleanFromLocation()
{
	// need to clean CardsDraggedFromLocation with CardsDraggingAround
	int LastCardFrom, LastCardDrag;

	LastCardFrom = GetLastRow(CardsDraggedFromLocation);
	LastCardDrag = GetLastRow(CardsDraggingAround);
	while (LastCardDrag >= 0)
	{
		if (CardsDraggedFromLocation[LastCardFrom] == CardsDraggingAround[LastCardDrag])
		{
			CardsDraggedFromLocation[LastCardFrom] = -1;
			LastCardFrom--;
			LastCardDrag --;
		}
		else
		{
			return;
		}
	}
}

bool CFreeCell::PlayAllCards()
{
	int aces[WORKAREACOLUMNS]; // contains the last card location for each ace
	int playarea[PLAYAREACOLUMNS]; // contains the las card location for each column
	int i, j;
	bool foundAmove = true;
	bool somethingchanged = false;


	while (foundAmove)
	{
		foundAmove = false;
		for (i = 0; i < WORKAREACOLUMNS; i++)
		{
			aces[i] = GetLastRow(pDeck->ACES[i]);
		}
		for (i = 0; i < PLAYAREACOLUMNS; i++)
		{
			playarea[i] = GetLastRow(pDeck->PlayArea[i]);
		}
		// check work area
		for(i=0; i < WORKAREACOLUMNS; i++)
		{
			for(j=0; j < WORKAREACOLUMNS; j++)
			{
				// make sure the last card is not a king
				if ((pDeck->ACES[j][aces[j]] != KINGOFHEARTS) && 
					(pDeck->ACES[j][aces[j]] != KINGOFCLUBS) && 
					(pDeck->ACES[j][aces[j]] != KINGOFDIAMONDS) && 
					(pDeck->ACES[j][aces[j]] != KINGOFSPADES))
				{
					if ((aces[j] == 0) && (pDeck->ACES[j][aces[j]] == -1))
					{
						// then we can only play an ace
						if ((pDeck->WorkLocation[i][0] == ACEOFSPADES) ||
							(pDeck->WorkLocation[i][0] == ACEOFDIAMONDS) ||
							(pDeck->WorkLocation[i][0] == ACEOFCLUBS) ||
							(pDeck->WorkLocation[i][0] == ACEOFHEARTS))
						{
							pDeck->ACES[j][aces[j]] = pDeck->WorkLocation[i][0];
							pDeck->WorkLocation[i][0] = -1;

							FCUndoArray[iUndoArrayLocation].FromCardLocation = 0;
							FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
							FCUndoArray[iUndoArrayLocation].FromLocation = FCWORKAREA;
							PaintWorkArea[i] = true;
							FCUndoArray[iUndoArrayLocation].ToCardLocation = aces[j];
							FCUndoArray[iUndoArrayLocation].ToColumnLocation = j;
							FCUndoArray[iUndoArrayLocation].ToLocation = FCACESAREA;
							PaintAcesArea[j] = true;
							FCUndoArray[iUndoArrayLocation].MoveID = iMoveID;
							iUndoArrayLocation++;
							
							somethingchanged = true;
							aces[j] += 1;
							foundAmove = true;
						}
					}
					else
					{
						if (pDeck->ACES[j][aces[j]] == (pDeck->WorkLocation[i][0] - 1))
						{
							aces[j] += 1;
							pDeck->ACES[j][aces[j]] = pDeck->WorkLocation[i][0];
							pDeck->WorkLocation[i][0] = -1;

							FCUndoArray[iUndoArrayLocation].FromCardLocation = 0;
							FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
							FCUndoArray[iUndoArrayLocation].FromLocation = FCWORKAREA;
							PaintWorkArea[i] = true;
							FCUndoArray[iUndoArrayLocation].ToCardLocation = aces[j];
							FCUndoArray[iUndoArrayLocation].ToColumnLocation = j;
							FCUndoArray[iUndoArrayLocation].ToLocation = FCACESAREA;
							PaintAcesArea[j] = true;
							FCUndoArray[iUndoArrayLocation].MoveID = iMoveID;
							iUndoArrayLocation++;
							
							foundAmove = true;
							somethingchanged = true;
						}
					}
				}
			}
		}
		// check play area
		for(i=0; i < PLAYAREACOLUMNS; i++)
		{
			for(j=0; j < WORKAREACOLUMNS; j++)
			{
				// make sure the last card is not a king
				if ((pDeck->ACES[j][aces[j]] != KINGOFHEARTS) && 
					(pDeck->ACES[j][aces[j]] != KINGOFCLUBS) && 
					(pDeck->ACES[j][aces[j]] != KINGOFDIAMONDS) && 
					(pDeck->ACES[j][aces[j]] != KINGOFSPADES))
				{
					
					if ((aces[j] == 0) && (pDeck->ACES[j][aces[j]] == -1))
					{
						// then we can only play an ace
						if ((pDeck->PlayArea[i][playarea[i]] == ACEOFSPADES) ||
							(pDeck->PlayArea[i][playarea[i]] == ACEOFDIAMONDS) ||
							(pDeck->PlayArea[i][playarea[i]] == ACEOFCLUBS) ||
							(pDeck->PlayArea[i][playarea[i]] == ACEOFHEARTS))
						{
							pDeck->ACES[j][aces[j]] = pDeck->PlayArea[i][playarea[i]];
							pDeck->PlayArea[i][playarea[i]] = -1;

							FCUndoArray[iUndoArrayLocation].FromCardLocation = playarea[i];
							FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
							FCUndoArray[iUndoArrayLocation].FromLocation = FCPLAYAREA;
							PaintPlayArea[i] = true;
							FCUndoArray[iUndoArrayLocation].ToCardLocation = aces[j];
							FCUndoArray[iUndoArrayLocation].ToColumnLocation = j;
							FCUndoArray[iUndoArrayLocation].ToLocation = FCACESAREA;
							PaintAcesArea[j] = true;
							FCUndoArray[iUndoArrayLocation].MoveID = iMoveID;
							iUndoArrayLocation++;
							
							playarea[i] -= 1;
							aces[j] += 1;
							foundAmove = true;
							somethingchanged = true;
						}
						//else
						//{
						//	if (pDeck->ACES[j][aces[j]] == (pDeck->PlayArea[i][playarea[i]] -1))
						//	{
						//		aces[j] += 1;
						//		pDeck->ACES[j][aces[j]] = pDeck->PlayArea[i][playarea[i]];

						//		FCUndoArray[iUndoArrayLocation].FromCardLocation = playarea[i];
						//		FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
						//		FCUndoArray[iUndoArrayLocation].FromLocation = FCPLAYAREA;
						//		PaintPlayArea[i] = true;
						//		FCUndoArray[iUndoArrayLocation].ToCardLocation = aces[j];
						//		FCUndoArray[iUndoArrayLocation].ToColumnLocation = j;
						//		FCUndoArray[iUndoArrayLocation].ToLocation = FCACESAREA;
						//		PaintAcesArea[j] = true;
						//		FCUndoArray[iUndoArrayLocation].MoveID = iMoveID;
						//		iUndoArrayLocation++;
						//	
						//		pDeck->PlayArea[i][playarea[i]] = -1;
						//		playarea[i] -= 1;
						//		foundAmove = true;
						//		somethingchanged = true;
						//	}
						//}
					}
					else
					{
						if (pDeck->ACES[j][aces[j]] == (pDeck->PlayArea[i][playarea[i]] -1))
						{
							aces[j] += 1;
							pDeck->ACES[j][aces[j]] = pDeck->PlayArea[i][playarea[i]];

							FCUndoArray[iUndoArrayLocation].FromCardLocation = playarea[i];
							FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
							FCUndoArray[iUndoArrayLocation].FromLocation = FCPLAYAREA;
							PaintPlayArea[i] = true;
							FCUndoArray[iUndoArrayLocation].ToCardLocation = aces[j];
							FCUndoArray[iUndoArrayLocation].ToColumnLocation = j;
							FCUndoArray[iUndoArrayLocation].ToLocation = FCACESAREA;
							PaintAcesArea[j] = true;
							FCUndoArray[iUndoArrayLocation].MoveID = iMoveID;
							iUndoArrayLocation++;

							pDeck->PlayArea[i][playarea[i]] = -1;
							playarea[i] -= 1;
							foundAmove = true;
							somethingchanged = true;
						}
					}
				}
			}
		}
	}
	if (somethingchanged)
	{
	 iMoveID++;
	}
	return somethingchanged;
}

void CFreeCell::OnRButtonUp(UINT nFlags, CPoint point)
{
	// Play any cards on the ace deck
	if (PlayAllCards())
	{
		Invalidate(false);
	}

	CView::OnRButtonUp(nFlags, point);
}

int CFreeCell::GetLastRow(int *arry)
{
	int i = 0;
	while(arry[i] != -1)
	{
		i++;
	}
	if (i > 0)
	{
		i--;
	}
	return i;
}

void CFreeCell::OnXButtonUp(UINT nFlags, UINT nButton, CPoint point)
{
	DoAnUnDo();
	Invalidate(false);

	CView::OnXButtonUp(nFlags, nButton, point);
}

bool CFreeCell::DoAnUnDo()
{
	int mID;
	int toValue;
	bool somethingchanged = false;
	bool change;

	if (iUndoArrayLocation == 0)
	{
		return somethingchanged;
	}
	iUndoArrayLocation--;
	mID = FCUndoArray[iUndoArrayLocation].MoveID;

	while ((mID == FCUndoArray[iUndoArrayLocation].MoveID) && (iUndoArrayLocation >= 0))
	{
		change = false;
		if (FCUndoArray[iUndoArrayLocation].ToLocation == FCPLAYAREA)
		{
			toValue = pDeck->PlayArea[FCUndoArray[iUndoArrayLocation].ToColumnLocation][FCUndoArray[iUndoArrayLocation].ToCardLocation];
			pDeck->PlayArea[FCUndoArray[iUndoArrayLocation].ToColumnLocation][FCUndoArray[iUndoArrayLocation].ToCardLocation] = -1;
			PaintPlayArea[FCUndoArray[iUndoArrayLocation].ToColumnLocation] = true;
			somethingchanged = true;
			change = true;
		}
		if (FCUndoArray[iUndoArrayLocation].ToLocation == FCWORKAREA)
		{
			toValue = pDeck->WorkLocation[FCUndoArray[iUndoArrayLocation].ToColumnLocation][FCUndoArray[iUndoArrayLocation].ToCardLocation];
			pDeck->WorkLocation[FCUndoArray[iUndoArrayLocation].ToColumnLocation][FCUndoArray[iUndoArrayLocation].ToCardLocation] = -1;
			PaintWorkArea[FCUndoArray[iUndoArrayLocation].ToColumnLocation] = true;
			somethingchanged = true;
			change = true;
		}
		if (FCUndoArray[iUndoArrayLocation].ToLocation == FCACESAREA)
		{
			toValue = pDeck->ACES[FCUndoArray[iUndoArrayLocation].ToColumnLocation][FCUndoArray[iUndoArrayLocation].ToCardLocation];
			pDeck->ACES[FCUndoArray[iUndoArrayLocation].ToColumnLocation][FCUndoArray[iUndoArrayLocation].ToCardLocation] = -1;
			PaintAcesArea[FCUndoArray[iUndoArrayLocation].ToColumnLocation] = true;
			somethingchanged = true;
			change = true;
		}


		if (FCUndoArray[iUndoArrayLocation].FromLocation == FCPLAYAREA)
		{
			pDeck->PlayArea[FCUndoArray[iUndoArrayLocation].FromColumnLocation][FCUndoArray[iUndoArrayLocation].FromCardLocation] = toValue;
			PaintPlayArea[FCUndoArray[iUndoArrayLocation].FromColumnLocation] = true;
			somethingchanged = true;
			change = true;
		}
		if (FCUndoArray[iUndoArrayLocation].FromLocation == FCWORKAREA)
		{
			pDeck->WorkLocation[FCUndoArray[iUndoArrayLocation].FromColumnLocation][FCUndoArray[iUndoArrayLocation].FromCardLocation] = toValue;
			PaintWorkArea[FCUndoArray[iUndoArrayLocation].FromColumnLocation] = true;
			somethingchanged = true;
			change = true;
		}
		if (FCUndoArray[iUndoArrayLocation].FromLocation == FCACESAREA)
		{
			pDeck->ACES[FCUndoArray[iUndoArrayLocation].FromColumnLocation][FCUndoArray[iUndoArrayLocation].FromCardLocation] = toValue;
			PaintAcesArea[FCUndoArray[iUndoArrayLocation].FromColumnLocation] = true;
			somethingchanged = true;
			change = true;
		}
		if (change == true)
		{
			FCUndoArray[iUndoArrayLocation].FromCardLocation = -1;
			FCUndoArray[iUndoArrayLocation].FromColumnLocation = -1;
			FCUndoArray[iUndoArrayLocation].FromLocation = -1;
			FCUndoArray[iUndoArrayLocation].MoveID = -1;
			FCUndoArray[iUndoArrayLocation].ToCardLocation = -1;
			FCUndoArray[iUndoArrayLocation].ToColumnLocation = -1;
			FCUndoArray[iUndoArrayLocation].ToLocation = -1;
		}
		iUndoArrayLocation--;
	}
	if (iUndoArrayLocation < 0)
	{
		iMoveID = 0;
		iUndoArrayLocation = 0;
	}
	else
	{
		iMoveID--;
		iUndoArrayLocation++;
	}
	return somethingchanged;
}

void CFreeCell::OnPaint()
{
	DoThePaint();
}

void CFreeCell::DoThePaint()
{
	CPaintDC dc(this); // device context for painting
	//int HorzLoc;
	//int VerticalLoc;
	int i, j,LastCard;
	CRect DeleteRect;

	
	FillScreenRects();
	// if paint everything then do the background
		// Get the location and dimensions of the control
	if (PaintAll)
	{
		GetWindowRect(&FCRectColorChanger);
		CBrush BrushETYellow(RGB(255, 255, 128));

		// Select the new brush
		pFCOldBrush = dc.SelectObject(&BrushETYellow);

		// Convert the current coordinates from Screen to Client
		ScreenToClient(&FCRectColorChanger);
		// Change the background of the control
		dc.Rectangle(FCRectColorChanger);
	}

	// draw the WorkLocation
	//HorzLoc = HorzGapSmall;
	//VerticalLoc = VerticalGapSmall;
	for (i = 0; i < WORKAREACOLUMNS; i++)
	{
		if (PaintAll || PaintWorkArea[i])
		{
			if (pDeck->WorkLocation[i][0] == -1)
			{
				//pCards->theCardImages[NOCARDSPOT].StretchBlt(dc, HorzLoc,VerticalLoc, CardWidth, CardHeight);
				pCards->theCardImages[NOCARDSPOT].StretchBlt(dc, pDeck->WorkLocationRect[i]);
			}
			else
			{
				//pCards->theCardImages[pDeck->WorkLocation[i][0]].StretchBlt(dc, HorzLoc,VerticalLoc, CardWidth, CardHeight);
				pCards->theCardImages[pDeck->WorkLocation[i][0]].StretchBlt(dc, pDeck->WorkLocationRect[i]);
			}
		}
		//HorzLoc += (HorzGapSmall + CardWidth);
	}

	// now do the Aces
	//HorzLoc += HorzGapLarge;
	for (i = 0; i < WORKAREACOLUMNS; i++)
	{
		if (PaintAll || PaintAcesArea[i])
		{
			j = 0;
			if (pDeck->ACES[i][j] == -1)
			{
				//pCards->theCardImages[NOCARDSPOT].StretchBlt(dc, HorzLoc,VerticalLoc, CardWidth, CardHeight);
				pCards->theCardImages[NOCARDSPOT].StretchBlt(dc, pDeck->ACESRect[i]);
			}
			else
			{
				//while ((pDeck->ACES[i][j+1] != -1) && ((j+1) < CARDSINSUITE))
				//{
					//j++;
				//}
				j = GetLastRow(pDeck->ACES[i]);
				//pCards->theCardImages[pDeck->ACES[i][j]].StretchBlt(dc, HorzLoc,VerticalLoc, CardWidth, CardHeight);
				pCards->theCardImages[pDeck->ACES[i][j]].StretchBlt(dc, pDeck->ACESRect[i]);
			}
		}
		//HorzLoc += (HorzGapSmall + CardWidth);
	}

	// now do the PlayArea
	//HorzLoc = HorzGapSmall;

	for (i = 0; i < PLAYAREACOLUMNS; i++)
	{
		if (PaintAll || PaintPlayArea[i])
		{
			j = 0;
			if (!PaintAll)
			{
				LastCard = GetLastRow(pDeck->PlayArea[i]);
				//DeleteRect.left = HorzLoc;
				//DeleteRect.right = HorzLoc + CardWidth;
				//DeleteRect.top = VerticalGapSmall + VerticalGapSmall + CardHeight;
				//DeleteRect.bottom = ScreenBottom;
				DeleteRect.left = pDeck->PlayAreaRect[i][j].left;
				DeleteRect.right = pDeck->PlayAreaRect[i][j].right;
				DeleteRect.top = pDeck->PlayAreaRect[i][j].top;
				DeleteRect.bottom = ScreenBottom;
				DeleteImagesInRect(&dc, DeleteRect);
			}
			//VerticalLoc = VerticalGapSmall + VerticalGapSmall + CardHeight;
			//IsColumnBelowEndOfScreen(pDeck->PlayArea[i], pDeck->PlayAreaRect[i]);
			if (pDeck->PlayArea[i][j] == -1)
			{
				//pCards->theCardImages[NOCARDSPOT].StretchBlt(dc, HorzLoc,VerticalLoc, CardWidth, CardHeight);
				pCards->theCardImages[NOCARDSPOT].StretchBlt(dc, pDeck->PlayAreaRect[i][j]);
			}
			else
			{
				do
				{
					//pCards->theCardImages[pDeck->PlayArea[i][j]].StretchBlt(dc, HorzLoc,VerticalLoc, CardWidth, CardHeight);
					pCards->theCardImages[pDeck->PlayArea[i][j]].StretchBlt(dc, pDeck->PlayAreaRect[i][j]);
					//if (ColTooTall)
					//{
					//	VerticalLoc += VerticalGapSmall;
					//}
					//else
					//{
					//	VerticalLoc += VerticalGapLarge;
					//}
					j++;
				} while (pDeck->PlayArea[i][j] != -1);
			}
		}
		//HorzLoc += (HorzGapSmall + CardWidth);
	}
	CleanWhereToPaint();
}

//void CFreeCell::IsColumnBelowEndOfScreen(int *col, CRect *mrect)
//{
//	int colLength, i;
//	int lastcard;
//	int cardscanplay;
//	int vertloc;
//	
//	colLength = VerticalGapSmall + VerticalGapSmall + CardHeight;
//	i= 0;
//	while (col[i] != -1)
//	{
//		colLength += VerticalGapLarge;
//		i++;
//	}
//
//	colLength += CardHeight;
//
//	if (ScreenBottom < colLength)
//	{	
//		lastcard = GetLastRow(col);
//		cardscanplay = HowManyCardsCanPlay(col);
//		lastcard -= cardscanplay;
//		i = 0;
//		vertloc = mrect[0].top;
//		while (col[i] != -1)
//		{
//			mrect[i].top = vertloc;
//			mrect[i].bottom = vertloc + CardHeight;
//			i++;
//			if (i >= lastcard)
//			{
//				vertloc += VerticalGapLarge;
//			}
//			else
//			{
//				vertloc += VerticalGapSmall;
//			}
//		}
//	}
//}

void CFreeCell::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	PaintAll = true;
	ScreenBottom = cy;
	ScreenRight = cx;

	CalcSize(cx, cy);
}

void CFreeCell::CalcSize(int x, int y)
{
	int FullCardWidth = pCards->theCardImages[33].GetWidth();
	int FullCardHeight = pCards->theCardImages[33].GetHeight();
	int Total;
	double WidthRatio;
	double HeightRatio;

	VerticalGapSmall = Round(FullCardHeight *.1);
	VerticalGapLarge = Round(FullCardHeight *.25);
	HorzGapSmall = Round(FullCardWidth *.1);
	HorzGapLarge = Round(FullCardWidth *.2);

	// we have 8 small gaps (10% of a card width) between the cards and one large gap (20%)
	Total = (8 * FullCardWidth) + (8 * HorzGapSmall) + HorzGapLarge;
	WidthRatio = (double)x/Total;

	// for vertical we have 2 gaps (10% of card height) One full row of full card height and up to 12 rows where cards are placed on each other
	// the gap of the cards that are face up are 13% of the card height
	Total = (2 * VerticalGapSmall) + (12 * VerticalGapLarge) + (FullCardHeight * 2);
	HeightRatio = (double)y/Total;

	if (HeightRatio > WidthRatio)
	{
		m_CardSizeModifier = WidthRatio;
	}
	else
	{
		m_CardSizeModifier = HeightRatio;
	}

	CardWidth = Round(pCards->theCardImages[33].GetWidth() * m_CardSizeModifier);
	CardHeight = Round(pCards->theCardImages[33].GetHeight() * m_CardSizeModifier);
	VerticalGapSmall = Round(CardHeight *.1);
	VerticalGapLarge = Round(CardHeight *.25);
	HorzGapSmall = Round(CardWidth *.1);
	HorzGapLarge = Round(CardWidth *.2);
	FillScreenRects();
}

void CFreeCell::FillScreenRects()
{
	int HorzLoc;
	int VerticalLoc;
	int i, j, lastcard, cardcanplay, PlayAreaWidth;
	bool largegaptoobig;
	
	PlayAreaWidth = ((CardWidth * WORKAREACOLUMNS) * 2) + HorzGapLarge;
	HorzLoc =  (int) (ScreenRight - PlayAreaWidth)/2;     //HorzGapSmall;
	VerticalLoc = VerticalGapSmall;
	for (i = 0; i < WORKAREACOLUMNS; i++)
	{
		pDeck->WorkLocationRect[i].left = HorzLoc;
		pDeck->WorkLocationRect[i].right = HorzLoc + CardWidth;
		pDeck->WorkLocationRect[i].top = VerticalLoc;
		pDeck->WorkLocationRect[i].bottom = VerticalLoc + CardHeight;
		HorzLoc += (HorzGapSmall + CardWidth);
	}

	// now do the Aces
	HorzLoc += HorzGapLarge;
	for (i = 0; i < WORKAREACOLUMNS; i++)
	{
		pDeck->ACESRect[i].left = HorzLoc;
		pDeck->ACESRect[i].right = HorzLoc + CardWidth;
		pDeck->ACESRect[i].top = VerticalLoc;
		pDeck->ACESRect[i].bottom = VerticalLoc + CardHeight;
		HorzLoc += (HorzGapSmall + CardWidth);
	}

	// now do the PlayArea
	HorzLoc = (int) (ScreenRight - PlayAreaWidth)/2;     //HorzGapSmall;

	for (i = 0; i < PLAYAREACOLUMNS; i++)
	{
		j = 0;
		VerticalLoc = VerticalGapSmall + VerticalGapSmall + CardHeight;
		do
		{
			pDeck->PlayAreaRect[i][j].left = HorzLoc;
			pDeck->PlayAreaRect[i][j].right = HorzLoc + CardWidth;
			pDeck->PlayAreaRect[i][j].top = VerticalLoc;
			pDeck->PlayAreaRect[i][j].bottom = VerticalLoc + CardHeight;

			VerticalLoc += VerticalGapLarge;
			j++;
		} while (pDeck->PlayArea[i][j] != -1);
		if (i == 3)
		{
			HorzLoc += (HorzGapSmall + HorzGapLarge + CardWidth);
		}
		else
		{
			HorzLoc += (HorzGapSmall + CardWidth);
		}
	}
	
	HorzLoc = (int) (ScreenRight - PlayAreaWidth)/2;     //HorzGapSmall;
	for (i = 0; i < PLAYAREACOLUMNS; i++)
	{
		largegaptoobig = false;
		lastcard = GetLastRow(pDeck->PlayArea[i]);
		if (ScreenBottom < pDeck->PlayAreaRect[i][lastcard].bottom)
		{
			cardcanplay = HowManyCardsCanPlay(pDeck->PlayArea[i]);
			VerticalLoc = VerticalGapSmall + VerticalGapSmall + CardHeight + (VerticalGapLarge * cardcanplay) + ((lastcard - cardcanplay) * VerticalGapSmall);
			if (ScreenBottom < VerticalLoc)
			{
				largegaptoobig = true;
			}
			VerticalLoc = VerticalGapSmall + VerticalGapSmall + CardHeight;
			for (j = 0; j <= lastcard; j++)
			{
				pDeck->PlayAreaRect[i][j].left = HorzLoc;
				pDeck->PlayAreaRect[i][j].right = HorzLoc + CardWidth;
				pDeck->PlayAreaRect[i][j].top = VerticalLoc;
				pDeck->PlayAreaRect[i][j].bottom = VerticalLoc + CardHeight;
				if ((lastcard - j) >= cardcanplay)
				{
					if (!largegaptoobig)
					{
						VerticalLoc += VerticalGapSmall;
					}
				}
				else
				{
					VerticalLoc += VerticalGapLarge;
				}
			}
		}
		if (i == 3)
		{
			HorzLoc += (HorzGapSmall + HorzGapLarge + CardWidth);
		}
		else
		{
			HorzLoc += (HorzGapSmall + CardWidth);
		}
	}
		
}

int CFreeCell::Round(double d)
{
	int i;
	// we sure there won't be a screen that is 65536 bytes wide
	i = (int)floor(d);
	if ((d - i) > .5)
	{
		i++;
	}

	return i;
}

void CFreeCell::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CFreeCell::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true; //CView::OnEraseBkgnd(pDC);
}

void CFreeCell::OnAppDeal()
{
	pDeck->CleanDeck();
	pDeck->Shuffle();
	pDeck->Deal();
	CleanUnDo();
	CleanWhereToPaint();
	PaintAll = true;
	Invalidate(false);
}

void CFreeCell::CleanUnDo()
{
	iMoveID = 0;
	iUndoArrayLocation = 0;
	for (int i = 0; i < MAXUNDOACTIONS; i++)
	{
		FCUndoArray[i].MoveID = -1;
		FCUndoArray[i].FromCardLocation = -1;
		FCUndoArray[i].FromColumnLocation = -1;
		FCUndoArray[i].FromLocation = -1;
		FCUndoArray[i].ToCardLocation = -1;
		FCUndoArray[i].ToColumnLocation = -1;
		FCUndoArray[i].ToLocation = -1;
	}
}

void CFreeCell::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int LastCard, HorzLoc, VerticalLoc, iWA, i;
	CRect testRect;

	iWA = -1;
	for (i = 0; i < WORKAREACOLUMNS; i++)
	{
		if(pDeck->WorkLocation[i][0] == -1)
		{
			iWA = i;
			break;
		}
	}
	if (iWA == -1)
	{
		return;
	}
	for (i = 0; i < PLAYAREACOLUMNS; i++)
	{
		// build a rect the whole size of the column
		//HorzLoc = HorzGapSmall + (HorzGapSmall * i) + (CardWidth * i);
		LastCard = GetLastRow(pDeck->PlayArea[i]);
		HorzLoc = pDeck->PlayAreaRect[i][LastCard].left;
		// VertialLoc = (Top of Row) + (number of gaps)
		VerticalLoc = (VerticalGapSmall + VerticalGapSmall + CardHeight) + (LastCard * VerticalGapLarge);

		testRect.left = HorzLoc;
		testRect.top = VerticalGapSmall + VerticalGapSmall + CardHeight;
		testRect.bottom = VerticalLoc + CardHeight;
		testRect.right = HorzLoc + CardWidth;

		if (testRect.PtInRect(point))
		{
			LastCard = GetLastRow(pDeck->PlayArea[i]);
			pDeck->WorkLocation[iWA][0] = pDeck->PlayArea[i][LastCard];

			FCUndoArray[iUndoArrayLocation].FromCardLocation = LastCard;
			FCUndoArray[iUndoArrayLocation].FromColumnLocation = i;
			FCUndoArray[iUndoArrayLocation].FromLocation = FCPLAYAREA;
			PaintPlayArea[i] = true;
			FCUndoArray[iUndoArrayLocation].ToCardLocation = 0;
			FCUndoArray[iUndoArrayLocation].ToColumnLocation = iWA;
			FCUndoArray[iUndoArrayLocation].ToLocation = FCWORKAREA;
			PaintWorkArea[iWA] = true;
			FCUndoArray[iUndoArrayLocation].MoveID = iMoveID;
			iUndoArrayLocation++;
			iMoveID++;
							
			 pDeck->PlayArea[i][LastCard] = -1;
			 PlayAllCards();
			 Invalidate(false);
		}
	}

	CView::OnLButtonDblClk(nFlags, point);
}

void CFreeCell::OnUndoAllButton()
{
	bool somethingchanged = false;
	while (DoAnUnDo())
	{
		somethingchanged = true;
	}
	if (somethingchanged)
	{
		Invalidate(false);
	}
}

void CFreeCell::CleanWhereToPaint()
{
	int i;
	PaintAll = false;
	for(i = 0; i < WORKAREACOLUMNS; i++)
	{
		PaintWorkArea[i] = false;
		PaintAcesArea[i] = false;
	}
	for (i = 0; i < PLAYAREACOLUMNS; i++)
	{
		PaintPlayArea[i] = false;
	}
}

void CFreeCell::DeleteImagesInRect(CDC *dc, CRect &RectToDrawBackGround)
{
	dc->FillSolidRect(RectToDrawBackGround, RGB(255, 255, 128));
}

BOOL CFreeCell::OnQueryOpen()
{
	PaintAll = true;

	return CView::OnQueryOpen();
}

void CFreeCell::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);
	CMFCRibbonBar *pRibbon;
	CMFCRibbonCategory *pRibbonCategory;

	pRibbon = ((CMainFrame*)AfxGetMainWnd())->GetRibbonBar();
	pRibbonCategory = pRibbon->GetCategory(2);
	pRibbon->SetActiveCategory(pRibbonCategory, true);

	PaintAll = true;
	Invalidate(false);
}
