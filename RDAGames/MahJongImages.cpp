#include "StdAfx.h"

#include "MahJongImages.h"


CMahJongImages::CMahJongImages(void)
{
}


CMahJongImages::~CMahJongImages(void)
{
}

void CMahJongImages::LoadImages()
{
	CString imagepath;
	CString imagefile;
	HRESULT hr;

	//imagepath = "K:\\src\\RDAGames\\Release\\MahJong\\";
	imagepath = ".\\MahJong\\";

	imagefile = imagepath + "Bamboo 1 Mask.png";
	
	hr = MJImagesMask[BAMBOO1_PNG].Load(imagefile);
	_com_error err(hr);
	imagefile = err.ErrorMessage();
	if (hr != S_OK)
	{
		MessageBox(0, imagefile, imagefile, 0);
	}

	imagefile = imagepath + "Bamboo 1.png";
	MJImages[BAMBOO1_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 2 Mask.png";
	MJImagesMask[BAMBOO2_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 2.png";
	MJImages[BAMBOO2_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 3 Mask.png";
	MJImagesMask[BAMBOO3_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 3.png";
	MJImages[BAMBOO3_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 4 Mask.png";
	MJImagesMask[BAMBOO4_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 4.png";
	MJImages[BAMBOO4_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 5 Mask.png";
	MJImagesMask[BAMBOO5_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 5.png";
	MJImages[BAMBOO5_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 6 Mask.png";
	MJImagesMask[BAMBOO6_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 6.png";
	MJImages[BAMBOO6_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 7 Mask.png";
	MJImagesMask[BAMBOO7_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 7.png";
	MJImages[BAMBOO7_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 8 Mask.png";
	MJImagesMask[BAMBOO8_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 8.png";
	MJImages[BAMBOO8_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 9 Mask.png";
	MJImagesMask[BAMBOO9_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo 9.png";
	MJImages[BAMBOO9_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 1 Mask.png";
	MJImagesMask[CIRCLE1_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 1.png";
	MJImages[CIRCLE1_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 2 Mask.png";
	MJImagesMask[CIRCLE2_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 2.png";
	MJImages[CIRCLE2_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 3 Mask.png";
	MJImagesMask[CIRCLE3_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 3.png";
	MJImages[CIRCLE3_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 4 Mask.png";
	MJImagesMask[CIRCLE4_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 4.png";
	MJImages[CIRCLE4_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 5 Mask.png";
	MJImagesMask[CIRCLE5_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 5.png";
	MJImages[CIRCLE5_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 6 Mask.png";
	MJImagesMask[CIRCLE6_PNg].Load(imagefile);
	
	imagefile = imagepath + "Circle 6.png";
	MJImages[CIRCLE6_PNg].Load(imagefile);
	
	imagefile = imagepath + "Circle 7 Mask.png";
	MJImagesMask[CIRCLE7_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 7.png";
	MJImages[CIRCLE7_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 8 Mask.png";
	MJImagesMask[CIRCLE8_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 8.png";
	MJImages[CIRCLE8_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 9 Mask.png";
	MJImagesMask[CIRCLE9_PNG].Load(imagefile);
	
	imagefile = imagepath + "Circle 9.png";
	MJImages[CIRCLE9_PNG].Load(imagefile);
	
	imagefile = imagepath + "Dragon 1 Mask.png";
	MJImagesMask[DRAGON1_PNG].Load(imagefile);
	
	imagefile = imagepath + "Dragon 1.png";
	MJImages[DRAGON1_PNG].Load(imagefile);
	
	imagefile = imagepath + "Dragon 2 Mask.png";
	MJImagesMask[DRAGON2_PNG].Load(imagefile);
	
	imagefile = imagepath + "Dragon 2.png";
	MJImages[DRAGON2_PNG].Load(imagefile);
	
	imagefile = imagepath + "Dragon 3 Mask.png";
	MJImagesMask[DRAGON3_PNG].Load(imagefile);
	
	imagefile = imagepath + "Dragon 3.png";
	MJImages[DRAGON3_PNG].Load(imagefile);
	
	imagefile = imagepath + "East Mask.png";
	MJImagesMask[EAST_PNG].Load(imagefile);
	
	imagefile = imagepath + "East.png";
	MJImages[EAST_PNG].Load(imagefile);
	
	imagefile = imagepath + "North Mask.png";
	MJImagesMask[NORTH_PNG].Load(imagefile);
	
	imagefile = imagepath + "North.png";
	MJImages[NORTH_PNG].Load(imagefile);
	
	imagefile = imagepath + "South Mask.png";
	MJImagesMask[SOUTH_PNG].Load(imagefile);
	
	imagefile = imagepath + "South.png";
	MJImages[SOUTH_PNG].Load(imagefile);
	
	imagefile = imagepath + "West Mask.png";
	MJImagesMask[WEST_PNG].Load(imagefile);
	
	imagefile = imagepath + "West.png";
	MJImages[WEST_PNG].Load(imagefile);
	
	imagefile = imagepath + "Chrysanthemum Mask.png";
	MJImagesMask[CHRYSANTHEMUM_PNG].Load(imagefile);
	
	imagefile = imagepath + "Chrysanthemum.png";
	MJImages[CHRYSANTHEMUM_PNG].Load(imagefile);
	
	imagefile = imagepath + "Orchid Mask.png";
	MJImagesMask[ORCHID_PNG].Load(imagefile);
	
	imagefile = imagepath + "Orchid.png";
	MJImages[ORCHID_PNG].Load(imagefile);
	
	imagefile = imagepath + "Plum Mask.png";
	MJImagesMask[PLUM_PNG].Load(imagefile);
	
	imagefile = imagepath + "Plum.png";
	MJImages[PLUM_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo Mask.png";
	MJImagesMask[BAMBOO_PNG].Load(imagefile);
	
	imagefile = imagepath + "Bamboo.png";
	MJImages[BAMBOO_PNG].Load(imagefile);
	
	imagefile = imagepath + "Fall Mask.png";
	MJImagesMask[FALL_PNG].Load(imagefile);
	
	imagefile = imagepath + "Fall.png";
	MJImages[FALL_PNG].Load(imagefile);
	
	imagefile = imagepath + "Spring Mask.png";
	MJImagesMask[SPRING_PNG].Load(imagefile);
	
	imagefile = imagepath + "Spring.png";
	MJImages[SPRING_PNG].Load(imagefile);
	
	imagefile = imagepath + "Summer Mask.png";
	MJImagesMask[SUMMER_PNG].Load(imagefile);
	
	imagefile = imagepath + "Summer.png";
	MJImages[SUMMER_PNG].Load(imagefile);
	
	imagefile = imagepath + "Winter Mask.png";
	MJImagesMask[WINTER_PNG].Load(imagefile);
	
	imagefile = imagepath + "Winter.png";
	MJImages[WINTER_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 1 Mask.png";
	MJImagesMask[WAN1_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 1.png";
	MJImages[WAN1_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 2 Mask.png";
	MJImagesMask[WAN2_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 2.png";
	MJImages[WAN2_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 3 Mask.png";
	MJImagesMask[WAN3_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 3.png";
	MJImages[WAN3_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 4 Mask.png";
	MJImagesMask[WAN4_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 4.png";
	MJImages[WAN4_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 5 Mask.png";
	MJImagesMask[WAN5_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 5.png";
	MJImages[WAN5_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 6 Mask.png";
	MJImagesMask[WAN6_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 6.png";
	MJImages[WAN6_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 7 Mask.png";
	MJImagesMask[WAN7_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 7.png";
	MJImages[WAN7_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 8 Mask.png";
	MJImagesMask[WAN8_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 8.png";
	MJImages[WAN8_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 9 Mask.png";
	MJImagesMask[WAN9_PNG].Load(imagefile);
	
	imagefile = imagepath + "WAN 9.png";
	MJImages[WAN9_PNG].Load(imagefile);

	imagefile = imagepath + "Bamboo 1 Highlighted.png";
	MJImagesHighLighted[BAMBOO1_PNG].Load(imagefile);

	imagefile = imagepath + "Bamboo 2 Highlighted.png";
	MJImagesHighLighted[BAMBOO2_PNG].Load(imagefile);

	imagefile = imagepath + "Bamboo 3 Highlighted.png";
	MJImagesHighLighted[BAMBOO3_PNG].Load(imagefile);

	imagefile = imagepath + "Bamboo 4 Highlighted.png";
	MJImagesHighLighted[BAMBOO4_PNG].Load(imagefile);

	imagefile = imagepath + "Bamboo 5 Highlighted.png";
	MJImagesHighLighted[BAMBOO5_PNG].Load(imagefile);

	imagefile = imagepath + "Bamboo 6 Highlighted.png";
	MJImagesHighLighted[BAMBOO6_PNG].Load(imagefile);

	imagefile = imagepath + "Bamboo 7 Highlighted.png";
	MJImagesHighLighted[BAMBOO7_PNG].Load(imagefile);

	imagefile = imagepath + "Bamboo 8 Highlighted.png";
	MJImagesHighLighted[BAMBOO8_PNG].Load(imagefile);

	imagefile = imagepath + "Bamboo 9 Highlighted.png";
	MJImagesHighLighted[BAMBOO9_PNG].Load(imagefile);

	imagefile = imagepath + "Chrysanthemum Highlighted.png";
	MJImagesHighLighted[CHRYSANTHEMUM_PNG].Load(imagefile);

	imagefile = imagepath + "Circle 1 Highlighted.png";
	MJImagesHighLighted[CIRCLE1_PNG].Load(imagefile);

	imagefile = imagepath + "Circle 2 Highlighted.png";
	MJImagesHighLighted[CIRCLE2_PNG].Load(imagefile);

	imagefile = imagepath + "Circle 3 Highlighted.png";
	MJImagesHighLighted[CIRCLE3_PNG].Load(imagefile);

	imagefile = imagepath + "Circle 4 Highlighted.png";
	MJImagesHighLighted[CIRCLE4_PNG].Load(imagefile);

	imagefile = imagepath + "Circle 5 Highlighted.png";
	MJImagesHighLighted[CIRCLE5_PNG].Load(imagefile);

	imagefile = imagepath + "Circle 6 Highlighted.png";
	MJImagesHighLighted[CIRCLE6_PNg].Load(imagefile);

	imagefile = imagepath + "Circle 7 Highlighted.png";
	MJImagesHighLighted[CIRCLE7_PNG].Load(imagefile);

	imagefile = imagepath + "Circle 8 Highlighted.png";
	MJImagesHighLighted[CIRCLE8_PNG].Load(imagefile);

	imagefile = imagepath + "Circle 9 Highlighted.png";
	MJImagesHighLighted[CIRCLE9_PNG].Load(imagefile);

	imagefile = imagepath + "Dragon 1 Highlighted.png";
	MJImagesHighLighted[DRAGON1_PNG].Load(imagefile);

	imagefile = imagepath + "Dragon 2 Highlighted.png";
	MJImagesHighLighted[DRAGON2_PNG].Load(imagefile);

	imagefile = imagepath + "Dragon 3 Highlighted.png";
	MJImagesHighLighted[DRAGON3_PNG].Load(imagefile);

	imagefile = imagepath + "East Highlighted.png";
	MJImagesHighLighted[EAST_PNG].Load(imagefile);

	imagefile = imagepath + "North Highlighted.png";
	MJImagesHighLighted[NORTH_PNG].Load(imagefile);

	imagefile = imagepath + "Orchid Highlighted.png";
	MJImagesHighLighted[ORCHID_PNG].Load(imagefile);

	imagefile = imagepath + "Bamboo Highlighted.png";
	MJImagesHighLighted[BAMBOO_PNG].Load(imagefile);

	imagefile = imagepath + "Plum Highlighted.png";
	MJImagesHighLighted[PLUM_PNG].Load(imagefile);

	imagefile = imagepath + "South Highlighted.png";
	MJImagesHighLighted[SOUTH_PNG].Load(imagefile);

	imagefile = imagepath + "Fall Highlighted.png";
	MJImagesHighLighted[FALL_PNG].Load(imagefile);

	imagefile = imagepath + "Spring Highlighted.png";
	MJImagesHighLighted[SPRING_PNG].Load(imagefile);

	imagefile = imagepath + "Summer Highlighted.png";
	MJImagesHighLighted[SUMMER_PNG].Load(imagefile);

	imagefile = imagepath + "WAN 1 Highlighted.png";
	MJImagesHighLighted[WAN1_PNG].Load(imagefile);

	imagefile = imagepath + "WAN 2 Highlighted.png";
	MJImagesHighLighted[WAN2_PNG].Load(imagefile);

	imagefile = imagepath + "WAN 3 Highlighted.png";
	MJImagesHighLighted[WAN3_PNG].Load(imagefile);

	imagefile = imagepath + "WAN 4 Highlighted.png";
	MJImagesHighLighted[WAN4_PNG].Load(imagefile);

	imagefile = imagepath + "WAN 5 Highlighted.png";
	MJImagesHighLighted[WAN5_PNG].Load(imagefile);

	imagefile = imagepath + "WAN 6 Highlighted.png";
	MJImagesHighLighted[WAN6_PNG].Load(imagefile);

	imagefile = imagepath + "WAN 7 Highlighted.png";
	MJImagesHighLighted[WAN7_PNG].Load(imagefile);

	imagefile = imagepath + "WAN 8 Highlighted.png";
	MJImagesHighLighted[WAN8_PNG].Load(imagefile);

	imagefile = imagepath + "WAN 9 Highlighted.png";
	MJImagesHighLighted[WAN9_PNG].Load(imagefile);

	imagefile = imagepath + "West Highlighted.png";
	MJImagesHighLighted[WEST_PNG].Load(imagefile);

	imagefile = imagepath + "Winter Highlighted.png";
	MJImagesHighLighted[WINTER_PNG].Load(imagefile);

	imagefile = imagepath + "Blank.png";
	MJImages[BLANK_PNG].Load(imagefile);
	imagefile = imagepath + "Blank Mask.png";
	MJImagesMask[BLANK_PNG].Load(imagefile);


}