#pragma once


// CSecondDialog dialog

class CSecondDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSecondDialog)

public:
	CSecondDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSecondDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
