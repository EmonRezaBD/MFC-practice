#pragma once


// COneDialog dialog

class COneDialog : public CDialogEx
{
	DECLARE_DYNAMIC(COneDialog)

public:
	COneDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~COneDialog();

// Dialog Data
	enum { IDD = IDD_One_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
