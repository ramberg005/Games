#pragma once



struct RowColumn
{
	int Row;
	int Column;
	int Plane;
};

struct Adjancent
{
	int leftID;
	int rightID;
	int topID;
	int bottomID;
	int aboveID;
	int belowID;
	RowColumn rc;
};

struct RectDefinition {
	bool Draw;
	bool Played;
	bool TileSelected;
	int locationID;
	int TileID;
	Adjancent adjancentIDs;
	CRect ScreenLocation;
};





class CMJLonghorn
{
public:
	CMJLonghorn(void);
	~CMJLonghorn(void);

public:
	RectDefinition LHRectDefinition[MAHJONGTILES];

public:
	void SetAdjancentIDs();
	void SetupData();
	void SetSize(double stretchval);
	int Round(double d);
};

