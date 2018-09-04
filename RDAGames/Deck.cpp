#include "stdafx.h"
#include "Deck.h"

Cdeck::Cdeck()
{
	CleanDeckArrays();
}

Cdeck::~Cdeck()
{
}

void Cdeck::Deal()
{
	CleanDeckArrays();
	Shuffle();
	DoTheDeal();

	// debug stuff
	//acecolonecards[0] = 1;
	//acecoltwocards[0] = 14;
	//acecolthreecards[0] = 27;
	//acecolfourcards[0] = 40;

	//unplayedfaceupcards[0] = 1;
	//unplayedfaceupcards[1] = 13;
	//unplayedfaceupcards[2] = 22;
	//unplayedfaceupcards[3] = 44;
}

void Cdeck::DoTheDeal()
{
	int i = 0;
	int j = 0;

	gamecolone[i].card = deck[1];
	gamecolone[i].faceup = true;
	gamecoltwo[i].card = deck[2];
	gamecoltwo[i].faceup = false;
	gamecolthree[i].card = deck[3];
	gamecolthree[i].faceup = false;
	gamecolfour[i].card = deck[4];
	gamecolfour[i].faceup = false;
	gamecolfive[i].card = deck[5];
	gamecolfive[i].faceup = false;
	gamecolsix[i].card = deck[6];
	gamecolsix[i].faceup = false;
	gamecolseven[i].card = deck[7];
	gamecolseven[i].faceup = false;
	i++;

	gamecoltwo[i].card = deck[8];
	gamecoltwo[i].faceup = true;
	gamecolthree[i].card = deck[9];
	gamecolthree[i].faceup = false;
	gamecolfour[i].card = deck[10];
	gamecolfour[i].faceup = false;
	gamecolfive[i].card = deck[11];
	gamecolfive[i].faceup = false;
	gamecolsix[i].card = deck[12];
	gamecolsix[i].faceup = false;
	gamecolseven[i].card = deck[13];
	gamecolseven[i].faceup = false;
	i++;

	gamecolthree[i].card = deck[14];
	gamecolthree[i].faceup = true;
	gamecolfour[i].card = deck[15];
	gamecolfour[i].faceup = false;
	gamecolfive[i].card = deck[16];
	gamecolfive[i].faceup = false;
	gamecolsix[i].card = deck[17];
	gamecolsix[i].faceup = false;
	gamecolseven[i].card = deck[18];
	gamecolseven[i].faceup = false;
	i++;

	gamecolfour[i].card = deck[19];
	gamecolfour[i].faceup = true;
	gamecolfive[i].card = deck[20];
	gamecolfive[i].faceup = false;
	gamecolsix[i].card = deck[21];
	gamecolsix[i].faceup = false;
	gamecolseven[i].card = deck[22];
	gamecolseven[i].faceup = false;
	i++;

	gamecolfive[i].card = deck[23];
	gamecolfive[i].faceup = true;
	gamecolsix[i].card = deck[24];
	gamecolsix[i].faceup = false;
	gamecolseven[i].card = deck[25];
	gamecolseven[i].faceup = false;
	i++;

	gamecolsix[i].card = deck[26];
	gamecolsix[i].faceup = true;
	gamecolseven[i].card = deck[27];
	gamecolseven[i].faceup = false;
	i++;

	gamecolseven[i].card = deck[28];
	gamecolseven[i].faceup = true;

	// debug stuff
	//i++;
	//for (int j = 7; j < GAMEROWMAX; j++)
	//{
	//	gamecolseven[j].card = deck[i];
	//	gamecolseven[j].faceup = true;
	//	i++;
	//}

	for (i = 29; i < CARDMAX; i++)
	{
		unplayedfacedowncards[j].card = deck[i];
		j++;
	}

}

void Cdeck::Shuffle()
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

void Cdeck::CleanDeckArrays()
{
	int i;
	for (i = 0; i < CARDMAX; i++)
	{
		deck[i] = -1;
		unplayedfacedowncards[i].card = -1;
		unplayedfacedowncards[i].faceup = false;
		
		unplayedfaceupcards[i].card = -1;
		unplayedfaceupcards[i].faceup = false;
	}
	for (i = 0; i <= CARDSINSUITE; i++)
	{
		acecolonecards[i].card = -1;
		acecolonecards[i].faceup = true;

		acecoltwocards[i].card = -1;
		acecoltwocards[i].faceup = true;

		acecolthreecards[i].card = -1;
		acecolthreecards[i].faceup = true;

		acecolfourcards[i].card = -1;
		acecolfourcards[i].faceup = true;
	}
	for (i = 0; i < GAMEROWMAX; i++)
	{
		gamecolone[i].card = -1;
		gamecolone[i].faceup = false;

		gamecoltwo[i].card = -1;
		gamecoltwo[i].faceup = false;

		gamecolthree[i].card = -1;
		gamecolthree[i].faceup = false;

		gamecolfour[i].card = -1;
		gamecolfour[i].faceup = false;

		gamecolfive[i].card = -1;
		gamecolfive[i].faceup = false;

		gamecolsix[i].card = -1;
		gamecolsix[i].faceup = false;

		gamecolseven[i].card = -1;
		gamecolseven[i].faceup = false;
	}
}
