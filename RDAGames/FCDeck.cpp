#include "stdafx.h"
#include "FCDeck.h"

CFCDeck::CFCDeck()
{
	CleanDeck();
}

CFCDeck::~CFCDeck()
{
}

void CFCDeck::Shuffle()
{
	int rndnum;
	int i;

	// seed our random number generator
	srand(GetTickCount());

	while (deck[CARDMAX - 1] == -1)
	{
		rndnum = rand() % 53;
		if (rndnum != 0)
		{
			for (i = 1; i < CARDMAX; i++)
			{
				if (deck[i] == -1)
				{
					deck[i] = rndnum;
					break;
				}
				if (deck[i] == rndnum)
				{
					break;
				}
			}
		}
	}
}

void CFCDeck::CleanDeck()
{
	int i;
	int j;
	for (i = 0; i <= CARDMAX; i++)
	{
		deck[i] = -1;
	}
	for (j=0; j <= WORKAREACOLUMNS; j++)
	{
		WorkLocation[j][0] = -1;
		WorkLocation[j][1] = -1;
		i = 0;
		for (i = 0; i <= CARDSINSUITE; i++)
		{
			ACES[j][i] = -1;
		}
	}
	// the play area
	for (j=0; j <= PLAYAREACOLUMNS; j++)
	{
		i = 0;
		for (i = 0; i <= CARDMAX; i++)
		{
			PlayArea[j][i] = -1;
		}
	}
}

void CFCDeck::Deal()
{
	int i,j;
	int k = 1;

	for (j=0; j < CARDSINSUITE; j++)
	{
		//k = 0;
		for (i = 0; i < PLAYAREACOLUMNS; i++)
		{
			PlayArea[i][j] = deck[k];
			k++;
			if (k > 52)
			{
				break;
			}
		}
	}
}
