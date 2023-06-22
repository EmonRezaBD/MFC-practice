
 //DemoProjectDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdialogex.h"
#include<map>
#include<string>
#include<vector>

//For chart
#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\Chartlabel.h"

//For dialog
#include "FirstDialog.h"
#include "SecondDialog.h"


using namespace std;


// CDemoProjectDlg dialog
class CDemoProjectDlg : public CDialogEx
{
// Construction
public:
	CDemoProjectDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DEMOPROJECT_DIALOG };

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
	afx_msg void OnBnClickedLoadFile();
	CButton m_btnLoadFile;
	afx_msg void buildTree();
	//afx_msg wstring ConvertToWideString(const string& );

private:
	CTreeCtrl * TreeSoft;
		//~CTree1Dlg(); 
	HTREEITEM InsertItem(LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST );
public:
	CTabCtrl m_Tab;
	CWnd* m_pwndShow;
	CFirstDialog m_firstDialog;
	CSecondDialog m_secondDialog;
	
	afx_msg void OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult);

	map<string,vector<double>> m_dataMap;
	map<string,vector<double>> ::iterator it;
	map<string,vector<double>> SomeFunc();
	CListCtrl m_List;
	void DeleteListControl(CListCtrl& listCtrl);
	void LoadCSVFile(CString& filePath, std::map<std::string, std::vector<double>>& m_dataMap);
};
