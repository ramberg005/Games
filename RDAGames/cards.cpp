#include "stdafx.h"
#include "cards.h"


CardImages::CardImages()
{
}

CardImages::~CardImages()
{
	int i = 0;
	for (i = 0; i < NUMBEROFCARDIMAGES; i++)
	{
		theCardImages[i].Destroy();
		theCardImages[i].ReleaseGDIPlus();
	}
}

void CardImages::init()
{
	initCanCardPlayArray();
	initCardImages();
}

void CardImages::initCardImages()
{
	CString imagepath;
	CString imagefile;

	imagepath = ".\\deck\\";

	imagefile = imagepath + "0.png";
	theCardImages[CARDBACK].Load(imagefile);
	imagefile = imagepath + "00.png";
	theCardImages[NOCARDSPOT].Load(imagefile);
	imagefile = imagepath + "EndOfGame.png";
	theCardImages[ENDOFGAME].Load(imagefile);
	imagefile = imagepath + "Longhorn.png";
	theCardImages[LONGHORN].Load(imagefile);



	imagefile = imagepath + "Heart1.png";
	theCardImages[ACEOFHEARTS].Load(imagefile);
	imagefile = imagepath + "Heart2.png";
	theCardImages[TWOOFHEARTS].Load(imagefile);
	imagefile = imagepath + "Heart3.png";
	theCardImages[THREEOFHEARTS].Load(imagefile);
	imagefile = imagepath + "Heart4.png";
	theCardImages[FOUROFHEARTS].Load(imagefile);
	imagefile = imagepath + "Heart5.png";
	theCardImages[FIVEOFHEARTS].Load(imagefile);
	imagefile = imagepath + "Heart6.png";
	theCardImages[SIXOFHEARTS].Load(imagefile);
	imagefile = imagepath + "Heart7.png";
	theCardImages[SEVENOFHEARTS].Load(imagefile);
	imagefile = imagepath + "Heart8.png";
	theCardImages[EIGHTOFHEARTS].Load(imagefile);
	imagefile = imagepath + "Heart9.png";
	theCardImages[NINEOFHEARTS].Load(imagefile);
	imagefile = imagepath + "Heart10.png";
	theCardImages[TENOFHEARTS].Load(imagefile);
	imagefile = imagepath + "Heart11.png";
	theCardImages[JACKOFHEARTS].Load(imagefile);
	imagefile = imagepath + "Heart12.png";
	theCardImages[QUEENOFHEARTS].Load(imagefile);
	imagefile = imagepath + "Heart13.png";
	theCardImages[KINGOFHEARTS].Load(imagefile);


	imagefile = imagepath + "Diamond1.png";
	theCardImages[ACEOFDIAMONDS].Load(imagefile);
	imagefile = imagepath + "Diamond2.png";
	theCardImages[TWOOFDIAMONDS].Load(imagefile);
	imagefile = imagepath + "Diamond3.png";
	theCardImages[THREEOFDIAMONDS].Load(imagefile);
	imagefile = imagepath + "Diamond4.png";
	theCardImages[FOUROFDIAMONDS].Load(imagefile);
	imagefile = imagepath + "Diamond5.png";
	theCardImages[FIVEOFDIAMONDS].Load(imagefile);
	imagefile = imagepath + "Diamond6.png";
	theCardImages[SIXOFDIAMONDS].Load(imagefile);
	imagefile = imagepath + "Diamond7.png";
	theCardImages[SEVENOFDIAMONDS].Load(imagefile);
	imagefile = imagepath + "Diamond8.png";
	theCardImages[EIGHTOFDIAMONDS].Load(imagefile);
	imagefile = imagepath + "Diamond9.png";
	theCardImages[NINEOFDIAMONDS].Load(imagefile);
	imagefile = imagepath + "Diamond10.png";
	theCardImages[TENOFDIAMONDS].Load(imagefile);
	imagefile = imagepath + "Diamond11.png";
	theCardImages[JACKOFDIAMONDS].Load(imagefile);
	imagefile = imagepath + "Diamond12.png";
	theCardImages[QUEENOFDIAMONDS].Load(imagefile);
	imagefile = imagepath + "Diamond13.png";
	theCardImages[KINGOFDIAMONDS].Load(imagefile);


	imagefile = imagepath + "Spade1.png";
	theCardImages[ACEOFSPADES].Load(imagefile);
	imagefile = imagepath + "Spade2.png";
	theCardImages[TWOOFSPADES].Load(imagefile);
	imagefile = imagepath + "Spade3.png";
	theCardImages[THREEOFSPADES].Load(imagefile);
	imagefile = imagepath + "Spade4.png";
	theCardImages[FOUROFSPADES].Load(imagefile);
	imagefile = imagepath + "Spade5.png";
	theCardImages[FIVEOFSPADES].Load(imagefile);
	imagefile = imagepath + "Spade6.png";
	theCardImages[SIXOFSPADES].Load(imagefile);
	imagefile = imagepath + "Spade7.png";
	theCardImages[SEVENOFSPADES].Load(imagefile);
	imagefile = imagepath + "Spade8.png";
	theCardImages[EIGHTOFSPADES].Load(imagefile);
	imagefile = imagepath + "Spade9.png";
	theCardImages[NINEOFSPADES].Load(imagefile);
	imagefile = imagepath + "Spade10.png";
	theCardImages[TENOFSPADES].Load(imagefile);
	imagefile = imagepath + "Spade11.png";
	theCardImages[JACKOFSPADES].Load(imagefile);
	imagefile = imagepath + "Spade12.png";
	theCardImages[QUEENOFSPADES].Load(imagefile);
	imagefile = imagepath + "Spade13.png";
	theCardImages[KINGOFSPADES].Load(imagefile);


	imagefile = imagepath + "Club1.png";
	theCardImages[ACEOFCLUBS].Load(imagefile);
	imagefile = imagepath + "Club2.png";
	theCardImages[TWOOFCLUBS].Load(imagefile);
	imagefile = imagepath + "Club3.png";
	theCardImages[THREEOFCLUBS].Load(imagefile);
	imagefile = imagepath + "Club4.png";
	theCardImages[FOUROFCLUBS].Load(imagefile);
	imagefile = imagepath + "Club5.png";
	theCardImages[FIVEOFCLUBS].Load(imagefile);
	imagefile = imagepath + "Club6.png";
	theCardImages[SIXOFCLUBS].Load(imagefile);
	imagefile = imagepath + "Club7.png";
	theCardImages[SEVENOFCLUBS].Load(imagefile);
	imagefile = imagepath + "Club8.png";
	theCardImages[EIGHTOFCLUBS].Load(imagefile);
	imagefile = imagepath + "Club9.png";
	theCardImages[NINEOFCLUBS].Load(imagefile);
	imagefile = imagepath + "Club10.png";
	theCardImages[TENOFCLUBS].Load(imagefile);
	imagefile = imagepath + "Club11.png";
	theCardImages[JACKOFCLUBS].Load(imagefile);
	imagefile = imagepath + "Club12.png";
	theCardImages[QUEENOFCLUBS].Load(imagefile);
	imagefile = imagepath + "Club13.png";
	theCardImages[KINGOFCLUBS].Load(imagefile);
}

void CardImages::initCanCardPlayArray()
{
	iaCanCardPlay[ACEOFSPADES][0] = 0;
	iaCanCardPlay[ACEOFSPADES][1] = 0;
	iaCanCardPlay[TWOOFSPADES][0] = 0;
	iaCanCardPlay[TWOOFSPADES][1] = 0;
	iaCanCardPlay[THREEOFSPADES][0] = TWOOFHEARTS;
	iaCanCardPlay[THREEOFSPADES][1] = TWOOFDIAMONDS;
	iaCanCardPlay[FOUROFSPADES][0] = THREEOFHEARTS;
	iaCanCardPlay[FOUROFSPADES][1] = THREEOFDIAMONDS;
	iaCanCardPlay[FIVEOFSPADES][0] = FOUROFHEARTS;
	iaCanCardPlay[FIVEOFSPADES][1] = FOUROFDIAMONDS;
	iaCanCardPlay[SIXOFSPADES][0] = FIVEOFHEARTS;
	iaCanCardPlay[SIXOFSPADES][1] = FIVEOFDIAMONDS;
	iaCanCardPlay[SEVENOFSPADES][0] = SIXOFHEARTS;
	iaCanCardPlay[SEVENOFSPADES][1] = SIXOFDIAMONDS;
	iaCanCardPlay[EIGHTOFSPADES][0] = SEVENOFHEARTS;
	iaCanCardPlay[EIGHTOFSPADES][1] = SEVENOFDIAMONDS;
	iaCanCardPlay[NINEOFSPADES][0] = EIGHTOFHEARTS;
	iaCanCardPlay[NINEOFSPADES][1] = EIGHTOFDIAMONDS;
	iaCanCardPlay[TENOFSPADES][0] = NINEOFHEARTS;
	iaCanCardPlay[TENOFSPADES][1] = NINEOFDIAMONDS;
	iaCanCardPlay[JACKOFSPADES][0] = TENOFHEARTS;
	iaCanCardPlay[JACKOFSPADES][1] = TENOFDIAMONDS;
	iaCanCardPlay[QUEENOFSPADES][0] = JACKOFHEARTS;
	iaCanCardPlay[QUEENOFSPADES][1] = JACKOFDIAMONDS;
	iaCanCardPlay[KINGOFSPADES][0] = QUEENOFHEARTS;
	iaCanCardPlay[KINGOFSPADES][1] = QUEENOFDIAMONDS;
	iaCanCardPlay[ACEOFDIAMONDS][0] = 0;
	iaCanCardPlay[ACEOFDIAMONDS][1] = 0;
	iaCanCardPlay[TWOOFDIAMONDS][0] = 0;
	iaCanCardPlay[TWOOFDIAMONDS][1] = 0;
	iaCanCardPlay[THREEOFDIAMONDS][0] = TWOOFSPADES;
	iaCanCardPlay[THREEOFDIAMONDS][1] = TWOOFCLUBS;
	iaCanCardPlay[FOUROFDIAMONDS][0] = THREEOFSPADES;
	iaCanCardPlay[FOUROFDIAMONDS][1] = THREEOFCLUBS;
	iaCanCardPlay[FIVEOFDIAMONDS][0] = FOUROFSPADES;
	iaCanCardPlay[FIVEOFDIAMONDS][1] = FOUROFCLUBS;
	iaCanCardPlay[SIXOFDIAMONDS][0] = FIVEOFSPADES;
	iaCanCardPlay[SIXOFDIAMONDS][1] = FIVEOFCLUBS;
	iaCanCardPlay[SEVENOFDIAMONDS][0] = SIXOFSPADES;
	iaCanCardPlay[SEVENOFDIAMONDS][1] = SIXOFCLUBS;
	iaCanCardPlay[EIGHTOFDIAMONDS][0] = SEVENOFSPADES;
	iaCanCardPlay[EIGHTOFDIAMONDS][1] = SEVENOFCLUBS;
	iaCanCardPlay[NINEOFDIAMONDS][0] = EIGHTOFSPADES;
	iaCanCardPlay[NINEOFDIAMONDS][1] = EIGHTOFCLUBS;
	iaCanCardPlay[TENOFDIAMONDS][0] = NINEOFSPADES;
	iaCanCardPlay[TENOFDIAMONDS][1] = NINEOFCLUBS;
	iaCanCardPlay[JACKOFDIAMONDS][0] = TENOFSPADES;
	iaCanCardPlay[JACKOFDIAMONDS][1] = TENOFCLUBS;
	iaCanCardPlay[QUEENOFDIAMONDS][0] = JACKOFSPADES;
	iaCanCardPlay[QUEENOFDIAMONDS][1] = JACKOFCLUBS;
	iaCanCardPlay[KINGOFDIAMONDS][0] = QUEENOFSPADES;
	iaCanCardPlay[KINGOFDIAMONDS][1] = QUEENOFCLUBS;
	iaCanCardPlay[ACEOFCLUBS][0] = 0;
	iaCanCardPlay[ACEOFCLUBS][1] = 0;
	iaCanCardPlay[TWOOFCLUBS][0] = 0;
	iaCanCardPlay[TWOOFCLUBS][1] = 0;
	iaCanCardPlay[THREEOFCLUBS][0] = TWOOFHEARTS;
	iaCanCardPlay[THREEOFCLUBS][1] = TWOOFDIAMONDS;
	iaCanCardPlay[FOUROFCLUBS][0] = THREEOFHEARTS;
	iaCanCardPlay[FOUROFCLUBS][1] = THREEOFDIAMONDS;
	iaCanCardPlay[FIVEOFCLUBS][0] = FOUROFHEARTS;
	iaCanCardPlay[FIVEOFCLUBS][1] = FOUROFDIAMONDS;
	iaCanCardPlay[SIXOFCLUBS][0] = FIVEOFHEARTS;
	iaCanCardPlay[SIXOFCLUBS][1] = FIVEOFDIAMONDS;
	iaCanCardPlay[SEVENOFCLUBS][0] = SIXOFHEARTS;
	iaCanCardPlay[SEVENOFCLUBS][1] = SIXOFDIAMONDS;
	iaCanCardPlay[EIGHTOFCLUBS][0] = SEVENOFHEARTS;
	iaCanCardPlay[EIGHTOFCLUBS][1] = SEVENOFDIAMONDS;
	iaCanCardPlay[NINEOFCLUBS][0] = EIGHTOFHEARTS;
	iaCanCardPlay[NINEOFCLUBS][1] = EIGHTOFDIAMONDS;
	iaCanCardPlay[TENOFCLUBS][0] = NINEOFHEARTS;
	iaCanCardPlay[TENOFCLUBS][1] = NINEOFDIAMONDS;
	iaCanCardPlay[JACKOFCLUBS][0] = TENOFHEARTS;
	iaCanCardPlay[JACKOFCLUBS][1] = TENOFDIAMONDS;
	iaCanCardPlay[QUEENOFCLUBS][0] = JACKOFHEARTS;
	iaCanCardPlay[QUEENOFCLUBS][1] = JACKOFDIAMONDS;
	iaCanCardPlay[KINGOFCLUBS][0] = QUEENOFHEARTS;
	iaCanCardPlay[KINGOFCLUBS][1] = QUEENOFDIAMONDS;
	iaCanCardPlay[ACEOFHEARTS][0] = 0;
	iaCanCardPlay[ACEOFHEARTS][1] = 0;
	iaCanCardPlay[TWOOFHEARTS][0] = 0;
	iaCanCardPlay[TWOOFHEARTS][1] = 0;
	iaCanCardPlay[THREEOFHEARTS][0] = TWOOFSPADES;
	iaCanCardPlay[THREEOFHEARTS][1] = TWOOFCLUBS;
	iaCanCardPlay[FOUROFHEARTS][0] = THREEOFSPADES;
	iaCanCardPlay[FOUROFHEARTS][1] = THREEOFCLUBS;
	iaCanCardPlay[FIVEOFHEARTS][0] = FOUROFSPADES;
	iaCanCardPlay[FIVEOFHEARTS][1] = FOUROFCLUBS;
	iaCanCardPlay[SIXOFHEARTS][0] = FIVEOFSPADES;
	iaCanCardPlay[SIXOFHEARTS][1] = FIVEOFCLUBS;
	iaCanCardPlay[SEVENOFHEARTS][0] = SIXOFSPADES;
	iaCanCardPlay[SEVENOFHEARTS][1] = SIXOFCLUBS;
	iaCanCardPlay[EIGHTOFHEARTS][0] = SEVENOFSPADES;
	iaCanCardPlay[EIGHTOFHEARTS][1] = SEVENOFCLUBS;
	iaCanCardPlay[NINEOFHEARTS][0] = EIGHTOFSPADES;
	iaCanCardPlay[NINEOFHEARTS][1] = EIGHTOFCLUBS;
	iaCanCardPlay[TENOFHEARTS][0] = NINEOFSPADES;
	iaCanCardPlay[TENOFHEARTS][1] = NINEOFCLUBS;
	iaCanCardPlay[JACKOFHEARTS][0] = TENOFSPADES;
	iaCanCardPlay[JACKOFHEARTS][1] = TENOFCLUBS;
	iaCanCardPlay[QUEENOFHEARTS][0] = JACKOFSPADES;
	iaCanCardPlay[QUEENOFHEARTS][1] = JACKOFCLUBS;
	iaCanCardPlay[KINGOFHEARTS][0] = QUEENOFSPADES;
	iaCanCardPlay[KINGOFHEARTS][1] = QUEENOFCLUBS;
}