#include "stdafx.h"
#include "UndoStack.h"

CUNDO::CUNDO()
{
}

CUNDO::~CUNDO()
{
}

void CUNDO::InitUndoStack()
{
	int i;
	int j;
	CurrentUndoStackLocation = 0;
	CurrentActionID = 0;
	for (i = 0; i < MAXUNDOACTIONS; i++)
	{
		UndoStack[i].ActionID = -1;
		UndoStack[i].ColumnIDWhereGameActionEnded = -1;
		UndoStack[i].ColumnIDWhereGameActionStarted = -1;
		UndoStack[i].UnplayedFaceUpCardsShowing = -1;
		UndoStack[i].TimeThroughDeck = -1;
		for (j = 0; j < CARDMAX; j++)
		{
			UndoStack[i].CardID[j] = -1;
		}
	}
}