// Sudoku.cpp : implementation file
//

#include "stdafx.h"
#include "RDAGames.h"
#include "Sudoku.h"
#include "definitions.h"
#include "MainFrm.h"
#include "TrackViews.h"


// CSudoku

IMPLEMENT_DYNCREATE(CSudoku, CView)

CSudoku::CSudoku()
{
	PlayLevel = 0;
	Init();
	LoadImages();
	SetupRegions();
	OnAppDeal();
}

CSudoku::~CSudoku()
{
	CTrackViews tv;
	tv.RemoveStatus(SUDOKUVIEW);
}

BEGIN_MESSAGE_MAP(CSudoku, CView)
	ON_COMMAND(ID_APP_DEAL, &CSudoku::OnAppDeal)
	ON_COMMAND(ID_UNDO_ALL_BUTTON, &CSudoku::OnUndoAllButton)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_SUDOKUNEW_BUTTON, &CSudoku::OnSudokunewButton)
	ON_WM_LBUTTONUP()
	ON_WM_XBUTTONUP()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// CSudoku drawing

void CSudoku::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

void CSudoku::Init()
{
	int i,j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			SgameDetails[i][j].CellValue = 0;
			SgameDetails[i][j].DoPaint = true;
			SgameDetails[i][j].Highlighted = NOTHIGHLIGHTED;
		}
	}
	for (i = 0; i < 10; i++)
	{
		IsKeyHighlighted[i] = false;
	}
	SelectedRow = -1;
	SelectedCol = -1;
	PreviousSelectedRow = -1;
	PreviousSelectedCol = -1;

	GameOver = false;
	PaintKeyPad = false;
	UndoLocation = -1;
	PlayAreaSelected = false;
	PaintAll = true;
}

// CSudoku diagnostics

#ifdef _DEBUG
void CSudoku::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSudoku::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSudoku message handlers


void CSudoku::OnAppDeal()
{
	row = 0;
	col = 0;
	generate(PlayLevel);
	//int minPos, maxPos, noOfSets;
	//int row;
	//int aryVal;
	//int NumberOfNumbersInRegion;
	//struct NewGame
	//{
	//	int RRow;
	//	int RCol;
	//	bool HasNums;
	//};

	//Init();
	//srand((unsigned)time(NULL));

	//NewGame RegionArray[9];
	//for (row = 0; row < 9; row++)
	//{
	//	RegionArray[row].HasNums = false;
	//	RegionArray[row].RRow = (int) row/3;
	//	RegionArray[row].RCol = row % 3;
	//}

	//switch(PlayLevel)
	//{
	//	case 0:
	//		minPos=4;
	//		maxPos=6;
	//		noOfSets=8;
	//		break;
	//	case 1:
	//		minPos=3;
	//		maxPos=5;
	//		noOfSets= 7;
	//		break;
	//	case 3:
	//		minPos=3;
	//		maxPos=5;
	//		noOfSets = 6;
	//		break;
	//	default:
	//		minPos=4;
	//		maxPos=6;
	//		noOfSets=8;
	//		break;
	//}

	//while (noOfSets > 0)
	//{
	//	aryVal = rand()%10;
	//	if (RegionArray[aryVal].HasNums == false)
	//	{
	//		RegionArray[aryVal].HasNums = true;
	//		noOfSets--;
	//	}
	//}
	//for (row = 0; row < 9; row++)
	//{
	//	if (RegionArray[row].HasNums == true)
	//	{
	//		NumberOfNumbersInRegion = 0;
	//		while (!((NumberOfNumbersInRegion >= minPos) && (NumberOfNumbersInRegion <= maxPos)))
	//		{
	//			NumberOfNumbersInRegion = rand()%10;
	//		}
	//	}
	//	while (NumberOfNumbersInRegion > 0)
	//	{
	//		AddNumberToRegionAndValidate(RegionArray[row].RRow, RegionArray[row].RCol);
	//		NumberOfNumbersInRegion--;
	//	}
	//}
}

void CSudoku::AddNumberToRegionAndValidate(int RRow, int RCol)
{
	int row, col;
	int a,b;
	bool valid = false;

	row = rand()%3;
	col = rand()%3;

	a = Regions[RRow][RCol].Rcells[row][col].row;
	b = Regions[RRow][RCol].Rcells[row][col].column;
	while (SgameDetails[Regions[RRow][RCol].Rcells[row][col].row][Regions[RRow][RCol].Rcells[row][col].column].CellValue != 0)
	{
		row = rand()%3;
		col = rand()%3;
	}
	while (valid == false)
	{
		valid = true;
		SgameDetails[Regions[RRow][RCol].Rcells[row][col].row][Regions[RRow][RCol].Rcells[row][col].column].CellValue = rand()%10;
		if (ValidateRow(Regions[RRow][RCol].Rcells[row][col].row) == false)
		{
			valid = false;
		}
		if (ValidateColumn(Regions[RRow][RCol].Rcells[row][col].column) == false)
		{
			valid = false;
		}
		if (ValidateRegion(RRow, RCol) == false)
		{
			valid = false;
		}
	}
}

bool CSudoku::ValidateRow(int rownum)
{
	int one1 = 0;
	int two1 = 0;
	int three1 = 0;
	int four1 = 0;
	int five1 = 0;
	int six1 = 0;
	int seven1 = 0;
	int eight1 = 0;
	int nine1 = 0;

	for (int i = 0; i < 10; i++)
	{
		switch (SgameDetails[rownum][i].CellValue)
		{
			case 1:
				one1++;
				break;
			case 2:
				two1++;
				break;
			case 3:
				three1++;
				break;
			case 4:
				four1++;
				break;
			case 5:
				five1++;
				break;
			case 6:
				six1++;
				break;
			case 7:
				seven1++;
				break;
			case 8:
				eight1++;
				break;
			case 9:
				nine1++;
				break;
		}
	}
	if ((one1 > 1) || (two1 > 1) || (three1 > 1) || (four1 > 1) || (five1 > 1) || (six1 > 1) || (seven1 > 1) || (eight1 > 1) || (nine1 > 1))
	{
		return false;
	}
	return true;
}

bool CSudoku::ValidateColumn(int colnum)
{
	int one1 = 0;
	int two1 = 0;
	int three1 = 0;
	int four1 = 0;
	int five1 = 0;
	int six1 = 0;
	int seven1 = 0;
	int eight1 = 0;
	int nine1 = 0;

	for (int i = 0; i < 10; i++)
	{
		switch (SgameDetails[i][colnum].CellValue)
		{
			case 1:
				one1++;
				break;
			case 2:
				two1++;
				break;
			case 3:
				three1++;
				break;
			case 4:
				four1++;
				break;
			case 5:
				five1++;
				break;
			case 6:
				six1++;
				break;
			case 7:
				seven1++;
				break;
			case 8:
				eight1++;
				break;
			case 9:
				nine1++;
				break;
		}
	}
	if ((one1 > 1) || (two1 > 1) || (three1 > 1) || (four1 > 1) || (five1 > 1) || (six1 > 1) || (seven1 > 1) || (eight1 > 1) || (nine1 > 1))
	{
		return false;
	}
	return true;
}

bool CSudoku::ValidateRegion (int RegionRow, int RegionColumn)
{
	int one1 = 0;
	int two1 = 0;
	int three1 = 0;
	int four1 = 0;
	int five1 = 0;
	int six1 = 0;
	int seven1 = 0;
	int eight1 = 0;
	int nine1 = 0;

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			switch (SgameDetails[Regions[RegionRow][RegionColumn].Rcells[row][col].row][Regions[RegionRow][RegionColumn].Rcells[row][col].column].CellValue)
			{
				case 1:
					one1++;
					break;
				case 2:
					two1++;
					break;
				case 3:
					three1++;
					break;
				case 4:
					four1++;
					break;
				case 5:
					five1++;
					break;
				case 6:
					six1++;
					break;
				case 7:
					seven1++;
					break;
				case 8:
					eight1++;
					break;
				case 9:
					nine1++;
					break;
			}
		}
	}
	if ((one1 > 1) || (two1 > 1) || (three1 > 1) || (four1 > 1) || (five1 > 1) || (six1 > 1) || (seven1 > 1) || (eight1 > 1) || (nine1 > 1))
	{
		return false;
	}
	return true;
}
//
//void CSudoku::OldDeal()
//{
//	char *cell;
//	srand(time(0));
//	int l=rand()%30;
//	int strsubpos = 0;
//
//	Init();
//
//	char cell0[]="060300087010900050002040030500600009400020001800703002070060400080001020140007090";
//	char cell1[]="080003006040280100000450002006000340004000200013000600500014000001027060400600091";
//	char cell2[]="300008700000009004100060002005023080070004090060001500800050006700100000009800005";
//	char cell3[]="060050020000300090700600010006030400004070100005090800040001006030008000020040050";
//	char cell4[]="006000003000750008020010400800000040091007300000930600050008000004605000000003700";
//	char cell5[]="000700109030040000000800060000500000070436000008000900000920004000000007306007000";
//	char cell6[]="026000030400030060080090014007000001004000020310600040090000000000700295000025000";
//	char cell7[]="000000030900601000400085000106040900003006120500008040000000002012000390009050010";
//	char cell8[]="000209000000040250000000000009006000023000001476000800002850700500004600007060300";
//	char cell9[]="071030000000000020000790601000000980020063010005000000067000000004027100800910030";
//	char cell10[]="000900400000006007000080920000070043058090000040000070007341000801200000005009000";
//	char cell11[]="005060009100052080030000000501000000000600020900020000000400210000008030008009407";
//	char cell12[]="000700001000000004009560070006007100500010000000096080100003020004008600080940000";
//	char cell13[]="001002000600000580702006000100007030025030090000690001000204000079000000400000010";
//	char cell14[]="000003080010000304000500000000007008602304900003010200065000010189060000000000040";
//	char cell15[]="002300050000000104810000000000019536050006001008000200000000000003200000000907028";
//	char cell16[]="008090000000070065030000408380650009000009300027000000000023016000760800200000000";
//	char cell17[]="047000000000000946000003010000408009460007000500029000070600034082000000100000000";
//	char cell18[]="000000801400007000005000030000050004020080100000003020003068050100000090600094002";
//	char cell19[]="000000000040315060050006030000000100500000600009620004070000000080430002003090050";
//	char cell20[]="690004800000000002003620010010000020000805900004700106500000470000000008438007000";
//	char cell21[]="000000709507000600230900004040001006000570300600000000458000002063000000000090000";
//	char cell22[]="050020080100007000000300250030000104000005000012704000006000020000000809040203070";
//	char cell23[]="000000001045000080386000000000050004038670000000000079200900100007010020090060407";
//	char cell24[]="200000300000341780000050004000070000760003800001200090080000000000100070093000406";
//	char cell25[]="600000590010030000080105000000209008000000060170500000030000652000000080700081400";
//	char cell26[]="057020060000901000200060000030040000519000000062000800000305020000006005000070094";
//	char cell27[]="004100000000040007500090800700004203050000000060052700010008000370200000000000018";
//	char cell28[]="080002059000060000000904607670000090001000500930001020009200040250608000300000005";
//	char cell29[]="007000012000000530010020000000360040032005008008700000000041000050800090400000051";
//
//	switch (l)
//	{
//		case 0:
//			cell = cell0;
//			break;
//
//		case 1:
//			cell = cell1;
//			break;
//
//		case 2:
//			cell = cell2;
//			break;
//
//		case 3:
//			cell = cell3;
//			break;
//
//		case 4:
//			cell = cell4;
//			break;
//
//		case 5:
//			cell = cell5;
//			break;
//
//		case 6:
//			cell = cell6;
//			break;
//
//		case 7:
//			cell = cell7;
//			break;
//
//		case 8:
//			cell = cell8;
//			break;
//
//		case 9:
//			cell = cell9;
//			break;
//
//		case 10:
//			cell = cell10;
//			break;
//
//		case 11:
//			cell = cell11;
//			break;
//
//		case 12:
//			cell = cell12;
//			break;
//
//		case 13:
//			cell = cell13;
//			break;
//
//		case 14:
//			cell = cell14;
//			break;
//
//		case 15:
//			cell = cell15;
//			break;
//
//		case 16:
//			cell = cell16;
//			break;
//
//		case 17:
//			cell = cell17;
//			break;
//
//		case 18:
//			cell = cell18;
//			break;
//
//		case 19:
//			cell = cell19;
//			break;
//
//		case 20:
//			cell = cell20;
//			break;
//
//		case 21:
//			cell = cell21;
//			break;
//
//		case 22:
//			cell = cell22;
//			break;
//
//		case 23:
//			cell = cell23;
//			break;
//
//		case 24:
//			cell = cell24;
//			break;
//
//		case 25:
//			cell = cell25;
//			break;
//
//		case 26:
//			cell = cell26;
//			break;
//
//		case 27:
//			cell = cell27;
//			break;
//
//		case 28:
//			cell = cell28;
//			break;
//
//		case 29:
//			cell = cell29;
//			break;
//
//	}
//	for(int row=0; row<=8; row++)
//	{
//		for(int col=0; col<=8; col++)
//		{
//			SgameDetails[row][col].CellValue = cell[strsubpos] - 48;
//			strsubpos++;
//		}
//	}
//	PaintAll = true;
//}
//
void CSudoku::OnUndoAllButton()
{
	while (UndoLocation >= 0)
	{
		SgameDetails[SelectedRow][SelectedCol].DoPaint = true;
		SgameDetails[SelectedRow][SelectedCol].Highlighted = NOTHIGHLIGHTED;

		SelectedRow = Undo[UndoLocation].row;
		SelectedCol = Undo[UndoLocation].col;
		SgameDetails[SelectedRow][SelectedCol].CellValue = Undo[UndoLocation].oldval;
		SgameDetails[SelectedRow][SelectedCol].DoPaint = true;
		SgameDetails[SelectedRow][SelectedCol].Highlighted = HIGHILIGHTED;
		HighlightLikeNumber(-1);
		UndoLocation--;
	}
	Invalidate(false);
}

void CSudoku::LoadImages()
{
	CString imagepath;
	CString imagefile;

	imagepath = ".\\sudoku\\";

	imagefile = imagepath + "0.png";
	numbers[0].Load(imagefile);
	
	imagefile = imagepath + "1.png";
	numbers[1].Load(imagefile);
	
	imagefile = imagepath + "2.png";
	numbers[2].Load(imagefile);
	
	imagefile = imagepath + "3.png";
	numbers[3].Load(imagefile);
	
	imagefile = imagepath + "4.png";
	numbers[4].Load(imagefile);
	
	imagefile = imagepath + "5.png";
	numbers[5].Load(imagefile);
	
	imagefile = imagepath + "6.png";
	numbers[6].Load(imagefile);
	
	imagefile = imagepath + "7.png";
	numbers[7].Load(imagefile);
	
	imagefile = imagepath + "8.png";
	numbers[8].Load(imagefile);
	
	imagefile = imagepath + "9.png";
	numbers[9].Load(imagefile);



	imagefile = imagepath + "0y.png";
	ynumbers[0].Load(imagefile);
	
	imagefile = imagepath + "1y.png";
	ynumbers[1].Load(imagefile);
	
	imagefile = imagepath + "2y.png";
	ynumbers[2].Load(imagefile);
	
	imagefile = imagepath + "3y.png";
	ynumbers[3].Load(imagefile);
	
	imagefile = imagepath + "4y.png";
	ynumbers[4].Load(imagefile);
	
	imagefile = imagepath + "5y.png";
	ynumbers[5].Load(imagefile);
	
	imagefile = imagepath + "6y.png";
	ynumbers[6].Load(imagefile);
	
	imagefile = imagepath + "7y.png";
	ynumbers[7].Load(imagefile);
	
	imagefile = imagepath + "8y.png";
	ynumbers[8].Load(imagefile);
	
	imagefile = imagepath + "9y.png";
	ynumbers[9].Load(imagefile);




	imagefile = imagepath + "0z.png";
	znumbers[0].Load(imagefile);
	
	imagefile = imagepath + "1z.png";
	znumbers[1].Load(imagefile);
	
	imagefile = imagepath + "2z.png";
	znumbers[2].Load(imagefile);
	
	imagefile = imagepath + "3z.png";
	znumbers[3].Load(imagefile);
	
	imagefile = imagepath + "4z.png";
	znumbers[4].Load(imagefile);
	
	imagefile = imagepath + "5z.png";
	znumbers[5].Load(imagefile);
	
	imagefile = imagepath + "6z.png";
	znumbers[6].Load(imagefile);
	
	imagefile = imagepath + "7z.png";
	znumbers[7].Load(imagefile);
	
	imagefile = imagepath + "8z.png";
	znumbers[8].Load(imagefile);
	
	imagefile = imagepath + "9z.png";
	znumbers[9].Load(imagefile);

	imagefile = imagepath + "simple.png";
	PlayLevels[0].Load(imagefile);

	imagefile = imagepath + "medium.png";
	PlayLevels[1].Load(imagefile);

	imagefile = imagepath + "complex.png";
	PlayLevels[2].Load(imagefile);

	imagefile = imagepath + "simpley.png";
	PlayLevels[3].Load(imagefile);

	imagefile = imagepath + "mediumy.png";
	PlayLevels[4].Load(imagefile);

	imagefile = imagepath + "complexy.png";
	PlayLevels[5].Load(imagefile);

}

void CSudoku::CalcSize(int x, int y)
{
	int otop, oleft, top, left, bottom, right;
	int width, height;
	int i = 0;
	int j = 0;
	int stretchfactor, defaultwidthsize, defaultheightsize;
	double sfactor,sfactorw;
	// defaults for outer
	margin = 100;
	playrect = 200;
	thickline = 7;
	
	// defaults for inner
	inner_playrect = 64;
	inner_thickline = 4;

	if (x > y)
	{
		stretchfactor = y;
	}
	else
	{
		stretchfactor = x;
	}

	defaultwidthsize = (4*playrect) + (10 * thickline) + margin;
	defaultheightsize = (3*playrect) + (4 * thickline) + (2 * margin);
	sfactor = (double)stretchfactor/defaultheightsize;
	sfactorw = (double)stretchfactor/defaultwidthsize;

	if (sfactor > sfactorw)
	{
		sfactor = sfactorw;
	}

	margin = (int)(margin * sfactor);
	playrect = (int)(playrect * sfactor);
	thickline = (int)(thickline * sfactor);

	inner_playrect = (int)(inner_playrect * sfactor);
	inner_thickline = (int)(inner_thickline * sfactor);

	otop = margin;
	oleft = margin;
	width = (3*playrect) + (4 * thickline) + margin;
	height = (3*playrect) + (4 * thickline) + margin;

	PlayArea.top = otop;
	PlayArea.left = oleft;
	PlayArea.right = width;
	PlayArea.bottom = height;

	top = otop + thickline;
	bottom = top + inner_playrect;
	left = oleft + thickline;
	right = left + inner_playrect;

	for (i = 0; i < 9; i++)
	{
		if (i != 0)
		{
			if ((i == 3) || (i == 6))
			{
				top = top + inner_playrect + thickline;
				bottom = top + inner_playrect;
			}
			else
			{
				top = top + inner_playrect + inner_thickline;
				bottom = top + inner_playrect;
			}
		}
		left = oleft + thickline;
		right = left + inner_playrect;

		for (j = 0; j < 9; j++)
		{
			if (j != 0)
			{
				if ((j == 3) || (j == 6))
				{
					left = left + inner_playrect + thickline;
					right = left + inner_playrect;
				}
				else
				{
					left = left + inner_playrect + inner_thickline;
					right = left + inner_playrect;
				}
			}
			SgameDetails[i][j].CellRect.top = top;
			SgameDetails[i][j].CellRect.bottom = bottom;
			SgameDetails[i][j].CellRect.left = left;
			SgameDetails[i][j].CellRect.right = right;
		}
	}
	top = SgameDetails[0][0].CellRect.top;
	left = SgameDetails[0][8].CellRect.right + (5 * thickline);
	right = left + inner_playrect;
	bottom = top + inner_playrect;
	for (i = 1; i <= 10; i++)
	{
		if (i != 10)
		{
			KeyPad[i].left = left;
			KeyPad[i].top = top;
			KeyPad[i].right = right;
			KeyPad[i].bottom = bottom;
		}
		else
		{
			KeyPad[0].left = left;
			KeyPad[0].top = top;
			KeyPad[0].right = right;
			KeyPad[0].bottom = bottom;
		}
		left = left + inner_playrect + inner_thickline;
		right = left + inner_playrect;
		if ((i == 3) || (i == 6))
		{
			top = bottom + inner_thickline;
			left = SgameDetails[0][8].CellRect.right + (5 * thickline);
			right = left + inner_playrect;
			bottom = top + inner_playrect;
		}
		if (i == 9)
		{
			top = bottom + inner_thickline;
			left = SgameDetails[0][8].CellRect.right + (5 * thickline);
			left = left + inner_playrect + inner_thickline;
			right = left + inner_playrect;
			bottom = top + inner_playrect;
		}
	}
	KeyPadArea.top = KeyPad[1].top - inner_thickline;
	KeyPadArea.left = KeyPad[1].left - inner_thickline;
	KeyPadArea.right = KeyPad[3].right + inner_thickline;
	KeyPadArea.bottom = KeyPad[0].bottom + inner_thickline;

	top = KeyPadArea.bottom + (5 * thickline);
	left = KeyPadArea.left;
	bottom = top + (int)(100 * sfactor);
	right = left + (int)(200 * sfactor);

	for (i = 0; i < 3; i++)
	{
		PlayLevelRects[i].top = top;
		PlayLevelRects[i].left = left;
		PlayLevelRects[i].right = right;
		PlayLevelRects[i].bottom = bottom;
		top = bottom + inner_thickline;
		bottom = top + (int)(100 * sfactor);
	}
	PlayLevelArea.top = PlayLevelRects[0].top - inner_thickline;
	PlayLevelArea.left = PlayLevelRects[0].left - inner_thickline;
	PlayLevelArea.right = PlayLevelRects[0].right + inner_thickline;
	PlayLevelArea.bottom = PlayLevelRects[2].bottom + inner_thickline;

	PaintAll = true;
	//Invalidate(false);
}

void CSudoku::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	if (PaintAll == true)
	{
		GetWindowRect(&SRectColorChanger);
		CBrush BrushETYellow(RGB(255, 255, 128));

		// Select the new brush
		pSOldBrush = dc.SelectObject(&BrushETYellow);

		// Convert the current coordinates from Screen to Client
		ScreenToClient(&SRectColorChanger);
		// Change the background of the control
		dc.Rectangle(SRectColorChanger);

		CPen lPen(PS_SOLID, 3, RGB(0, 0, 0));
		CBrush BBrush(RGB(0,0,0));

		dc.SelectObject(&lPen);
		dc.SelectObject(&BBrush);
		dc.Rectangle(PlayArea);
		dc.Rectangle(KeyPadArea);
		dc.Rectangle(PlayLevelArea);		
	}

	if ((PaintKeyPad == true) || (PaintAll == true))
	{
		for (int i = 0; i < 10; i++)
		{
			if (IsKeyHighlighted[i] == true)
			{
				ynumbers[i].StretchBlt(dc, KeyPad[i]);
			}
			else
			{
				numbers[i].StretchBlt(dc, KeyPad[i]);
			}
		}
	}

	if ((PaintAll == true) || (PaintLevels == true))
	{
		for (int i = 0; i < 3; i++)
		{
			if (PlayLevel == i)
			{
				PlayLevels[i + 3].StretchBlt(dc, PlayLevelRects[i]);
			}
			else
			{
				PlayLevels[i].StretchBlt(dc, PlayLevelRects[i]);
			}
		}
		PaintLevels = false;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((PaintAll == true) || (SgameDetails[i][j].DoPaint == true))
			{
				DrawRect(&dc, SgameDetails[i][j]);
				SgameDetails[i][j].DoPaint = false;
			}
		}
	}

	PaintAll = false;
}

void CSudoku::DrawRect(CPaintDC *dc, GameDetails &GD)
{
	if (GD.Highlighted == HIGHILIGHTED)
	{
		ynumbers[GD.CellValue].StretchBlt(*dc, GD.CellRect);
	}
	else
	{
		if (GD.Highlighted == ROWHIGHLIHTED)
		{
			znumbers[GD.CellValue].StretchBlt(*dc, GD.CellRect);
		}
		else
		{
			numbers[GD.CellValue].StretchBlt(*dc, GD.CellRect);
		}
	}
}

void CSudoku::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	CMFCRibbonBar *pRibbon;
	CMFCRibbonCategory *pRibbonCategory;

	pRibbon = ((CMainFrame*)AfxGetMainWnd())->GetRibbonBar();
	pRibbonCategory = pRibbon->GetCategory(6);
	pRibbon->SetActiveCategory(pRibbonCategory, true);

	PaintAll = true;
	Invalidate(false);
}

void CSudoku::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	PaintAll = true;
	ScreenBottom = cy;
	ScreenRight = cx;

	CalcSize(cx, cy);
}

bool CSudoku::ClickOnPlayLevel(CPoint point)
{
	for (int i = 0; i < 3; i++)
	{
		if (PlayLevelRects[i].PtInRect(point) == TRUE)
		{
			PlayLevel = i;
			return true;
		}
	}
	return false;
}

void CSudoku::OnSudokunewButton()
{
	OnAppDeal();
}

void CSudoku::UpdatePlayArea()
{
	SgameDetails[SelectedRow][SelectedCol].CellValue = KeySelected;
	SgameDetails[SelectedRow][SelectedCol].DoPaint = true;
}

bool CSudoku::ClickOnPlayArea(CPoint point)
{
	int row, col;
	if ((SelectedRow >= 0) && (SelectedCol >= 0))
	{
		if (SgameDetails[SelectedRow][SelectedCol].Highlighted == HIGHILIGHTED)
		{
			PreviousSelectedRow = SelectedRow;
			PreviousSelectedCol = SelectedCol;
			 
			SgameDetails[SelectedRow][SelectedCol].Highlighted = NOTHIGHLIGHTED;
			SgameDetails[SelectedRow][SelectedCol].DoPaint = true;
		}
	}
	for (row = 0; row < 9; row++)
	{
		for (col = 0; col < 9; col++)
		{
			if (SgameDetails[row][col].CellRect.PtInRect(point) == TRUE)
			{
				TRACE("SgameDetails[row][col].CellValue = %d\n", SgameDetails[row][col].CellValue);
				TRACE("SgameDetails[SelectedRow][SelectedCol].CellValue = %d\n", SgameDetails[SelectedRow][SelectedCol].CellValue);
				TRACE("SgameDetails[SelectedRow][SelectedCol].Highlighted = %d\n", SgameDetails[SelectedRow][SelectedCol].Highlighted);
				TRACE("SgameDetails[SelectedRow][SelectedCol].DoPaint = %d\n", SgameDetails[SelectedRow][SelectedCol].DoPaint);
				if ((SelectedRow == -1) && (SelectedCol == -1))
				{
					SelectedRow = row;
					SelectedCol = col;
				}
				if ((SgameDetails[row][col].CellValue == 0) && (SgameDetails[SelectedRow][SelectedCol].CellValue != 0))
				{
					SgameDetails[SelectedRow][SelectedCol].Highlighted = HIGHILIGHTED;
					SgameDetails[SelectedRow][SelectedCol].DoPaint = true;
				}
				SelectedRow = row;
				SelectedCol = col;
				return true;
			}
		}
	}
	return false;
}

void CSudoku::ClearEasyHighlightedRowAndColumn()
{
	return;
	for(int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (SgameDetails[i][j].Highlighted == ROWHIGHLIHTED)
			{
				SgameDetails[i][j].Highlighted = NOTHIGHLIGHTED;
				SgameDetails[i][j].DoPaint = true;
			}
		}
	}
}

void CSudoku::IfEasyHighlightRowAndColumn(int RRow, int RCol)
{
	return;
	int i;
	for (i = 0; i < 9; i++)
	{
		if (SgameDetails[i][RCol].Highlighted == NOTHIGHLIGHTED)
		{
			SgameDetails[i][RCol].Highlighted = ROWHIGHLIHTED;
			SgameDetails[i][RCol].DoPaint = true;
		}
	}
	for (i = 0; i < 9; i++)
	{
		if (SgameDetails[RRow][i].Highlighted == NOTHIGHLIGHTED)
		{
			SgameDetails[RRow][i].Highlighted = ROWHIGHLIHTED;
			SgameDetails[RRow][i].DoPaint = true;
		}
	}
}

void CSudoku::HighlightLikeNumber(int key)
{
	int number;
	if (key == -1)
	{
		number = SgameDetails[SelectedRow][SelectedCol].CellValue;
	}
	else
	{
		number = key;
	}

	if (PlayLevel == 0)
	{
		ClearEasyHighlightedRowAndColumn();
	}
	if (number == 0)
	{
		SgameDetails[SelectedRow][SelectedCol].Highlighted = HIGHILIGHTED;
		SgameDetails[SelectedRow][SelectedCol].DoPaint = true;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((SgameDetails[i][j].CellValue == number) && (number != 0))
			{
				SgameDetails[i][j].Highlighted = HIGHILIGHTED;
				SgameDetails[i][j].DoPaint = true;
				if (PlayLevel == 0)
				{
					IfEasyHighlightRowAndColumn(i, j);
				}
			}
			else
			{
				if (number != 0)
				{
					if (SgameDetails[i][j].Highlighted == HIGHILIGHTED)
					{
						SgameDetails[i][j].Highlighted = NOTHIGHLIGHTED;
						SgameDetails[i][j].DoPaint = true;
					}
					else
					{
						if (!((PreviousSelectedRow == i) && (PreviousSelectedCol == j)))
						{
							if (SgameDetails[i][j].Highlighted != ROWHIGHLIHTED)
							{
								SgameDetails[i][j].Highlighted = NOTHIGHLIGHTED;
								SgameDetails[i][j].DoPaint = false;
							}
						}
					}
				}
			}
		}
	}
}

bool CSudoku::ClickOnKeyPad(CPoint point)
{
	for (int i = 0; i < 10; i++)
	{
		if (KeyPad[i].PtInRect(point) == TRUE)
		{
			KeySelected = i;
			return true;
		}
	}
	return false;
}

void CSudoku::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (GameOver == false)
	{
		if (ClickOnPlayLevel(point) == TRUE)
		{
			PaintLevels = true;
			Invalidate(false);
		}
		else
		{
			if (ClickOnPlayArea(point) == TRUE)
			{
				PlayAreaSelected = true;
				HighlightLikeNumber(-1);
				Invalidate(false);
			}
			else
			{
				if (ClickOnKeyPad(point) == TRUE)
				{
					if (PlayAreaSelected == true)
					{
						UndoLocation++;
						Undo[UndoLocation].row = SelectedRow;
						Undo[UndoLocation].col = SelectedCol;
						Undo[UndoLocation].oldval = SgameDetails[SelectedRow][SelectedCol].CellValue;
						Undo[UndoLocation].newval = KeySelected;
						UpdatePlayArea();
						HighlightLikeNumber(-1);
						SeeIfAllNumberIsPlayed();
						Invalidate(false);
					}
				}
			}
		}
	
		SeeIfGameIsWon();
	}
	CView::OnLButtonUp(nFlags, point);
}

void CSudoku::ClearBools()
{
	one = false;
	two = false;
	three = false;
	four = false;
	five = false;
	six = false;
	seven = false;
	eight = false;
	nine = false;
}

void CSudoku::SetBools(int val)
{
	switch (val)
	{
		case 1:
			one = true;
			break;
		case 2:
			two = true;
			break;
		case 3:
			three = true;
			break;
		case 4:
			four = true;
			break;
		case 5:
			five = true;
			break;
		case 6:
			six = true;
			break;
		case 7:
			seven = true;
			break;
		case 8:
			eight = true;
			break;
		case 9:
			nine = true;
			break;
	}
}

void CSudoku::SeeIfGameIsWon()
{
	int rows,cols;
	//int GoodColumns = 0;
	//int GoodRows = 0;
	//int GoodRegions = 0;
	//int Good;
	

	// check to make sure our rows are good
	for (rows = 0; rows < 9; rows++)
	{
		ClearBools();
		for (cols = 0; cols < 9; cols++)
		{
			SetBools(SgameDetails[rows][cols].CellValue);
		}
		// if we found all numbes we are good
		if (!(one && two && three && four && five && six && seven && eight && nine))
		{
			// didn't find a number so we are not good
			return;
		}
	}

	// check to make sure our columns are good
	for (cols = 0; cols < 9; cols++)
	{
		ClearBools();
		for (rows = 0; rows < 9; rows++)
		{
			SetBools(SgameDetails[rows][cols].CellValue);
		}
		// if we found all numbers we are good
		if (!(one && two && three && four && five && six && seven && eight && nine))
		{
			// didn't find a number so we are not good
			return;
		}
	}

	// make sure our regions are good
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ClearBools();
			for (rows = 0; rows < 3; rows++)
			{
				for (cols = 0; cols < 3; cols++)
				{
					SetBools(SgameDetails[Regions[i][j].Rcells[rows][cols].row][Regions[i][j].Rcells[rows][cols].column].CellValue);
				}
			}
			if (!(one && two && three && four && five && six && seven && eight && nine))
			{
				// didn't find a number so we are not good
				return;
			}

		}
	}

	// check rows
	GameOver = true;
	MessageBox("You won the game", "WINNER");

}

void CSudoku::SeeIfAllNumberIsPlayed()
{
	int count;
	for (int num = 1; num < 10; num++)
	{
		count = 0;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (SgameDetails[i][j].CellValue == num)
				{
					count++;
				}
			}
		}
		if (count == 9)
		{
			IsKeyHighlighted[num] = true;
			PaintKeyPad = true;
		}
		else
		{
			if (IsKeyHighlighted[num] == true)
			{
				IsKeyHighlighted[num] = false;
				PaintKeyPad = true;
			}
		}
	}
}

void CSudoku::OnXButtonUp(UINT nFlags, UINT nButton, CPoint point)
{
	if (UndoLocation >= 0)
	{
		SgameDetails[SelectedRow][SelectedCol].DoPaint = true;
		SgameDetails[SelectedRow][SelectedCol].Highlighted = NOTHIGHLIGHTED;

		SelectedRow = Undo[UndoLocation].row;
		SelectedCol = Undo[UndoLocation].col;
		SgameDetails[SelectedRow][SelectedCol].CellValue = Undo[UndoLocation].oldval;
		SgameDetails[SelectedRow][SelectedCol].DoPaint = true;
		SgameDetails[SelectedRow][SelectedCol].Highlighted = HIGHILIGHTED;
		HighlightLikeNumber(-1);
		UndoLocation--;
		Invalidate(false);
	}

	CView::OnXButtonUp(nFlags, nButton, point);
}

void CSudoku::SetupRegions()
{
	int cellRow = -1;
	int cellCol = -1;
	int regionRow = -1;
	int regionCol = -1;

	for (int row = 0; row < 9; row++)
	{
		cellRow = row % 3;
		if (row < 3)
		{
			regionRow = 0;
		}
		if ((row < 6) && (row >= 3))
		{
			regionRow = 1;
		}
		if (row >= 6)
		{
			regionRow = 2;
		}
		for (int col = 0; col < 9; col++)
		{
			cellCol = col % 3;
			if (col < 3)
			{
				regionCol = 0;
			}
			if ((col < 6) && (col >= 3))
			{
				regionCol = 1;
			}
			if (col >= 6)
			{
				regionCol = 2;
			}
			Regions[regionRow][regionCol].Rcells[cellRow][cellCol].row = row;
			Regions[regionRow][regionCol].Rcells[cellRow][cellCol].column = col;
		}
	}
	
}

void CSudoku::generate(int choice)
{

	int c,i,m,n,count=1,fixed,error;
	
	Init();
	srand((unsigned)time(NULL));

generate:
	for(i=0;i<60;i++)
	{
		r[i][0]=20; r[i][1]=20;
	}
	switch(choice)
	{
		case 0: 
			mode=38+rand()%4;
			break;
		case 1: 
			mode=29+rand()%4;
			break;
		case 2: 
			mode=27+rand()%2;
			break;
		case 3: 
			mode=25+rand()%2;
			break;
	}
	
	SgameDetails[0][0].CellValue=1+rand()%8;
	r[0][0]=0; r[0][1]=0;
	
	for(count=1;count<10;count++)
	{
choose:
		m=rand()%9; 
		n=rand()%9;
		fixed=isfixed(icount,m,n);
		if(fixed==1)
		{
			goto choose;
		}

		r[count][0]=m; 
		r[count][1]=n;
allot:
		SgameDetails[m][n].CellValue=1+rand()%9;
		if(SgameDetails[m][n].CellValue==0)
		{
			goto allot;
		}
		c=check(m,n);
		if(c==0)
		{
			goto allot;
		}
	}
	icount=count;
	error=solve();
	for(m=0;m<9;m++)
	{
		for(n=0;n<9;n++)
		{
			b[m][n]=SgameDetails[m][n].CellValue;
		}
	}
	row=0; col=0;
	for(i=0;i<60;i++)
	{
		r[i][0]=20; r[i][1]=20;
	}
	if(error==0)
		goto generate;
	for(count=0;count<mode/2;count++)
	{
choose2:
		m=rand()%9; n=rand()%9;
		fixed=isfixed(count,m,n);
		if(fixed==1)
		{
			goto choose2;
		}
		r[count][0]=m; r[count][1]=n;
		r[count+mode/2][0]=8-m;
		r[count+mode/2][1]=8-n;
	}
	for(m=0;m<9;m++)
		for(n=0;n<9;n++)
		{
			fixed=isfixed(mode,m,n);
			if(fixed!=1)
			{
				SgameDetails[m][n].CellValue=0;
			}
		}
	icount=mode;

}

int CSudoku::isfixed(int count, int m, int n)
{
	int i;
	for(i=0;i<count;i++)
	{
		if(m==r[i][0] && n==r[i][1])
		{
			return(1);
		}
	}
	return(0);
}

int CSudoku::checkrow(int m, int n)
{
	int x;
	for(x=0;x<9;x++)
	{
		if(x!=n)
		{
			if(SgameDetails[m][n].CellValue==SgameDetails[m][x].CellValue)
			{
				return(0);
			}
		}
	}
	return(1);
}


int CSudoku::checkcolumn(int m, int n)
{
	int x;
	for(x=0;x<9;x++)
	{
		if(x!=m)
		{
			if(SgameDetails[m][n].CellValue==SgameDetails[x][n].CellValue)
			{
				return(0);
			}
		}
	}
	return(1);
}

/*FUNCTION TO CHECK CONSISTENCY OF AN ELEMENT*/

int CSudoku::check(int m,int n)
{
	int c;
	c=checkmat(m,n);
	if(c==1)
	{
		c=c*checkrow(m,n);
	}
	else
	{
		return(c);
	}
	if(c==1)
	{
		c=c*checkcolumn(m,n);
	}
	else
	{
		return(c);
	}
	return(c);
}

int CSudoku::checkmat(int m, int n)
{
	int x,y;
	for(x=(m/3)*3;x<((m/3)*3+3);x++)
	{
		for(y=(n/3)*3;y<((n/3)*3+3);y++)
		{
			if(m!=x && n!=y)
			{
				if(SgameDetails[m][n].CellValue==SgameDetails[x][y].CellValue)
				{
					return(0);
				}
			}
		}
	}
	return(1);
}



int CSudoku::solve()
{
	int m=0,n=0,number,c,fixed;

mainallot:

	for(m=row;m<9;m++)
	{
		n=col;
		while(n<9)
		{
			number=1;
			fixed=isfixed(icount,m,n);
			if(fixed==0)
			{
allot:
				SgameDetails[m][n].CellValue=number;
				
				c=check(m,n);
				if(c==0)
				{
					number++;
					if(number>9)
					{
						SgameDetails[m][n].CellValue=0;
						if(n==0)
						{
							row=m-1; col=8;
							if(row<0)
							{
								return(0);
							}
							goto backadjust;
						}
						else
						{
							row=m; col=n-1;
							if(row<0 || col<0)
							{
								return(0);
							}
							goto backadjust;
						}
					}
					goto allot;
				}
			}
			n++;
			if(n>8)
			{
				col=0;
			}
		}
	}
	return(1);

backadjust:

	fixed=isfixed(icount,row,col);
	if(fixed==0)
	{
		number=SgameDetails[row][col].CellValue;
allot1:
		number++;
		SgameDetails[row][col].CellValue=number;
		if(number>9)
		{
			SgameDetails[row][col].CellValue=0;
			if(col==0)
			{
				row--; col=8;
				if(row<0)
				{
					return(0);
				}
				goto backadjust;
			}
			else
			{
				col--;
				if(col<0)
				{
					return(0);
				}
				goto backadjust;
			}
		}
		c=check(row,col);
		if(c==0)
			goto allot1;
		else
		{
			if(col==8)
			{
				row++;
				if(row>8)
				{
					return(0);
				}
				col=0;
				goto mainallot;
			}
			else
			{
				col++;
				if(col>8)
				{
					return(0);
				}
				goto mainallot;
			}
		}
	}
	else
	{
		if(col==0)
		{
			row--; col=8;
			if(row<0)
			{
				return(0);
			}
			goto backadjust;
		}
		else
		{
			col--;
			if(col<0)
			{
				return(0);
			}
			goto backadjust;
		}
	}
}


void CSudoku::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (ClickOnKeyPad(point) == TRUE)
	{
		HighlightLikeNumber(KeySelected);
		Invalidate(false);
	}
	CView::OnRButtonUp(nFlags, point);
}
