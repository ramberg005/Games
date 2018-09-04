#pragma once


// CJewelGameOver dialog

class CJewelGameOver : public CDialogEx
{
	DECLARE_DYNAMIC(CJewelGameOver)

public:
	CJewelGameOver(CWnd* pParent = NULL);   // standard constructor
	virtual ~CJewelGameOver();

// Dialog Data
	enum { IDD = IDD_JEWEL_GAMEOVER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
