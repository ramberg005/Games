#include "stdafx.h"

#include <math.h>
#include "DrawScreen.h"


CDrawScreen::CDrawScreen()
{
	theDragStack = new CDragStack;
	theCards = new CardImages;
	theDeck = new Cdeck;
	theUndoStack = new CUNDO;
	BaseScore = 0;
	GamesWon = 0;
	GamesPlayed = 0;

	InitPaintValues();
	init();
}

CDrawScreen::~CDrawScreen()
{
	delete theDragStack;
	delete theCards;
	delete theDeck;
	delete theUndoStack;
}
// Init the column locations
void CDrawScreen::init()
{
	CardStretchSize = -1.0;
	TimeThroughDeck = -1;
	ScreenWidth = -1;
	ScreenHeight = -1;
	GapBetweenGameCols = -1;
	GapBetweenTopandBottomRow = -1;
	GapOfFaceDownCardsUnderOtherCard = -1;
	GapOfFaceUpCardsUnderOtherCard = -1;
	OneHeight = -1;
	OneWidth = -1;
	DefaultCardWidth = -1;
	DefaultCardHeight = -1;
	SideGapOfUnplayedFaceUpCards = -1;
	TheCurrentScore = 0;

	StretchedGapBetweenGameCols = -1;
	StretchedGapBetweenTopandBottomRow = -1;
	StretchedGapOfFaceDownCardsUnderOtherCard = -1;
	StretchedGapOfFaceUpCardsUnderOtherCard = -1;
	StretchedSideGapOfUnplayedFaceUpCards = -1;
	UnPlayedFaceUpCardsDisplayCount = 0;

	UnplayedFaceUpCardsShowing = -1;
	DoubleSpaceCard.ColumnID = -1;
	DoubleSpaceCard.RowID = -1;

	// Row Column information
	SourceColumnID = -1;
	DestinationColumnID = -1;
	AceColumn1Location = -1;
	AceColumn1CardID = -1;
	AceColumn2Location = -1;
	AceColumn2CardID = -1;
	AceColumn3Location = -1;
	AceColumn3CardID = -1;
	AceColumn4Location = -1;
	AceColumn4CardID = -1;

	theCards->init();
	theDragStack->InitDragStack();
	theDeck->Deal();
	theUndoStack->InitUndoStack();
	SetDefaultCardSize();
}

// The workhorse to display what is going on
void CDrawScreen::DrawTheScreen(CPaintDC *dc)
{
	int CardID;
	CRect rect;

	if (Paint_UNPLAYEDFACEDOWNCARDSCOLUMNID == true || Paint_All == true)
	{
		if (theDeck->unplayedfacedowncards[0].card != -1)
		{
			CardID = CARDBACK;
		}
		else
		{
			if (TimeThroughDeck >= MAXTIMETHROUGHDECK)
			{
				CardID = ENDOFGAME;
			}
			else
			{
				CardID = NOCARDSPOT;
			}
		}
		DeleteImagesInRect(dc, unplayedfacedowncardsLocation);
		theCards->theCardImages[CardID].TransparentBlt(*dc, unplayedfacedowncardsLocation.left,unplayedfacedowncardsLocation.top,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
	}

	if (Paint_UNPLAYEDFACEUPCARDSCOLUMNID == true || Paint_All == true)
	{
		// setup the rect to the default location so we can draw the cards correctly
		unplayedfaceupcardsLocation.left = StretchedGapBetweenGameCols + StretchCardWidth + StretchedGapBetweenGameCols;
		unplayedfaceupcardsLocation.top = StretchedGapBetweenTopandBottomRow;
		unplayedfaceupcardsLocation.right = StretchedGapBetweenGameCols + StretchCardWidth + StretchedGapBetweenGameCols + StretchCardWidth;
		unplayedfaceupcardsLocation.bottom = StretchedGapBetweenTopandBottomRow + StretchCardHeight;
		// delete the old images first
		rect.left = unplayedfaceupcardsLocation.left;
		rect.right = unplayedfaceupcardsLocation.left + (2*StretchedSideGapOfUnplayedFaceUpCards) + StretchCardWidth;
		rect.top = unplayedfaceupcardsLocation.top;
		rect.bottom = unplayedfaceupcardsLocation.top + StretchCardHeight;
		DeleteImagesInRect(dc, rect);
		// Cards that have been flipped over
		if (theDeck->unplayedfaceupcards[0].card != -1)
		{
			CardID = GetLastLocation(theDeck->unplayedfaceupcards, CARDMAX);

			if (UnplayedFaceUpCardsShowing > 2)
			{
				theCards->theCardImages[theDeck->unplayedfaceupcards[CardID - 2].card].TransparentBlt(*dc, unplayedfaceupcardsLocation.left,unplayedfaceupcardsLocation.top,StretchCardWidth,StretchCardHeight, COLORTOBETRANSPARENT);
				theCards->theCardImages[theDeck->unplayedfaceupcards[CardID - 1].card].TransparentBlt(*dc, unplayedfaceupcardsLocation.left + StretchedSideGapOfUnplayedFaceUpCards,unplayedfaceupcardsLocation.top,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
				theCards->theCardImages[theDeck->unplayedfaceupcards[CardID].card].TransparentBlt(*dc, unplayedfaceupcardsLocation.left + (2*StretchedSideGapOfUnplayedFaceUpCards),unplayedfaceupcardsLocation.top,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
				// move the rect to the last card so that we can determine if the mouse is on the correct card
				unplayedfaceupcardsLocation.left += (StretchedSideGapOfUnplayedFaceUpCards + StretchedSideGapOfUnplayedFaceUpCards);
				unplayedfaceupcardsLocation.right += (StretchedSideGapOfUnplayedFaceUpCards + StretchedSideGapOfUnplayedFaceUpCards);

			}
			else if (UnplayedFaceUpCardsShowing > 1)
			{
				theCards->theCardImages[theDeck->unplayedfaceupcards[CardID - 1].card].TransparentBlt(*dc, unplayedfaceupcardsLocation.left,unplayedfaceupcardsLocation.top,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
				theCards->theCardImages[theDeck->unplayedfaceupcards[CardID].card].TransparentBlt(*dc, unplayedfaceupcardsLocation.left + StretchedSideGapOfUnplayedFaceUpCards,unplayedfaceupcardsLocation.top,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
				// move the rect to the last card so that we can determine if the mouse is on the correct card
				unplayedfaceupcardsLocation.left += StretchedSideGapOfUnplayedFaceUpCards;
				unplayedfaceupcardsLocation.right += StretchedSideGapOfUnplayedFaceUpCards;
			}
			else
			{
				theCards->theCardImages[theDeck->unplayedfaceupcards[CardID].card].TransparentBlt(*dc, unplayedfaceupcardsLocation.left,unplayedfaceupcardsLocation.top,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
			}
		}
		else
		{
			theCards->theCardImages[NOCARDSPOT].TransparentBlt(*dc, unplayedfaceupcardsLocation.left,unplayedfaceupcardsLocation.top,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
		}
	}

	if (Paint_LONGHORNCOLUMNID == true || Paint_All == true)
	{
		// draw the longhorn
		theCards->theCardImages[LONGHORN].TransparentBlt(*dc, LonghornLocation.left,LonghornLocation.top,Round(theCards->theCardImages[LONGHORN].GetWidth() * CardStretchSize),Round(theCards->theCardImages[LONGHORN].GetHeight() * CardStretchSize),COLORTOBETRANSPARENT);
	}

	if (Paint_ACECOLONECARDSCOLUMNID == true || Paint_All == true)
	{
		// draw the ace stacks
		CardID = NOCARDSPOT;
		if (theDeck->acecolonecards[0].card != -1)
		{
			CardID = GetLastLocation(theDeck->acecolonecards, CARDSINSUITE);
			CardID = theDeck->acecolonecards[CardID].card;
		}
		DeleteImagesInRect(dc, acecolonecardsLocation);
		theCards->theCardImages[CardID].TransparentBlt(*dc, acecolonecardsLocation.left,acecolonecardsLocation.top,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
	}
	if (Paint_ACECOLTWOCARDSCOLUMNID == true || Paint_All == true)
	{
		CardID = NOCARDSPOT;
		if (theDeck->acecoltwocards[0].card != -1)
		{
			CardID = GetLastLocation(theDeck->acecoltwocards, CARDSINSUITE);
			CardID = theDeck->acecoltwocards[CardID].card;
		}
		DeleteImagesInRect(dc, acecoltwocardsLocation);
		theCards->theCardImages[CardID].TransparentBlt(*dc, acecoltwocardsLocation.left,acecoltwocardsLocation.top,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
	}
	if (Paint_ACECOLTHREECARDSCOLUMNID == true || Paint_All == true)
	{
		CardID = NOCARDSPOT;
		if (theDeck->acecolthreecards[0].card != -1)
		{
			CardID = GetLastLocation(theDeck->acecolthreecards, CARDSINSUITE);
			CardID = theDeck->acecolthreecards[CardID].card;
		}
		DeleteImagesInRect(dc, acecolthreecardsLocation);
		theCards->theCardImages[CardID].TransparentBlt(*dc, acecolthreecardsLocation.left,acecolthreecardsLocation.top,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
	}
	if (Paint_ACECOLFOURCARDSCOLUMNID == true || Paint_All == true)
	{
		CardID = NOCARDSPOT;
		if (theDeck->acecolfourcards[0].card != -1)
		{
			CardID = GetLastLocation(theDeck->acecolfourcards, CARDSINSUITE);
			CardID = theDeck->acecolfourcards[CardID].card;
		}
		DeleteImagesInRect(dc, acecolfourcardsLocation);
		theCards->theCardImages[CardID].TransparentBlt(*dc, acecolfourcardsLocation.left,acecolfourcardsLocation.top,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
	}

	if (Paint_GAMECOLONECOLUMNID == true || Paint_All == true)
	{
		// delete the old images first
		rect.left = gamecoloneLocation.left;
		rect.right = gamecoloneLocation.left + StretchCardWidth;
		rect.top = gamecoloneLocation.top;
		rect.bottom = ScreenHeight;
		DeleteImagesInRect(dc, rect);
		DrawGameColumn(dc, theDeck->gamecolone, gamecoloneLocation.left, gamecoloneLocation.top, GAMECOLONECOLUMNID);
	}
	if (Paint_GAMECOLTWOCOLUMNID == true || Paint_All == true)
	{
		// delete the old images first
		rect.left = gamecoltwoLocation.left;
		rect.right = gamecoltwoLocation.left + StretchCardWidth;
		rect.top = gamecoltwoLocation.top;
		rect.bottom = ScreenHeight;
		DeleteImagesInRect(dc, rect);
		DrawGameColumn(dc, theDeck->gamecoltwo, gamecoltwoLocation.left, gamecoltwoLocation.top, GAMECOLTWOCOLUMNID);
	}
	if (Paint_GAMECOLTHREECOLUMNID == true || Paint_All == true)
	{
		// delete the old images first
		rect.left = gamecolthreeLocation.left;
		rect.right = gamecolthreeLocation.left + StretchCardWidth;
		rect.top = gamecolthreeLocation.top;
		rect.bottom = ScreenHeight;
		DeleteImagesInRect(dc, rect);
		DrawGameColumn(dc, theDeck->gamecolthree, gamecolthreeLocation.left, gamecolthreeLocation.top, GAMECOLTHREECOLUMNID);
	}
	if (Paint_GAMECOLFOURCOLUMNID == true || Paint_All == true)
	{
		// delete the old images first
		rect.left = gamecolfourLocation.left;
		rect.right = gamecolfourLocation.left + StretchCardWidth;
		rect.top = gamecolfourLocation.top;
		rect.bottom = ScreenHeight;
		DeleteImagesInRect(dc, rect);
		DrawGameColumn(dc, theDeck->gamecolfour, gamecolfourLocation.left, gamecolfourLocation.top, GAMECOLFOURCOLUMNID);
	}
	if (Paint_GAMECOLFIVECOLUMNID == true || Paint_All == true)
	{
		// delete the old images first
		rect.left = gamecolfiveLocation.left;
		rect.right = gamecolfiveLocation.left + StretchCardWidth;
		rect.top = gamecolfiveLocation.top;
		rect.bottom = ScreenHeight;
		DeleteImagesInRect(dc, rect);
		DrawGameColumn(dc, theDeck->gamecolfive, gamecolfiveLocation.left, gamecolfiveLocation.top, GAMECOLFIVECOLUMNID);
	}
	if (Paint_GAMECOLSIXCOLUMNID == true || Paint_All == true)
	{
		// delete the old images first
		rect.left = gamecolsixLocation.left;
		rect.right = gamecolsixLocation.left + StretchCardWidth;
		rect.top = gamecolsixLocation.top;
		rect.bottom = ScreenHeight;
		DeleteImagesInRect(dc, rect);
		DrawGameColumn(dc, theDeck->gamecolsix, gamecolsixLocation.left, gamecolsixLocation.top, GAMECOLSIXCOLUMNID);
	}
	if (Paint_GAMECOLSEVENCOLUMNID == true || Paint_All == true)
	{
		// delete the old images first
		rect.left = gamecolsevenLocation.left;
		rect.right = gamecolsevenLocation.left + StretchCardWidth;
		rect.top = gamecolsevenLocation.top;
		rect.bottom = ScreenHeight;
		DeleteImagesInRect(dc, rect);
		DrawGameColumn(dc, theDeck->gamecolseven, gamecolsevenLocation.left, gamecolsevenLocation.top, GAMECOLSEVENCOLUMNID);
	}
}


// sees if we have exceeded our screen hieght and if so return where we need to start displaying cards again
int CDrawScreen::SeeIfGameColumnExceedsScreenHeight(CARDS *gamerow, int y, int maxcolrows, int ColumnBeingDrawn)
{
	int lastrow;
	int i;
	bool doublespace;

	lastrow = GetLastLocation(gamerow, maxcolrows);
	if (ColumnBeingDrawn == DoubleSpaceCard.ColumnID)
	{
		doublespace = true;
	}
	else
	{
		doublespace = false;
	}

	for (i = 0; i <= lastrow; i++)
	{
		if (gamerow[i].faceup == true)
		{
			if (doublespace && (i == DoubleSpaceCard.RowID))
			{
				y += StretchedGapOfFaceUpCardsUnderOtherCard * 2;
			}
			y += StretchedGapOfFaceUpCardsUnderOtherCard;
		}
		else
		{
			y += StretchedGapOfFaceDownCardsUnderOtherCard;
		}
	}
	y += StretchCardHeight;
	// if we've exceeded screen height then return playable cards
	if (y > ScreenHeight)
	{
		for (i = lastrow - 1; i > 0; i--)
		{
			if (!((theCards->iaCanCardPlay[gamerow[i-1].card][0] == gamerow[i].card) || (theCards->iaCanCardPlay[gamerow[i-1].card][1] == gamerow[i].card)))
			{
				return i - 1;
			}
		}
	}
	return -1;
}

// draws the seven columns on the bottom row
void CDrawScreen::DrawGameColumn(CPaintDC *dc, CARDS *gamerow, int x, int y, int ColumnBeingDrawn)
{
	int i;
	int cardid;
	bool faceup;
	bool doublespace;
	int ExceedHeight;
	bool doExceedOnce = true;

	ExceedHeight = SeeIfGameColumnExceedsScreenHeight(gamerow,  y,  GAMEROWMAX,  ColumnBeingDrawn);

	faceup = false;
	if (ColumnBeingDrawn == DoubleSpaceCard.ColumnID)
	{
		doublespace = true;
	}
	else
	{
		doublespace = false;
	}

	if(gamerow[0].card == -1)
	{
		theCards->theCardImages[NOCARDSPOT].TransparentBlt(*dc, x,y,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
		return;
	}

	for (i = 0; i < GAMEROWMAX; i++)
	{
		if (gamerow[i].card == -1)
		{
			return;
		}
		cardid = CARDBACK;
		if (gamerow[i].faceup == true)
		{
			cardid = gamerow[i].card;
			//if (cardid > 52)
			//{
			//	cardid = 13;
			//}
		}
		theCards->theCardImages[cardid].TransparentBlt(*dc, x,y,StretchCardWidth,StretchCardHeight,COLORTOBETRANSPARENT);
		if ((ExceedHeight == -1) || (doublespace == true))
		{
			if (gamerow[i].faceup == true)
			{
				if (doublespace && (i == DoubleSpaceCard.RowID))
				{
					y += StretchedGapOfFaceUpCardsUnderOtherCard * 2;
				}
				y += StretchedGapOfFaceUpCardsUnderOtherCard;
			}
			else
			{
				y += StretchedGapOfFaceDownCardsUnderOtherCard;
			}
		}
		if ((ExceedHeight != -1) && (cardid == CARDBACK))
		{
			if ((doExceedOnce) && (doublespace == false))
			{
				doExceedOnce = false;
				y += StretchedGapOfFaceDownCardsUnderOtherCard;
			}
		}
		if (ExceedHeight == i)
		{
			ExceedHeight = -1;
		}
	}
}

// Gets the location in an array
int CDrawScreen::GetLastLocation(CARDS *iarray, int maxarraysize)
{
	int i;
	for (i = 0; i < maxarraysize; i++)
	{
		if (iarray[i].card == -1)
		{
			i--;
			return i;
		}
	}
	return maxarraysize - 1;
}

// sets the cards size info when we start the game
void CDrawScreen::SetDefaultCardSize()
{
	// got to define what our baseline height and width needed to display cards then use that to calculate CardStretchSize

	DefaultCardWidth = theCards->theCardImages[CARDBACK].GetWidth();
	DefaultCardHeight = theCards->theCardImages[CARDBACK].GetHeight();

	// gap of face down cards is 7.5 of height
	GapOfFaceDownCardsUnderOtherCard = int(DefaultCardHeight *.075);
	// gap of face up cards is 13% of height
	GapOfFaceUpCardsUnderOtherCard = int(DefaultCardHeight *.13);
	// gap between columns is 23% of the width
	GapBetweenGameCols = int(DefaultCardWidth * .23);
	// gap between the two top rows is 15% of cardheight
	GapBetweenTopandBottomRow = int(DefaultCardHeight * .15);
	// gap to show cards that have been turned face up
	SideGapOfUnplayedFaceUpCards = int(DefaultCardWidth * .15);

	OneHeight = GapBetweenTopandBottomRow + DefaultCardHeight + GapBetweenTopandBottomRow + (GapOfFaceDownCardsUnderOtherCard * 6) + (GapOfFaceUpCardsUnderOtherCard * 12) + DefaultCardHeight;
	OneWidth = (GapBetweenGameCols * 8) + (DefaultCardWidth * 7);
	// for Etauta
	//OneWidth = (GapBetweenGameCols * 10) + (DefaultCardWidth * 7);
}

// when the screen changes size we need to stretch the cards this sets up how much we need to stretch
void CDrawScreen::SizeTheCards()
{
	CardStretchSize = (double)ScreenWidth / OneWidth;
	//if (CardStretchSize > (double)ScreenHeight / OneHeight)
	//{
	//	CardStretchSize = (double)ScreenHeight / OneHeight;
	//}
	StretchedGapBetweenGameCols = Round(GapBetweenGameCols * CardStretchSize);
	StretchedGapBetweenTopandBottomRow = Round(GapBetweenTopandBottomRow * CardStretchSize);
	StretchedGapOfFaceDownCardsUnderOtherCard = Round(GapOfFaceDownCardsUnderOtherCard * CardStretchSize);
	StretchedGapOfFaceUpCardsUnderOtherCard = Round(GapOfFaceUpCardsUnderOtherCard * CardStretchSize);
	StretchedSideGapOfUnplayedFaceUpCards = Round(SideGapOfUnplayedFaceUpCards * CardStretchSize);

	SetCardLocationInformation();

	//debug
	//theDragStack.TopLeftCornerX = ScreenWidth/2;
	//theDragStack.TopLeftCornerY = ScreenHeight/2;
	//theDragStack.CardsInStack[0] = 25;
}

// simple rounding tool
int CDrawScreen::Round(double d)
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

// sets the location where the cards need to be on the screen
void CDrawScreen::SetCardLocationInformation()
{

	StretchCardWidth = Round(DefaultCardWidth*CardStretchSize);
	StretchCardHeight = Round(DefaultCardHeight*CardStretchSize);

	unplayedfacedowncardsLocation.left = StretchedGapBetweenGameCols;
	unplayedfacedowncardsLocation.top = StretchedGapBetweenTopandBottomRow;
	unplayedfacedowncardsLocation.right = StretchedGapBetweenGameCols + StretchCardWidth;
	unplayedfacedowncardsLocation.bottom = StretchedGapBetweenTopandBottomRow + StretchCardHeight;
	
	unplayedfaceupcardsLocation.left = StretchedGapBetweenGameCols + StretchCardWidth + StretchedGapBetweenGameCols;
	unplayedfaceupcardsLocation.top = StretchedGapBetweenTopandBottomRow;
	unplayedfaceupcardsLocation.right = StretchedGapBetweenGameCols + StretchCardWidth + StretchedGapBetweenGameCols + StretchCardWidth;
	unplayedfaceupcardsLocation.bottom = StretchedGapBetweenTopandBottomRow + StretchCardHeight;
	
	acecolonecardsLocation.left = StretchedGapBetweenGameCols + StretchCardWidth + StretchedGapBetweenGameCols + StretchCardWidth + StretchedGapBetweenGameCols + StretchCardWidth + StretchedGapBetweenGameCols;
	acecolonecardsLocation.top = StretchedGapBetweenTopandBottomRow;
	acecolonecardsLocation.right = StretchedGapBetweenGameCols + StretchCardWidth + StretchedGapBetweenGameCols + StretchCardWidth + StretchedGapBetweenGameCols + StretchCardWidth + StretchedGapBetweenGameCols + StretchCardWidth;
	acecolonecardsLocation.bottom = StretchedGapBetweenTopandBottomRow + StretchCardHeight;
	
	acecoltwocardsLocation.left = acecolonecardsLocation.left + StretchCardWidth + StretchedGapBetweenGameCols;
	acecoltwocardsLocation.top = StretchedGapBetweenTopandBottomRow;
	acecoltwocardsLocation.right = acecoltwocardsLocation.left + StretchCardWidth;
	acecoltwocardsLocation.bottom = acecoltwocardsLocation.top + StretchCardHeight;
	
	acecolthreecardsLocation.left = acecoltwocardsLocation.left + StretchCardWidth + StretchedGapBetweenGameCols;
	acecolthreecardsLocation.top = StretchedGapBetweenTopandBottomRow;
	acecolthreecardsLocation.right = acecolthreecardsLocation.left + StretchCardWidth;
	acecolthreecardsLocation.bottom = acecolthreecardsLocation.top + StretchCardHeight;
	
	acecolfourcardsLocation.left = acecolthreecardsLocation.left + StretchCardWidth + StretchedGapBetweenGameCols;
	acecolfourcardsLocation.top = StretchedGapBetweenTopandBottomRow;
	acecolfourcardsLocation.right = acecolfourcardsLocation.left + StretchCardWidth;
	acecolfourcardsLocation.bottom = acecolfourcardsLocation.top + StretchCardHeight;

	gamecoloneLocation.left = StretchedGapBetweenGameCols;
	gamecoloneLocation.top = StretchedGapBetweenTopandBottomRow + StretchCardHeight + StretchedGapBetweenTopandBottomRow;
	gamecoloneLocation.right = gamecoloneLocation.left + StretchCardWidth;
	gamecoloneLocation.bottom = ScreenHeight;

	gamecoltwoLocation.left = gamecoloneLocation.left + StretchCardWidth + StretchedGapBetweenGameCols;
	gamecoltwoLocation.top = StretchedGapBetweenTopandBottomRow + StretchCardHeight + StretchedGapBetweenTopandBottomRow;
	gamecoltwoLocation.right = gamecoltwoLocation.left + StretchCardWidth;
	gamecoltwoLocation.bottom = ScreenHeight;

	gamecolthreeLocation.left = gamecoltwoLocation.left + StretchCardWidth + StretchedGapBetweenGameCols;
	gamecolthreeLocation.top = StretchedGapBetweenTopandBottomRow + StretchCardHeight + StretchedGapBetweenTopandBottomRow;
	gamecolthreeLocation.right = gamecolthreeLocation.left + StretchCardWidth;
	gamecolthreeLocation.bottom = ScreenHeight;

	gamecolfourLocation.left = gamecolthreeLocation.left + StretchCardWidth + StretchedGapBetweenGameCols;
	gamecolfourLocation.top = StretchedGapBetweenTopandBottomRow + StretchCardHeight + StretchedGapBetweenTopandBottomRow;
	gamecolfourLocation.right = gamecolfourLocation.left + StretchCardWidth;
	gamecolfourLocation.bottom = ScreenHeight;

	gamecolfiveLocation.left = gamecolfourLocation.left + StretchCardWidth + StretchedGapBetweenGameCols;
	gamecolfiveLocation.top = StretchedGapBetweenTopandBottomRow + StretchCardHeight + StretchedGapBetweenTopandBottomRow;
	gamecolfiveLocation.right = gamecolfiveLocation.left + StretchCardWidth;
	gamecolfiveLocation.bottom = ScreenHeight;

	gamecolsixLocation.left = gamecolfiveLocation.left + StretchCardWidth + StretchedGapBetweenGameCols;
	gamecolsixLocation.top = StretchedGapBetweenTopandBottomRow + StretchCardHeight + StretchedGapBetweenTopandBottomRow;
	gamecolsixLocation.right = gamecolsixLocation.left + StretchCardWidth;
	gamecolsixLocation.bottom = ScreenHeight;

	gamecolsevenLocation.left = gamecolsixLocation.left + StretchCardWidth + StretchedGapBetweenGameCols;
	gamecolsevenLocation.top = StretchedGapBetweenTopandBottomRow + StretchCardHeight + StretchedGapBetweenTopandBottomRow;
	gamecolsevenLocation.right = gamecolsevenLocation.left + StretchCardWidth;
	gamecolsevenLocation.bottom = ScreenHeight;

	LonghornLocation.left = unplayedfaceupcardsLocation.left + (3*StretchedSideGapOfUnplayedFaceUpCards) + StretchCardWidth;
	LonghornLocation.top = unplayedfaceupcardsLocation.top;
	LonghornLocation.right = LonghornLocation.left + StretchCardWidth;
	LonghornLocation.bottom = LonghornLocation.top + (int)(StretchCardHeight/2);

	ScoreLocation.left = LonghornLocation.left;
	ScoreLocation.top = LonghornLocation.top + StretchCardWidth;
	ScoreLocation.right = LonghornLocation.left + StretchCardWidth;
	ScoreLocation.bottom = LonghornLocation.bottom + (int)(StretchCardHeight/2);


}

// find out what and how many cards are being draged around
void CDrawScreen::SeeIfWeAreDragingCards(CPoint point)
{
	int CardLocation;
	int i;
	bool AceColumn = false;
	CARDS *pGameRow;
	CRect GetCardLocation;

	SourceColumnID = SetupRowColumnInformation(point);
	if (SeeIfMouseIsOnAMoveableCard() == true)
	{
		if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
		{
			CardLocation = GetLastLocation(theDeck->unplayedfaceupcards, CARDMAX);
			theDragStack->SetStackInfoWhenMoveStarts(unplayedfaceupcardsLocation, point);
			theDragStack->CardsInStack[0] = theDeck->unplayedfaceupcards[CardLocation].card;
			return;
		}
		switch(SourceColumnID)
		{
			case GAMECOLONECOLUMNID:
				pGameRow = theDeck->gamecolone;
				GetCardLocation = gamecoloneLocation;
				break;
			case GAMECOLTWOCOLUMNID:
				pGameRow = theDeck->gamecoltwo;
				GetCardLocation = gamecoltwoLocation;
				break;
			case GAMECOLTHREECOLUMNID:
				pGameRow = theDeck->gamecolthree;
				GetCardLocation = gamecolthreeLocation;
				break;
			case GAMECOLFOURCOLUMNID:
				pGameRow = theDeck->gamecolfour;
				GetCardLocation = gamecolfourLocation;
				break;
			case GAMECOLFIVECOLUMNID:
				pGameRow = theDeck->gamecolfive;
				GetCardLocation = gamecolfiveLocation;
				break;
			case GAMECOLSIXCOLUMNID:
				pGameRow = theDeck->gamecolsix;
				GetCardLocation = gamecolsixLocation;
				break;
			case GAMECOLSEVENCOLUMNID:
				pGameRow = theDeck->gamecolseven;
				GetCardLocation = gamecolsevenLocation;
				break;
			case ACECOLONECARDSCOLUMNID:
				CardLocation = GetLastLocation(theDeck->acecolonecards, CARDSINSUITE);
				pGameRow = theDeck->acecolonecards;
				AceColumn = true;
				break;
			case ACECOLTWOCARDSCOLUMNID:
				CardLocation = GetLastLocation(theDeck->acecoltwocards, CARDSINSUITE);
				pGameRow = theDeck->acecoltwocards;
				AceColumn = true;
				break;
			case ACECOLTHREECARDSCOLUMNID:
				CardLocation = GetLastLocation(theDeck->acecolthreecards, CARDSINSUITE);
				pGameRow = theDeck->acecolthreecards;
				AceColumn = true;
				break;
			case ACECOLFOURCARDSCOLUMNID:
				CardLocation = GetLastLocation(theDeck->acecolfourcards, CARDSINSUITE);
				pGameRow = theDeck->acecolfourcards;
				AceColumn = true;
				break;
		}
		if (AceColumn == false)
		{
			CardLocation = GetCardLocationInGameRow(pGameRow, point, GetCardLocation);
		}
		if (CardLocation == -1)
		{
			return;
		}
		GetCardLocation = CalculateRectForDraging(SourceColumnID, CardLocation);
		theDragStack->SetStackInfoWhenMoveStarts(GetCardLocation, point);
		for (i = 0; i < CARDSINSUITE; i++)
		{
			if (AceColumn == true)
			{
				if (CardLocation + i >= CARDSINSUITE)
				{
					return;
				}
			}
			if (pGameRow[CardLocation + i].card != -1)
			{
				theDragStack->CardsInStack[i] = pGameRow[CardLocation + i].card;
			}
		}
		return;
	}
}

// calc the rect size of what we are going to drag around.
CRect CDrawScreen::CalculateRectForDraging(int ColumnID, int CardLocation)
{
	CARDS *theColumnToUse;
	CRect ColumnRect;
	CRect ReturnRect;
	int i;
	int newBottom;
	int newTop;
	bool AceColumn = false;

	switch(ColumnID)
	{
		case GAMECOLONECOLUMNID:
			theColumnToUse = (theDeck->gamecolone);
			ColumnRect = gamecoloneLocation;
			break;
		case GAMECOLTWOCOLUMNID:
			theColumnToUse = (theDeck->gamecoltwo);
			ColumnRect = gamecoltwoLocation;
			break;
		case GAMECOLTHREECOLUMNID:
			theColumnToUse = (theDeck->gamecolthree);
			ColumnRect = gamecolthreeLocation;
			break;
		case GAMECOLFOURCOLUMNID:
			theColumnToUse = (theDeck->gamecolfour);
			ColumnRect = gamecolfourLocation;
			break;
		case GAMECOLFIVECOLUMNID:
			theColumnToUse = (theDeck->gamecolfive);
			ColumnRect = gamecolfiveLocation;
			break;
		case GAMECOLSIXCOLUMNID:
			theColumnToUse = (theDeck->gamecolsix);
			ColumnRect = gamecolsixLocation;
			break;
		case GAMECOLSEVENCOLUMNID:
			theColumnToUse = (theDeck->gamecolseven);
			ColumnRect = gamecolsevenLocation;
			break;
		case ACECOLONECARDSCOLUMNID:
			theColumnToUse = (theDeck->acecolonecards);
			ColumnRect = acecolonecardsLocation;
			AceColumn = true;
			break;
		case ACECOLTWOCARDSCOLUMNID:
			theColumnToUse = (theDeck->acecoltwocards);
			ColumnRect = acecoltwocardsLocation;
			AceColumn = true;
			break;
		case ACECOLTHREECARDSCOLUMNID:
			theColumnToUse = (theDeck->acecolthreecards);
			ColumnRect = acecolthreecardsLocation;
			AceColumn = true;
			break;
		case ACECOLFOURCARDSCOLUMNID:
			theColumnToUse = (theDeck->acecolfourcards);
			ColumnRect = acecolfourcardsLocation;
			AceColumn = true;
			break;
	}
	newTop = ColumnRect.top;
	newBottom = ColumnRect.top + StretchCardHeight;
	if (AceColumn != true)
	{
		for (i = 0; i < CardLocation; i++)
		{
			if (theColumnToUse[i].faceup == false)
			{
				newTop += StretchedGapOfFaceDownCardsUnderOtherCard;
				newBottom += StretchedGapOfFaceDownCardsUnderOtherCard;
			}
			else
			{
				newTop += StretchedGapOfFaceUpCardsUnderOtherCard;
				newBottom += StretchedGapOfFaceUpCardsUnderOtherCard;
			}
		}
		for (i = CardLocation; i < GAMEROWMAX; i++)
		{
			if (theColumnToUse[i + 1].card == -1)
			{
				break;
			}
			if ((!((i+1) >= GAMEROWMAX)) && (i == (CardLocation)) && (theColumnToUse[i + 1].card != -1))
			{
				// then double the stretch gap
				//newBottom += StretchedGapOfFaceUpCardsUnderOtherCard;
				newBottom += StretchedGapOfFaceUpCardsUnderOtherCard;
			}
			newBottom += StretchedGapOfFaceUpCardsUnderOtherCard;
		}
	}
	ReturnRect.top = newTop;
	if (ScreenHeight < newBottom)
	{
		ReturnRect.bottom = ScreenHeight;
	}
	else
	{
		ReturnRect.bottom = newBottom;
	}
	ReturnRect.left = ColumnRect.left;
	ReturnRect.right = ColumnRect.right;
	return ReturnRect;
}

// used to validate that we are trying to drag a valid card plus returns it location if we are
int CDrawScreen::GetCardLocationInGameRow(CARDS *pGameRow, CPoint point, CRect CardLocation)
{
	int i;
	CRect rect;

	rect = CardLocation;

	if (pGameRow[0].card != -1)
	{
		if (pGameRow[0].faceup == false)
		{
			rect.bottom = rect.top + StretchedGapOfFaceDownCardsUnderOtherCard;
		}
		else
		{
			rect.bottom = rect.top + StretchedGapOfFaceUpCardsUnderOtherCard;
		}

		for (i = 0; i < GAMEROWMAX; i++)
		{
			if (pGameRow[i + 1].card != -1)
			{
				if (pGameRow[i].faceup == false)
				{
					rect.top += StretchedGapOfFaceDownCardsUnderOtherCard;
					if (pGameRow[i+1].faceup == false)
					{
						rect.bottom += StretchedGapOfFaceDownCardsUnderOtherCard;
					}
					else
					{
						rect.bottom += StretchedGapOfFaceUpCardsUnderOtherCard;
					}
				}
				else
				{
					if (pGameRow[i+1].card == -1)
					{
						rect.bottom = rect.top + StretchCardHeight;
						if (rect.PtInRect(point))
						{
							return i;
						}
						return -1;
					}
					if (rect.PtInRect(point))
					{
						return i;
					}
					rect.top += StretchedGapOfFaceUpCardsUnderOtherCard;
					rect.bottom += StretchedGapOfFaceUpCardsUnderOtherCard;
				}
			}
			else
			{
				rect.bottom = rect.top + StretchCardHeight;
				if (rect.PtInRect(point))
				{
					return i;
				}
				return -1;
			}
		}
	}
	return -1;
}

// sets up the new stack location when we get a mouse move
bool CDrawScreen::MoveDragStack(CPoint point)
{
	if (theDragStack->CardsInStack[0] == -1)
	{
		// nothing to do
		return false;
	}
	return theDragStack->CalculateNewCornersAfterMouseMove(point);
}
// quick test to see if we are in a valid column
bool CDrawScreen::SeeIfMouseIsOnAMoveableCard()
{
	switch(SourceColumnID)
	{
		case UNPLAYEDFACEUPCARDSCOLUMNID:
			return true;
		case GAMECOLONECOLUMNID:
			return true;
		case GAMECOLTWOCOLUMNID:
			return true;
		case GAMECOLTHREECOLUMNID:
			return true;
		case GAMECOLFOURCOLUMNID:
			return true;
		case GAMECOLFIVECOLUMNID:
			return true;
		case GAMECOLSIXCOLUMNID:
			return true;
		case GAMECOLSEVENCOLUMNID:
			return true;
		case ACECOLONECARDSCOLUMNID:
			return true;
		case ACECOLTWOCARDSCOLUMNID:
			return true;
		case ACECOLTHREECARDSCOLUMNID:
			return true;
		case ACECOLFOURCARDSCOLUMNID:
			return true;
	}
	return false;
}

// identifies which column the mouse is on.
int CDrawScreen::SetupRowColumnInformation(CPoint point)
{
	if (unplayedfacedowncardsLocation.PtInRect(point))
	{
		return UNPLAYEDFACEDOWNCARDSCOLUMNID;
	}
	if (unplayedfaceupcardsLocation.PtInRect(point))
	{
		return UNPLAYEDFACEUPCARDSCOLUMNID;
	}
	if (acecolonecardsLocation.PtInRect(point))
	{
		return ACECOLONECARDSCOLUMNID;
	}
	if (acecoltwocardsLocation.PtInRect(point))
	{
		return ACECOLTWOCARDSCOLUMNID;
	}
	if (acecolthreecardsLocation.PtInRect(point))
	{
		return ACECOLTHREECARDSCOLUMNID;
	}
	if (acecolfourcardsLocation.PtInRect(point))
	{
		return ACECOLFOURCARDSCOLUMNID;
	}
	if (gamecoloneLocation.PtInRect(point))
	{
		return GAMECOLONECOLUMNID;
	}
	if (gamecoltwoLocation.PtInRect(point))
	{
		return GAMECOLTWOCOLUMNID;
	}
	if (gamecolthreeLocation.PtInRect(point))
	{
		return GAMECOLTHREECOLUMNID;
	}
	if (gamecolfourLocation.PtInRect(point))
	{
		return GAMECOLFOURCOLUMNID;
	}
	if (gamecolfiveLocation.PtInRect(point))
	{
		return GAMECOLFIVECOLUMNID;
	}
	if (gamecolsixLocation.PtInRect(point))
	{
		return GAMECOLSIXCOLUMNID;
	}
	if (gamecolsevenLocation.PtInRect(point))
	{
		return GAMECOLSEVENCOLUMNID;
	}
	if (LonghornLocation.PtInRect(point))
	{
		return LONGHORNCOLUMNID;
	}
	return -1;
}
// calculates where we have moved a card
CRect CDrawScreen::CalculateDirtyRectangle()
{
	CSize PicSize(StretchCardWidth,StretchCardHeight);
	CRect r1(theDragStack->StackLocation,PicSize);
	CRect r2(theDragStack->OldStackLocation,PicSize);

	return r1 | r2;

}

CRect CDrawScreen::GetDragImageRectangle(CPoint point)
{
	CRect rect(theDragStack->StackLocation.x, theDragStack->StackLocation.y, theDragStack->StackLocation.x + theDragStack->StackSize.cx, theDragStack->StackLocation.y + theDragStack->StackSize.cy);

	return rect;
}

bool CDrawScreen::DropDragAroundStack(CPoint point)
{
	bool SomethingChanged = false;

	SomethingChanged = DropDragAroundStack2(point);
	if (SomethingChanged)
	{
		FlipTopCardAfterMove();
		theUndoStack->CurrentActionID++;
	}

	return SomethingChanged;
}

bool CDrawScreen::DropDragAroundStack2(CPoint point)
{
	CARDS *pGameRow = NULL;
	CRect MaxDropRect; // what the rect should look like if you have all of the dragimage instead of just the mouse point;
	int DividingLineBetweenTopAndBottomRows = StretchCardHeight + StretchedGapBetweenTopandBottomRow + StretchedGapBetweenTopandBottomRow;

	if (DividingLineBetweenTopAndBottomRows >= (point.y - offset.cy))
	{
		// acecolonecardsLocation
		MaxDropRect = acecolonecardsLocation;
		pGameRow = theDeck->acecolonecards;
		DestinationColumnID = ACECOLONECARDSCOLUMNID;
		if (DropOnAceColumn(MaxDropRect, pGameRow, point) == true)
		{
			return true;
		}
		// acecoltwocardsLocation
		MaxDropRect = acecoltwocardsLocation;
		pGameRow = theDeck->acecoltwocards;
		DestinationColumnID = ACECOLTWOCARDSCOLUMNID;
		if (DropOnAceColumn(MaxDropRect, pGameRow, point) == true)
		{
			return true;
		}
		// acecolthreecardsLocation
		MaxDropRect = acecolthreecardsLocation;
		pGameRow = theDeck->acecolthreecards;
		DestinationColumnID = ACECOLTHREECARDSCOLUMNID;
		if (DropOnAceColumn(MaxDropRect, pGameRow, point) == true)
		{
			return true;
		}
		// acecolfourcardsLocation
		MaxDropRect = acecolfourcardsLocation;
		pGameRow = theDeck->acecolfourcards;
		DestinationColumnID = ACECOLFOURCARDSCOLUMNID;
		if (DropOnAceColumn(MaxDropRect, pGameRow, point) == true)
		{
			return true;
		}
	}
	if (DividingLineBetweenTopAndBottomRows <= (point.y + offset.cy + DragingRect.Height()))
	{
		// gamecoloneLocation
		MaxDropRect = gamecoloneLocation;
		pGameRow = theDeck->gamecolone;
		DestinationColumnID = GAMECOLONECOLUMNID;
		if (DropOnGameColumn(MaxDropRect, pGameRow, point) == true)
		{
			return true;
		}
		// gamecoltwoLocation
		MaxDropRect = gamecoltwoLocation;
		pGameRow = theDeck->gamecoltwo;
		DestinationColumnID = GAMECOLTWOCOLUMNID;
		if (DropOnGameColumn(MaxDropRect, pGameRow, point) == true)
		{
			return true;
		}
		// gamecolthreeLocation
		MaxDropRect = gamecolthreeLocation;
		pGameRow = theDeck->gamecolthree;
		DestinationColumnID = GAMECOLTHREECOLUMNID;
		if (DropOnGameColumn(MaxDropRect, pGameRow, point) == true)
		{
			return true;
		}
		// gamecolfourLocation
		MaxDropRect = gamecolfourLocation;
		pGameRow = theDeck->gamecolfour;
		DestinationColumnID = GAMECOLFOURCOLUMNID;
		if (DropOnGameColumn(MaxDropRect, pGameRow, point) == true)
		{
			return true;
		}
		// gamecolfiveLocation
		MaxDropRect = gamecolfiveLocation;
		pGameRow = theDeck->gamecolfive;
		DestinationColumnID = GAMECOLFIVECOLUMNID;
		if (DropOnGameColumn(MaxDropRect, pGameRow, point) == true)
		{
			return true;
		}
		// gamecolsixLocation
		MaxDropRect = gamecolsixLocation;
		pGameRow = theDeck->gamecolsix;
		DestinationColumnID = GAMECOLSIXCOLUMNID;
		if (DropOnGameColumn(MaxDropRect, pGameRow, point) == true)
		{
			return true;
		}
		// gamecolsevenLocation
		MaxDropRect = gamecolsevenLocation;
		pGameRow = theDeck->gamecolseven;
		DestinationColumnID = GAMECOLSEVENCOLUMNID;
		if (DropOnGameColumn(MaxDropRect, pGameRow, point) == true)
		{
			return true;
		}
	}

	return false;
}

bool CDrawScreen::DropOnAceColumn(CRect &MaxDropRect, CARDS *pGameRow, CPoint point)
{
	int lastcardloc;

	if(theDragStack->CardsInStack[1] == -1)
	{
		MaxDropRect.left = MaxDropRect.left - (StretchCardWidth  - offset.cx);
		if (MaxDropRect.left < 0)
		{
			MaxDropRect.left = 0;
		}
		MaxDropRect.right = MaxDropRect.right + DragingRect.Width() - (StretchCardWidth  - offset.cx);
		if (MaxDropRect.right > ScreenWidth)
		{
			MaxDropRect.right = ScreenWidth;
		}
		MaxDropRect.top = MaxDropRect.top - (StretchCardHeight - offset.cy);
		if (MaxDropRect.top < 0)
		{
			MaxDropRect.top = 0;
		}
		MaxDropRect.bottom = MaxDropRect.bottom + DragingRect.Height() - (StretchCardHeight - offset.cy);
		if (MaxDropRect.bottom > ScreenHeight)
		{
			MaxDropRect.bottom = ScreenHeight;
		}

		if (MaxDropRect.PtInRect(point) == TRUE)
		{
			if (pGameRow[0].card == -1)
			{
				// then we have to have an ace
				if (theDragStack->CardsInStack[0] == ACEOFHEARTS || theDragStack->CardsInStack[0] == ACEOFCLUBS || 
					theDragStack->CardsInStack[0] == ACEOFDIAMONDS || theDragStack->CardsInStack[0] == ACEOFSPADES)
				{
					pGameRow[0].card = theDragStack->CardsInStack[0];
					pGameRow[0].faceup = true;
					AddToUndoFromDragStack(UnplayedFaceUpCardsShowing);
					if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
					{
						UnplayedFaceUpCardsShowing--;
						if (UnplayedFaceUpCardsShowing < 1)
						{
							UnplayedFaceUpCardsShowing = 1;
						}
					}
					Paint_Score = true;
					TheCurrentScore += 5;
					BaseScore += 5;
					SetPaintBasedOnColumnID(SourceColumnID);
					SetPaintBasedOnColumnID(DestinationColumnID);
					return true;
				}
				return false;
			}
			lastcardloc = GetLastLocation(pGameRow, CARDSINSUITE);
			if (pGameRow[lastcardloc].card + 1 == theDragStack->CardsInStack[0])
			{
				// if the card in the drag stack is an ace we can't play it
				if (theDragStack->CardsInStack[0] == ACEOFHEARTS || theDragStack->CardsInStack[0] == ACEOFCLUBS || 
					theDragStack->CardsInStack[0] == ACEOFDIAMONDS || theDragStack->CardsInStack[0] == ACEOFSPADES)
				{
					return false;
				}
				pGameRow[lastcardloc + 1].card = theDragStack->CardsInStack[0];
				pGameRow[lastcardloc =1].faceup = true;
				AddToUndoFromDragStack(UnplayedFaceUpCardsShowing);
				if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
				{
					if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
					{
						UnplayedFaceUpCardsShowing--;
						if (UnplayedFaceUpCardsShowing < 1)
						{
							UnplayedFaceUpCardsShowing = 1;
						}
					}
				}
				TheCurrentScore += 5;
				BaseScore += 5;
				Paint_Score = true;
				SetPaintBasedOnColumnID(SourceColumnID);
				SetPaintBasedOnColumnID(DestinationColumnID);
				return true;
			}
		}				
	}


	return false;
}
bool CDrawScreen::DropOnGameColumn(CRect &MaxDropRect, CARDS *pGameRow, CPoint point)
{
	int lastcardloc;
	CRect GetCardLocation;

	MaxDropRect.left = MaxDropRect.left - (StretchCardWidth  - offset.cx);
	if (MaxDropRect.left < 0)
	{
		MaxDropRect.left = 0;
	}
	MaxDropRect.right = MaxDropRect.right + DragingRect.Width() - (StretchCardWidth  - offset.cx);
	if (MaxDropRect.right > ScreenWidth)
	{
		MaxDropRect.right = ScreenWidth;
	}
	MaxDropRect.top = MaxDropRect.top - (StretchCardHeight - offset.cy);
	if (MaxDropRect.top < 0)
	{
		MaxDropRect.top = 0;
	}
	MaxDropRect.bottom = MaxDropRect.bottom + DragingRect.Height() - (StretchCardHeight - offset.cy);
	if (MaxDropRect.bottom > ScreenHeight)
	{
		MaxDropRect.bottom = ScreenHeight;
	}

	if (MaxDropRect.PtInRect(point) == TRUE)
	{
		lastcardloc = GetLastLocation(pGameRow, GAMEROWMAX);
		if ((lastcardloc == -1)) // && (pGameRow[lastcardloc].card == -1))
		{
			// then there are no cards in this row so the first card in dragaround deck has to be a king
			if (theDragStack->CardsInStack[0] == KINGOFSPADES ||
				theDragStack->CardsInStack[0] == KINGOFDIAMONDS ||
				theDragStack->CardsInStack[0] == KINGOFCLUBS ||
				theDragStack->CardsInStack[0] == KINGOFHEARTS)
			{
				MoveDragStackToNewRow(pGameRow);
				AddToUndoFromDragStack(UnplayedFaceUpCardsShowing);
				if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
				{
					if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
					{
						UnplayedFaceUpCardsShowing--;
						if (UnplayedFaceUpCardsShowing < 1)
						{
							UnplayedFaceUpCardsShowing = 1;
						}
					}
				}
				SetPaintBasedOnColumnID(SourceColumnID);
				SetPaintBasedOnColumnID(DestinationColumnID);
				return true;
			}
			return false;
		}
		else
		{
			if (theCards->iaCanCardPlay[pGameRow[lastcardloc].card][0] == theDragStack->CardsInStack[0] ||
				theCards->iaCanCardPlay[pGameRow[lastcardloc].card][1] == theDragStack->CardsInStack[0])
			{
				// then the cards can play
				MoveDragStackToNewRow(pGameRow);
				AddToUndoFromDragStack(UnplayedFaceUpCardsShowing);
				if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
				{
					if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
					{
						UnplayedFaceUpCardsShowing--;
						if (UnplayedFaceUpCardsShowing < 1)
						{
							UnplayedFaceUpCardsShowing = 1;
						}
					}
				}
				SetPaintBasedOnColumnID(SourceColumnID);
				SetPaintBasedOnColumnID(DestinationColumnID);
				return true;
			}
			return false;
		}
	}

	return false;
}

//bool CDrawScreen::DropDragAroundStack2(CPoint point)
//{
//	int lastcardloc;
//	CARDS *pGameRow = NULL;
//	CRect GetCardLocation;
//
//	DestinationColumnID = SetupRowColumnInformation(point);
//	if(SeeIfMouseIsOnAMoveableCard())
//	{
//		switch (DestinationColumnID)
//		{
//			case GAMECOLONECOLUMNID:
//				pGameRow = theDeck->gamecolone;
//				GetCardLocation = gamecoloneLocation;
//				break;
//			case GAMECOLTWOCOLUMNID:
//				pGameRow = theDeck->gamecoltwo;
//				GetCardLocation = gamecoltwoLocation;
//				break;
//			case GAMECOLTHREECOLUMNID:
//				pGameRow = theDeck->gamecolthree;
//				GetCardLocation = gamecolthreeLocation;
//				break;
//			case GAMECOLFOURCOLUMNID:
//				pGameRow = theDeck->gamecolfour;
//				GetCardLocation = gamecolfourLocation;
//				break;
//			case GAMECOLFIVECOLUMNID:
//				pGameRow = theDeck->gamecolfive;
//				GetCardLocation = gamecolfiveLocation;
//				break;
//			case GAMECOLSIXCOLUMNID:
//				pGameRow = theDeck->gamecolsix;
//				GetCardLocation = gamecolsixLocation;
//				break;
//			case GAMECOLSEVENCOLUMNID:
//				pGameRow = theDeck->gamecolseven;
//				GetCardLocation = gamecolsevenLocation;
//				break;
//		}
//		if (pGameRow != NULL)
//		{
//			lastcardloc = GetLastLocation(pGameRow, GAMEROWMAX);
//			if ((lastcardloc == -1)) // && (pGameRow[lastcardloc].card == -1))
//			{
//				// then there are no cards in this row so the first card in dragaround deck has to be a king
//				if (theDragStack->CardsInStack[0] == KINGOFSPADES ||
//					theDragStack->CardsInStack[0] == KINGOFDIAMONDS ||
//					theDragStack->CardsInStack[0] == KINGOFCLUBS ||
//					theDragStack->CardsInStack[0] == KINGOFHEARTS)
//				{
//					MoveDragStackToNewRow(pGameRow);
//					AddToUndoFromDragStack(UnplayedFaceUpCardsShowing);
//					if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
//					{
//						if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
//						{
//							UnplayedFaceUpCardsShowing--;
//							if (UnplayedFaceUpCardsShowing < 1)
//							{
//								UnplayedFaceUpCardsShowing = 1;
//							}
//						}
//					}
//					SetPaintBasedOnColumnID(SourceColumnID);
//					SetPaintBasedOnColumnID(DestinationColumnID);
//					return true;
//				}
//				return false;
//			}
//			else
//			{
//				if (theCards->iaCanCardPlay[pGameRow[lastcardloc].card][0] == theDragStack->CardsInStack[0] ||
//					theCards->iaCanCardPlay[pGameRow[lastcardloc].card][1] == theDragStack->CardsInStack[0])
//				{
//					// then the cards can play
//					MoveDragStackToNewRow(pGameRow);
//					AddToUndoFromDragStack(UnplayedFaceUpCardsShowing);
//					if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
//					{
//						if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
//						{
//							UnplayedFaceUpCardsShowing--;
//							if (UnplayedFaceUpCardsShowing < 1)
//							{
//								UnplayedFaceUpCardsShowing = 1;
//							}
//						}
//					}
//					SetPaintBasedOnColumnID(SourceColumnID);
//					SetPaintBasedOnColumnID(DestinationColumnID);
//					return true;
//				}
//				return false;
//			}
//		}
//
//		// ok then it has to be a singe card on the ace rows if it can play
//		if (theDragStack->CardsInStack[1] == -1)
//		{
//			switch (DestinationColumnID)
//			{
//				case ACECOLONECARDSCOLUMNID:
//					pGameRow = theDeck->acecolonecards;
//					break;
//				case ACECOLTWOCARDSCOLUMNID:
//					pGameRow = theDeck->acecoltwocards;
//					break;
//				case ACECOLTHREECARDSCOLUMNID:
//					pGameRow = theDeck->acecolthreecards;
//					break;
//				case ACECOLFOURCARDSCOLUMNID:
//					pGameRow = theDeck->acecolfourcards;
//					break;
//			}
//			if (pGameRow != NULL)
//			{
//				if (pGameRow[0].card == -1)
//				{
//					// then we have to have an ace
//					if (theDragStack->CardsInStack[0] == ACEOFHEARTS || theDragStack->CardsInStack[0] == ACEOFCLUBS || 
//						theDragStack->CardsInStack[0] == ACEOFDIAMONDS || theDragStack->CardsInStack[0] == ACEOFSPADES)
//					{
//						pGameRow[0].card = theDragStack->CardsInStack[0];
//						pGameRow[0].faceup = true;
//						AddToUndoFromDragStack(UnplayedFaceUpCardsShowing);
//						if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
//						{
//							UnplayedFaceUpCardsShowing--;
//							if (UnplayedFaceUpCardsShowing < 1)
//							{
//								UnplayedFaceUpCardsShowing = 1;
//							}
//						}
//						Paint_Score = true;
//						TheCurrentScore += 5;
//						BaseScore += 5;
//						SetPaintBasedOnColumnID(SourceColumnID);
//						SetPaintBasedOnColumnID(DestinationColumnID);
//						return true;
//					}
//					return false;
//				}
//				lastcardloc = GetLastLocation(pGameRow, CARDSINSUITE);
//				if (pGameRow[lastcardloc].card + 1 == theDragStack->CardsInStack[0])
//				{
//					// if the card in the drag stack is an ace we can't play it
//					if (theDragStack->CardsInStack[0] == ACEOFHEARTS || theDragStack->CardsInStack[0] == ACEOFCLUBS || 
//						theDragStack->CardsInStack[0] == ACEOFDIAMONDS || theDragStack->CardsInStack[0] == ACEOFSPADES)
//					{
//						return false;
//					}
//					pGameRow[lastcardloc + 1].card = theDragStack->CardsInStack[0];
//					pGameRow[lastcardloc =1].faceup = true;
//					AddToUndoFromDragStack(UnplayedFaceUpCardsShowing);
//					if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
//					{
//						if (SourceColumnID == UNPLAYEDFACEUPCARDSCOLUMNID)
//						{
//							UnplayedFaceUpCardsShowing--;
//							if (UnplayedFaceUpCardsShowing < 1)
//							{
//								UnplayedFaceUpCardsShowing = 1;
//							}
//						}
//					}
//					TheCurrentScore += 5;
//					BaseScore += 5;
//					Paint_Score = true;
//					SetPaintBasedOnColumnID(SourceColumnID);
//					SetPaintBasedOnColumnID(DestinationColumnID);
//					return true;
//				}
//			}
//		}
//	}
//	return false;
//}

void CDrawScreen::MoveDragStackToNewRow(CARDS *pGameRow)
{
	int lastcardloc;
	int i;
	int j = 0;

	lastcardloc = GetLastLocation(pGameRow, GAMEROWMAX);
	for (i = lastcardloc + 1; i < GAMEROWMAX; i++)
	{
		if (theDragStack->CardsInStack[j] == -1)
		{
			break;
		}
		pGameRow[i].card = theDragStack->CardsInStack[j];
		pGameRow[i].faceup = true;
		j++;
	}

}

void CDrawScreen::AddToUndoFromDragStack(int iUnplayedFaceUpCardsShowing)
{
	int i;
	int j = 0;
	bool foundfirstcard = false;
	CARDS *pGameRow = NULL;
	switch (SourceColumnID)
	{
		case GAMECOLONECOLUMNID:
			pGameRow = theDeck->gamecolone;
			break;
		case GAMECOLTWOCOLUMNID:
			pGameRow = theDeck->gamecoltwo;
			break;
		case GAMECOLTHREECOLUMNID:
			pGameRow = theDeck->gamecolthree;
			break;
		case GAMECOLFOURCOLUMNID:
			pGameRow = theDeck->gamecolfour;
			break;
		case GAMECOLFIVECOLUMNID:
			pGameRow = theDeck->gamecolfive;
			break;
		case GAMECOLSIXCOLUMNID:
			pGameRow = theDeck->gamecolsix;
			break;
		case GAMECOLSEVENCOLUMNID:
			pGameRow = theDeck->gamecolseven;
			break;
		case ACECOLONECARDSCOLUMNID:
			pGameRow = theDeck->acecolonecards;
			break;
		case ACECOLTWOCARDSCOLUMNID:
			pGameRow = theDeck->acecoltwocards;
			break;
		case ACECOLTHREECARDSCOLUMNID:
			pGameRow = theDeck->acecolthreecards;
			break;
		case ACECOLFOURCARDSCOLUMNID:
			pGameRow = theDeck->acecolfourcards;
			break;
		case UNPLAYEDFACEUPCARDSCOLUMNID:
			pGameRow = theDeck->unplayedfaceupcards;
			break;
	}
	if (pGameRow != NULL)
	{
		theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ActionID = theUndoStack->CurrentActionID;
		theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded = DestinationColumnID;
		theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionStarted = SourceColumnID;
		theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].UnplayedFaceUpCardsShowing = iUnplayedFaceUpCardsShowing;
		theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].TimeThroughDeck = TimeThroughDeck;
		for (i = 0; i < CARDMAX; i++)
		{
			if (foundfirstcard == false && pGameRow[i].card == theDragStack->CardsInStack[j])
			{
				foundfirstcard = true;
			}
			if (foundfirstcard == true)
			{
				if(theDragStack->CardsInStack[j] == -1 || j > CARDSINSUITE)
				{
					theUndoStack->CurrentUndoStackLocation++;
					return;
				}
				theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[j] = pGameRow[i].card;
				pGameRow[i].card = -1;
				pGameRow[i].faceup = false;
				j++;
			}
		}
		theUndoStack->CurrentUndoStackLocation++;
	}
}

void CDrawScreen::FlipTopCardAfterMove()
{
	int i;
	CARDS *pGameRow = NULL;
	switch (SourceColumnID)
	{
		case GAMECOLONECOLUMNID:
			pGameRow = theDeck->gamecolone;
			break;
		case GAMECOLTWOCOLUMNID:
			pGameRow = theDeck->gamecoltwo;
			break;
		case GAMECOLTHREECOLUMNID:
			pGameRow = theDeck->gamecolthree;
			break;
		case GAMECOLFOURCOLUMNID:
			pGameRow = theDeck->gamecolfour;
			break;
		case GAMECOLFIVECOLUMNID:
			pGameRow = theDeck->gamecolfive;
			break;
		case GAMECOLSIXCOLUMNID:
			pGameRow = theDeck->gamecolsix;
			break;
		case GAMECOLSEVENCOLUMNID:
			pGameRow = theDeck->gamecolseven;
			break;
	}
	if (pGameRow != NULL)
	{
		i = GetLastLocation(pGameRow, GAMEROWMAX);
		if ((i > -1) && (pGameRow[i].faceup == false))
		{
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ActionID = theUndoStack->CurrentActionID;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded = SourceColumnID;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionStarted = SourceColumnID;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].UnplayedFaceUpCardsShowing = UnplayedFaceUpCardsShowing;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].TimeThroughDeck = TimeThroughDeck;

			pGameRow[i].faceup = true;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[0] = pGameRow[i].card;
			theUndoStack->CurrentUndoStackLocation++;
		}
	}
}

void CDrawScreen::DealInit()
{
	DoubleSpaceCard.ColumnID = -1;
	DoubleSpaceCard.RowID = -1;
	UnplayedFaceUpCardsShowing = 1;
	TheCurrentScore -= 52;
	Paint_Score = true;
	TimeThroughDeck = 0;
	theUndoStack->InitUndoStack();
}

bool CDrawScreen::SetupDoubleSpaceView(CPoint point)
{
	CARDS *pGameRow;
	CRect GetCardLocation;

	DoubleSpaceCard.ColumnID = SetupRowColumnInformation(point);

	switch(DoubleSpaceCard.ColumnID)
	{
		case GAMECOLONECOLUMNID:
			pGameRow = theDeck->gamecolone;
			GetCardLocation = gamecoloneLocation;
			break;
		case GAMECOLTWOCOLUMNID:
			pGameRow = theDeck->gamecoltwo;
			GetCardLocation = gamecoltwoLocation;
			break;
		case GAMECOLTHREECOLUMNID:
			pGameRow = theDeck->gamecolthree;
			GetCardLocation = gamecolthreeLocation;
			break;
		case GAMECOLFOURCOLUMNID:
			pGameRow = theDeck->gamecolfour;
			GetCardLocation = gamecolfourLocation;
			break;
		case GAMECOLFIVECOLUMNID:
			pGameRow = theDeck->gamecolfive;
			GetCardLocation = gamecolfiveLocation;
			break;
		case GAMECOLSIXCOLUMNID:
			pGameRow = theDeck->gamecolsix;
			GetCardLocation = gamecolsixLocation;
			break;
		case GAMECOLSEVENCOLUMNID:
			pGameRow = theDeck->gamecolseven;
			GetCardLocation = gamecolsevenLocation;
			break;
		default:
			DoubleSpaceCard.ColumnID = -1;
			DoubleSpaceCard.RowID = -1;
			return false;
	}
	DoubleSpaceCard.RowID = GetCardLocationInGameRow(pGameRow, point, GetCardLocation);
	if (DoubleSpaceCard.RowID >= 0)
	{
		return true;
	}
	DoubleSpaceCard.ColumnID = -1;
	DoubleSpaceCard.RowID = -1;
	return false;
}

bool CDrawScreen::NextThreeCards()
{
	int UnPlayedLastCard;
	int PlayedLastCard;
	int i;

	// RDAHERE when I undo to bring the cards from unplayed face up to unplayed face down it messes up
	UnPlayedLastCard = GetLastLocation(theDeck->unplayedfacedowncards, CARDMAX);
	PlayedLastCard = GetLastLocation(theDeck->unplayedfaceupcards, CARDMAX);

	if (UnPlayedLastCard >= 0)
	{
		PlayedLastCard++;
		theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionStarted = UNPLAYEDFACEDOWNCARDSCOLUMNID;
		theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded = UNPLAYEDFACEUPCARDSCOLUMNID;
		theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ActionID = theUndoStack->CurrentActionID;
		theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].UnplayedFaceUpCardsShowing = UnplayedFaceUpCardsShowing;
		theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].TimeThroughDeck = TimeThroughDeck;

		for (i = 0; i < 3; i++)
		{
			// then we have cards to play
			theDeck->unplayedfaceupcards[PlayedLastCard + i].card = theDeck->unplayedfacedowncards[UnPlayedLastCard - i].card;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[i] = theDeck->unplayedfacedowncards[UnPlayedLastCard - i].card;
			theDeck->unplayedfacedowncards[UnPlayedLastCard - i].card = -1;
			if ((UnPlayedLastCard - i - 1) < 0)
			{
				// no more cards to move
				break;
			}
		}
		UnplayedFaceUpCardsShowing = i + 1;
		if (UnplayedFaceUpCardsShowing > 3)
		{
			UnplayedFaceUpCardsShowing = 3;
		}
		theUndoStack->CurrentActionID++;
		theUndoStack->CurrentUndoStackLocation++;
		return true;
	}
	else
	{
		if (TimeThroughDeck < MAXTIMETHROUGHDECK)
		{
			// move cards back
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionStarted = UNPLAYEDFACEUPCARDSCOLUMNID;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded = UNPLAYEDFACEDOWNCARDSCOLUMNID;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ActionID = theUndoStack->CurrentActionID;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].UnplayedFaceUpCardsShowing = UnplayedFaceUpCardsShowing;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].TimeThroughDeck = TimeThroughDeck;
			for (i = 0; i <= PlayedLastCard; i++)
			{
				theDeck->unplayedfacedowncards[PlayedLastCard - i].card = theDeck->unplayedfaceupcards[i].card;
				theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[PlayedLastCard - i] = theDeck->unplayedfaceupcards[i].card;
				theDeck->unplayedfaceupcards[i].card = -1;
			}
			TimeThroughDeck++;
			UnplayedFaceUpCardsShowing = 1;
			theUndoStack->CurrentActionID++;
			theUndoStack->CurrentUndoStackLocation++;
			return true;
		}
	}
	return false;
}

bool CDrawScreen::DoAnUnDo()
{
	CARDS *From;
	CARDS *To;
	int FromArraySize;
	int ToArraySize;
	int FromLastLocation;
	int ToLastLocation;
	int FromColumnID;
	int ToColumnID;
	int i;
	int j;
	bool rtnval = false;

	theUndoStack->CurrentActionID--;
	theUndoStack->CurrentUndoStackLocation--;

	while ((theUndoStack->CurrentActionID == theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ActionID) &&
		(theUndoStack->CurrentUndoStackLocation >= 0) && (theUndoStack->CurrentActionID >= 0))
	{
		//if ((theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded == 
		//	theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionStarted) &&
		//	(theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[1] == -1))
		if ((theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded == 
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionStarted))
		{
			// then we fliped a card
			From = GetPointerToColumn(theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded);
			FromArraySize = GetColumnArraySize(theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded);
			FromLastLocation = GetLastLocation(From,FromArraySize);
			From[FromLastLocation].faceup = false;
			UnplayedFaceUpCardsShowing = theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].UnplayedFaceUpCardsShowing;
			TimeThroughDeck = theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].TimeThroughDeck;
			SetPaintBasedOnColumnID(theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded);
			//SetPaintBasedOnColumnID(theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionStarted);

			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ActionID = -1;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded = -1;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionStarted = -1;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[0] = -1;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].UnplayedFaceUpCardsShowing = -1;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].TimeThroughDeck = -1;
			rtnval = true;
		}
		else
		{
			// we are moving cards
			rtnval = true;
			FromColumnID = theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded;
			From = GetPointerToColumn(FromColumnID);
			FromArraySize = GetColumnArraySize(FromColumnID);

			ToColumnID = theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionStarted;
			To = GetPointerToColumn(ToColumnID);
			ToArraySize = GetColumnArraySize(ToColumnID);
			SetPaintBasedOnColumnID(theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded);
			SetPaintBasedOnColumnID(theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionStarted);

			for (i = 0; i < FromArraySize; i++)
			{
				if (From[i].card == theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[0])
				{
					FromLastLocation = i;
					break;
				}
			}
			j = 0;
			ToLastLocation = GetLastLocation(To,ToArraySize) + 1;
			UnplayedFaceUpCardsShowing = theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].UnplayedFaceUpCardsShowing;
			TimeThroughDeck = theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].TimeThroughDeck;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ActionID = -1;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded = -1;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionStarted = -1;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].UnplayedFaceUpCardsShowing = -1;
			theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].TimeThroughDeck = -1;
			if ((FromColumnID == UNPLAYEDFACEUPCARDSCOLUMNID || FromColumnID == UNPLAYEDFACEDOWNCARDSCOLUMNID) && (ToColumnID == UNPLAYEDFACEUPCARDSCOLUMNID || ToColumnID == UNPLAYEDFACEDOWNCARDSCOLUMNID))
			{
				// we have to reverse the undo
				for (j = 0; j < CARDMAX; j++)
				{
					if (theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[j] == -1)
					{
						j--;
						break;
					}
				}
				for (;i < FromArraySize; i++)
				{
					if (From[i].card == -1  || j < 0)
					{
						break;
					}
					To[ToLastLocation].card = theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[j];
					To[ToLastLocation].faceup = From[i + j].faceup;
					From[i].card = -1;
					From[i].faceup = false;
					theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[j] = -1;
					j--;
					ToLastLocation++;
				}
			}
			else
			{
				for (;i < FromArraySize; i++)
				{
					if (From[i].card == -1  || theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[j] == -1)
					{
						break;
					}
					To[ToLastLocation + j].card = From[i].card;
					To[ToLastLocation + j].faceup = From[i].faceup;
					From[i].card = -1;
					From[i].faceup = false;
					theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[j] = -1;
					if (FromColumnID == ACECOLONECARDSCOLUMNID || FromColumnID == ACECOLTWOCARDSCOLUMNID || FromColumnID == ACECOLTHREECARDSCOLUMNID || FromColumnID == ACECOLFOURCARDSCOLUMNID)
					{
						// lose our score
						Paint_Score = true;
						TheCurrentScore -= 5;
						BaseScore -= 5;
					}
					j++;
				}
			}
		}
		theUndoStack->CurrentUndoStackLocation--;
	}
	if (theUndoStack->CurrentActionID < 0 || theUndoStack->CurrentUndoStackLocation < 0)
	{
		// then we tried to undo pass the last undo
		theUndoStack->CurrentActionID = 0;
		theUndoStack->CurrentUndoStackLocation = 0;
	}
	else
	{
		theUndoStack->CurrentUndoStackLocation++;
	}
	return rtnval;
}

int CDrawScreen::GetColumnArraySize(int ColumnID)
{
	int ColumnArraySize = 0;
	switch (ColumnID)
	{
		case GAMECOLONECOLUMNID:
			ColumnArraySize = GAMEROWMAX;
			break;
		case GAMECOLTWOCOLUMNID:
			ColumnArraySize = GAMEROWMAX;
			break;
		case GAMECOLTHREECOLUMNID:
			ColumnArraySize = GAMEROWMAX;
			break;
		case GAMECOLFOURCOLUMNID:
			ColumnArraySize = GAMEROWMAX;
			break;
		case GAMECOLFIVECOLUMNID:
			ColumnArraySize = GAMEROWMAX;
			break;
		case GAMECOLSIXCOLUMNID:
			ColumnArraySize = GAMEROWMAX;
			break;
		case GAMECOLSEVENCOLUMNID:
			ColumnArraySize = GAMEROWMAX;
			break;
		case ACECOLONECARDSCOLUMNID:
			ColumnArraySize = CARDSINSUITE;
			break;
		case ACECOLTWOCARDSCOLUMNID:
			ColumnArraySize = CARDSINSUITE;
			break;
		case ACECOLTHREECARDSCOLUMNID:
			ColumnArraySize = CARDSINSUITE;
			break;
		case ACECOLFOURCARDSCOLUMNID:
			ColumnArraySize = CARDSINSUITE;
			break;
		case UNPLAYEDFACEUPCARDSCOLUMNID:
			ColumnArraySize = CARDMAX;
			break;
		case UNPLAYEDFACEDOWNCARDSCOLUMNID:
			ColumnArraySize = CARDMAX;
			break;
	}
	return ColumnArraySize;
}

CARDS * CDrawScreen::GetPointerToColumn(int ColumnID)
{
	CARDS *pGameRow = NULL;
	switch (ColumnID)
	{
		case GAMECOLONECOLUMNID:
			pGameRow = theDeck->gamecolone;
			break;
		case GAMECOLTWOCOLUMNID:
			pGameRow = theDeck->gamecoltwo;
			break;
		case GAMECOLTHREECOLUMNID:
			pGameRow = theDeck->gamecolthree;
			break;
		case GAMECOLFOURCOLUMNID:
			pGameRow = theDeck->gamecolfour;
			break;
		case GAMECOLFIVECOLUMNID:
			pGameRow = theDeck->gamecolfive;
			break;
		case GAMECOLSIXCOLUMNID:
			pGameRow = theDeck->gamecolsix;
			break;
		case GAMECOLSEVENCOLUMNID:
			pGameRow = theDeck->gamecolseven;
			break;
		case ACECOLONECARDSCOLUMNID:
			pGameRow = theDeck->acecolonecards;
			break;
		case ACECOLTWOCARDSCOLUMNID:
			pGameRow = theDeck->acecoltwocards;
			break;
		case ACECOLTHREECARDSCOLUMNID:
			pGameRow = theDeck->acecolthreecards;
			break;
		case ACECOLFOURCARDSCOLUMNID:
			pGameRow = theDeck->acecolfourcards;
			break;
		case UNPLAYEDFACEUPCARDSCOLUMNID:
			pGameRow = theDeck->unplayedfaceupcards;
			break;
		case UNPLAYEDFACEDOWNCARDSCOLUMNID:
			pGameRow = theDeck->unplayedfacedowncards;
			break;
	}
	return pGameRow;
}

bool CDrawScreen::PlayWhatYouCanOnRightButtonClick()
{
	bool MadeAPlay = true;
	bool rtnval = false;
	int LastCardID;
	int LastCardLocation;
	int pPlayOnAceColumn;

	SetNewAceColumnValues();

	while (MadeAPlay == true)
	{
		MadeAPlay = false;
		// get unplayed face up card
		LastCardLocation = GetLastLocation(theDeck->unplayedfaceupcards, CARDMAX);
		LastCardID = theDeck->unplayedfaceupcards[LastCardLocation].card;
		pPlayOnAceColumn = SeeIfCardCanPlay(LastCardID);
		if (pPlayOnAceColumn != -1)
		{
			MoveCardToAceColumn(UNPLAYEDFACEUPCARDSCOLUMNID, pPlayOnAceColumn);
			SetPaintBasedOnColumnID(UNPLAYEDFACEUPCARDSCOLUMNID);
			SetPaintBasedOnColumnID(pPlayOnAceColumn);
			SetNewAceColumnValues();
			UnplayedFaceUpCardsShowing--;
			if (UnplayedFaceUpCardsShowing < 1)
			{
				UnplayedFaceUpCardsShowing = 1;
			}
			MadeAPlay = true;
			rtnval = true;
		}
		LastCardLocation = GetLastLocation(theDeck->gamecolone, GAMEROWMAX);
		LastCardID = theDeck->gamecolone[LastCardLocation].card;
		pPlayOnAceColumn = SeeIfCardCanPlay(LastCardID);
		if (pPlayOnAceColumn != -1)
		{
			MoveCardToAceColumn(GAMECOLONECOLUMNID, pPlayOnAceColumn);
			SetPaintBasedOnColumnID(GAMECOLONECOLUMNID);
			SetPaintBasedOnColumnID(pPlayOnAceColumn);
			SetNewAceColumnValues();
			MadeAPlay = true;
			rtnval = true;
		}
		LastCardLocation = GetLastLocation(theDeck->gamecoltwo, GAMEROWMAX);
		LastCardID = theDeck->gamecoltwo[LastCardLocation].card;
		pPlayOnAceColumn = SeeIfCardCanPlay(LastCardID);
		if (pPlayOnAceColumn != -1)
		{
			MoveCardToAceColumn(GAMECOLTWOCOLUMNID, pPlayOnAceColumn);
			SetPaintBasedOnColumnID(GAMECOLTWOCOLUMNID);
			SetPaintBasedOnColumnID(pPlayOnAceColumn);
			SetNewAceColumnValues();
			MadeAPlay = true;
			rtnval = true;
		}
		LastCardLocation = GetLastLocation(theDeck->gamecolthree, GAMEROWMAX);
		LastCardID = theDeck->gamecolthree[LastCardLocation].card;
		pPlayOnAceColumn = SeeIfCardCanPlay(LastCardID);
		if (pPlayOnAceColumn != -1)
		{
			MoveCardToAceColumn(GAMECOLTHREECOLUMNID, pPlayOnAceColumn);
			SetPaintBasedOnColumnID(GAMECOLTHREECOLUMNID);
			SetPaintBasedOnColumnID(pPlayOnAceColumn);
			SetNewAceColumnValues();
			MadeAPlay = true;
			rtnval = true;
		}
		LastCardLocation = GetLastLocation(theDeck->gamecolfour, GAMEROWMAX);
		LastCardID = theDeck->gamecolfour[LastCardLocation].card;
		pPlayOnAceColumn = SeeIfCardCanPlay(LastCardID);
		if (pPlayOnAceColumn != -1)
		{
			MoveCardToAceColumn(GAMECOLFOURCOLUMNID, pPlayOnAceColumn);
			SetPaintBasedOnColumnID(GAMECOLFOURCOLUMNID);
			SetPaintBasedOnColumnID(pPlayOnAceColumn);
			SetNewAceColumnValues();
			MadeAPlay = true;
			rtnval = true;
		}
		LastCardLocation = GetLastLocation(theDeck->gamecolfive, GAMEROWMAX);
		LastCardID = theDeck->gamecolfive[LastCardLocation].card;
		pPlayOnAceColumn = SeeIfCardCanPlay(LastCardID);
		if (pPlayOnAceColumn != -1)
		{
			MoveCardToAceColumn(GAMECOLFIVECOLUMNID, pPlayOnAceColumn);
			SetPaintBasedOnColumnID(GAMECOLFIVECOLUMNID);
			SetPaintBasedOnColumnID(pPlayOnAceColumn);
			SetNewAceColumnValues();
			MadeAPlay = true;
			rtnval = true;
		}
		LastCardLocation = GetLastLocation(theDeck->gamecolsix, GAMEROWMAX);
		LastCardID = theDeck->gamecolsix[LastCardLocation].card;
		pPlayOnAceColumn = SeeIfCardCanPlay(LastCardID);
		if (pPlayOnAceColumn != -1)
		{
			MoveCardToAceColumn(GAMECOLSIXCOLUMNID, pPlayOnAceColumn);
			SetPaintBasedOnColumnID(GAMECOLSIXCOLUMNID);
			SetPaintBasedOnColumnID(pPlayOnAceColumn);
			SetNewAceColumnValues();
			MadeAPlay = true;
			rtnval = true;
		}
		LastCardLocation = GetLastLocation(theDeck->gamecolseven, GAMEROWMAX);
		LastCardID = theDeck->gamecolseven[LastCardLocation].card;
		pPlayOnAceColumn = SeeIfCardCanPlay(LastCardID);
		if (pPlayOnAceColumn != -1)
		{
			MoveCardToAceColumn(GAMECOLSEVENCOLUMNID, pPlayOnAceColumn);
			SetPaintBasedOnColumnID(GAMECOLSEVENCOLUMNID);
			SetPaintBasedOnColumnID(pPlayOnAceColumn);
			SetNewAceColumnValues();
			MadeAPlay = true;
			rtnval = true;
		}
	}
	return rtnval;
}

void CDrawScreen::MoveCardToAceColumn(int FromColumnID, int ToColumnID)
{
	CARDS * From;
	int FromSize;
	int FromLastCard;

	CARDS * To;
	int ToSize;
	int ToLastCard;

	SourceColumnID = FromColumnID;
	DestinationColumnID = ToColumnID;

	theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ActionID = theUndoStack->CurrentActionID;
	theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionEnded = ToColumnID;
	theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].ColumnIDWhereGameActionStarted = FromColumnID;
	theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].UnplayedFaceUpCardsShowing = UnplayedFaceUpCardsShowing;
	theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].TimeThroughDeck = TimeThroughDeck;


	From = GetPointerToColumn(FromColumnID);
	FromSize = GetColumnArraySize(FromColumnID);
	FromLastCard = GetLastLocation(From, FromSize);

	To = GetPointerToColumn(ToColumnID);
	ToSize = GetColumnArraySize(ToColumnID);
	ToLastCard = GetLastLocation(To, ToSize);

	To[ToLastCard + 1].card = From[FromLastCard].card;
	To[ToLastCard + 1].faceup = true;
	theUndoStack->UndoStack[theUndoStack->CurrentUndoStackLocation].CardID[0] = From[FromLastCard].card;
	theUndoStack->CurrentUndoStackLocation++;
	Paint_Score = true;
	TheCurrentScore += 5;
	BaseScore += 5;
	From[FromLastCard].card = -1;
	From[FromLastCard].faceup = false;
	FlipTopCardAfterMove();
	theUndoStack->CurrentActionID++;
}

void CDrawScreen::SetNewAceColumnValues()
{
	AceColumn1Location = GetLastLocation(theDeck->acecolonecards, CARDSINSUITE);
	AceColumn1CardID = theDeck->acecolonecards[AceColumn1Location].card;

	AceColumn2Location = GetLastLocation(theDeck->acecoltwocards, CARDSINSUITE);
	AceColumn2CardID = theDeck->acecoltwocards[AceColumn2Location].card;

	AceColumn3Location = GetLastLocation(theDeck->acecolthreecards, CARDSINSUITE);
	AceColumn3CardID = theDeck->acecolthreecards[AceColumn3Location].card;

	AceColumn4Location = GetLastLocation(theDeck->acecolfourcards, CARDSINSUITE);
	AceColumn4CardID = theDeck->acecolfourcards[AceColumn4Location].card;
}

int CDrawScreen::SeeIfCardCanPlay(int LastCardID)
{
	if (LastCardID == ACEOFSPADES || LastCardID == ACEOFDIAMONDS || LastCardID == ACEOFCLUBS || LastCardID == ACEOFHEARTS)
	{
		if (AceColumn1CardID == -1)
		{
			return ACECOLONECARDSCOLUMNID;
		}
		if (AceColumn2CardID == -1)
		{
			return ACECOLTWOCARDSCOLUMNID;
		}
		if (AceColumn3CardID == -1)
		{
			return ACECOLTHREECARDSCOLUMNID;
		}
		if (AceColumn4CardID == -1)
		{
			return ACECOLFOURCARDSCOLUMNID;
		}
	}
	if (AceColumn1CardID != KINGOFSPADES && AceColumn1CardID != KINGOFDIAMONDS && AceColumn1CardID != KINGOFCLUBS && AceColumn1CardID != KINGOFHEARTS)
	{
		if ((AceColumn1CardID + 1) == LastCardID)
		{
			return ACECOLONECARDSCOLUMNID;
		}
	}
	if (AceColumn2CardID != KINGOFSPADES && AceColumn2CardID != KINGOFDIAMONDS && AceColumn2CardID != KINGOFCLUBS && AceColumn2CardID != KINGOFHEARTS)
	{
		if ((AceColumn2CardID + 1) == LastCardID)
		{
			return ACECOLTWOCARDSCOLUMNID;
		}
	}
	if (AceColumn3CardID != KINGOFSPADES && AceColumn3CardID != KINGOFDIAMONDS && AceColumn3CardID != KINGOFCLUBS && AceColumn3CardID != KINGOFHEARTS)
	{
		if ((AceColumn3CardID + 1) == LastCardID)
		{
			return ACECOLTHREECARDSCOLUMNID;
		}
	}
	if (AceColumn4CardID != KINGOFSPADES && AceColumn4CardID != KINGOFDIAMONDS && AceColumn4CardID != KINGOFCLUBS && AceColumn4CardID != KINGOFHEARTS)
	{
		if ((AceColumn4CardID + 1) == LastCardID)
		{
			return ACECOLFOURCARDSCOLUMNID;
		}
	}
	return -1;
}

void CDrawScreen::DumpUndo()
{
	FILE *outfile;
	int i;

	SetupCardNameArray();

	fopen_s(&outfile, _T("DumpUndo.dat"),"w");

	//SUNDO UndoStack[MAXUNDOACTIONS];
	for (i = 0; i < MAXUNDOACTIONS; i++)
	{
		if (theUndoStack->UndoStack[i].ColumnIDWhereGameActionStarted != -1)
		{
			fprintf(outfile, "The UndoStack\n");
			//CARDS unplayedfacedowncards[CARDMAX];
			fprintf(outfile, "%d ColumnIDWhereGameActionStarted %s\n", i, &ColumnNames[theUndoStack->UndoStack[i].ColumnIDWhereGameActionStarted][0]);
			fprintf(outfile, "%d ColumnIDWhereGameActionEnded %s\n", i, &ColumnNames[theUndoStack->UndoStack[i].ColumnIDWhereGameActionEnded][0]);
			fprintf(outfile, "%d ActionID %d\n", i, theUndoStack->UndoStack[i].ActionID);
			fprintf(outfile, "%d UnplayedFaceUpCardsShowing %d\n", i, theUndoStack->UndoStack[i].UnplayedFaceUpCardsShowing);
			fprintf(outfile, "%d TimeThroughDeck %d\n", i, theUndoStack->UndoStack[i].TimeThroughDeck);
			for (int j = 0; j < CARDMAX; j++)
			{
				if (theUndoStack->UndoStack[i].CardID[j] > 0)
				{
					fprintf(outfile, "%d CardID %s\n", j, &CardNames[theUndoStack->UndoStack[i].CardID[j]][0]);
				}
				else
				{
					//fprintf(outfile, "%d CardID -1\n", j);
				}
			}
			fprintf(outfile, "\n\n");
		}
	}

	//CDragStack *theDragStack;
	fprintf(outfile, "\n\nThe DragStack\n");
	for (i = 0; i < CARDSINSUITE; i++)
	{
		if (theDragStack->CardsInStack[i] > 0)
		{
			fprintf(outfile, "%d CardsInStack %s\n", i, &CardNames[theDragStack->CardsInStack[i]][0]);
		}
		else
		{
			//fprintf(outfile, "%d CardsInStack -1\n", i);
		}
	}

	//CARDS unplayedfacedowncards[CARDMAX];
	fprintf(outfile, "\n\nUnplayedFaceDownCards\n");
	for (i = 0; i < CARDMAX; i++)
	{
		if (theDeck->unplayedfacedowncards[i].card > 0)
		{
			fprintf(outfile, "%d card %s    ", i, &CardNames[theDeck->unplayedfacedowncards[i].card][0]);
			if (theDeck->unplayedfacedowncards[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}
		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	//CARDS unplayedfaceupcards[CARDMAX];
	fprintf(outfile, "\n\nUnplayedFaceUpCards\n");
	for (i = 0; i < CARDMAX; i++)
	{
		if (theDeck->unplayedfaceupcards[i].card > 0)
		{
			fprintf(outfile, "%d card %s    ", i, &CardNames[theDeck->unplayedfaceupcards[i].card][0]);
			if (theDeck->unplayedfaceupcards[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}
		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	//CARDS acecolonecards[CARDSINSUITE];
	fprintf(outfile, "\n\nacecolonecards\n");
	for (i = 0; i < CARDSINSUITE; i++)
	{
		if (theDeck->acecolonecards[i].card > 0)
		{
			fprintf(outfile, "%d card %s    ", i, &CardNames[theDeck->acecolonecards[i].card][0]);
			if (theDeck->acecolonecards[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}
		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	//CARDS acecoltwocards[CARDSINSUITE];
	fprintf(outfile, "\n\nacecoltwocards\n");
	for (i = 0; i < CARDSINSUITE; i++)
	{
		if (theDeck->acecoltwocards[i].card > 0)
		{
			fprintf(outfile, "%d card %s    ", i, &CardNames[theDeck->acecoltwocards[i].card][0]);
			if (theDeck->acecoltwocards[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}
		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	//CARDS acecolthreecards[CARDSINSUITE];
	fprintf(outfile, "\n\nacecolthreecards\n");
	for (i = 0; i < CARDSINSUITE; i++)
	{
		if (theDeck->acecolthreecards[i].card > 0)
		{
			fprintf(outfile, "%d card %s    ", i, &CardNames[theDeck->acecolthreecards[i].card][0]);
			if (theDeck->acecolthreecards[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}
		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	//CARDS acecolfourcards[CARDSINSUITE];
	fprintf(outfile, "\n\nacecolfourcards\n");
	for (i = 0; i < CARDSINSUITE; i++)
	{
		if (theDeck->acecolfourcards[i].card > 0)
		{
			fprintf(outfile, "%d card %s    ", i, &CardNames[theDeck->acecolfourcards[i].card][0]);
			if (theDeck->acecolfourcards[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}
		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	//CARDS gamecolone[GAMEROWMAX];
	fprintf(outfile, "\n\ngamecolone\n");
	for (i = 0; i < GAMEROWMAX; i++)
	{
		if (theDeck->gamecolone[i].card > 0)
		{
			fprintf(outfile, "%d card %s    ", i, &CardNames[theDeck->gamecolone[i].card][0]);
			if (theDeck->gamecolone[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}
		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	//CARDS gamecoltwo[GAMEROWMAX];
	fprintf(outfile, "\n\ngamecoltwo\n");
	for (i = 0; i < GAMEROWMAX; i++)
	{
		if (theDeck->gamecoltwo[i].card > 0)
		{
			fprintf(outfile, "%d card %s    ", i, &CardNames[theDeck->gamecoltwo[i].card][0]);
			if (theDeck->gamecoltwo[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	//CARDS gamecolthree[GAMEROWMAX];
	fprintf(outfile, "\n\ngamecolthree\n");
	for (i = 0; i < GAMEROWMAX; i++)
	{
		if (theDeck->gamecolthree[i].card > 0)
		{
			fprintf(outfile, "%d card %s    ", i, &CardNames[theDeck->gamecolthree[i].card][0]);
			if (theDeck->gamecolthree[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}
		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	//CARDS gamecolfour[GAMEROWMAX];
	fprintf(outfile, "\n\ngamecolfour\n");
	for (i = 0; i < GAMEROWMAX; i++)
	{
		if (theDeck->gamecolfour[i].card > 0)
		{
			fprintf(outfile, "%d card %s    ", i, &CardNames[theDeck->gamecolfour[i].card][0]);
			if (theDeck->gamecolfour[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}
		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	//CARDS gamecolfive[GAMEROWMAX];
	fprintf(outfile, "\n\ngamecolfive\n");
	for (i = 0; i < GAMEROWMAX; i++)
	{
		if (theDeck->gamecolfive[i].card > 0)
		{
			fprintf(outfile, "%d card %s    ", i, &CardNames[theDeck->gamecolfive[i].card][0]);
			if (theDeck->gamecolfive[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}
		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	//CARDS gamecolsix[GAMEROWMAX];
	fprintf(outfile, "\n\ngamecolsix\n");
	for (i = 0; i < GAMEROWMAX; i++)
	{
		if (theDeck->gamecolsix[i].card > 0)
		{
			fprintf(outfile, "%d card %s    ", i, &CardNames[theDeck->gamecolsix[i].card][0]);
			if (theDeck->gamecolsix[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}
		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	//CARDS gamecolseven[GAMEROWMAX];
	fprintf(outfile, "\n\ngamecolseven\n");
	for (i = 0; i < GAMEROWMAX; i++)
	{
		if (theDeck->gamecolseven[i].card > 0)
		{
			fprintf(outfile, "%d card %s   ", i, &CardNames[theDeck->gamecolseven[i].card][0]);
			if (theDeck->gamecolseven[i].faceup == true)
			{
				fprintf(outfile, "faceup = true\n");
			}
			else
			{
				fprintf(outfile, "faceup = false\n");
			}
		}
		else
		{
			//fprintf(outfile, "%d card -1\n", i);
		}
	}

	fclose(outfile);
}

void CDrawScreen::SetupCardNameArray()
{
	sprintf_s(&ColumnNames[0][0], 1, "");
	sprintf_s(&ColumnNames[1][0], 31, "UNPLAYED FACEUP CARDS COLUMNID");
	sprintf_s(&ColumnNames[2][0], 26, "ACECOL ONE CARDS COLUMNID");
	sprintf_s(&ColumnNames[3][0], 26, "ACECOL TWO CARDS COLUMNID");
	sprintf_s(&ColumnNames[4][0], 28, "ACECOL THREE CARDS COLUMNID");
	sprintf_s(&ColumnNames[5][0], 27, "ACECOL FOUR CARDS COLUMNID");
	sprintf_s(&ColumnNames[6][0], 21, "GAMECOL ONE COLUMNID");
	sprintf_s(&ColumnNames[7][0], 21, "GAMECOL TWO COLUMNID");
	sprintf_s(&ColumnNames[8][0], 23, "GAMECOL THREE COLUMNID");
	sprintf_s(&ColumnNames[9][0], 22, "GAMECOL FOUR COLUMNID");
	sprintf_s(&ColumnNames[10][0], 22, "GAMECOL FIVE COLUMNID");
	sprintf_s(&ColumnNames[11][0], 21, "GAMECOL SIX COLUMNID");
	sprintf_s(&ColumnNames[12][0], 23, "GAMECOL SEVEN COLUMNID");
	sprintf_s(&ColumnNames[13][0], 18, "LONGHORN COLUMNID");
	sprintf_s(&ColumnNames[14][0], 33, "UNPLAYED FACEDOWN CARDS COLUMNID");



	sprintf_s(&CardNames[0][0], 1, "");
	sprintf_s(&CardNames[1][0], 14, "ACE OF SPADES");
	sprintf_s(&CardNames[2][0], 14, "TWO OF SPADES");
	sprintf_s(&CardNames[3][0], 16, "THREE OF SPADES");
	sprintf_s(&CardNames[4][0], 15, "FOUR OF SPADES");
	sprintf_s(&CardNames[5][0], 15, "FIVE OF SPADES");
	sprintf_s(&CardNames[6][0], 14, "SIX OF SPADES");
	sprintf_s(&CardNames[7][0], 16, "SEVEN OF SPADES");
	sprintf_s(&CardNames[8][0], 16, "EIGHT OF SPADES");
	sprintf_s(&CardNames[9][0], 15, "NINE OF SPADES");
	sprintf_s(&CardNames[10][0], 14, "TEN OF SPADES");
	sprintf_s(&CardNames[11][0], 15, "JACK OF SPADES");
	sprintf_s(&CardNames[12][0], 16, "QUEEN OF SPADES");
	sprintf_s(&CardNames[13][0], 15, "KING OF SPADES");
	sprintf_s(&CardNames[14][0], 16, "ACE OF DIAMONDS");
	sprintf_s(&CardNames[15][0], 16, "TWO OF DIAMONDS");
	sprintf_s(&CardNames[16][0], 18, "THREE OF DIAMONDS");
	sprintf_s(&CardNames[17][0], 17, "FOUR OF DIAMONDS");
	sprintf_s(&CardNames[18][0], 17, "FIVE OF DIAMONDS");
	sprintf_s(&CardNames[19][0], 16, "SIX OF DIAMONDS");
	sprintf_s(&CardNames[20][0], 18, "SEVEN OF DIAMONDS");
	sprintf_s(&CardNames[21][0], 18, "EIGHT OF DIAMONDS");
	sprintf_s(&CardNames[22][0], 17, "NINE OF DIAMONDS");
	sprintf_s(&CardNames[23][0], 16, "TEN OF DIAMONDS");
	sprintf_s(&CardNames[24][0], 17, "JACK OF DIAMONDS");
	sprintf_s(&CardNames[25][0], 18, "QUEEN OF DIAMONDS");
	sprintf_s(&CardNames[26][0], 17, "KING OF DIAMONDS");
	sprintf_s(&CardNames[27][0], 13, "ACE OF CLUBS");
	sprintf_s(&CardNames[28][0], 13, "TWO OF CLUBS");
	sprintf_s(&CardNames[29][0], 15, "THREE OF CLUBS");
	sprintf_s(&CardNames[30][0], 14, "FOUR OF CLUBS");
	sprintf_s(&CardNames[31][0], 14, "FIVE OF CLUBS");
	sprintf_s(&CardNames[32][0], 13, "SIX OF CLUBS");
	sprintf_s(&CardNames[33][0], 15, "SEVEN OF CLUBS");
	sprintf_s(&CardNames[34][0], 15, "EIGHT OF CLUBS");
	sprintf_s(&CardNames[35][0], 14, "NINE OF CLUBS");
	sprintf_s(&CardNames[36][0], 13, "TEN OF CLUBS");
	sprintf_s(&CardNames[37][0], 14, "JACK OF CLUBS");
	sprintf_s(&CardNames[38][0], 15, "QUEEN OF CLUBS");
	sprintf_s(&CardNames[39][0], 14, "KING OF CLUBS");
	sprintf_s(&CardNames[40][0], 14, "ACE OF HEARTS");
	sprintf_s(&CardNames[41][0], 14, "TWO OF HEARTS");
	sprintf_s(&CardNames[42][0], 16, "THREE OF HEARTS");
	sprintf_s(&CardNames[43][0], 15, "FOUR OF HEARTS");
	sprintf_s(&CardNames[44][0], 15, "FIVE OF HEARTS");
	sprintf_s(&CardNames[45][0], 14, "SIX OF HEARTS");
	sprintf_s(&CardNames[46][0], 16, "SEVEN OF HEARTS");
	sprintf_s(&CardNames[47][0], 16, "EIGHT OF HEARTS");
	sprintf_s(&CardNames[48][0], 15, "NINE OF HEARTS");
	sprintf_s(&CardNames[49][0], 14, "TEN OF HEARTS");
	sprintf_s(&CardNames[50][0], 15, "JACK OF HEARTS");
	sprintf_s(&CardNames[51][0], 16, "QUEEN OF HEARTS");
	sprintf_s(&CardNames[52][0], 15, "KING OF HEARTS");
}

bool CDrawScreen::SaveData()
{
	int i;

	CFile cfile;
	if (cfile.Open(_T("ETSolSavedData.dat"), CFile::modeCreate | CFile::modeReadWrite) == 0)
	{
		return false;
	}
	
	int DrawScreenValues[16];
	
	DrawScreenValues[0] = TimeThroughDeck;
	DrawScreenValues[1] = UnPlayedFaceUpCardsDisplayCount;
	DrawScreenValues[2] = UnplayedFaceUpCardsShowing;
	DrawScreenValues[3] = TheCurrentScore;
	DrawScreenValues[4] = DoubleSpaceCard.ColumnID;
	DrawScreenValues[5] = DoubleSpaceCard.RowID;

	// Row Column information
	DrawScreenValues[6] = SourceColumnID;
	DrawScreenValues[7] = DestinationColumnID;
	DrawScreenValues[8] = AceColumn1Location;
	DrawScreenValues[9] = AceColumn1CardID;
	DrawScreenValues[10] = AceColumn2Location;
	DrawScreenValues[11] = AceColumn2CardID;
	DrawScreenValues[12] = AceColumn3Location;
	DrawScreenValues[13] = AceColumn3CardID;
	DrawScreenValues[14] = AceColumn4Location;
	DrawScreenValues[15] = AceColumn4CardID;

	cfile.Write(DrawScreenValues, sizeof(int) * 16);         
	cfile.Flush();

	//CDragStack *theDragStack;
	long DragStackValues[8];
	DragStackValues[0] = theDragStack->StackLocation.x;
	DragStackValues[1] = theDragStack->StackLocation.y;
	DragStackValues[2] = theDragStack->OldStackLocation.x;
	DragStackValues[3] = theDragStack->OldStackLocation.y;
	DragStackValues[4] = theDragStack->StackSize.cx;
	DragStackValues[5] = theDragStack->StackSize.cy;
	DragStackValues[6] = theDragStack->MouseOffset.cx;
	DragStackValues[7] = theDragStack->MouseOffset.cy;
	cfile.Write(DragStackValues, sizeof(long) * 8);         
	cfile.Flush();

	for (i = 0; i < CARDSINSUITE; i++)
	{
		cfile.Write(&theDragStack->CardsInStack[i], sizeof(int));         
	}
	cfile.Flush();

	//CUNDO *theUndoStack;
	DrawScreenValues[0] = theUndoStack->CurrentUndoStackLocation;
	DrawScreenValues[1] = theUndoStack->CurrentActionID;
	cfile.Write(DrawScreenValues, sizeof(int) * 2);         
	cfile.Flush();

	//SUNDO UndoStack[MAXUNDOACTIONS];
	for (i = 0; i < MAXUNDOACTIONS; i++)
	{
		//CARDS unplayedfacedowncards[CARDMAX];
		cfile.Write(&theUndoStack->UndoStack[i].ColumnIDWhereGameActionStarted, sizeof(int));
		cfile.Write(&theUndoStack->UndoStack[i].ColumnIDWhereGameActionEnded, sizeof(int));
		cfile.Write(&theUndoStack->UndoStack[i].ActionID, sizeof(int));
		cfile.Write(&theUndoStack->UndoStack[i].UnplayedFaceUpCardsShowing, sizeof(int));
		cfile.Write(&theUndoStack->UndoStack[i].TimeThroughDeck, sizeof(int));
		for (int j = 0; j < CARDMAX; j++)
		{
			cfile.Write(&theUndoStack->UndoStack[i].CardID[j], sizeof(int));
		}
	}
	cfile.Flush();

	//Cdeck *theDeck;
	//int deck[CARDMAX];
	cfile.Write(theDeck->deck, sizeof(int) * CARDMAX);         
	cfile.Flush();

	for (i = 0; i < CARDMAX; i++)
	{
		//CARDS unplayedfacedowncards[CARDMAX];
		cfile.Write(&theDeck->unplayedfacedowncards[i].card, sizeof(int));
		cfile.Write(&theDeck->unplayedfacedowncards[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	for (i = 0; i < CARDMAX; i++)
	{
		//CARDS unplayedfaceupcards[CARDMAX];
		cfile.Write(&theDeck->unplayedfaceupcards[i].card, sizeof(int));
		cfile.Write(&theDeck->unplayedfaceupcards[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	for (i = 0; i < CARDSINSUITE; i++)
	{
		//CARDS acecolonecards[CARDSINSUITE];
		cfile.Write(&theDeck->acecolonecards[i].card, sizeof(int));
		cfile.Write(&theDeck->acecolonecards[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	for (i = 0; i < CARDSINSUITE; i++)
	{
		//CARDS acecoltwocards[CARDSINSUITE];
		cfile.Write(&theDeck->acecoltwocards[i].card, sizeof(int));
		cfile.Write(&theDeck->acecoltwocards[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	for (i = 0; i < CARDSINSUITE; i++)
	{
		//CARDS acecolthreecards[CARDSINSUITE];
		cfile.Write(&theDeck->acecolthreecards[i].card, sizeof(int));
		cfile.Write(&theDeck->acecolthreecards[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	for (i = 0; i < CARDSINSUITE; i++)
	{
		//CARDS acecolfourcards[CARDSINSUITE];
		cfile.Write(&theDeck->acecolfourcards[i].card, sizeof(int));
		cfile.Write(&theDeck->acecolfourcards[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecolone[GAMEROWMAX];
		cfile.Write(&theDeck->gamecolone[i].card, sizeof(int));
		cfile.Write(&theDeck->gamecolone[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecoltwo[GAMEROWMAX];
		cfile.Write(&theDeck->gamecoltwo[i].card, sizeof(int));
		cfile.Write(&theDeck->gamecoltwo[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecolthree[GAMEROWMAX];
		cfile.Write(&theDeck->gamecolthree[i].card, sizeof(int));
		cfile.Write(&theDeck->gamecolthree[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecolfour[GAMEROWMAX];
		cfile.Write(&theDeck->gamecolfour[i].card, sizeof(int));
		cfile.Write(&theDeck->gamecolfour[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecolfive[GAMEROWMAX];
		cfile.Write(&theDeck->gamecolfive[i].card, sizeof(int));
		cfile.Write(&theDeck->gamecolfive[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecolsix[GAMEROWMAX];
		cfile.Write(&theDeck->gamecolsix[i].card, sizeof(int));
		cfile.Write(&theDeck->gamecolsix[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecolseven[GAMEROWMAX];
		cfile.Write(&theDeck->gamecolseven[i].card, sizeof(int));
		cfile.Write(&theDeck->gamecolseven[i].faceup, sizeof(bool));
	}
	cfile.Flush();

	cfile.Write(&BaseScore, sizeof(int));
	cfile.Write(&GamesWon, sizeof(int));
	cfile.Write(&GamesPlayed, sizeof(int));
	cfile.Flush();

	cfile.Close();
	return true;
}

bool CDrawScreen::LoadData()
{
	int i;
	CFile cfile;
	ULONGLONG dwLength;

	if (cfile.Open(_T("ETSolSavedData.dat"), CFile::modeRead) == 0)
	{
		return false;
	}
	cfile.SeekToBegin();
	dwLength = cfile.GetLength();

	int DrawScreenValues[256];
	cfile.Read(DrawScreenValues, sizeof(int) * 16);         

	TimeThroughDeck = DrawScreenValues[0];
	UnPlayedFaceUpCardsDisplayCount = DrawScreenValues[1];
	UnplayedFaceUpCardsShowing = DrawScreenValues[2];
	TheCurrentScore = DrawScreenValues[3];
	DoubleSpaceCard.ColumnID = DrawScreenValues[4];
	DoubleSpaceCard.RowID = DrawScreenValues[5];

	// Row Column information
	SourceColumnID = DrawScreenValues[6];
	DestinationColumnID = DrawScreenValues[7];
	AceColumn1Location = DrawScreenValues[8];
	AceColumn1CardID = DrawScreenValues[9];
	AceColumn2Location = DrawScreenValues[10];
	AceColumn2CardID = DrawScreenValues[11];
	AceColumn3Location = DrawScreenValues[12];
	AceColumn3CardID = DrawScreenValues[13];
	AceColumn4Location = DrawScreenValues[14];
	AceColumn4CardID = DrawScreenValues[15];


	//CDragStack *theDragStack;
	long DragStackValues[256];
	cfile.Read(DragStackValues, sizeof(long) * 8);         
	theDragStack->StackLocation.x = DragStackValues[0];
	theDragStack->StackLocation.y = DragStackValues[1];
	theDragStack->OldStackLocation.x = DragStackValues[2];
	theDragStack->OldStackLocation.y = DragStackValues[3];
	theDragStack->StackSize.cx = DragStackValues[4];
	theDragStack->StackSize.cy = DragStackValues[5];
	theDragStack->MouseOffset.cx = DragStackValues[6];
	theDragStack->MouseOffset.cy = DragStackValues[7];

	for (i = 0; i < CARDSINSUITE; i++)
	{
		cfile.Read(&theDragStack->CardsInStack[i], sizeof(int));         
	}

	//CUNDO *theUndoStack;
	cfile.Read(DrawScreenValues, sizeof(int) * 2);         
	theUndoStack->CurrentUndoStackLocation = DrawScreenValues[0];
	theUndoStack->CurrentActionID = DrawScreenValues[1];

	//SUNDO UndoStack[MAXUNDOACTIONS];
	for (i = 0; i < MAXUNDOACTIONS; i++)
	{
		//CARDS unplayedfacedowncards[CARDMAX];
		cfile.Read(&theUndoStack->UndoStack[i].ColumnIDWhereGameActionStarted, sizeof(int));
		cfile.Read(&theUndoStack->UndoStack[i].ColumnIDWhereGameActionEnded, sizeof(int));
		cfile.Read(&theUndoStack->UndoStack[i].ActionID, sizeof(int));
		cfile.Read(&theUndoStack->UndoStack[i].UnplayedFaceUpCardsShowing, sizeof(int));
		cfile.Read(&theUndoStack->UndoStack[i].TimeThroughDeck, sizeof(int));
		for (int j = 0; j < CARDMAX; j++)
		{
			cfile.Read(&theUndoStack->UndoStack[i].CardID[j], sizeof(int));
		}
	}

	//Cdeck *theDeck;
	//int deck[CARDMAX];
	cfile.Read(theDeck->deck, sizeof(int) * CARDMAX);         

	for (i = 0; i < CARDMAX; i++)
	{
		//CARDS unplayedfacedowncards[CARDMAX];
		cfile.Read(&theDeck->unplayedfacedowncards[i].card, sizeof(int));
		cfile.Read(&theDeck->unplayedfacedowncards[i].faceup, sizeof(bool));
	}

	for (i = 0; i < CARDMAX; i++)
	{
		//CARDS unplayedfaceupcards[CARDMAX];
		cfile.Read(&theDeck->unplayedfaceupcards[i].card, sizeof(int));
		cfile.Read(&theDeck->unplayedfaceupcards[i].faceup, sizeof(bool));
	}

	for (i = 0; i < CARDSINSUITE; i++)
	{
		//CARDS acecolonecards[CARDSINSUITE];
		cfile.Read(&theDeck->acecolonecards[i].card, sizeof(int));
		cfile.Read(&theDeck->acecolonecards[i].faceup, sizeof(bool));
	}

	for (i = 0; i < CARDSINSUITE; i++)
	{
		//CARDS acecoltwocards[CARDSINSUITE];
		cfile.Read(&theDeck->acecoltwocards[i].card, sizeof(int));
		cfile.Read(&theDeck->acecoltwocards[i].faceup, sizeof(bool));
	}

	for (i = 0; i < CARDSINSUITE; i++)
	{
		//CARDS acecolthreecards[CARDSINSUITE];
		cfile.Read(&theDeck->acecolthreecards[i].card, sizeof(int));
		cfile.Read(&theDeck->acecolthreecards[i].faceup, sizeof(bool));
	}

	for (i = 0; i < CARDSINSUITE; i++)
	{
		//CARDS acecolfourcards[CARDSINSUITE];
		cfile.Read(&theDeck->acecolfourcards[i].card, sizeof(int));
		cfile.Read(&theDeck->acecolfourcards[i].faceup, sizeof(bool));
	}

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecolone[GAMEROWMAX];
		cfile.Read(&theDeck->gamecolone[i].card, sizeof(int));
		cfile.Read(&theDeck->gamecolone[i].faceup, sizeof(bool));
	}

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecoltwo[GAMEROWMAX];
		cfile.Read(&theDeck->gamecoltwo[i].card, sizeof(int));
		cfile.Read(&theDeck->gamecoltwo[i].faceup, sizeof(bool));
	}

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecolthree[GAMEROWMAX];
		cfile.Read(&theDeck->gamecolthree[i].card, sizeof(int));
		cfile.Read(&theDeck->gamecolthree[i].faceup, sizeof(bool));
	}

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecolfour[GAMEROWMAX];
		cfile.Read(&theDeck->gamecolfour[i].card, sizeof(int));
		cfile.Read(&theDeck->gamecolfour[i].faceup, sizeof(bool));
	}

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecolfive[GAMEROWMAX];
		cfile.Read(&theDeck->gamecolfive[i].card, sizeof(int));
		cfile.Read(&theDeck->gamecolfive[i].faceup, sizeof(bool));
	}

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecolsix[GAMEROWMAX];
		cfile.Read(&theDeck->gamecolsix[i].card, sizeof(int));
		cfile.Read(&theDeck->gamecolsix[i].faceup, sizeof(bool));
	}

	for (i = 0; i < GAMEROWMAX; i++)
	{
		//CARDS gamecolseven[GAMEROWMAX];
		cfile.Read(&theDeck->gamecolseven[i].card, sizeof(int));
		cfile.Read(&theDeck->gamecolseven[i].faceup, sizeof(bool));
	}
	if (cfile.GetPosition() < dwLength)
	{
		cfile.Read(&BaseScore, sizeof(int));
		cfile.Read(&GamesWon, sizeof(int));
		cfile.Read(&GamesPlayed, sizeof(int));
	}
	cfile.Close();
	return true;
}

void CDrawScreen::InitPaintValues()
{
	Paint_UNPLAYEDFACEUPCARDSCOLUMNID = false;
	Paint_ACECOLONECARDSCOLUMNID = false;
	Paint_ACECOLTWOCARDSCOLUMNID = false;
	Paint_ACECOLTHREECARDSCOLUMNID = false;
	Paint_ACECOLFOURCARDSCOLUMNID = false;
	Paint_GAMECOLONECOLUMNID = false;
	Paint_GAMECOLTWOCOLUMNID = false;
	Paint_GAMECOLTHREECOLUMNID = false;
	Paint_GAMECOLFOURCOLUMNID = false;
	Paint_GAMECOLFIVECOLUMNID = false;
	Paint_GAMECOLSIXCOLUMNID = false;
	Paint_GAMECOLSEVENCOLUMNID = false;
	Paint_LONGHORNCOLUMNID = false;
	Paint_UNPLAYEDFACEDOWNCARDSCOLUMNID = false;
	Paint_Score = false;
	Paint_All = false;
}

void CDrawScreen::SetPaintBasedOnColumnID(int ColID)
{
	switch (ColID)
	{
			case GAMECOLONECOLUMNID:
				Paint_GAMECOLONECOLUMNID = true;
				break;
			case GAMECOLTWOCOLUMNID:
				Paint_GAMECOLTWOCOLUMNID = true;
				break;
			case GAMECOLTHREECOLUMNID:
				Paint_GAMECOLTHREECOLUMNID = true;
				break;
			case GAMECOLFOURCOLUMNID:
				Paint_GAMECOLFOURCOLUMNID = true;
				break;
			case GAMECOLFIVECOLUMNID:
				Paint_GAMECOLFIVECOLUMNID = true;
				break;
			case GAMECOLSIXCOLUMNID:
				Paint_GAMECOLSIXCOLUMNID = true;
				break;
			case GAMECOLSEVENCOLUMNID:
				Paint_GAMECOLSEVENCOLUMNID = true;
				break;
			case ACECOLONECARDSCOLUMNID:
				Paint_ACECOLONECARDSCOLUMNID = true;
				break;
			case ACECOLTWOCARDSCOLUMNID:
				Paint_ACECOLTWOCARDSCOLUMNID = true;
				break;
			case ACECOLTHREECARDSCOLUMNID:
				Paint_ACECOLTHREECARDSCOLUMNID = true;
				break;
			case ACECOLFOURCARDSCOLUMNID:
				Paint_ACECOLFOURCARDSCOLUMNID = true;
				break;
			case UNPLAYEDFACEUPCARDSCOLUMNID:
				Paint_UNPLAYEDFACEUPCARDSCOLUMNID = true;
				break;
			case UNPLAYEDFACEDOWNCARDSCOLUMNID:
				Paint_UNPLAYEDFACEDOWNCARDSCOLUMNID = true;
				break;
	}
}

void CDrawScreen::DeleteImagesInRect(CDC *dc, CRect &RectToDrawBackGround)
{
	dc->FillSolidRect(RectToDrawBackGround, RGB(255, 255, 128)); //dc->GetBkColor())
}