
#pragma once

#include "definitions.h"
#include "cards.h"
#include "deck.h"
#include "DragStack.h"
#include "UndoStack.h"

struct DOUBLESPACECARD
{
	int ColumnID;
	int RowID; // which card needs double spaced when you have a left button click on it
};

class CDrawScreen
{
public:
	// want to only paint the part of the screen that has changed this section tracks that
	bool Paint_UNPLAYEDFACEUPCARDSCOLUMNID;
	bool Paint_ACECOLONECARDSCOLUMNID;
	bool Paint_ACECOLTWOCARDSCOLUMNID;
	bool Paint_ACECOLTHREECARDSCOLUMNID;
	bool Paint_ACECOLFOURCARDSCOLUMNID;
	bool Paint_GAMECOLONECOLUMNID;
	bool Paint_GAMECOLTWOCOLUMNID;
	bool Paint_GAMECOLTHREECOLUMNID;
	bool Paint_GAMECOLFOURCOLUMNID;
	bool Paint_GAMECOLFIVECOLUMNID;
	bool Paint_GAMECOLSIXCOLUMNID;
	bool Paint_GAMECOLSEVENCOLUMNID;
	bool Paint_LONGHORNCOLUMNID;
	bool Paint_UNPLAYEDFACEDOWNCARDSCOLUMNID;
	bool Paint_Score;
	bool Paint_All;

	void InitPaintValues();
	void SetPaintBasedOnColumnID(int ColID);
	void DeleteImagesInRect(CDC *dc, CRect &RectToDrawBackGround);

public:
	double CardStretchSize;
	int TimeThroughDeck;
	int ScreenWidth;
	int ScreenHeight;
	int GapBetweenGameCols;
	int GapBetweenTopandBottomRow;
	int GapOfFaceDownCardsUnderOtherCard;
	int GapOfFaceUpCardsUnderOtherCard;
	int OneHeight;
	int OneWidth;
	int DefaultCardWidth;
	int DefaultCardHeight;
	int SideGapOfUnplayedFaceUpCards;
	int UnPlayedFaceUpCardsDisplayCount;  // let us know if we are displaying 1, 2 or 3 cards

	int StretchedGapBetweenGameCols;
	int StretchedGapBetweenTopandBottomRow;
	int StretchedGapOfFaceDownCardsUnderOtherCard;
	int StretchedGapOfFaceUpCardsUnderOtherCard;
	int StretchedSideGapOfUnplayedFaceUpCards;
	int StretchCardWidth;
	int StretchCardHeight;
	int UnplayedFaceUpCardsShowing;
	int TheCurrentScore;

	unsigned int BaseScore;
	unsigned int GamesWon;
	unsigned int GamesPlayed;

	DOUBLESPACECARD DoubleSpaceCard;

	// Row Column information
	int SourceColumnID;
	int DestinationColumnID;
	int AceColumn1Location;
	int AceColumn1CardID;
	int AceColumn2Location;
	int AceColumn2CardID;
	int AceColumn3Location;
	int AceColumn3CardID;
	int AceColumn4Location;
	int AceColumn4CardID;
	
	CSize offset;
	CRect DragingRect;

	CRect unplayedfacedowncardsLocation;
	CRect unplayedfaceupcardsLocation;
	CRect acecolonecardsLocation;
	CRect acecoltwocardsLocation;
	CRect acecolthreecardsLocation;
	CRect acecolfourcardsLocation;
	CRect gamecoloneLocation;
	CRect gamecoltwoLocation;
	CRect gamecolthreeLocation;
	CRect gamecolfourLocation;
	CRect gamecolfiveLocation;
	CRect gamecolsixLocation;
	CRect gamecolsevenLocation;
	CRect LonghornLocation;
	CRect ScoreLocation;
	CRect UndoStack;

	CDragStack *theDragStack;
	CardImages *theCards;
	Cdeck *theDeck;
	CUNDO *theUndoStack;

	char CardNames[CARDMAX][NAMEMAX];
	char ColumnNames[15][NAMEMAX];

public:
	void DrawTheScreen(CPaintDC *dc);
	void SizeTheCards();
	void SetDefaultCardSize();
	void SetCardLocationInformation();
	void init();
	void SeeIfWeAreDragingCards(CPoint point);
	bool MoveDragStack(CPoint point);
	CRect GetDragImageRectangle(CPoint point);
	CRect CalculateDirtyRectangle();
	bool DropDragAroundStack(CPoint point);
	bool DropDragAroundStack2(CPoint point);
	void AddToUndoFromDragStack(int iUnplayedFaceUpCardsShowing);
	void FlipTopCardAfterMove();
	void DealInit();
	bool SetupDoubleSpaceView(CPoint point);
	bool NextThreeCards();
	int SetupRowColumnInformation(CPoint point);
	bool DoAnUnDo();
	bool PlayWhatYouCanOnRightButtonClick();
	bool SaveData();
	bool LoadData();
	void DumpUndo();
	void SetupCardNameArray();
	int SeeIfGameColumnExceedsScreenHeight(CARDS *gamerow, int y, int maxcolrows, int ColumnBeingDrawn);

private:
	int GetLastLocation(CARDS *iarray, int maxarraysize);
	int Round(double d);
	void DrawGameColumn(CPaintDC *dc, CARDS *row, int x, int y, int ColumnBeingDrawn); 
	bool SeeIfMouseIsOnAMoveableCard();
	int GetCardLocationInGameRow(CARDS *pGameRow, CPoint point, CRect CardLocation);
	CRect CalculateRectForDraging(int ColumnID, int CardLocation);
	void MoveDragStackToNewRow(CARDS *pGameRow);
	CARDS * GetPointerToColumn(int ColumnID);
	int GetColumnArraySize(int ColumnID);
	int SeeIfCardCanPlay(int LastCardID);
	void MoveCardToAceColumn(int FromColumnID, int ToColumnID);
	void SetNewAceColumnValues();
	bool DropOnAceColumn(CRect &MaxDropRect, CARDS *pGameRow, CPoint point);
	bool DropOnGameColumn(CRect &MaxDropRect, CARDS *pGameRow, CPoint point);

private:

public:
	CDrawScreen();
	~CDrawScreen();
};