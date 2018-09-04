// cards.h : define our card class
//


#pragma once
#include "definitions.h"
#include <atlimage.h>


class CardImages
{
public:
	CardImages();
	~CardImages();

public:
// lookup array on what cards can play where
	int iaCanCardPlay[53][2];
	CImage theCardImages[NUMBEROFCARDIMAGES];

// Operations
public:
	void init();
	void initCanCardPlayArray();
	void initCardImages();

// Overrides

// Implementation
};
