
#pragma once

#include "definitions.h"
#include <stdlib.h>
#include <time.h>

struct CARDS
{
	int card;
	bool faceup;
};


class Cdeck
{
public:
	int deck[CARDMAX];
	CARDS unplayedfacedowncards[CARDMAX];
	CARDS unplayedfaceupcards[CARDMAX];
	CARDS acecolonecards[CARDSINSUITE+1];
	CARDS acecoltwocards[CARDSINSUITE+1];
	CARDS acecolthreecards[CARDSINSUITE+1];
	CARDS acecolfourcards[CARDSINSUITE+1];
	CARDS gamecolone[GAMEROWMAX];
	CARDS gamecoltwo[GAMEROWMAX];
	CARDS gamecolthree[GAMEROWMAX];
	CARDS gamecolfour[GAMEROWMAX];
	CARDS gamecolfive[GAMEROWMAX];
	CARDS gamecolsix[GAMEROWMAX];
	CARDS gamecolseven[GAMEROWMAX];
public:
	void Deal();
	void CleanDeckArrays();

private:
	void Shuffle();
	void DoTheDeal();

public:
	Cdeck();
	~Cdeck();
};