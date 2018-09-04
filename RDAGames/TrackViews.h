#pragma once
class CTrackViews
{
public:
	CTrackViews(void);
	~CTrackViews(void);

public:
	CFile viewstatus;

public:
	void TVDeleteFile();
	int GetStatus(int viewtype);
	int SetStatus(int viewtype);
	void RemoveStatus(int viewtype);
};

