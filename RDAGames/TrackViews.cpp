#include "StdAfx.h"
#include "TrackViews.h"


CTrackViews::CTrackViews(void)
{
}


CTrackViews::~CTrackViews(void)
{
}

void CTrackViews::TVDeleteFile()
{
	viewstatus.Open("trackview.vi", CFile::modeCreate);
	viewstatus.Close();
}

int CTrackViews::GetStatus(int viewtype)
{
	BOOL fileexists;
	char vals[2];
	int bytesread;

	fileexists = viewstatus.Open("trackview.vi", CFile::modeRead);
	if (!fileexists)
	{
		viewstatus.Close();
		return -1;
	}
	viewstatus.SeekToBegin();
	do
	{
		bytesread= viewstatus.Read(vals, 2);
		if (vals[0] == viewtype)
		{
			viewstatus.Close();
			return vals[1];
		}
	} while (bytesread > 0);
	viewstatus.Close();
	return -1;
}

int CTrackViews::SetStatus(int viewtype)
{
	char vals[2];
	int viewID;
	int bytesread;

	viewstatus.Open("trackview.vi", CFile::modeReadWrite | CFile::modeNoTruncate);
	viewID = -1;
	viewstatus.SeekToBegin();
	do
	{
		bytesread = viewstatus.Read(vals, 2);
		if (bytesread > 0)
		{
			viewID = vals[1];
		}
	} while (bytesread > 0);
	viewID++;
	viewstatus.SeekToEnd();
	vals[0] = viewtype;
	vals[1] = viewID;
	viewstatus.Write(vals, 2);
	viewstatus.Close();
	return viewID;
}

void CTrackViews::RemoveStatus(int viewtype)
{
	char vals[10][2];
	int i;
	int k;
	int bytesread;

	viewstatus.Open("trackview.vi", CFile::modeReadWrite | CFile::modeNoTruncate);
	i = 0;
	viewstatus.SeekToBegin();
	do
	{
		bytesread = viewstatus.Read(vals[i], 2);
		if (bytesread > 0)
		{
			i++;
		}
	} while (bytesread > 0);
	
	viewstatus.Close();
	viewstatus.Open("trackview.vi", CFile::modeCreate);
	viewstatus.Close();

	viewstatus.Open("trackview.vi", CFile::modeReadWrite | CFile::modeNoTruncate);

	k = 0;
	for (int j = 0; j < i; j++)
	{
		if (vals[j][0] != viewtype)
		{
			vals[j][1] = k;
			viewstatus.Write(vals[j], 2);
			k++;
		}
	}
	viewstatus.Close();
}