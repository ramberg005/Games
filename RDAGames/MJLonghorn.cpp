#include "StdAfx.h"
#include "MahjongView.h"
#include "MJLonghorn.h"
#include <math.h>

CMJLonghorn::CMJLonghorn(void)
{
}


CMJLonghorn::~CMJLonghorn(void)
{
}

int CMJLonghorn::Round(double d)
{
	int i;
	// we sure there won't be a screen that is 65536 bytes wide
	i = (int)floor(d);
	if ((d - i) > .5)
	{
		i++;
	}

	return i;
}

void CMJLonghorn::SetSize(double stretchval)
{

	LHRectDefinition[0].ScreenLocation.top = Round(50 * stretchval);
	LHRectDefinition[0].ScreenLocation.bottom = Round(130 * stretchval);
	LHRectDefinition[0].ScreenLocation.left = Round(25 * stretchval);
	LHRectDefinition[0].ScreenLocation.right = Round(78 * stretchval);
	LHRectDefinition[0].locationID = 0;

	LHRectDefinition[1].ScreenLocation.top = Round(50 * stretchval);
	LHRectDefinition[1].ScreenLocation.bottom = Round(130 * stretchval);
	LHRectDefinition[1].ScreenLocation.left = Round(78 * stretchval);
	LHRectDefinition[1].ScreenLocation.right = Round(131 * stretchval);
	LHRectDefinition[1].locationID = 1;

	LHRectDefinition[2].ScreenLocation.top = Round(50 * stretchval);
	LHRectDefinition[2].ScreenLocation.bottom = Round(130 * stretchval);
	LHRectDefinition[2].ScreenLocation.left = Round(131 * stretchval);
	LHRectDefinition[2].ScreenLocation.right = Round(184 * stretchval);
	LHRectDefinition[2].locationID = 2;

	LHRectDefinition[3].ScreenLocation.top = Round(50 * stretchval);
	LHRectDefinition[3].ScreenLocation.bottom = Round(130 * stretchval);
	LHRectDefinition[3].ScreenLocation.left = Round(184 * stretchval);
	LHRectDefinition[3].ScreenLocation.right = Round(237 * stretchval);
	LHRectDefinition[3].locationID = 3;

	LHRectDefinition[4].ScreenLocation.top = Round(50 * stretchval);
	LHRectDefinition[4].ScreenLocation.bottom = Round(130 * stretchval);
	LHRectDefinition[4].ScreenLocation.left = Round(1562 * stretchval);
	LHRectDefinition[4].ScreenLocation.right = Round(1615 * stretchval);
	LHRectDefinition[4].locationID = 4;

	LHRectDefinition[5].ScreenLocation.top = Round(50 * stretchval);
	LHRectDefinition[5].ScreenLocation.bottom = Round(130 * stretchval);
	LHRectDefinition[5].ScreenLocation.left = Round(1615 * stretchval);
	LHRectDefinition[5].ScreenLocation.right = Round(1668 * stretchval);
	LHRectDefinition[5].locationID = 5;

	LHRectDefinition[6].ScreenLocation.top = Round(50 * stretchval);
	LHRectDefinition[6].ScreenLocation.bottom = Round(130 * stretchval);
	LHRectDefinition[6].ScreenLocation.left = Round(1668 * stretchval);
	LHRectDefinition[6].ScreenLocation.right = Round(1721 * stretchval);
	LHRectDefinition[6].locationID = 6;

	LHRectDefinition[7].ScreenLocation.top = Round(50 * stretchval);
	LHRectDefinition[7].ScreenLocation.bottom = Round(130 * stretchval);
	LHRectDefinition[7].ScreenLocation.left = Round(1721 * stretchval);
	LHRectDefinition[7].ScreenLocation.right = Round(1774 * stretchval);
	LHRectDefinition[7].locationID = 7;

	LHRectDefinition[8].ScreenLocation.top = Round(130 * stretchval);
	LHRectDefinition[8].ScreenLocation.bottom = Round(210 * stretchval);
	LHRectDefinition[8].ScreenLocation.left = Round(184 * stretchval);
	LHRectDefinition[8].ScreenLocation.right = Round(237 * stretchval);
	LHRectDefinition[8].locationID = 8;

	LHRectDefinition[9].ScreenLocation.top = Round(130 * stretchval);
	LHRectDefinition[9].ScreenLocation.bottom = Round(210 * stretchval);
	LHRectDefinition[9].ScreenLocation.left = Round(237 * stretchval);
	LHRectDefinition[9].ScreenLocation.right = Round(290 * stretchval);
	LHRectDefinition[9].locationID = 9;

	LHRectDefinition[10].ScreenLocation.top = Round(130 * stretchval);
	LHRectDefinition[10].ScreenLocation.bottom = Round(210 * stretchval);
	LHRectDefinition[10].ScreenLocation.left = Round(290 * stretchval);
	LHRectDefinition[10].ScreenLocation.right = Round(343 * stretchval);
	LHRectDefinition[10].locationID = 10;

	LHRectDefinition[11].ScreenLocation.top = Round(130 * stretchval);
	LHRectDefinition[11].ScreenLocation.bottom = Round(210 * stretchval);
	LHRectDefinition[11].ScreenLocation.left = Round(343 * stretchval);
	LHRectDefinition[11].ScreenLocation.right = Round(396 * stretchval);
	LHRectDefinition[11].locationID = 11;

	LHRectDefinition[12].ScreenLocation.top = Round(130 * stretchval);
	LHRectDefinition[12].ScreenLocation.bottom = Round(210 * stretchval);
	LHRectDefinition[12].ScreenLocation.left = Round(1403 * stretchval);
	LHRectDefinition[12].ScreenLocation.right = Round(1456 * stretchval);
	LHRectDefinition[12].locationID = 12;

	LHRectDefinition[13].ScreenLocation.top = Round(130 * stretchval);
	LHRectDefinition[13].ScreenLocation.bottom = Round(210 * stretchval);
	LHRectDefinition[13].ScreenLocation.left = Round(1456 * stretchval);
	LHRectDefinition[13].ScreenLocation.right = Round(1509 * stretchval);
	LHRectDefinition[13].locationID = 13;

	LHRectDefinition[14].ScreenLocation.top = Round(130 * stretchval);
	LHRectDefinition[14].ScreenLocation.bottom = Round(210 * stretchval);
	LHRectDefinition[14].ScreenLocation.left = Round(1509 * stretchval);
	LHRectDefinition[14].ScreenLocation.right = Round(1562 * stretchval);
	LHRectDefinition[14].locationID = 14;

	LHRectDefinition[15].ScreenLocation.top = Round(130 * stretchval);
	LHRectDefinition[15].ScreenLocation.bottom = Round(210 * stretchval);
	LHRectDefinition[15].ScreenLocation.left = Round(1562 * stretchval);
	LHRectDefinition[15].ScreenLocation.right = Round(1615 * stretchval);
	LHRectDefinition[15].locationID = 15;

	LHRectDefinition[16].ScreenLocation.top = Round(210 * stretchval);
	LHRectDefinition[16].ScreenLocation.bottom = Round(290 * stretchval);
	LHRectDefinition[16].ScreenLocation.left = Round(343 * stretchval);
	LHRectDefinition[16].ScreenLocation.right = Round(396 * stretchval);
	LHRectDefinition[16].locationID = 16;

	LHRectDefinition[17].ScreenLocation.top = Round(210 * stretchval);
	LHRectDefinition[17].ScreenLocation.bottom = Round(290 * stretchval);
	LHRectDefinition[17].ScreenLocation.left = Round(396 * stretchval);
	LHRectDefinition[17].ScreenLocation.right = Round(449 * stretchval);
	LHRectDefinition[17].locationID = 17;

	LHRectDefinition[18].ScreenLocation.top = Round(210 * stretchval);
	LHRectDefinition[18].ScreenLocation.bottom = Round(290 * stretchval);
	LHRectDefinition[18].ScreenLocation.left = Round(449 * stretchval);
	LHRectDefinition[18].ScreenLocation.right = Round(502 * stretchval);
	LHRectDefinition[18].locationID = 18;

	LHRectDefinition[19].ScreenLocation.top = Round(210 * stretchval);
	LHRectDefinition[19].ScreenLocation.bottom = Round(290 * stretchval);
	LHRectDefinition[19].ScreenLocation.left = Round(502 * stretchval);
	LHRectDefinition[19].ScreenLocation.right = Round(555 * stretchval);
	LHRectDefinition[19].locationID = 19;

	LHRectDefinition[20].ScreenLocation.top = Round(210 * stretchval);
	LHRectDefinition[20].ScreenLocation.bottom = Round(290 * stretchval);
	LHRectDefinition[20].ScreenLocation.left = Round(1244 * stretchval);
	LHRectDefinition[20].ScreenLocation.right = Round(1297 * stretchval);
	LHRectDefinition[20].locationID = 20;

	LHRectDefinition[21].ScreenLocation.top = Round(210 * stretchval);
	LHRectDefinition[21].ScreenLocation.bottom = Round(290 * stretchval);
	LHRectDefinition[21].ScreenLocation.left = Round(1297 * stretchval);
	LHRectDefinition[21].ScreenLocation.right = Round(1350 * stretchval);
	LHRectDefinition[21].locationID = 21;

	LHRectDefinition[22].ScreenLocation.top = Round(210 * stretchval);
	LHRectDefinition[22].ScreenLocation.bottom = Round(290 * stretchval);
	LHRectDefinition[22].ScreenLocation.left = Round(1350 * stretchval);
	LHRectDefinition[22].ScreenLocation.right = Round(1403 * stretchval);
	LHRectDefinition[22].locationID = 22;

	LHRectDefinition[23].ScreenLocation.top = Round(210 * stretchval);
	LHRectDefinition[23].ScreenLocation.bottom = Round(290 * stretchval);
	LHRectDefinition[23].ScreenLocation.left = Round(1403 * stretchval);
	LHRectDefinition[23].ScreenLocation.right = Round(1456 * stretchval);
	LHRectDefinition[23].locationID = 23;

	LHRectDefinition[24].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[24].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[24].ScreenLocation.left = Round(449 * stretchval);
	LHRectDefinition[24].ScreenLocation.right = Round(502 * stretchval);
	LHRectDefinition[24].locationID = 24;

	LHRectDefinition[25].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[25].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[25].ScreenLocation.left = Round(502 * stretchval);
	LHRectDefinition[25].ScreenLocation.right = Round(555 * stretchval);
	LHRectDefinition[25].locationID = 25;

	LHRectDefinition[26].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[26].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[26].ScreenLocation.left = Round(555 * stretchval);
	LHRectDefinition[26].ScreenLocation.right = Round(608 * stretchval);
	LHRectDefinition[26].locationID = 26;

	LHRectDefinition[27].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[27].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[27].ScreenLocation.left = Round(608 * stretchval);
	LHRectDefinition[27].ScreenLocation.right = Round(661 * stretchval);
	LHRectDefinition[27].locationID = 27;

	LHRectDefinition[28].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[28].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[28].ScreenLocation.left = Round(661 * stretchval);
	LHRectDefinition[28].ScreenLocation.right = Round(714 * stretchval);
	LHRectDefinition[28].locationID = 28;

	LHRectDefinition[29].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[29].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[29].ScreenLocation.left = Round(714 * stretchval);
	LHRectDefinition[29].ScreenLocation.right = Round(767 * stretchval);
	LHRectDefinition[29].locationID = 29;

	LHRectDefinition[30].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[30].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[30].ScreenLocation.left = Round(767 * stretchval);
	LHRectDefinition[30].ScreenLocation.right = Round(820 * stretchval);
	LHRectDefinition[30].locationID = 30;

	LHRectDefinition[31].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[31].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[31].ScreenLocation.left = Round(820 * stretchval);
	LHRectDefinition[31].ScreenLocation.right = Round(873 * stretchval);
	LHRectDefinition[31].locationID = 31;

	LHRectDefinition[32].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[32].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[32].ScreenLocation.left = Round(873 * stretchval);
	LHRectDefinition[32].ScreenLocation.right = Round(926 * stretchval);
	LHRectDefinition[32].locationID = 32;

	LHRectDefinition[33].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[33].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[33].ScreenLocation.left = Round(926 * stretchval);
	LHRectDefinition[33].ScreenLocation.right = Round(979 * stretchval);
	LHRectDefinition[33].locationID = 33;

	LHRectDefinition[34].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[34].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[34].ScreenLocation.left = Round(979 * stretchval);
	LHRectDefinition[34].ScreenLocation.right = Round(1032 * stretchval);
	LHRectDefinition[34].locationID = 34;

	LHRectDefinition[35].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[35].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[35].ScreenLocation.left = Round(1032 * stretchval);
	LHRectDefinition[35].ScreenLocation.right = Round(1085 * stretchval);
	LHRectDefinition[35].locationID = 35;

	LHRectDefinition[36].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[36].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[36].ScreenLocation.left = Round(1085 * stretchval);
	LHRectDefinition[36].ScreenLocation.right = Round(1138 * stretchval);
	LHRectDefinition[36].locationID = 36;

	LHRectDefinition[37].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[37].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[37].ScreenLocation.left = Round(1138 * stretchval);
	LHRectDefinition[37].ScreenLocation.right = Round(1191 * stretchval);
	LHRectDefinition[37].locationID = 37;

	LHRectDefinition[38].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[38].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[38].ScreenLocation.left = Round(1191 * stretchval);
	LHRectDefinition[38].ScreenLocation.right = Round(1244 * stretchval);
	LHRectDefinition[38].locationID = 38;

	LHRectDefinition[39].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[39].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[39].ScreenLocation.left = Round(1244 * stretchval);
	LHRectDefinition[39].ScreenLocation.right = Round(1297 * stretchval);
	LHRectDefinition[39].locationID = 39;

	LHRectDefinition[40].ScreenLocation.top = Round(290 * stretchval);
	LHRectDefinition[40].ScreenLocation.bottom = Round(370 * stretchval);
	LHRectDefinition[40].ScreenLocation.left = Round(1297 * stretchval);
	LHRectDefinition[40].ScreenLocation.right = Round(1350 * stretchval);
	LHRectDefinition[40].locationID = 40;

	LHRectDefinition[41].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[41].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[41].ScreenLocation.left = Round(502 * stretchval);
	LHRectDefinition[41].ScreenLocation.right = Round(555 * stretchval);
	LHRectDefinition[41].locationID = 41;

	LHRectDefinition[42].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[42].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[42].ScreenLocation.left = Round(555 * stretchval);
	LHRectDefinition[42].ScreenLocation.right = Round(608 * stretchval);
	LHRectDefinition[42].locationID = 42;

	LHRectDefinition[43].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[43].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[43].ScreenLocation.left = Round(608 * stretchval);
	LHRectDefinition[43].ScreenLocation.right = Round(661 * stretchval);
	LHRectDefinition[43].locationID = 43;

	LHRectDefinition[44].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[44].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[44].ScreenLocation.left = Round(661 * stretchval);
	LHRectDefinition[44].ScreenLocation.right = Round(714 * stretchval);
	LHRectDefinition[44].locationID = 44;

	LHRectDefinition[45].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[45].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[45].ScreenLocation.left = Round(714 * stretchval);
	LHRectDefinition[45].ScreenLocation.right = Round(767 * stretchval);
	LHRectDefinition[45].locationID = 45;

	LHRectDefinition[46].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[46].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[46].ScreenLocation.left = Round(767 * stretchval);
	LHRectDefinition[46].ScreenLocation.right = Round(820 * stretchval);
	LHRectDefinition[46].locationID = 46;

	LHRectDefinition[47].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[47].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[47].ScreenLocation.left = Round(820 * stretchval);
	LHRectDefinition[47].ScreenLocation.right = Round(873 * stretchval);
	LHRectDefinition[47].locationID = 47;

	LHRectDefinition[48].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[48].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[48].ScreenLocation.left = Round(873 * stretchval);
	LHRectDefinition[48].ScreenLocation.right = Round(926 * stretchval);
	LHRectDefinition[48].locationID = 48;

	LHRectDefinition[49].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[49].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[49].ScreenLocation.left = Round(926 * stretchval);
	LHRectDefinition[49].ScreenLocation.right = Round(979 * stretchval);
	LHRectDefinition[49].locationID = 49;

	LHRectDefinition[50].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[50].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[50].ScreenLocation.left = Round(979 * stretchval);
	LHRectDefinition[50].ScreenLocation.right = Round(1032 * stretchval);
	LHRectDefinition[50].locationID = 50;

	LHRectDefinition[51].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[51].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[51].ScreenLocation.left = Round(1032 * stretchval);
	LHRectDefinition[51].ScreenLocation.right = Round(1085 * stretchval);
	LHRectDefinition[51].locationID = 51;

	LHRectDefinition[52].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[52].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[52].ScreenLocation.left = Round(1085 * stretchval);
	LHRectDefinition[52].ScreenLocation.right = Round(1138 * stretchval);
	LHRectDefinition[52].locationID = 52;

	LHRectDefinition[53].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[53].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[53].ScreenLocation.left = Round(1138 * stretchval);
	LHRectDefinition[53].ScreenLocation.right = Round(1191 * stretchval);
	LHRectDefinition[53].locationID = 53;

	LHRectDefinition[54].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[54].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[54].ScreenLocation.left = Round(1191 * stretchval);
	LHRectDefinition[54].ScreenLocation.right = Round(1244 * stretchval);
	LHRectDefinition[54].locationID = 54;

	LHRectDefinition[55].ScreenLocation.top = Round(370 * stretchval);
	LHRectDefinition[55].ScreenLocation.bottom = Round(450 * stretchval);
	LHRectDefinition[55].ScreenLocation.left = Round(1244 * stretchval);
	LHRectDefinition[55].ScreenLocation.right = Round(1297 * stretchval);
	LHRectDefinition[55].locationID = 55;

	LHRectDefinition[56].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[56].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[56].ScreenLocation.left = Round(555 * stretchval);
	LHRectDefinition[56].ScreenLocation.right = Round(608 * stretchval);
	LHRectDefinition[56].locationID = 56;

	LHRectDefinition[57].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[57].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[57].ScreenLocation.left = Round(608 * stretchval);
	LHRectDefinition[57].ScreenLocation.right = Round(661 * stretchval);
	LHRectDefinition[57].locationID = 57;

	LHRectDefinition[58].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[58].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[58].ScreenLocation.left = Round(661 * stretchval);
	LHRectDefinition[58].ScreenLocation.right = Round(714 * stretchval);
	LHRectDefinition[58].locationID = 58;

	LHRectDefinition[59].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[59].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[59].ScreenLocation.left = Round(714 * stretchval);
	LHRectDefinition[59].ScreenLocation.right = Round(767 * stretchval);
	LHRectDefinition[59].locationID = 59;

	LHRectDefinition[60].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[60].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[60].ScreenLocation.left = Round(767 * stretchval);
	LHRectDefinition[60].ScreenLocation.right = Round(820 * stretchval);
	LHRectDefinition[60].locationID = 60;

	LHRectDefinition[61].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[61].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[61].ScreenLocation.left = Round(820 * stretchval);
	LHRectDefinition[61].ScreenLocation.right = Round(873 * stretchval);
	LHRectDefinition[61].locationID = 61;

	LHRectDefinition[62].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[62].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[62].ScreenLocation.left = Round(873 * stretchval);
	LHRectDefinition[62].ScreenLocation.right = Round(926 * stretchval);
	LHRectDefinition[62].locationID = 62;

	LHRectDefinition[63].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[63].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[63].ScreenLocation.left = Round(926 * stretchval);
	LHRectDefinition[63].ScreenLocation.right = Round(979 * stretchval);
	LHRectDefinition[63].locationID = 63;

	LHRectDefinition[64].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[64].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[64].ScreenLocation.left = Round(979 * stretchval);
	LHRectDefinition[64].ScreenLocation.right = Round(1032 * stretchval);
	LHRectDefinition[64].locationID = 64;

	LHRectDefinition[65].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[65].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[65].ScreenLocation.left = Round(1032 * stretchval);
	LHRectDefinition[65].ScreenLocation.right = Round(1085 * stretchval);
	LHRectDefinition[65].locationID = 65;

	LHRectDefinition[66].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[66].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[66].ScreenLocation.left = Round(1085 * stretchval);
	LHRectDefinition[66].ScreenLocation.right = Round(1138 * stretchval);
	LHRectDefinition[66].locationID = 66;

	LHRectDefinition[67].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[67].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[67].ScreenLocation.left = Round(1138 * stretchval);
	LHRectDefinition[67].ScreenLocation.right = Round(1191 * stretchval);
	LHRectDefinition[67].locationID = 67;

	LHRectDefinition[68].ScreenLocation.top = Round(450 * stretchval);
	LHRectDefinition[68].ScreenLocation.bottom = Round(530 * stretchval);
	LHRectDefinition[68].ScreenLocation.left = Round(1191 * stretchval);
	LHRectDefinition[68].ScreenLocation.right = Round(1244 * stretchval);
	LHRectDefinition[68].locationID = 68;

	LHRectDefinition[69].ScreenLocation.top = Round(530 * stretchval);
	LHRectDefinition[69].ScreenLocation.bottom = Round(610 * stretchval);
	LHRectDefinition[69].ScreenLocation.left = Round(714 * stretchval);
	LHRectDefinition[69].ScreenLocation.right = Round(767 * stretchval);
	LHRectDefinition[69].locationID = 69;

	LHRectDefinition[70].ScreenLocation.top = Round(530 * stretchval);
	LHRectDefinition[70].ScreenLocation.bottom = Round(610 * stretchval);
	LHRectDefinition[70].ScreenLocation.left = Round(767 * stretchval);
	LHRectDefinition[70].ScreenLocation.right = Round(820 * stretchval);
	LHRectDefinition[70].locationID = 70;

	LHRectDefinition[71].ScreenLocation.top = Round(530 * stretchval);
	LHRectDefinition[71].ScreenLocation.bottom = Round(610 * stretchval);
	LHRectDefinition[71].ScreenLocation.left = Round(820 * stretchval);
	LHRectDefinition[71].ScreenLocation.right = Round(873 * stretchval);
	LHRectDefinition[71].locationID = 71;

	LHRectDefinition[72].ScreenLocation.top = Round(530 * stretchval);
	LHRectDefinition[72].ScreenLocation.bottom = Round(610 * stretchval);
	LHRectDefinition[72].ScreenLocation.left = Round(873 * stretchval);
	LHRectDefinition[72].ScreenLocation.right = Round(926 * stretchval);
	LHRectDefinition[72].locationID = 72;

	LHRectDefinition[73].ScreenLocation.top = Round(530 * stretchval);
	LHRectDefinition[73].ScreenLocation.bottom = Round(610 * stretchval);
	LHRectDefinition[73].ScreenLocation.left = Round(926 * stretchval);
	LHRectDefinition[73].ScreenLocation.right = Round(979 * stretchval);
	LHRectDefinition[73].locationID = 73;

	LHRectDefinition[74].ScreenLocation.top = Round(530 * stretchval);
	LHRectDefinition[74].ScreenLocation.bottom = Round(610 * stretchval);
	LHRectDefinition[74].ScreenLocation.left = Round(979 * stretchval);
	LHRectDefinition[74].ScreenLocation.right = Round(1032 * stretchval);
	LHRectDefinition[74].locationID = 74;

	LHRectDefinition[75].ScreenLocation.top = Round(530 * stretchval);
	LHRectDefinition[75].ScreenLocation.bottom = Round(610 * stretchval);
	LHRectDefinition[75].ScreenLocation.left = Round(1032 * stretchval);
	LHRectDefinition[75].ScreenLocation.right = Round(1085 * stretchval);
	LHRectDefinition[75].locationID = 75;

	LHRectDefinition[76].ScreenLocation.top = Round(610 * stretchval);
	LHRectDefinition[76].ScreenLocation.bottom = Round(690 * stretchval);
	LHRectDefinition[76].ScreenLocation.left = Round(767 * stretchval);
	LHRectDefinition[76].ScreenLocation.right = Round(820 * stretchval);
	LHRectDefinition[76].locationID = 76;

	LHRectDefinition[77].ScreenLocation.top = Round(610 * stretchval);
	LHRectDefinition[77].ScreenLocation.bottom = Round(690 * stretchval);
	LHRectDefinition[77].ScreenLocation.left = Round(820 * stretchval);
	LHRectDefinition[77].ScreenLocation.right = Round(873 * stretchval);
	LHRectDefinition[77].locationID = 77;

	LHRectDefinition[78].ScreenLocation.top = Round(610 * stretchval);
	LHRectDefinition[78].ScreenLocation.bottom = Round(690 * stretchval);
	LHRectDefinition[78].ScreenLocation.left = Round(873 * stretchval);
	LHRectDefinition[78].ScreenLocation.right = Round(926 * stretchval);
	LHRectDefinition[78].locationID = 78;

	LHRectDefinition[79].ScreenLocation.top = Round(610 * stretchval);
	LHRectDefinition[79].ScreenLocation.bottom = Round(690 * stretchval);
	LHRectDefinition[79].ScreenLocation.left = Round(926 * stretchval);
	LHRectDefinition[79].ScreenLocation.right = Round(979 * stretchval);
	LHRectDefinition[79].locationID = 79;

	LHRectDefinition[80].ScreenLocation.top = Round(610 * stretchval);
	LHRectDefinition[80].ScreenLocation.bottom = Round(690 * stretchval);
	LHRectDefinition[80].ScreenLocation.left = Round(979 * stretchval);
	LHRectDefinition[80].ScreenLocation.right = Round(1032 * stretchval);
	LHRectDefinition[80].locationID = 80;

	LHRectDefinition[81].ScreenLocation.top = Round(690 * stretchval);
	LHRectDefinition[81].ScreenLocation.bottom = Round(770 * stretchval);
	LHRectDefinition[81].ScreenLocation.left = Round(767 * stretchval);
	LHRectDefinition[81].ScreenLocation.right = Round(820 * stretchval);
	LHRectDefinition[81].locationID = 81;

	LHRectDefinition[82].ScreenLocation.top = Round(690 * stretchval);
	LHRectDefinition[82].ScreenLocation.bottom = Round(770 * stretchval);
	LHRectDefinition[82].ScreenLocation.left = Round(820 * stretchval);
	LHRectDefinition[82].ScreenLocation.right = Round(873 * stretchval);
	LHRectDefinition[82].locationID = 82;

	LHRectDefinition[83].ScreenLocation.top = Round(690 * stretchval);
	LHRectDefinition[83].ScreenLocation.bottom = Round(770 * stretchval);
	LHRectDefinition[83].ScreenLocation.left = Round(873 * stretchval);
	LHRectDefinition[83].ScreenLocation.right = Round(926 * stretchval);
	LHRectDefinition[83].locationID = 83;

	LHRectDefinition[84].ScreenLocation.top = Round(690 * stretchval);
	LHRectDefinition[84].ScreenLocation.bottom = Round(770 * stretchval);
	LHRectDefinition[84].ScreenLocation.left = Round(926 * stretchval);
	LHRectDefinition[84].ScreenLocation.right = Round(979 * stretchval);
	LHRectDefinition[84].locationID = 84;

	LHRectDefinition[85].ScreenLocation.top = Round(690 * stretchval);
	LHRectDefinition[85].ScreenLocation.bottom = Round(770 * stretchval);
	LHRectDefinition[85].ScreenLocation.left = Round(979 * stretchval);
	LHRectDefinition[85].ScreenLocation.right = Round(1032 * stretchval);
	LHRectDefinition[85].locationID = 85;

	LHRectDefinition[86].ScreenLocation.top = Round(770 * stretchval);
	LHRectDefinition[86].ScreenLocation.bottom = Round(850 * stretchval);
	LHRectDefinition[86].ScreenLocation.left = Round(820 * stretchval);
	LHRectDefinition[86].ScreenLocation.right = Round(873 * stretchval);
	LHRectDefinition[86].locationID = 86;

	LHRectDefinition[87].ScreenLocation.top = Round(770 * stretchval);
	LHRectDefinition[87].ScreenLocation.bottom = Round(850 * stretchval);
	LHRectDefinition[87].ScreenLocation.left = Round(873 * stretchval);
	LHRectDefinition[87].ScreenLocation.right = Round(926 * stretchval);
	LHRectDefinition[87].locationID = 87;

	LHRectDefinition[88].ScreenLocation.top = Round(770 * stretchval);
	LHRectDefinition[88].ScreenLocation.bottom = Round(850 * stretchval);
	LHRectDefinition[88].ScreenLocation.left = Round(926 * stretchval);
	LHRectDefinition[88].ScreenLocation.right = Round(979 * stretchval);
	LHRectDefinition[88].locationID = 88;

	LHRectDefinition[89].ScreenLocation.top = Round(850 * stretchval);
	LHRectDefinition[89].ScreenLocation.bottom = Round(930 * stretchval);
	LHRectDefinition[89].ScreenLocation.left = Round(820 * stretchval);
	LHRectDefinition[89].ScreenLocation.right = Round(873 * stretchval);
	LHRectDefinition[89].locationID = 89;

	LHRectDefinition[90].ScreenLocation.top = Round(850 * stretchval);
	LHRectDefinition[90].ScreenLocation.bottom = Round(930 * stretchval);
	LHRectDefinition[90].ScreenLocation.left = Round(873 * stretchval);
	LHRectDefinition[90].ScreenLocation.right = Round(926 * stretchval);
	LHRectDefinition[90].locationID = 90;

	LHRectDefinition[91].ScreenLocation.top = Round(850 * stretchval);
	LHRectDefinition[91].ScreenLocation.bottom = Round(930 * stretchval);
	LHRectDefinition[91].ScreenLocation.left = Round(926 * stretchval);
	LHRectDefinition[91].ScreenLocation.right = Round(979 * stretchval);
	LHRectDefinition[91].locationID = 91;

	LHRectDefinition[92].ScreenLocation.top = Round(930 * stretchval);
	LHRectDefinition[92].ScreenLocation.bottom = Round(1010 * stretchval);
	LHRectDefinition[92].ScreenLocation.left = Round(820 * stretchval);
	LHRectDefinition[92].ScreenLocation.right = Round(873 * stretchval);
	LHRectDefinition[92].locationID = 92;

	LHRectDefinition[93].ScreenLocation.top = Round(930 * stretchval);
	LHRectDefinition[93].ScreenLocation.bottom = Round(1010 * stretchval);
	LHRectDefinition[93].ScreenLocation.left = Round(873 * stretchval);
	LHRectDefinition[93].ScreenLocation.right = Round(926 * stretchval);
	LHRectDefinition[93].locationID = 93;

	LHRectDefinition[94].ScreenLocation.top = Round(930 * stretchval);
	LHRectDefinition[94].ScreenLocation.bottom = Round(1010 * stretchval);
	LHRectDefinition[94].ScreenLocation.left = Round(926 * stretchval);
	LHRectDefinition[94].ScreenLocation.right = Round(979 * stretchval);
	LHRectDefinition[94].locationID = 94;

	LHRectDefinition[95].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[95].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[95].ScreenLocation.left = Round((502 - TILESHIFT) * stretchval);
	LHRectDefinition[95].ScreenLocation.right = Round((555 - TILESHIFT) * stretchval);
	LHRectDefinition[95].locationID = 95;

	LHRectDefinition[96].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[96].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[96].ScreenLocation.left = Round((555 - TILESHIFT) * stretchval);
	LHRectDefinition[96].ScreenLocation.right = Round((608 - TILESHIFT) * stretchval);
	LHRectDefinition[96].locationID = 96;

	LHRectDefinition[97].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[97].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[97].ScreenLocation.left = Round((608 - TILESHIFT) * stretchval);
	LHRectDefinition[97].ScreenLocation.right = Round((661 - TILESHIFT) * stretchval);
	LHRectDefinition[97].locationID = 97;

	LHRectDefinition[98].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[98].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[98].ScreenLocation.left = Round((661 - TILESHIFT) * stretchval);
	LHRectDefinition[98].ScreenLocation.right = Round((714 - TILESHIFT) * stretchval);
	LHRectDefinition[98].locationID = 98;

	LHRectDefinition[99].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[99].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[99].ScreenLocation.left = Round((714 - TILESHIFT) * stretchval);
	LHRectDefinition[99].ScreenLocation.right = Round((767 - TILESHIFT) * stretchval);
	LHRectDefinition[99].locationID = 99;

	LHRectDefinition[100].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[100].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[100].ScreenLocation.left = Round((767 - TILESHIFT) * stretchval);
	LHRectDefinition[100].ScreenLocation.right = Round((820 - TILESHIFT) * stretchval);
	LHRectDefinition[100].locationID = 100;

	LHRectDefinition[101].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[101].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[101].ScreenLocation.left = Round((820 - TILESHIFT) * stretchval);
	LHRectDefinition[101].ScreenLocation.right = Round((873 - TILESHIFT) * stretchval);
	LHRectDefinition[101].locationID = 101;

	LHRectDefinition[102].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[102].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[102].ScreenLocation.left = Round((873 - TILESHIFT) * stretchval);
	LHRectDefinition[102].ScreenLocation.right = Round((926 - TILESHIFT) * stretchval);
	LHRectDefinition[102].locationID = 102;

	LHRectDefinition[103].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[103].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[103].ScreenLocation.left = Round((926 - TILESHIFT) * stretchval);
	LHRectDefinition[103].ScreenLocation.right = Round((979 - TILESHIFT) * stretchval);
	LHRectDefinition[103].locationID = 103;

	LHRectDefinition[104].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[104].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[104].ScreenLocation.left = Round((979 - TILESHIFT) * stretchval);
	LHRectDefinition[104].ScreenLocation.right = Round((1032 - TILESHIFT) * stretchval);
	LHRectDefinition[104].locationID = 104;

	LHRectDefinition[105].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[105].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[105].ScreenLocation.left = Round((1032 - TILESHIFT) * stretchval);
	LHRectDefinition[105].ScreenLocation.right = Round((1085 - TILESHIFT) * stretchval);
	LHRectDefinition[105].locationID = 105;

	LHRectDefinition[106].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[106].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[106].ScreenLocation.left = Round((1085 - TILESHIFT) * stretchval);
	LHRectDefinition[106].ScreenLocation.right = Round((1138 - TILESHIFT) * stretchval);
	LHRectDefinition[106].locationID = 106;

	LHRectDefinition[107].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[107].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[107].ScreenLocation.left = Round((1138 - TILESHIFT) * stretchval);
	LHRectDefinition[107].ScreenLocation.right = Round((1191 - TILESHIFT) * stretchval);
	LHRectDefinition[107].locationID = 107;

	LHRectDefinition[108].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[108].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[108].ScreenLocation.left = Round((1191 - TILESHIFT) * stretchval);
	LHRectDefinition[108].ScreenLocation.right = Round((1244 - TILESHIFT) * stretchval);
	LHRectDefinition[108].locationID = 108;

	LHRectDefinition[109].ScreenLocation.top = Round((290 + TILESHIFT) * stretchval);
	LHRectDefinition[109].ScreenLocation.bottom = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[109].ScreenLocation.left = Round((1244 - TILESHIFT) * stretchval);
	LHRectDefinition[109].ScreenLocation.right = Round((1297 - TILESHIFT) * stretchval);
	LHRectDefinition[109].locationID = 109;

	LHRectDefinition[110].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[110].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[110].ScreenLocation.left = Round((555 - TILESHIFT) * stretchval);
	LHRectDefinition[110].ScreenLocation.right = Round((608 - TILESHIFT) * stretchval);
	LHRectDefinition[110].locationID = 110;

	LHRectDefinition[111].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[111].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[111].ScreenLocation.left = Round((608 - TILESHIFT) * stretchval);
	LHRectDefinition[111].ScreenLocation.right = Round((661 - TILESHIFT) * stretchval);
	LHRectDefinition[111].locationID = 111;

	LHRectDefinition[112].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[112].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[112].ScreenLocation.left = Round((661 - TILESHIFT) * stretchval);
	LHRectDefinition[112].ScreenLocation.right = Round((714 - TILESHIFT) * stretchval);
	LHRectDefinition[112].locationID = 112;

	LHRectDefinition[113].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[113].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[113].ScreenLocation.left = Round((714 - TILESHIFT) * stretchval);
	LHRectDefinition[113].ScreenLocation.right = Round((767 - TILESHIFT) * stretchval);
	LHRectDefinition[113].locationID = 113;

	LHRectDefinition[114].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[114].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[114].ScreenLocation.left = Round((767 - TILESHIFT) * stretchval);
	LHRectDefinition[114].ScreenLocation.right = Round((820 - TILESHIFT) * stretchval);
	LHRectDefinition[114].locationID = 114;

	LHRectDefinition[115].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[115].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[115].ScreenLocation.left = Round((820 - TILESHIFT) * stretchval);
	LHRectDefinition[115].ScreenLocation.right = Round((873 - TILESHIFT) * stretchval);
	LHRectDefinition[115].locationID = 115;

	LHRectDefinition[116].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[116].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[116].ScreenLocation.left = Round((873 - TILESHIFT) * stretchval);
	LHRectDefinition[116].ScreenLocation.right = Round((926 - TILESHIFT) * stretchval);
	LHRectDefinition[116].locationID = 116;

	LHRectDefinition[117].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[117].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[117].ScreenLocation.left = Round((926 - TILESHIFT) * stretchval);
	LHRectDefinition[117].ScreenLocation.right = Round((979 - TILESHIFT) * stretchval);
	LHRectDefinition[117].locationID = 117;

	LHRectDefinition[118].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[118].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[118].ScreenLocation.left = Round((979 - TILESHIFT) * stretchval);
	LHRectDefinition[118].ScreenLocation.right = Round((1032 - TILESHIFT) * stretchval);
	LHRectDefinition[118].locationID = 118;

	LHRectDefinition[119].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[119].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[119].ScreenLocation.left = Round((1032 - TILESHIFT) * stretchval);
	LHRectDefinition[119].ScreenLocation.right = Round((1085 - TILESHIFT) * stretchval);
	LHRectDefinition[119].locationID = 119;

	LHRectDefinition[120].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[120].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[120].ScreenLocation.left = Round((1085 - TILESHIFT) * stretchval);
	LHRectDefinition[120].ScreenLocation.right = Round((1138 - TILESHIFT) * stretchval);
	LHRectDefinition[120].locationID = 120;

	LHRectDefinition[121].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[121].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[121].ScreenLocation.left = Round((1138 - TILESHIFT) * stretchval);
	LHRectDefinition[121].ScreenLocation.right = Round((1191 - TILESHIFT) * stretchval);
	LHRectDefinition[121].locationID = 121;

	LHRectDefinition[122].ScreenLocation.top = Round((370 + TILESHIFT) * stretchval);
	LHRectDefinition[122].ScreenLocation.bottom = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[122].ScreenLocation.left = Round((1191 - TILESHIFT) * stretchval);
	LHRectDefinition[122].ScreenLocation.right = Round((1244 - TILESHIFT) * stretchval);
	LHRectDefinition[122].locationID = 122;

	LHRectDefinition[123].ScreenLocation.top = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[123].ScreenLocation.bottom = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[123].ScreenLocation.left = Round((608 - TILESHIFT) * stretchval);
	LHRectDefinition[123].ScreenLocation.right = Round((661 - TILESHIFT) * stretchval);
	LHRectDefinition[123].locationID = 123;

	LHRectDefinition[124].ScreenLocation.top = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[124].ScreenLocation.bottom = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[124].ScreenLocation.left = Round((661 - TILESHIFT) * stretchval);
	LHRectDefinition[124].ScreenLocation.right = Round((714 - TILESHIFT) * stretchval);
	LHRectDefinition[124].locationID = 124;

	LHRectDefinition[125].ScreenLocation.top = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[125].ScreenLocation.bottom = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[125].ScreenLocation.left = Round((714 - TILESHIFT) * stretchval);
	LHRectDefinition[125].ScreenLocation.right = Round((767 - TILESHIFT) * stretchval);
	LHRectDefinition[125].locationID = 125;

	LHRectDefinition[126].ScreenLocation.top = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[126].ScreenLocation.bottom = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[126].ScreenLocation.left = Round((767 - TILESHIFT) * stretchval);
	LHRectDefinition[126].ScreenLocation.right = Round((820 - TILESHIFT) * stretchval);
	LHRectDefinition[126].locationID = 126;

	LHRectDefinition[127].ScreenLocation.top = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[127].ScreenLocation.bottom = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[127].ScreenLocation.left = Round((820 - TILESHIFT) * stretchval);
	LHRectDefinition[127].ScreenLocation.right = Round((873 - TILESHIFT) * stretchval);
	LHRectDefinition[127].locationID = 127;

	LHRectDefinition[128].ScreenLocation.top = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[128].ScreenLocation.bottom = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[128].ScreenLocation.left = Round((873 - TILESHIFT) * stretchval);
	LHRectDefinition[128].ScreenLocation.right = Round((926 - TILESHIFT) * stretchval);
	LHRectDefinition[128].locationID = 128;

	LHRectDefinition[129].ScreenLocation.top = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[129].ScreenLocation.bottom = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[129].ScreenLocation.left = Round((926 - TILESHIFT) * stretchval);
	LHRectDefinition[129].ScreenLocation.right = Round((979 - TILESHIFT) * stretchval);
	LHRectDefinition[129].locationID = 129;

	LHRectDefinition[130].ScreenLocation.top = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[130].ScreenLocation.bottom = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[130].ScreenLocation.left = Round((979 - TILESHIFT) * stretchval);
	LHRectDefinition[130].ScreenLocation.right = Round((1032 - TILESHIFT) * stretchval);
	LHRectDefinition[130].locationID = 130;

	LHRectDefinition[131].ScreenLocation.top = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[131].ScreenLocation.bottom = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[131].ScreenLocation.left = Round((1032 - TILESHIFT) * stretchval);
	LHRectDefinition[131].ScreenLocation.right = Round((1085 - TILESHIFT) * stretchval);
	LHRectDefinition[131].locationID = 131;

	LHRectDefinition[132].ScreenLocation.top = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[132].ScreenLocation.bottom = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[132].ScreenLocation.left = Round((1085 - TILESHIFT) * stretchval);
	LHRectDefinition[132].ScreenLocation.right = Round((1138 - TILESHIFT) * stretchval);
	LHRectDefinition[132].locationID = 132;

	LHRectDefinition[133].ScreenLocation.top = Round((450 + TILESHIFT) * stretchval);
	LHRectDefinition[133].ScreenLocation.bottom = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[133].ScreenLocation.left = Round((1138 - TILESHIFT) * stretchval);
	LHRectDefinition[133].ScreenLocation.right = Round((1191 - TILESHIFT) * stretchval);
	LHRectDefinition[133].locationID = 133;

	LHRectDefinition[134].ScreenLocation.top = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[134].ScreenLocation.bottom = Round((610 + TILESHIFT) * stretchval);
	LHRectDefinition[134].ScreenLocation.left = Round((767 - TILESHIFT) * stretchval);
	LHRectDefinition[134].ScreenLocation.right = Round((820 - TILESHIFT) * stretchval);
	LHRectDefinition[134].locationID = 134;

	LHRectDefinition[135].ScreenLocation.top = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[135].ScreenLocation.bottom = Round((610 + TILESHIFT) * stretchval);
	LHRectDefinition[135].ScreenLocation.left = Round((820 - TILESHIFT) * stretchval);
	LHRectDefinition[135].ScreenLocation.right = Round((873 - TILESHIFT) * stretchval);
	LHRectDefinition[135].locationID = 135;

	LHRectDefinition[136].ScreenLocation.top = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[136].ScreenLocation.bottom = Round((610 + TILESHIFT) * stretchval);
	LHRectDefinition[136].ScreenLocation.left = Round((873 - TILESHIFT) * stretchval);
	LHRectDefinition[136].ScreenLocation.right = Round((926 - TILESHIFT) * stretchval);
	LHRectDefinition[136].locationID = 136;

	LHRectDefinition[137].ScreenLocation.top = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[137].ScreenLocation.bottom = Round((610 + TILESHIFT) * stretchval);
	LHRectDefinition[137].ScreenLocation.left = Round((926 - TILESHIFT) * stretchval);
	LHRectDefinition[137].ScreenLocation.right = Round((979 - TILESHIFT) * stretchval);
	LHRectDefinition[137].locationID = 137;

	LHRectDefinition[138].ScreenLocation.top = Round((530 + TILESHIFT) * stretchval);
	LHRectDefinition[138].ScreenLocation.bottom = Round((610 + TILESHIFT) * stretchval);
	LHRectDefinition[138].ScreenLocation.left = Round((979 - TILESHIFT) * stretchval);
	LHRectDefinition[138].ScreenLocation.right = Round((1032 - TILESHIFT) * stretchval);
	LHRectDefinition[138].locationID = 138;

	LHRectDefinition[139].ScreenLocation.top = Round((610 + TILESHIFT) * stretchval);
	LHRectDefinition[139].ScreenLocation.bottom = Round((690 + TILESHIFT) * stretchval);
	LHRectDefinition[139].ScreenLocation.left = Round((820 - TILESHIFT) * stretchval);
	LHRectDefinition[139].ScreenLocation.right = Round((873 - TILESHIFT) * stretchval);
	LHRectDefinition[139].locationID = 139;

	LHRectDefinition[140].ScreenLocation.top = Round((610 + TILESHIFT) * stretchval);
	LHRectDefinition[140].ScreenLocation.bottom = Round((690 + TILESHIFT) * stretchval);
	LHRectDefinition[140].ScreenLocation.left = Round((873 - TILESHIFT) * stretchval);
	LHRectDefinition[140].ScreenLocation.right = Round((926 - TILESHIFT) * stretchval);
	LHRectDefinition[140].locationID = 140;

	LHRectDefinition[141].ScreenLocation.top = Round((610 + TILESHIFT) * stretchval);
	LHRectDefinition[141].ScreenLocation.bottom = Round((690 + TILESHIFT) * stretchval);
	LHRectDefinition[141].ScreenLocation.left = Round((926 - TILESHIFT) * stretchval);
	LHRectDefinition[141].ScreenLocation.right = Round((979 - TILESHIFT) * stretchval);
	LHRectDefinition[141].locationID = 141;

	LHRectDefinition[142].ScreenLocation.top = Round((690 + TILESHIFT) * stretchval);
	LHRectDefinition[142].ScreenLocation.bottom = Round((770 + TILESHIFT) * stretchval);
	LHRectDefinition[142].ScreenLocation.left = Round((820 - TILESHIFT) * stretchval);
	LHRectDefinition[142].ScreenLocation.right = Round((873 - TILESHIFT) * stretchval);
	LHRectDefinition[142].locationID = 142;

	LHRectDefinition[143].ScreenLocation.top = Round((690 + TILESHIFT) * stretchval);
	LHRectDefinition[143].ScreenLocation.bottom = Round((770 + TILESHIFT) * stretchval);
	LHRectDefinition[143].ScreenLocation.left = Round((873 - TILESHIFT) * stretchval);
	LHRectDefinition[143].ScreenLocation.right = Round((926 - TILESHIFT) * stretchval);
	LHRectDefinition[143].locationID = 143;

}

void CMJLonghorn::SetAdjancentIDs()
{

	LHRectDefinition[0].adjancentIDs.aboveID = -1;
	LHRectDefinition[0].adjancentIDs.bottomID = -1;
	LHRectDefinition[0].adjancentIDs.leftID = -1;
	LHRectDefinition[0].adjancentIDs.rightID = 1;
	LHRectDefinition[0].adjancentIDs.topID = -1;
	LHRectDefinition[0].adjancentIDs.belowID = -1;

	LHRectDefinition[1].adjancentIDs.aboveID = -1;
	LHRectDefinition[1].adjancentIDs.bottomID = -1;
	LHRectDefinition[1].adjancentIDs.leftID = 0;
	LHRectDefinition[1].adjancentIDs.rightID = 2;
	LHRectDefinition[1].adjancentIDs.topID = -1;
	LHRectDefinition[1].adjancentIDs.belowID = -1;

	LHRectDefinition[2].adjancentIDs.aboveID = -1;
	LHRectDefinition[2].adjancentIDs.bottomID = -1;
	LHRectDefinition[2].adjancentIDs.leftID = 1;
	LHRectDefinition[2].adjancentIDs.rightID = 3;
	LHRectDefinition[2].adjancentIDs.topID = -1;
	LHRectDefinition[2].adjancentIDs.belowID = -1;

	LHRectDefinition[3].adjancentIDs.aboveID = -1;
	LHRectDefinition[3].adjancentIDs.bottomID = 8;
	LHRectDefinition[3].adjancentIDs.leftID = 2;
	LHRectDefinition[3].adjancentIDs.rightID = -1;
	LHRectDefinition[3].adjancentIDs.topID = -1;
	LHRectDefinition[3].adjancentIDs.belowID = -1;

	LHRectDefinition[4].adjancentIDs.aboveID = -1;
	LHRectDefinition[4].adjancentIDs.bottomID = 15;
	LHRectDefinition[4].adjancentIDs.leftID = -1;
	LHRectDefinition[4].adjancentIDs.rightID = 5;
	LHRectDefinition[4].adjancentIDs.topID = -1;
	LHRectDefinition[4].adjancentIDs.belowID = -1;

	LHRectDefinition[5].adjancentIDs.aboveID = -1;
	LHRectDefinition[5].adjancentIDs.bottomID = -1;
	LHRectDefinition[5].adjancentIDs.leftID = 4;
	LHRectDefinition[5].adjancentIDs.rightID = 6;
	LHRectDefinition[5].adjancentIDs.topID = -1;
	LHRectDefinition[5].adjancentIDs.belowID = -1;

	LHRectDefinition[6].adjancentIDs.aboveID = -1;
	LHRectDefinition[6].adjancentIDs.bottomID = -1;
	LHRectDefinition[6].adjancentIDs.leftID = 5;
	LHRectDefinition[6].adjancentIDs.rightID = 7;
	LHRectDefinition[6].adjancentIDs.topID = -1;
	LHRectDefinition[6].adjancentIDs.belowID = -1;

	LHRectDefinition[7].adjancentIDs.aboveID = -1;
	LHRectDefinition[7].adjancentIDs.bottomID = -1;
	LHRectDefinition[7].adjancentIDs.leftID = 6;
	LHRectDefinition[7].adjancentIDs.rightID = -1;
	LHRectDefinition[7].adjancentIDs.topID = -1;
	LHRectDefinition[7].adjancentIDs.belowID = -1;

	LHRectDefinition[8].adjancentIDs.aboveID = -1;
	LHRectDefinition[8].adjancentIDs.bottomID = -1;
	LHRectDefinition[8].adjancentIDs.leftID = -1;
	LHRectDefinition[8].adjancentIDs.rightID = 9;
	LHRectDefinition[8].adjancentIDs.topID = 3;
	LHRectDefinition[8].adjancentIDs.belowID = -1;

	LHRectDefinition[9].adjancentIDs.aboveID = -1;
	LHRectDefinition[9].adjancentIDs.bottomID = -1;
	LHRectDefinition[9].adjancentIDs.leftID = 8;
	LHRectDefinition[9].adjancentIDs.rightID = 10;
	LHRectDefinition[9].adjancentIDs.topID = -1;
	LHRectDefinition[9].adjancentIDs.belowID = -1;

	LHRectDefinition[10].adjancentIDs.aboveID = -1;
	LHRectDefinition[10].adjancentIDs.bottomID = -1;
	LHRectDefinition[10].adjancentIDs.leftID = 9;
	LHRectDefinition[10].adjancentIDs.rightID = 11;
	LHRectDefinition[10].adjancentIDs.topID = -1;
	LHRectDefinition[10].adjancentIDs.belowID = -1;

	LHRectDefinition[11].adjancentIDs.aboveID = -1;
	LHRectDefinition[11].adjancentIDs.bottomID = 16;
	LHRectDefinition[11].adjancentIDs.leftID = 10;
	LHRectDefinition[11].adjancentIDs.rightID = -1;
	LHRectDefinition[11].adjancentIDs.topID = -1;
	LHRectDefinition[11].adjancentIDs.belowID = -1;

	LHRectDefinition[12].adjancentIDs.aboveID = -1;
	LHRectDefinition[12].adjancentIDs.bottomID = 23;
	LHRectDefinition[12].adjancentIDs.leftID = -1;
	LHRectDefinition[12].adjancentIDs.rightID = 13;
	LHRectDefinition[12].adjancentIDs.topID = -1;
	LHRectDefinition[12].adjancentIDs.belowID = -1;

	LHRectDefinition[13].adjancentIDs.aboveID = -1;
	LHRectDefinition[13].adjancentIDs.bottomID = -1;
	LHRectDefinition[13].adjancentIDs.leftID = 12;
	LHRectDefinition[13].adjancentIDs.rightID = 14;
	LHRectDefinition[13].adjancentIDs.topID = -1;
	LHRectDefinition[13].adjancentIDs.belowID = -1;

	LHRectDefinition[14].adjancentIDs.aboveID = -1;
	LHRectDefinition[14].adjancentIDs.bottomID = -1;
	LHRectDefinition[14].adjancentIDs.leftID = 13;
	LHRectDefinition[14].adjancentIDs.rightID = 15;
	LHRectDefinition[14].adjancentIDs.topID = -1;
	LHRectDefinition[14].adjancentIDs.belowID = -1;

	LHRectDefinition[15].adjancentIDs.aboveID = -1;
	LHRectDefinition[15].adjancentIDs.bottomID = -1;
	LHRectDefinition[15].adjancentIDs.leftID = 14;
	LHRectDefinition[15].adjancentIDs.rightID = -1;
	LHRectDefinition[15].adjancentIDs.topID = 4;
	LHRectDefinition[15].adjancentIDs.belowID = -1;

	LHRectDefinition[16].adjancentIDs.aboveID = -1;
	LHRectDefinition[16].adjancentIDs.bottomID = -1;
	LHRectDefinition[16].adjancentIDs.leftID = -1;
	LHRectDefinition[16].adjancentIDs.rightID = 17;
	LHRectDefinition[16].adjancentIDs.topID = 11;
	LHRectDefinition[16].adjancentIDs.belowID = -1;

	LHRectDefinition[17].adjancentIDs.aboveID = -1;
	LHRectDefinition[17].adjancentIDs.bottomID = -1;
	LHRectDefinition[17].adjancentIDs.leftID = 16;
	LHRectDefinition[17].adjancentIDs.rightID = 18;
	LHRectDefinition[17].adjancentIDs.topID = -1;
	LHRectDefinition[17].adjancentIDs.belowID = -1;

	LHRectDefinition[18].adjancentIDs.aboveID = -1;
	LHRectDefinition[18].adjancentIDs.bottomID = 24;
	LHRectDefinition[18].adjancentIDs.leftID = 17;
	LHRectDefinition[18].adjancentIDs.rightID = 19;
	LHRectDefinition[18].adjancentIDs.topID = -1;
	LHRectDefinition[18].adjancentIDs.belowID = -1;

	LHRectDefinition[19].adjancentIDs.aboveID = -1;
	LHRectDefinition[19].adjancentIDs.bottomID = 25;
	LHRectDefinition[19].adjancentIDs.leftID = 18;
	LHRectDefinition[19].adjancentIDs.rightID = -1;
	LHRectDefinition[19].adjancentIDs.topID = -1;
	LHRectDefinition[19].adjancentIDs.belowID = -1;

	LHRectDefinition[20].adjancentIDs.aboveID = -1;
	LHRectDefinition[20].adjancentIDs.bottomID = 39;
	LHRectDefinition[20].adjancentIDs.leftID = -1;
	LHRectDefinition[20].adjancentIDs.rightID = 21;
	LHRectDefinition[20].adjancentIDs.topID = -1;
	LHRectDefinition[20].adjancentIDs.belowID = -1;

	LHRectDefinition[21].adjancentIDs.aboveID = -1;
	LHRectDefinition[21].adjancentIDs.bottomID = 40;
	LHRectDefinition[21].adjancentIDs.leftID = 20;
	LHRectDefinition[21].adjancentIDs.rightID = 22;
	LHRectDefinition[21].adjancentIDs.topID = -1;
	LHRectDefinition[21].adjancentIDs.belowID = -1;

	LHRectDefinition[22].adjancentIDs.aboveID = -1;
	LHRectDefinition[22].adjancentIDs.bottomID = -1;
	LHRectDefinition[22].adjancentIDs.leftID = 21;
	LHRectDefinition[22].adjancentIDs.rightID = 23;
	LHRectDefinition[22].adjancentIDs.topID = -1;
	LHRectDefinition[22].adjancentIDs.belowID = -1;

	LHRectDefinition[23].adjancentIDs.aboveID = -1;
	LHRectDefinition[23].adjancentIDs.bottomID = -1;
	LHRectDefinition[23].adjancentIDs.leftID = 22;
	LHRectDefinition[23].adjancentIDs.rightID = -1;
	LHRectDefinition[23].adjancentIDs.topID = 12;
	LHRectDefinition[23].adjancentIDs.belowID = -1;

	LHRectDefinition[24].adjancentIDs.aboveID = -1;
	LHRectDefinition[24].adjancentIDs.bottomID = -1;
	LHRectDefinition[24].adjancentIDs.leftID = -1;
	LHRectDefinition[24].adjancentIDs.rightID = 25;
	LHRectDefinition[24].adjancentIDs.topID = 18;
	LHRectDefinition[24].adjancentIDs.belowID = -1;

	LHRectDefinition[25].adjancentIDs.aboveID = 95;
	LHRectDefinition[25].adjancentIDs.bottomID = 41;
	LHRectDefinition[25].adjancentIDs.leftID = 24;
	LHRectDefinition[25].adjancentIDs.rightID = 26;
	LHRectDefinition[25].adjancentIDs.topID = 19;
	LHRectDefinition[25].adjancentIDs.belowID = -1;

	LHRectDefinition[26].adjancentIDs.aboveID = 96;
	LHRectDefinition[26].adjancentIDs.bottomID = 42;
	LHRectDefinition[26].adjancentIDs.leftID = 25;
	LHRectDefinition[26].adjancentIDs.rightID = 27;
	LHRectDefinition[26].adjancentIDs.topID = -1;
	LHRectDefinition[26].adjancentIDs.belowID = -1;

	LHRectDefinition[27].adjancentIDs.aboveID = 97;
	LHRectDefinition[27].adjancentIDs.bottomID = 43;
	LHRectDefinition[27].adjancentIDs.leftID = 26;
	LHRectDefinition[27].adjancentIDs.rightID = 28;
	LHRectDefinition[27].adjancentIDs.topID = -1;
	LHRectDefinition[27].adjancentIDs.belowID = -1;

	LHRectDefinition[28].adjancentIDs.aboveID = 98;
	LHRectDefinition[28].adjancentIDs.bottomID = 44;
	LHRectDefinition[28].adjancentIDs.leftID = 27;
	LHRectDefinition[28].adjancentIDs.rightID = 29;
	LHRectDefinition[28].adjancentIDs.topID = -1;
	LHRectDefinition[28].adjancentIDs.belowID = -1;

	LHRectDefinition[29].adjancentIDs.aboveID = 99;
	LHRectDefinition[29].adjancentIDs.bottomID = 45;
	LHRectDefinition[29].adjancentIDs.leftID = 28;
	LHRectDefinition[29].adjancentIDs.rightID = 30;
	LHRectDefinition[29].adjancentIDs.topID = -1;
	LHRectDefinition[29].adjancentIDs.belowID = -1;

	LHRectDefinition[30].adjancentIDs.aboveID = 100;
	LHRectDefinition[30].adjancentIDs.bottomID = 46;
	LHRectDefinition[30].adjancentIDs.leftID = 29;
	LHRectDefinition[30].adjancentIDs.rightID = 31;
	LHRectDefinition[30].adjancentIDs.topID = -1;
	LHRectDefinition[30].adjancentIDs.belowID = -1;

	LHRectDefinition[31].adjancentIDs.aboveID = 101;
	LHRectDefinition[31].adjancentIDs.bottomID = 47;
	LHRectDefinition[31].adjancentIDs.leftID = 30;
	LHRectDefinition[31].adjancentIDs.rightID = 32;
	LHRectDefinition[31].adjancentIDs.topID = -1;
	LHRectDefinition[31].adjancentIDs.belowID = -1;

	LHRectDefinition[32].adjancentIDs.aboveID = 102;
	LHRectDefinition[32].adjancentIDs.bottomID = 48;
	LHRectDefinition[32].adjancentIDs.leftID = 31;
	LHRectDefinition[32].adjancentIDs.rightID = 33;
	LHRectDefinition[32].adjancentIDs.topID = -1;
	LHRectDefinition[32].adjancentIDs.belowID = -1;

	LHRectDefinition[33].adjancentIDs.aboveID = 103;
	LHRectDefinition[33].adjancentIDs.bottomID = 49;
	LHRectDefinition[33].adjancentIDs.leftID = 32;
	LHRectDefinition[33].adjancentIDs.rightID = 34;
	LHRectDefinition[33].adjancentIDs.topID = -1;
	LHRectDefinition[33].adjancentIDs.belowID = -1;

	LHRectDefinition[34].adjancentIDs.aboveID = 104;
	LHRectDefinition[34].adjancentIDs.bottomID = 50;
	LHRectDefinition[34].adjancentIDs.leftID = 33;
	LHRectDefinition[34].adjancentIDs.rightID = 35;
	LHRectDefinition[34].adjancentIDs.topID = -1;
	LHRectDefinition[34].adjancentIDs.belowID = -1;

	LHRectDefinition[35].adjancentIDs.aboveID = 105;
	LHRectDefinition[35].adjancentIDs.bottomID = 51;
	LHRectDefinition[35].adjancentIDs.leftID = 34;
	LHRectDefinition[35].adjancentIDs.rightID = 36;
	LHRectDefinition[35].adjancentIDs.topID = -1;
	LHRectDefinition[35].adjancentIDs.belowID = -1;

	LHRectDefinition[36].adjancentIDs.aboveID = 106;
	LHRectDefinition[36].adjancentIDs.bottomID = 52;
	LHRectDefinition[36].adjancentIDs.leftID = 35;
	LHRectDefinition[36].adjancentIDs.rightID = 37;
	LHRectDefinition[36].adjancentIDs.topID = -1;
	LHRectDefinition[36].adjancentIDs.belowID = -1;

	LHRectDefinition[37].adjancentIDs.aboveID = 107;
	LHRectDefinition[37].adjancentIDs.bottomID = 53;
	LHRectDefinition[37].adjancentIDs.leftID = 36;
	LHRectDefinition[37].adjancentIDs.rightID = 38;
	LHRectDefinition[37].adjancentIDs.topID = -1;
	LHRectDefinition[37].adjancentIDs.belowID = -1;

	LHRectDefinition[38].adjancentIDs.aboveID = 108;
	LHRectDefinition[38].adjancentIDs.bottomID = 54;
	LHRectDefinition[38].adjancentIDs.leftID = 37;
	LHRectDefinition[38].adjancentIDs.rightID = 39;
	LHRectDefinition[38].adjancentIDs.topID = -1;
	LHRectDefinition[38].adjancentIDs.belowID = -1;

	LHRectDefinition[39].adjancentIDs.aboveID = 109;
	LHRectDefinition[39].adjancentIDs.bottomID = 55;
	LHRectDefinition[39].adjancentIDs.leftID = 38;
	LHRectDefinition[39].adjancentIDs.rightID = 40;
	LHRectDefinition[39].adjancentIDs.topID = 20;
	LHRectDefinition[39].adjancentIDs.belowID = -1;

	LHRectDefinition[40].adjancentIDs.aboveID = -1;
	LHRectDefinition[40].adjancentIDs.bottomID = -1;
	LHRectDefinition[40].adjancentIDs.leftID = 39;
	LHRectDefinition[40].adjancentIDs.rightID = -1;
	LHRectDefinition[40].adjancentIDs.topID = 21;
	LHRectDefinition[40].adjancentIDs.belowID = -1;

	LHRectDefinition[41].adjancentIDs.aboveID = -1;
	LHRectDefinition[41].adjancentIDs.bottomID = -1;
	LHRectDefinition[41].adjancentIDs.leftID = -1;
	LHRectDefinition[41].adjancentIDs.rightID = 42;
	LHRectDefinition[41].adjancentIDs.topID = 25;
	LHRectDefinition[41].adjancentIDs.belowID = -1;

	LHRectDefinition[42].adjancentIDs.aboveID = 110;
	LHRectDefinition[42].adjancentIDs.bottomID = 56;
	LHRectDefinition[42].adjancentIDs.leftID = 41;
	LHRectDefinition[42].adjancentIDs.rightID = 43;
	LHRectDefinition[42].adjancentIDs.topID = 26;
	LHRectDefinition[42].adjancentIDs.belowID = -1;

	LHRectDefinition[43].adjancentIDs.aboveID = 111;
	LHRectDefinition[43].adjancentIDs.bottomID = 57;
	LHRectDefinition[43].adjancentIDs.leftID = 42;
	LHRectDefinition[43].adjancentIDs.rightID = 44;
	LHRectDefinition[43].adjancentIDs.topID = 27;
	LHRectDefinition[43].adjancentIDs.belowID = -1;

	LHRectDefinition[44].adjancentIDs.aboveID = 112;
	LHRectDefinition[44].adjancentIDs.bottomID = 58;
	LHRectDefinition[44].adjancentIDs.leftID = 43;
	LHRectDefinition[44].adjancentIDs.rightID = 45;
	LHRectDefinition[44].adjancentIDs.topID = 28;
	LHRectDefinition[44].adjancentIDs.belowID = -1;

	LHRectDefinition[45].adjancentIDs.aboveID = 113;
	LHRectDefinition[45].adjancentIDs.bottomID = 59;
	LHRectDefinition[45].adjancentIDs.leftID = 44;
	LHRectDefinition[45].adjancentIDs.rightID = 46;
	LHRectDefinition[45].adjancentIDs.topID = 29;
	LHRectDefinition[45].adjancentIDs.belowID = -1;

	LHRectDefinition[46].adjancentIDs.aboveID = 114;
	LHRectDefinition[46].adjancentIDs.bottomID = 60;
	LHRectDefinition[46].adjancentIDs.leftID = 45;
	LHRectDefinition[46].adjancentIDs.rightID = 47;
	LHRectDefinition[46].adjancentIDs.topID = 30;
	LHRectDefinition[46].adjancentIDs.belowID = -1;

	LHRectDefinition[47].adjancentIDs.aboveID = 115;
	LHRectDefinition[47].adjancentIDs.bottomID = 61;
	LHRectDefinition[47].adjancentIDs.leftID = 46;
	LHRectDefinition[47].adjancentIDs.rightID = 48;
	LHRectDefinition[47].adjancentIDs.topID = 31;
	LHRectDefinition[47].adjancentIDs.belowID = -1;

	LHRectDefinition[48].adjancentIDs.aboveID = 116;
	LHRectDefinition[48].adjancentIDs.bottomID = 62;
	LHRectDefinition[48].adjancentIDs.leftID = 47;
	LHRectDefinition[48].adjancentIDs.rightID = 49;
	LHRectDefinition[48].adjancentIDs.topID = 32;
	LHRectDefinition[48].adjancentIDs.belowID = -1;

	LHRectDefinition[49].adjancentIDs.aboveID = 117;
	LHRectDefinition[49].adjancentIDs.bottomID = 63;
	LHRectDefinition[49].adjancentIDs.leftID = 48;
	LHRectDefinition[49].adjancentIDs.rightID = 50;
	LHRectDefinition[49].adjancentIDs.topID = 33;
	LHRectDefinition[49].adjancentIDs.belowID = -1;

	LHRectDefinition[50].adjancentIDs.aboveID = 118;
	LHRectDefinition[50].adjancentIDs.bottomID = 64;
	LHRectDefinition[50].adjancentIDs.leftID = 49;
	LHRectDefinition[50].adjancentIDs.rightID = 51;
	LHRectDefinition[50].adjancentIDs.topID = 34;
	LHRectDefinition[50].adjancentIDs.belowID = -1;

	LHRectDefinition[51].adjancentIDs.aboveID = 119;
	LHRectDefinition[51].adjancentIDs.bottomID = 65;
	LHRectDefinition[51].adjancentIDs.leftID = 50;
	LHRectDefinition[51].adjancentIDs.rightID = 52;
	LHRectDefinition[51].adjancentIDs.topID = 35;
	LHRectDefinition[51].adjancentIDs.belowID = -1;

	LHRectDefinition[52].adjancentIDs.aboveID = 120;
	LHRectDefinition[52].adjancentIDs.bottomID = 66;
	LHRectDefinition[52].adjancentIDs.leftID = 51;
	LHRectDefinition[52].adjancentIDs.rightID = 53;
	LHRectDefinition[52].adjancentIDs.topID = 36;
	LHRectDefinition[52].adjancentIDs.belowID = -1;

	LHRectDefinition[53].adjancentIDs.aboveID = 121;
	LHRectDefinition[53].adjancentIDs.bottomID = 67;
	LHRectDefinition[53].adjancentIDs.leftID = 52;
	LHRectDefinition[53].adjancentIDs.rightID = 54;
	LHRectDefinition[53].adjancentIDs.topID = 37;
	LHRectDefinition[53].adjancentIDs.belowID = -1;

	LHRectDefinition[54].adjancentIDs.aboveID = 122;
	LHRectDefinition[54].adjancentIDs.bottomID = 68;
	LHRectDefinition[54].adjancentIDs.leftID = 53;
	LHRectDefinition[54].adjancentIDs.rightID = 55;
	LHRectDefinition[54].adjancentIDs.topID = 38;
	LHRectDefinition[54].adjancentIDs.belowID = -1;

	LHRectDefinition[55].adjancentIDs.aboveID = -1;
	LHRectDefinition[55].adjancentIDs.bottomID = -1;
	LHRectDefinition[55].adjancentIDs.leftID = 54;
	LHRectDefinition[55].adjancentIDs.rightID = -1;
	LHRectDefinition[55].adjancentIDs.topID = 39;
	LHRectDefinition[55].adjancentIDs.belowID = -1;

	LHRectDefinition[56].adjancentIDs.aboveID = -1;
	LHRectDefinition[56].adjancentIDs.bottomID = -1;
	LHRectDefinition[56].adjancentIDs.leftID = -1;
	LHRectDefinition[56].adjancentIDs.rightID = 57;
	LHRectDefinition[56].adjancentIDs.topID = 42;
	LHRectDefinition[56].adjancentIDs.belowID = -1;

	LHRectDefinition[57].adjancentIDs.aboveID = 123;
	LHRectDefinition[57].adjancentIDs.bottomID = -1;
	LHRectDefinition[57].adjancentIDs.leftID = 56;
	LHRectDefinition[57].adjancentIDs.rightID = 58;
	LHRectDefinition[57].adjancentIDs.topID = 43;
	LHRectDefinition[57].adjancentIDs.belowID = -1;

	LHRectDefinition[58].adjancentIDs.aboveID = 124;
	LHRectDefinition[58].adjancentIDs.bottomID = -1;
	LHRectDefinition[58].adjancentIDs.leftID = 57;
	LHRectDefinition[58].adjancentIDs.rightID = 59;
	LHRectDefinition[58].adjancentIDs.topID = 44;
	LHRectDefinition[58].adjancentIDs.belowID = -1;

	LHRectDefinition[59].adjancentIDs.aboveID = 125;
	LHRectDefinition[59].adjancentIDs.bottomID = 69;
	LHRectDefinition[59].adjancentIDs.leftID = 58;
	LHRectDefinition[59].adjancentIDs.rightID = 60;
	LHRectDefinition[59].adjancentIDs.topID = 45;
	LHRectDefinition[59].adjancentIDs.belowID = -1;

	LHRectDefinition[60].adjancentIDs.aboveID = 126;
	LHRectDefinition[60].adjancentIDs.bottomID = 70;
	LHRectDefinition[60].adjancentIDs.leftID = 59;
	LHRectDefinition[60].adjancentIDs.rightID = 61;
	LHRectDefinition[60].adjancentIDs.topID = 46;
	LHRectDefinition[60].adjancentIDs.belowID = -1;

	LHRectDefinition[61].adjancentIDs.aboveID = 127;
	LHRectDefinition[61].adjancentIDs.bottomID = 71;
	LHRectDefinition[61].adjancentIDs.leftID = 60;
	LHRectDefinition[61].adjancentIDs.rightID = 62;
	LHRectDefinition[61].adjancentIDs.topID = 47;
	LHRectDefinition[61].adjancentIDs.belowID = -1;

	LHRectDefinition[62].adjancentIDs.aboveID = 128;
	LHRectDefinition[62].adjancentIDs.bottomID = 72;
	LHRectDefinition[62].adjancentIDs.leftID = 61;
	LHRectDefinition[62].adjancentIDs.rightID = 63;
	LHRectDefinition[62].adjancentIDs.topID = 48;
	LHRectDefinition[62].adjancentIDs.belowID = -1;

	LHRectDefinition[63].adjancentIDs.aboveID = 129;
	LHRectDefinition[63].adjancentIDs.bottomID = 73;
	LHRectDefinition[63].adjancentIDs.leftID = 62;
	LHRectDefinition[63].adjancentIDs.rightID = 64;
	LHRectDefinition[63].adjancentIDs.topID = 49;
	LHRectDefinition[63].adjancentIDs.belowID = -1;

	LHRectDefinition[64].adjancentIDs.aboveID = 130;
	LHRectDefinition[64].adjancentIDs.bottomID = 74;
	LHRectDefinition[64].adjancentIDs.leftID = 63;
	LHRectDefinition[64].adjancentIDs.rightID = 65;
	LHRectDefinition[64].adjancentIDs.topID = 50;
	LHRectDefinition[64].adjancentIDs.belowID = -1;

	LHRectDefinition[65].adjancentIDs.aboveID = 131;
	LHRectDefinition[65].adjancentIDs.bottomID = 75;
	LHRectDefinition[65].adjancentIDs.leftID = 64;
	LHRectDefinition[65].adjancentIDs.rightID = 66;
	LHRectDefinition[65].adjancentIDs.topID = 51;
	LHRectDefinition[65].adjancentIDs.belowID = -1;

	LHRectDefinition[66].adjancentIDs.aboveID = 132;
	LHRectDefinition[66].adjancentIDs.bottomID = -1;
	LHRectDefinition[66].adjancentIDs.leftID = 65;
	LHRectDefinition[66].adjancentIDs.rightID = 67;
	LHRectDefinition[66].adjancentIDs.topID = 52;
	LHRectDefinition[66].adjancentIDs.belowID = -1;

	LHRectDefinition[67].adjancentIDs.aboveID = 133;
	LHRectDefinition[67].adjancentIDs.bottomID = -1;
	LHRectDefinition[67].adjancentIDs.leftID = 66;
	LHRectDefinition[67].adjancentIDs.rightID = 68;
	LHRectDefinition[67].adjancentIDs.topID = 53;
	LHRectDefinition[67].adjancentIDs.belowID = -1;

	LHRectDefinition[68].adjancentIDs.aboveID = -1;
	LHRectDefinition[68].adjancentIDs.bottomID = -1;
	LHRectDefinition[68].adjancentIDs.leftID = 67;
	LHRectDefinition[68].adjancentIDs.rightID = -1;
	LHRectDefinition[68].adjancentIDs.topID = 54;
	LHRectDefinition[68].adjancentIDs.belowID = -1;

	LHRectDefinition[69].adjancentIDs.aboveID = -1;
	LHRectDefinition[69].adjancentIDs.bottomID = -1;
	LHRectDefinition[69].adjancentIDs.leftID = -1;
	LHRectDefinition[69].adjancentIDs.rightID = 70;
	LHRectDefinition[69].adjancentIDs.topID = 59;
	LHRectDefinition[69].adjancentIDs.belowID = -1;

	LHRectDefinition[70].adjancentIDs.aboveID = 134;
	LHRectDefinition[70].adjancentIDs.bottomID = 76;
	LHRectDefinition[70].adjancentIDs.leftID = 69;
	LHRectDefinition[70].adjancentIDs.rightID = 71;
	LHRectDefinition[70].adjancentIDs.topID = 60;
	LHRectDefinition[70].adjancentIDs.belowID = -1;

	LHRectDefinition[71].adjancentIDs.aboveID = 135;
	LHRectDefinition[71].adjancentIDs.bottomID = 77;
	LHRectDefinition[71].adjancentIDs.leftID = 70;
	LHRectDefinition[71].adjancentIDs.rightID = 72;
	LHRectDefinition[71].adjancentIDs.topID = 61;
	LHRectDefinition[71].adjancentIDs.belowID = -1;

	LHRectDefinition[72].adjancentIDs.aboveID = 136;
	LHRectDefinition[72].adjancentIDs.bottomID = 78;
	LHRectDefinition[72].adjancentIDs.leftID = 71;
	LHRectDefinition[72].adjancentIDs.rightID = 73;
	LHRectDefinition[72].adjancentIDs.topID = 62;
	LHRectDefinition[72].adjancentIDs.belowID = -1;

	LHRectDefinition[73].adjancentIDs.aboveID = 137;
	LHRectDefinition[73].adjancentIDs.bottomID = 79;
	LHRectDefinition[73].adjancentIDs.leftID = 72;
	LHRectDefinition[73].adjancentIDs.rightID = 74;
	LHRectDefinition[73].adjancentIDs.topID = 63;
	LHRectDefinition[73].adjancentIDs.belowID = -1;

	LHRectDefinition[74].adjancentIDs.aboveID = 138;
	LHRectDefinition[74].adjancentIDs.bottomID = 80;
	LHRectDefinition[74].adjancentIDs.leftID = 73;
	LHRectDefinition[74].adjancentIDs.rightID = 75;
	LHRectDefinition[74].adjancentIDs.topID = 64;
	LHRectDefinition[74].adjancentIDs.belowID = -1;

	LHRectDefinition[75].adjancentIDs.aboveID = -1;
	LHRectDefinition[75].adjancentIDs.bottomID = -1;
	LHRectDefinition[75].adjancentIDs.leftID = 74;
	LHRectDefinition[75].adjancentIDs.rightID = -1;
	LHRectDefinition[75].adjancentIDs.topID = 65;
	LHRectDefinition[75].adjancentIDs.belowID = -1;

	LHRectDefinition[76].adjancentIDs.aboveID = -1;
	LHRectDefinition[76].adjancentIDs.bottomID = 81;
	LHRectDefinition[76].adjancentIDs.leftID = -1;
	LHRectDefinition[76].adjancentIDs.rightID = 77;
	LHRectDefinition[76].adjancentIDs.topID = 70;
	LHRectDefinition[76].adjancentIDs.belowID = -1;

	LHRectDefinition[77].adjancentIDs.aboveID = 139;
	LHRectDefinition[77].adjancentIDs.bottomID = 82;
	LHRectDefinition[77].adjancentIDs.leftID = 76;
	LHRectDefinition[77].adjancentIDs.rightID = 78;
	LHRectDefinition[77].adjancentIDs.topID = 71;
	LHRectDefinition[77].adjancentIDs.belowID = -1;

	LHRectDefinition[78].adjancentIDs.aboveID = 140;
	LHRectDefinition[78].adjancentIDs.bottomID = 83;
	LHRectDefinition[78].adjancentIDs.leftID = 77;
	LHRectDefinition[78].adjancentIDs.rightID = 79;
	LHRectDefinition[78].adjancentIDs.topID = 72;
	LHRectDefinition[78].adjancentIDs.belowID = -1;

	LHRectDefinition[79].adjancentIDs.aboveID = 141;
	LHRectDefinition[79].adjancentIDs.bottomID = 84;
	LHRectDefinition[79].adjancentIDs.leftID = 78;
	LHRectDefinition[79].adjancentIDs.rightID = 80;
	LHRectDefinition[79].adjancentIDs.topID = 73;
	LHRectDefinition[79].adjancentIDs.belowID = -1;

	LHRectDefinition[80].adjancentIDs.aboveID = -1;
	LHRectDefinition[80].adjancentIDs.bottomID = 85;
	LHRectDefinition[80].adjancentIDs.leftID = 79;
	LHRectDefinition[80].adjancentIDs.rightID = -1;
	LHRectDefinition[80].adjancentIDs.topID = 74;
	LHRectDefinition[80].adjancentIDs.belowID = -1;

	LHRectDefinition[81].adjancentIDs.aboveID = -1;
	LHRectDefinition[81].adjancentIDs.bottomID = -1;
	LHRectDefinition[81].adjancentIDs.leftID = -1;
	LHRectDefinition[81].adjancentIDs.rightID = 82;
	LHRectDefinition[81].adjancentIDs.topID = 76;
	LHRectDefinition[81].adjancentIDs.belowID = -1;

	LHRectDefinition[82].adjancentIDs.aboveID = 142;
	LHRectDefinition[82].adjancentIDs.bottomID = 86;
	LHRectDefinition[82].adjancentIDs.leftID = 81;
	LHRectDefinition[82].adjancentIDs.rightID = 83;
	LHRectDefinition[82].adjancentIDs.topID = 77;
	LHRectDefinition[82].adjancentIDs.belowID = -1;

	LHRectDefinition[83].adjancentIDs.aboveID = 143;
	LHRectDefinition[83].adjancentIDs.bottomID = 87;
	LHRectDefinition[83].adjancentIDs.leftID = 82;
	LHRectDefinition[83].adjancentIDs.rightID = 84;
	LHRectDefinition[83].adjancentIDs.topID = 78;
	LHRectDefinition[83].adjancentIDs.belowID = -1;

	LHRectDefinition[84].adjancentIDs.aboveID = -1;
	LHRectDefinition[84].adjancentIDs.bottomID = 88;
	LHRectDefinition[84].adjancentIDs.leftID = 83;
	LHRectDefinition[84].adjancentIDs.rightID = 85;
	LHRectDefinition[84].adjancentIDs.topID = 79;
	LHRectDefinition[84].adjancentIDs.belowID = -1;

	LHRectDefinition[85].adjancentIDs.aboveID = -1;
	LHRectDefinition[85].adjancentIDs.bottomID = -1;
	LHRectDefinition[85].adjancentIDs.leftID = 84;
	LHRectDefinition[85].adjancentIDs.rightID = -1;
	LHRectDefinition[85].adjancentIDs.topID = 80;
	LHRectDefinition[85].adjancentIDs.belowID = -1;

	LHRectDefinition[86].adjancentIDs.aboveID = -1;
	LHRectDefinition[86].adjancentIDs.bottomID = 89;
	LHRectDefinition[86].adjancentIDs.leftID = -1;
	LHRectDefinition[86].adjancentIDs.rightID = 87;
	LHRectDefinition[86].adjancentIDs.topID = 82;
	LHRectDefinition[86].adjancentIDs.belowID = -1;

	LHRectDefinition[87].adjancentIDs.aboveID = -1;
	LHRectDefinition[87].adjancentIDs.bottomID = 90;
	LHRectDefinition[87].adjancentIDs.leftID = 86;
	LHRectDefinition[87].adjancentIDs.rightID = 88;
	LHRectDefinition[87].adjancentIDs.topID = 83;
	LHRectDefinition[87].adjancentIDs.belowID = -1;

	LHRectDefinition[88].adjancentIDs.aboveID = -1;
	LHRectDefinition[88].adjancentIDs.bottomID = 91;
	LHRectDefinition[88].adjancentIDs.leftID = 87;
	LHRectDefinition[88].adjancentIDs.rightID = -1;
	LHRectDefinition[88].adjancentIDs.topID = 84;
	LHRectDefinition[88].adjancentIDs.belowID = -1;

	LHRectDefinition[89].adjancentIDs.aboveID = -1;
	LHRectDefinition[89].adjancentIDs.bottomID = 92;
	LHRectDefinition[89].adjancentIDs.leftID = -1;
	LHRectDefinition[89].adjancentIDs.rightID = 90;
	LHRectDefinition[89].adjancentIDs.topID = 86;
	LHRectDefinition[89].adjancentIDs.belowID = -1;

	LHRectDefinition[90].adjancentIDs.aboveID = -1;
	LHRectDefinition[90].adjancentIDs.bottomID = 93;
	LHRectDefinition[90].adjancentIDs.leftID = 89;
	LHRectDefinition[90].adjancentIDs.rightID = 91;
	LHRectDefinition[90].adjancentIDs.topID = 87;
	LHRectDefinition[90].adjancentIDs.belowID = -1;

	LHRectDefinition[91].adjancentIDs.aboveID = -1;
	LHRectDefinition[91].adjancentIDs.bottomID = 94;
	LHRectDefinition[91].adjancentIDs.leftID = 90;
	LHRectDefinition[91].adjancentIDs.rightID = -1;
	LHRectDefinition[91].adjancentIDs.topID = 88;
	LHRectDefinition[91].adjancentIDs.belowID = -1;

	LHRectDefinition[92].adjancentIDs.aboveID = -1;
	LHRectDefinition[92].adjancentIDs.bottomID = -1;
	LHRectDefinition[92].adjancentIDs.leftID = -1;
	LHRectDefinition[92].adjancentIDs.rightID = 93;
	LHRectDefinition[92].adjancentIDs.topID = 89;
	LHRectDefinition[92].adjancentIDs.belowID = -1;

	LHRectDefinition[93].adjancentIDs.aboveID = -1;
	LHRectDefinition[93].adjancentIDs.bottomID = -1;
	LHRectDefinition[93].adjancentIDs.leftID = 92;
	LHRectDefinition[93].adjancentIDs.rightID = 94;
	LHRectDefinition[93].adjancentIDs.topID = 90;
	LHRectDefinition[93].adjancentIDs.belowID = -1;

	LHRectDefinition[94].adjancentIDs.aboveID = -1;
	LHRectDefinition[94].adjancentIDs.bottomID = -1;
	LHRectDefinition[94].adjancentIDs.leftID = 93;
	LHRectDefinition[94].adjancentIDs.rightID = -1;
	LHRectDefinition[94].adjancentIDs.topID = 91;
	LHRectDefinition[94].adjancentIDs.belowID = -1;

	LHRectDefinition[95].adjancentIDs.aboveID = -1;
	LHRectDefinition[95].adjancentIDs.bottomID = -1;
	LHRectDefinition[95].adjancentIDs.leftID = -1;
	LHRectDefinition[95].adjancentIDs.rightID = 96;
	LHRectDefinition[95].adjancentIDs.topID = -1;
	LHRectDefinition[95].adjancentIDs.belowID = 25;

	LHRectDefinition[96].adjancentIDs.aboveID = -1;
	LHRectDefinition[96].adjancentIDs.bottomID = 110;
	LHRectDefinition[96].adjancentIDs.leftID = 95;
	LHRectDefinition[96].adjancentIDs.rightID = 97;
	LHRectDefinition[96].adjancentIDs.topID = -1;
	LHRectDefinition[96].adjancentIDs.belowID = 26;

	LHRectDefinition[97].adjancentIDs.aboveID = -1;
	LHRectDefinition[97].adjancentIDs.bottomID = 111;
	LHRectDefinition[97].adjancentIDs.leftID = 96;
	LHRectDefinition[97].adjancentIDs.rightID = 98;
	LHRectDefinition[97].adjancentIDs.topID = -1;
	LHRectDefinition[97].adjancentIDs.belowID = 27;

	LHRectDefinition[98].adjancentIDs.aboveID = -1;
	LHRectDefinition[98].adjancentIDs.bottomID = 112;
	LHRectDefinition[98].adjancentIDs.leftID = 97;
	LHRectDefinition[98].adjancentIDs.rightID = 99;
	LHRectDefinition[98].adjancentIDs.topID = -1;
	LHRectDefinition[98].adjancentIDs.belowID = 28;

	LHRectDefinition[99].adjancentIDs.aboveID = -1;
	LHRectDefinition[99].adjancentIDs.bottomID = 113;
	LHRectDefinition[99].adjancentIDs.leftID = 98;
	LHRectDefinition[99].adjancentIDs.rightID = 100;
	LHRectDefinition[99].adjancentIDs.topID = -1;
	LHRectDefinition[99].adjancentIDs.belowID = 29;

	LHRectDefinition[100].adjancentIDs.aboveID = -1;
	LHRectDefinition[100].adjancentIDs.bottomID = 114;
	LHRectDefinition[100].adjancentIDs.leftID = 99;
	LHRectDefinition[100].adjancentIDs.rightID = 101;
	LHRectDefinition[100].adjancentIDs.topID = -1;
	LHRectDefinition[100].adjancentIDs.belowID = 30;

	LHRectDefinition[101].adjancentIDs.aboveID = -1;
	LHRectDefinition[101].adjancentIDs.bottomID = 115;
	LHRectDefinition[101].adjancentIDs.leftID = 100;
	LHRectDefinition[101].adjancentIDs.rightID = 102;
	LHRectDefinition[101].adjancentIDs.topID = -1;
	LHRectDefinition[101].adjancentIDs.belowID = 31;

	LHRectDefinition[102].adjancentIDs.aboveID = -1;
	LHRectDefinition[102].adjancentIDs.bottomID = 116;
	LHRectDefinition[102].adjancentIDs.leftID = 101;
	LHRectDefinition[102].adjancentIDs.rightID = 103;
	LHRectDefinition[102].adjancentIDs.topID = -1;
	LHRectDefinition[102].adjancentIDs.belowID = 32;

	LHRectDefinition[103].adjancentIDs.aboveID = -1;
	LHRectDefinition[103].adjancentIDs.bottomID = 117;
	LHRectDefinition[103].adjancentIDs.leftID = 102;
	LHRectDefinition[103].adjancentIDs.rightID = 104;
	LHRectDefinition[103].adjancentIDs.topID = -1;
	LHRectDefinition[103].adjancentIDs.belowID = 33;

	LHRectDefinition[104].adjancentIDs.aboveID = -1;
	LHRectDefinition[104].adjancentIDs.bottomID = 118;
	LHRectDefinition[104].adjancentIDs.leftID = 103;
	LHRectDefinition[104].adjancentIDs.rightID = 105;
	LHRectDefinition[104].adjancentIDs.topID = -1;
	LHRectDefinition[104].adjancentIDs.belowID = 34;

	LHRectDefinition[105].adjancentIDs.aboveID = -1;
	LHRectDefinition[105].adjancentIDs.bottomID = 119;
	LHRectDefinition[105].adjancentIDs.leftID = 104;
	LHRectDefinition[105].adjancentIDs.rightID = 106;
	LHRectDefinition[105].adjancentIDs.topID = -1;
	LHRectDefinition[105].adjancentIDs.belowID = 35;

	LHRectDefinition[106].adjancentIDs.aboveID = -1;
	LHRectDefinition[106].adjancentIDs.bottomID = 120;
	LHRectDefinition[106].adjancentIDs.leftID = 105;
	LHRectDefinition[106].adjancentIDs.rightID = 107;
	LHRectDefinition[106].adjancentIDs.topID = -1;
	LHRectDefinition[106].adjancentIDs.belowID = 36;

	LHRectDefinition[107].adjancentIDs.aboveID = -1;
	LHRectDefinition[107].adjancentIDs.bottomID = 121;
	LHRectDefinition[107].adjancentIDs.leftID = 106;
	LHRectDefinition[107].adjancentIDs.rightID = 108;
	LHRectDefinition[107].adjancentIDs.topID = -1;
	LHRectDefinition[107].adjancentIDs.belowID = 37;

	LHRectDefinition[108].adjancentIDs.aboveID = -1;
	LHRectDefinition[108].adjancentIDs.bottomID = 122;
	LHRectDefinition[108].adjancentIDs.leftID = 107;
	LHRectDefinition[108].adjancentIDs.rightID = 109;
	LHRectDefinition[108].adjancentIDs.topID = -1;
	LHRectDefinition[108].adjancentIDs.belowID = 38;

	LHRectDefinition[109].adjancentIDs.aboveID = -1;
	LHRectDefinition[109].adjancentIDs.bottomID = -1;
	LHRectDefinition[109].adjancentIDs.leftID = 108;
	LHRectDefinition[109].adjancentIDs.rightID = -1;
	LHRectDefinition[109].adjancentIDs.topID = -1;
	LHRectDefinition[109].adjancentIDs.belowID = 39;

	LHRectDefinition[110].adjancentIDs.aboveID = -1;
	LHRectDefinition[110].adjancentIDs.bottomID = -1;
	LHRectDefinition[110].adjancentIDs.leftID = -1;
	LHRectDefinition[110].adjancentIDs.rightID = 111;
	LHRectDefinition[110].adjancentIDs.topID = 96;
	LHRectDefinition[110].adjancentIDs.belowID = 42;

	LHRectDefinition[111].adjancentIDs.aboveID = -1;
	LHRectDefinition[111].adjancentIDs.bottomID = 123;
	LHRectDefinition[111].adjancentIDs.leftID = 110;
	LHRectDefinition[111].adjancentIDs.rightID = 112;
	LHRectDefinition[111].adjancentIDs.topID = 97;
	LHRectDefinition[111].adjancentIDs.belowID = 43;

	LHRectDefinition[112].adjancentIDs.aboveID = -1;
	LHRectDefinition[112].adjancentIDs.bottomID = 124;
	LHRectDefinition[112].adjancentIDs.leftID = 111;
	LHRectDefinition[112].adjancentIDs.rightID = 113;
	LHRectDefinition[112].adjancentIDs.topID = 98;
	LHRectDefinition[112].adjancentIDs.belowID = 44;

	LHRectDefinition[113].adjancentIDs.aboveID = -1;
	LHRectDefinition[113].adjancentIDs.bottomID = 125;
	LHRectDefinition[113].adjancentIDs.leftID = 112;
	LHRectDefinition[113].adjancentIDs.rightID = 114;
	LHRectDefinition[113].adjancentIDs.topID = 99;
	LHRectDefinition[113].adjancentIDs.belowID = 45;

	LHRectDefinition[114].adjancentIDs.aboveID = -1;
	LHRectDefinition[114].adjancentIDs.bottomID = 126;
	LHRectDefinition[114].adjancentIDs.leftID = 113;
	LHRectDefinition[114].adjancentIDs.rightID = 115;
	LHRectDefinition[114].adjancentIDs.topID = 100;
	LHRectDefinition[114].adjancentIDs.belowID = 46;

	LHRectDefinition[115].adjancentIDs.aboveID = -1;
	LHRectDefinition[115].adjancentIDs.bottomID = 127;
	LHRectDefinition[115].adjancentIDs.leftID = 114;
	LHRectDefinition[115].adjancentIDs.rightID = 116;
	LHRectDefinition[115].adjancentIDs.topID = 101;
	LHRectDefinition[115].adjancentIDs.belowID = 47;

	LHRectDefinition[116].adjancentIDs.aboveID = -1;
	LHRectDefinition[116].adjancentIDs.bottomID = 128;
	LHRectDefinition[116].adjancentIDs.leftID = 115;
	LHRectDefinition[116].adjancentIDs.rightID = 117;
	LHRectDefinition[116].adjancentIDs.topID = 102;
	LHRectDefinition[116].adjancentIDs.belowID = 48;

	LHRectDefinition[117].adjancentIDs.aboveID = -1;
	LHRectDefinition[117].adjancentIDs.bottomID = 129;
	LHRectDefinition[117].adjancentIDs.leftID = 116;
	LHRectDefinition[117].adjancentIDs.rightID = 118;
	LHRectDefinition[117].adjancentIDs.topID = 103;
	LHRectDefinition[117].adjancentIDs.belowID = 49;

	LHRectDefinition[118].adjancentIDs.aboveID = -1;
	LHRectDefinition[118].adjancentIDs.bottomID = 130;
	LHRectDefinition[118].adjancentIDs.leftID = 117;
	LHRectDefinition[118].adjancentIDs.rightID = 119;
	LHRectDefinition[118].adjancentIDs.topID = 104;
	LHRectDefinition[118].adjancentIDs.belowID = 50;

	LHRectDefinition[119].adjancentIDs.aboveID = -1;
	LHRectDefinition[119].adjancentIDs.bottomID = 131;
	LHRectDefinition[119].adjancentIDs.leftID = 118;
	LHRectDefinition[119].adjancentIDs.rightID = 120;
	LHRectDefinition[119].adjancentIDs.topID = 105;
	LHRectDefinition[119].adjancentIDs.belowID = 51;

	LHRectDefinition[120].adjancentIDs.aboveID = -1;
	LHRectDefinition[120].adjancentIDs.bottomID = 132;
	LHRectDefinition[120].adjancentIDs.leftID = 119;
	LHRectDefinition[120].adjancentIDs.rightID = 121;
	LHRectDefinition[120].adjancentIDs.topID = 106;
	LHRectDefinition[120].adjancentIDs.belowID = 52;

	LHRectDefinition[121].adjancentIDs.aboveID = -1;
	LHRectDefinition[121].adjancentIDs.bottomID = 133;
	LHRectDefinition[121].adjancentIDs.leftID = 120;
	LHRectDefinition[121].adjancentIDs.rightID = 122;
	LHRectDefinition[121].adjancentIDs.topID = 107;
	LHRectDefinition[121].adjancentIDs.belowID = 53;

	LHRectDefinition[122].adjancentIDs.aboveID = -1;
	LHRectDefinition[122].adjancentIDs.bottomID = -1;
	LHRectDefinition[122].adjancentIDs.leftID = 121;
	LHRectDefinition[122].adjancentIDs.rightID = -1;
	LHRectDefinition[122].adjancentIDs.topID = 108;
	LHRectDefinition[122].adjancentIDs.belowID = 54;

	LHRectDefinition[123].adjancentIDs.aboveID = -1;
	LHRectDefinition[123].adjancentIDs.bottomID = -1;
	LHRectDefinition[123].adjancentIDs.leftID = -1;
	LHRectDefinition[123].adjancentIDs.rightID = 124;
	LHRectDefinition[123].adjancentIDs.topID = 111;
	LHRectDefinition[123].adjancentIDs.belowID = 57;

	LHRectDefinition[124].adjancentIDs.aboveID = -1;
	LHRectDefinition[124].adjancentIDs.bottomID = -1;
	LHRectDefinition[124].adjancentIDs.leftID = 123;
	LHRectDefinition[124].adjancentIDs.rightID = 125;
	LHRectDefinition[124].adjancentIDs.topID = 112;
	LHRectDefinition[124].adjancentIDs.belowID = 58;

	LHRectDefinition[125].adjancentIDs.aboveID = -1;
	LHRectDefinition[125].adjancentIDs.bottomID = -1;
	LHRectDefinition[125].adjancentIDs.leftID = 124;
	LHRectDefinition[125].adjancentIDs.rightID = 126;
	LHRectDefinition[125].adjancentIDs.topID = 113;
	LHRectDefinition[125].adjancentIDs.belowID = 59;

	LHRectDefinition[126].adjancentIDs.aboveID = -1;
	LHRectDefinition[126].adjancentIDs.bottomID = 134;
	LHRectDefinition[126].adjancentIDs.leftID = 125;
	LHRectDefinition[126].adjancentIDs.rightID = 127;
	LHRectDefinition[126].adjancentIDs.topID = 114;
	LHRectDefinition[126].adjancentIDs.belowID = 60;

	LHRectDefinition[127].adjancentIDs.aboveID = -1;
	LHRectDefinition[127].adjancentIDs.bottomID = 135;
	LHRectDefinition[127].adjancentIDs.leftID = 126;
	LHRectDefinition[127].adjancentIDs.rightID = 128;
	LHRectDefinition[127].adjancentIDs.topID = 115;
	LHRectDefinition[127].adjancentIDs.belowID = 61;

	LHRectDefinition[128].adjancentIDs.aboveID = -1;
	LHRectDefinition[128].adjancentIDs.bottomID = 136;
	LHRectDefinition[128].adjancentIDs.leftID = 127;
	LHRectDefinition[128].adjancentIDs.rightID = 129;
	LHRectDefinition[128].adjancentIDs.topID = 116;
	LHRectDefinition[128].adjancentIDs.belowID = 62;

	LHRectDefinition[129].adjancentIDs.aboveID = -1;
	LHRectDefinition[129].adjancentIDs.bottomID = 137;
	LHRectDefinition[129].adjancentIDs.leftID = 128;
	LHRectDefinition[129].adjancentIDs.rightID = 130;
	LHRectDefinition[129].adjancentIDs.topID = 117;
	LHRectDefinition[129].adjancentIDs.belowID = 63;

	LHRectDefinition[130].adjancentIDs.aboveID = -1;
	LHRectDefinition[130].adjancentIDs.bottomID = 138;
	LHRectDefinition[130].adjancentIDs.leftID = 129;
	LHRectDefinition[130].adjancentIDs.rightID = 131;
	LHRectDefinition[130].adjancentIDs.topID = 118;
	LHRectDefinition[130].adjancentIDs.belowID = 64;

	LHRectDefinition[131].adjancentIDs.aboveID = -1;
	LHRectDefinition[131].adjancentIDs.bottomID = -1;
	LHRectDefinition[131].adjancentIDs.leftID = 130;
	LHRectDefinition[131].adjancentIDs.rightID = 132;
	LHRectDefinition[131].adjancentIDs.topID = 119;
	LHRectDefinition[131].adjancentIDs.belowID = 65;

	LHRectDefinition[132].adjancentIDs.aboveID = -1;
	LHRectDefinition[132].adjancentIDs.bottomID = -1;
	LHRectDefinition[132].adjancentIDs.leftID = 131;
	LHRectDefinition[132].adjancentIDs.rightID = 133;
	LHRectDefinition[132].adjancentIDs.topID = 120;
	LHRectDefinition[132].adjancentIDs.belowID = 66;

	LHRectDefinition[133].adjancentIDs.aboveID = -1;
	LHRectDefinition[133].adjancentIDs.bottomID = -1;
	LHRectDefinition[133].adjancentIDs.leftID = 132;
	LHRectDefinition[133].adjancentIDs.rightID = -1;
	LHRectDefinition[133].adjancentIDs.topID = 121;
	LHRectDefinition[133].adjancentIDs.belowID = 67;

	LHRectDefinition[134].adjancentIDs.aboveID = -1;
	LHRectDefinition[134].adjancentIDs.bottomID = -1;
	LHRectDefinition[134].adjancentIDs.leftID = -1;
	LHRectDefinition[134].adjancentIDs.rightID = 135;
	LHRectDefinition[134].adjancentIDs.topID = 126;
	LHRectDefinition[134].adjancentIDs.belowID = 70;

	LHRectDefinition[135].adjancentIDs.aboveID = -1;
	LHRectDefinition[135].adjancentIDs.bottomID = 139;
	LHRectDefinition[135].adjancentIDs.leftID = 134;
	LHRectDefinition[135].adjancentIDs.rightID = 136;
	LHRectDefinition[135].adjancentIDs.topID = 127;
	LHRectDefinition[135].adjancentIDs.belowID = 71;

	LHRectDefinition[136].adjancentIDs.aboveID = -1;
	LHRectDefinition[136].adjancentIDs.bottomID = 140;
	LHRectDefinition[136].adjancentIDs.leftID = 135;
	LHRectDefinition[136].adjancentIDs.rightID = 137;
	LHRectDefinition[136].adjancentIDs.topID = 128;
	LHRectDefinition[136].adjancentIDs.belowID = 72;

	LHRectDefinition[137].adjancentIDs.aboveID = -1;
	LHRectDefinition[137].adjancentIDs.bottomID = 141;
	LHRectDefinition[137].adjancentIDs.leftID = 136;
	LHRectDefinition[137].adjancentIDs.rightID = 138;
	LHRectDefinition[137].adjancentIDs.topID = 129;
	LHRectDefinition[137].adjancentIDs.belowID = 73;

	LHRectDefinition[138].adjancentIDs.aboveID = -1;
	LHRectDefinition[138].adjancentIDs.bottomID = -1;
	LHRectDefinition[138].adjancentIDs.leftID = 137;
	LHRectDefinition[138].adjancentIDs.rightID = -1;
	LHRectDefinition[138].adjancentIDs.topID = 130;
	LHRectDefinition[138].adjancentIDs.belowID = 74;

	LHRectDefinition[139].adjancentIDs.aboveID = -1;
	LHRectDefinition[139].adjancentIDs.bottomID = 142;
	LHRectDefinition[139].adjancentIDs.leftID = -1;
	LHRectDefinition[139].adjancentIDs.rightID = 140;
	LHRectDefinition[139].adjancentIDs.topID = 135;
	LHRectDefinition[139].adjancentIDs.belowID = 77;

	LHRectDefinition[140].adjancentIDs.aboveID = -1;
	LHRectDefinition[140].adjancentIDs.bottomID = 143;
	LHRectDefinition[140].adjancentIDs.leftID = 139;
	LHRectDefinition[140].adjancentIDs.rightID = 141;
	LHRectDefinition[140].adjancentIDs.topID = 136;
	LHRectDefinition[140].adjancentIDs.belowID = 78;

	LHRectDefinition[141].adjancentIDs.aboveID = -1;
	LHRectDefinition[141].adjancentIDs.bottomID = -1;
	LHRectDefinition[141].adjancentIDs.leftID = 140;
	LHRectDefinition[141].adjancentIDs.rightID = -1;
	LHRectDefinition[141].adjancentIDs.topID = 137;
	LHRectDefinition[141].adjancentIDs.belowID = 79;

	LHRectDefinition[142].adjancentIDs.aboveID = -1;
	LHRectDefinition[142].adjancentIDs.bottomID = -1;
	LHRectDefinition[142].adjancentIDs.leftID = -1;
	LHRectDefinition[142].adjancentIDs.rightID = 143;
	LHRectDefinition[142].adjancentIDs.topID = 139;
	LHRectDefinition[142].adjancentIDs.belowID = 82;

	LHRectDefinition[143].adjancentIDs.aboveID = -1;
	LHRectDefinition[143].adjancentIDs.bottomID = -1;
	LHRectDefinition[143].adjancentIDs.leftID = 142;
	LHRectDefinition[143].adjancentIDs.rightID = -1;
	LHRectDefinition[143].adjancentIDs.topID = 140;
	LHRectDefinition[143].adjancentIDs.belowID = 83;


}

void CMJLonghorn::SetupData()
{

	LHRectDefinition[0].Draw = false;
	LHRectDefinition[0].TileSelected = false;

	LHRectDefinition[1].Draw = false;
	LHRectDefinition[1].TileSelected = false;

	LHRectDefinition[2].Draw = false;
	LHRectDefinition[2].TileSelected = false;

	LHRectDefinition[3].Draw = false;
	LHRectDefinition[3].TileSelected = false;

	LHRectDefinition[4].Draw = false;
	LHRectDefinition[4].TileSelected = false;

	LHRectDefinition[5].Draw = false;
	LHRectDefinition[5].TileSelected = false;

	LHRectDefinition[6].Draw = false;
	LHRectDefinition[6].TileSelected = false;

	LHRectDefinition[7].Draw = false;
	LHRectDefinition[7].TileSelected = false;

	LHRectDefinition[8].Draw = false;
	LHRectDefinition[8].TileSelected = false;

	LHRectDefinition[9].Draw = false;
	LHRectDefinition[9].TileSelected = false;

	LHRectDefinition[10].Draw = false;
	LHRectDefinition[10].TileSelected = false;

	LHRectDefinition[11].Draw = false;
	LHRectDefinition[11].TileSelected = false;

	LHRectDefinition[12].Draw = false;
	LHRectDefinition[12].TileSelected = false;

	LHRectDefinition[13].Draw = false;
	LHRectDefinition[13].TileSelected = false;

	LHRectDefinition[14].Draw = false;
	LHRectDefinition[14].TileSelected = false;

	LHRectDefinition[15].Draw = false;
	LHRectDefinition[15].TileSelected = false;

	LHRectDefinition[16].Draw = false;
	LHRectDefinition[16].TileSelected = false;

	LHRectDefinition[17].Draw = false;
	LHRectDefinition[17].TileSelected = false;

	LHRectDefinition[18].Draw = false;
	LHRectDefinition[18].TileSelected = false;

	LHRectDefinition[19].Draw = false;
	LHRectDefinition[19].TileSelected = false;

	LHRectDefinition[20].Draw = false;
	LHRectDefinition[20].TileSelected = false;

	LHRectDefinition[21].Draw = false;
	LHRectDefinition[21].TileSelected = false;

	LHRectDefinition[22].Draw = false;
	LHRectDefinition[22].TileSelected = false;

	LHRectDefinition[23].Draw = false;
	LHRectDefinition[23].TileSelected = false;

	LHRectDefinition[24].Draw = false;
	LHRectDefinition[24].TileSelected = false;

	LHRectDefinition[25].Draw = false;
	LHRectDefinition[25].TileSelected = false;

	LHRectDefinition[26].Draw = false;
	LHRectDefinition[26].TileSelected = false;

	LHRectDefinition[27].Draw = false;
	LHRectDefinition[27].TileSelected = false;

	LHRectDefinition[28].Draw = false;
	LHRectDefinition[28].TileSelected = false;

	LHRectDefinition[29].Draw = false;
	LHRectDefinition[29].TileSelected = false;

	LHRectDefinition[30].Draw = false;
	LHRectDefinition[30].TileSelected = false;

	LHRectDefinition[31].Draw = false;
	LHRectDefinition[31].TileSelected = false;

	LHRectDefinition[32].Draw = false;
	LHRectDefinition[32].TileSelected = false;

	LHRectDefinition[33].Draw = false;
	LHRectDefinition[33].TileSelected = false;

	LHRectDefinition[34].Draw = false;
	LHRectDefinition[34].TileSelected = false;

	LHRectDefinition[35].Draw = false;
	LHRectDefinition[35].TileSelected = false;

	LHRectDefinition[36].Draw = false;
	LHRectDefinition[36].TileSelected = false;

	LHRectDefinition[37].Draw = false;
	LHRectDefinition[37].TileSelected = false;

	LHRectDefinition[38].Draw = false;
	LHRectDefinition[38].TileSelected = false;

	LHRectDefinition[39].Draw = false;
	LHRectDefinition[39].TileSelected = false;

	LHRectDefinition[40].Draw = false;
	LHRectDefinition[40].TileSelected = false;

	LHRectDefinition[41].Draw = false;
	LHRectDefinition[41].TileSelected = false;

	LHRectDefinition[42].Draw = false;
	LHRectDefinition[42].TileSelected = false;

	LHRectDefinition[43].Draw = false;
	LHRectDefinition[43].TileSelected = false;

	LHRectDefinition[44].Draw = false;
	LHRectDefinition[44].TileSelected = false;

	LHRectDefinition[45].Draw = false;
	LHRectDefinition[45].TileSelected = false;

	LHRectDefinition[46].Draw = false;
	LHRectDefinition[46].TileSelected = false;

	LHRectDefinition[47].Draw = false;
	LHRectDefinition[47].TileSelected = false;

	LHRectDefinition[48].Draw = false;
	LHRectDefinition[48].TileSelected = false;

	LHRectDefinition[49].Draw = false;
	LHRectDefinition[49].TileSelected = false;

	LHRectDefinition[50].Draw = false;
	LHRectDefinition[50].TileSelected = false;

	LHRectDefinition[51].Draw = false;
	LHRectDefinition[51].TileSelected = false;

	LHRectDefinition[52].Draw = false;
	LHRectDefinition[52].TileSelected = false;

	LHRectDefinition[53].Draw = false;
	LHRectDefinition[53].TileSelected = false;

	LHRectDefinition[54].Draw = false;
	LHRectDefinition[54].TileSelected = false;

	LHRectDefinition[55].Draw = false;
	LHRectDefinition[55].TileSelected = false;

	LHRectDefinition[56].Draw = false;
	LHRectDefinition[56].TileSelected = false;

	LHRectDefinition[57].Draw = false;
	LHRectDefinition[57].TileSelected = false;

	LHRectDefinition[58].Draw = false;
	LHRectDefinition[58].TileSelected = false;

	LHRectDefinition[59].Draw = false;
	LHRectDefinition[59].TileSelected = false;

	LHRectDefinition[60].Draw = false;
	LHRectDefinition[60].TileSelected = false;

	LHRectDefinition[61].Draw = false;
	LHRectDefinition[61].TileSelected = false;

	LHRectDefinition[62].Draw = false;
	LHRectDefinition[62].TileSelected = false;

	LHRectDefinition[63].Draw = false;
	LHRectDefinition[63].TileSelected = false;

	LHRectDefinition[64].Draw = false;
	LHRectDefinition[64].TileSelected = false;

	LHRectDefinition[65].Draw = false;
	LHRectDefinition[65].TileSelected = false;

	LHRectDefinition[66].Draw = false;
	LHRectDefinition[66].TileSelected = false;

	LHRectDefinition[67].Draw = false;
	LHRectDefinition[67].TileSelected = false;

	LHRectDefinition[68].Draw = false;
	LHRectDefinition[68].TileSelected = false;

	LHRectDefinition[69].Draw = false;
	LHRectDefinition[69].TileSelected = false;

	LHRectDefinition[70].Draw = false;
	LHRectDefinition[70].TileSelected = false;

	LHRectDefinition[71].Draw = false;
	LHRectDefinition[71].TileSelected = false;

	LHRectDefinition[72].Draw = false;
	LHRectDefinition[72].TileSelected = false;

	LHRectDefinition[73].Draw = false;
	LHRectDefinition[73].TileSelected = false;

	LHRectDefinition[74].Draw = false;
	LHRectDefinition[74].TileSelected = false;

	LHRectDefinition[75].Draw = false;
	LHRectDefinition[75].TileSelected = false;

	LHRectDefinition[76].Draw = false;
	LHRectDefinition[76].TileSelected = false;

	LHRectDefinition[77].Draw = false;
	LHRectDefinition[77].TileSelected = false;

	LHRectDefinition[78].Draw = false;
	LHRectDefinition[78].TileSelected = false;

	LHRectDefinition[79].Draw = false;
	LHRectDefinition[79].TileSelected = false;

	LHRectDefinition[80].Draw = false;
	LHRectDefinition[80].TileSelected = false;

	LHRectDefinition[81].Draw = false;
	LHRectDefinition[81].TileSelected = false;

	LHRectDefinition[82].Draw = false;
	LHRectDefinition[82].TileSelected = false;

	LHRectDefinition[83].Draw = false;
	LHRectDefinition[83].TileSelected = false;

	LHRectDefinition[84].Draw = false;
	LHRectDefinition[84].TileSelected = false;

	LHRectDefinition[85].Draw = false;
	LHRectDefinition[85].TileSelected = false;

	LHRectDefinition[86].Draw = false;
	LHRectDefinition[86].TileSelected = false;

	LHRectDefinition[87].Draw = false;
	LHRectDefinition[87].TileSelected = false;

	LHRectDefinition[88].Draw = false;
	LHRectDefinition[88].TileSelected = false;

	LHRectDefinition[89].Draw = false;
	LHRectDefinition[89].TileSelected = false;

	LHRectDefinition[90].Draw = false;
	LHRectDefinition[90].TileSelected = false;

	LHRectDefinition[91].Draw = false;
	LHRectDefinition[91].TileSelected = false;

	LHRectDefinition[92].Draw = false;
	LHRectDefinition[92].TileSelected = false;

	LHRectDefinition[93].Draw = false;
	LHRectDefinition[93].TileSelected = false;

	LHRectDefinition[94].Draw = false;
	LHRectDefinition[94].TileSelected = false;

	LHRectDefinition[95].Draw = false;
	LHRectDefinition[95].TileSelected = false;

	LHRectDefinition[96].Draw = false;
	LHRectDefinition[96].TileSelected = false;

	LHRectDefinition[97].Draw = false;
	LHRectDefinition[97].TileSelected = false;

	LHRectDefinition[98].Draw = false;
	LHRectDefinition[98].TileSelected = false;

	LHRectDefinition[99].Draw = false;
	LHRectDefinition[99].TileSelected = false;

	LHRectDefinition[100].Draw = false;
	LHRectDefinition[100].TileSelected = false;

	LHRectDefinition[101].Draw = false;
	LHRectDefinition[101].TileSelected = false;

	LHRectDefinition[102].Draw = false;
	LHRectDefinition[102].TileSelected = false;

	LHRectDefinition[103].Draw = false;
	LHRectDefinition[103].TileSelected = false;

	LHRectDefinition[104].Draw = false;
	LHRectDefinition[104].TileSelected = false;

	LHRectDefinition[105].Draw = false;
	LHRectDefinition[105].TileSelected = false;

	LHRectDefinition[106].Draw = false;
	LHRectDefinition[106].TileSelected = false;

	LHRectDefinition[107].Draw = false;
	LHRectDefinition[107].TileSelected = false;

	LHRectDefinition[108].Draw = false;
	LHRectDefinition[108].TileSelected = false;

	LHRectDefinition[109].Draw = false;
	LHRectDefinition[109].TileSelected = false;

	LHRectDefinition[110].Draw = false;
	LHRectDefinition[110].TileSelected = false;

	LHRectDefinition[111].Draw = false;
	LHRectDefinition[111].TileSelected = false;

	LHRectDefinition[112].Draw = false;
	LHRectDefinition[112].TileSelected = false;

	LHRectDefinition[113].Draw = false;
	LHRectDefinition[113].TileSelected = false;

	LHRectDefinition[114].Draw = false;
	LHRectDefinition[114].TileSelected = false;

	LHRectDefinition[115].Draw = false;
	LHRectDefinition[115].TileSelected = false;

	LHRectDefinition[116].Draw = false;
	LHRectDefinition[116].TileSelected = false;

	LHRectDefinition[117].Draw = false;
	LHRectDefinition[117].TileSelected = false;

	LHRectDefinition[118].Draw = false;
	LHRectDefinition[118].TileSelected = false;

	LHRectDefinition[119].Draw = false;
	LHRectDefinition[119].TileSelected = false;

	LHRectDefinition[120].Draw = false;
	LHRectDefinition[120].TileSelected = false;

	LHRectDefinition[121].Draw = false;
	LHRectDefinition[121].TileSelected = false;

	LHRectDefinition[122].Draw = false;
	LHRectDefinition[122].TileSelected = false;

	LHRectDefinition[123].Draw = false;
	LHRectDefinition[123].TileSelected = false;

	LHRectDefinition[124].Draw = false;
	LHRectDefinition[124].TileSelected = false;

	LHRectDefinition[125].Draw = false;
	LHRectDefinition[125].TileSelected = false;

	LHRectDefinition[126].Draw = false;
	LHRectDefinition[126].TileSelected = false;

	LHRectDefinition[127].Draw = false;
	LHRectDefinition[127].TileSelected = false;

	LHRectDefinition[128].Draw = false;
	LHRectDefinition[128].TileSelected = false;

	LHRectDefinition[129].Draw = false;
	LHRectDefinition[129].TileSelected = false;

	LHRectDefinition[130].Draw = false;
	LHRectDefinition[130].TileSelected = false;

	LHRectDefinition[131].Draw = false;
	LHRectDefinition[131].TileSelected = false;

	LHRectDefinition[132].Draw = false;
	LHRectDefinition[132].TileSelected = false;

	LHRectDefinition[133].Draw = false;
	LHRectDefinition[133].TileSelected = false;

	LHRectDefinition[134].Draw = false;
	LHRectDefinition[134].TileSelected = false;

	LHRectDefinition[135].Draw = false;
	LHRectDefinition[135].TileSelected = false;

	LHRectDefinition[136].Draw = false;
	LHRectDefinition[136].TileSelected = false;

	LHRectDefinition[137].Draw = false;
	LHRectDefinition[137].TileSelected = false;

	LHRectDefinition[138].Draw = false;
	LHRectDefinition[138].TileSelected = false;

	LHRectDefinition[139].Draw = false;
	LHRectDefinition[139].TileSelected = false;

	LHRectDefinition[140].Draw = false;
	LHRectDefinition[140].TileSelected = false;

	LHRectDefinition[141].Draw = false;
	LHRectDefinition[141].TileSelected = false;

	LHRectDefinition[142].Draw = false;
	LHRectDefinition[142].TileSelected = false;

	LHRectDefinition[143].Draw = false;
	LHRectDefinition[143].TileSelected = false;

}

