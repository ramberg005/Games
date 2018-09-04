#pragma once
#include "definitions.h"


struct SUNDO
{
	int ColumnIDWhereGameActionStarted;
	int ColumnIDWhereGameActionEnded;  // if action started and ended in the same ColumnID then a card was flipped over
	int CardID[CARDMAX];
	int ActionID; // tracks when multiple actions happened so you can undo all of them at once
	int UnplayedFaceUpCardsShowing;
	int TimeThroughDeck;
};


class CUNDO
{
public:
	SUNDO UndoStack[MAXUNDOACTIONS];
	int CurrentUndoStackLocation;
	int CurrentActionID;

public:
	void InitUndoStack();

public:
	CUNDO();
	~CUNDO();
};