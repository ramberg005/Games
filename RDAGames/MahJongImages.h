#pragma once
#include "definitions.h"

class CMahJongImages
{
public:
	CMahJongImages(void);
	~CMahJongImages(void);

public:
	CImage MJImages[BLANK_PNG + 1];
	CImage MJImagesMask[BLANK_PNG + 1];
	CImage MJImagesHighLighted[FALL_PNG + 1];

public:
	void LoadImages();
};

