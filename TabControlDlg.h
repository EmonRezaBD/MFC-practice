
// TabControlDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "onedialog.h"
#include "seconddialog.h"
#include "ThirdDialog.h"
#include "FourthDialog.h"
#include "FifthDialog.h"



// CTabControlDlg dialog
class CTabControlDlg : public CDialogEx
{
// Construction
public:
	CTabControlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TABCONTROL_DIALOG };

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
	CTabCtrl m_Tab;
	COneDialog m_one;
	CSecondDialog m_second;
	CThirdDialog m_third;
	CFourthDialog m_fourth;
	CFifthDialog m_fifth;
	CWnd* m_pwndShow;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
