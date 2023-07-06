//#include "DemoProjectDlg.h"

#pragma once
#include "afxwin.h"
#include "ChartCtrl\Chartctrl.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\Chartlabel.h"

//Building graph
#include<map>
#include<vector>

//Exporting chart
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace std;

// CFirstDialog dialog

class CFirstDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFirstDialog)
public:
	CFirstDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFirstDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };
	enum ChartImageFormat; //For exporting chart


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//For chart
	HICON m_hIcon;

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CComboBox m_First;
	CComboBox m_Second;

	afx_msg void OnBnClickedExportgraphbtn();
public:
	CChartCtrl m_ChartCtrl;
	CChartStandardAxis* pBottomAxis = NULL;
	CChartStandardAxis* pLeftAxis = NULL;
	CChartLineSerie* pSeries = NULL;

	CString xValue;
	CString yValue;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnExportContextMenu();

	//void ExportChartToJpg(CChartCtrl&,CString);

	bool xValFlag = false, yValFlag = false;
	void CopyValues();
	static CFirstDialog* child;
	void insertInCombo();
	void generateGraph();

	
};
