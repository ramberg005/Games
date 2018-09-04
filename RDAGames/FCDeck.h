
#pragma once

#include "definitions.h"
#include <stdlib.h>
#include <time.h>


class CFCDeck
{
public:
	int deck[CARDMAX+1];
	// the array that tracks what 4 cards that can move from top to bottom
	int WorkLocation[WORKAREACOLUMNS+1][2];
	CRect WorkLocationRect[WORKAREACOLUMNS];
	// location for aces and cards that play on top of them
	int ACES[WORKAREACOLUMNS+1][CARDSINSUITE+1];
	CRect ACESRect[WORKAREACOLUMNS];
	// the play area
	int PlayArea[PLAYAREACOLUMNS+1][CARDMAX];
	CRect PlayAreaRect[PLAYAREACOLUMNS][CARDMAX];

public:
	void CleanDeck();
	void Shuffle();
	void Deal();


public:
	CFCDeck();
	~CFCDeck();
};
