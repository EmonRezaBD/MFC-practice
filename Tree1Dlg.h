
// Tree1Dlg.h : header file
//

#pragma once


// CTree1Dlg dialog
class CTree1Dlg : public CDialogEx
{
// Construction
public:
	CTree1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TREE1_DIALOG };

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
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
private:
		CTreeCtrl * TreeSoft;
		//~CTree1Dlg(); 
	   HTREEITEM InsertItem(LPCTSTR lpszItem,
                                    HTREEITEM hParent = TVI_ROOT,
                                    HTREEITEM hInsertAfter = TVI_LAST );

};
