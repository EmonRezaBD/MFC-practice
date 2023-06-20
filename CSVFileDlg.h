
// CSVFileDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CCSVFileDlg dialog
class CCSVFileDlg : public CDialogEx
{
// Construction
public:
	CCSVFileDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CSVFILE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//enum Mode {modeRead,modeWrite};
	afx_msg void OnEnChangeValue();
	afx_msg void OnBnClickedSubmit();

	//afx_msg void Write
	CEdit m_editID;
	CEdit m_editValue;
	CButton m_btnSubmit;


/*#ifdef _DEBUG
Mode m_nMode;
#endif*/
};


