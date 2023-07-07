// FirstDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DemoProject.h"
#include "FirstDialog.h"
#include "afxdialogex.h"
#include "DemoProjectDlg.h"
#include<vector> //For vector
#include<map>
//For chart
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\ChartPointsSerie.h"
#include "ChartCtrl\ChartSurfaceSerie.h"
#include "ChartCtrl\ChartGrid.h"
#include "ChartCtrl\ChartBarSerie.h"
#include "ChartCtrl\ChartLabel.h"

#include "ChartCtrl\ChartAxisLabel.h"
#include "ChartCtrl\ChartStandardAxis.h"
#include "ChartCtrl\ChartDateTimeAxis.h"

#include "ChartCtrl\ChartCrossHairCursor.h"
#include "ChartCtrl\ChartDragLineCursor.h"

//For exporting chart
#include <gdiplus.h>
#include <atlimage.h>
#include <sstream> // This defines stringstream
#include <fstream> // This defines stringstream

#pragma comment(lib, "gdiplus.lib")
using namespace std;

map<CString, vector<double>> m_dataMap;
map<CString, vector<double>>::iterator it = m_dataMap.begin();
// CFirstDialog dialog

IMPLEMENT_DYNAMIC(CFirstDialog, CDialogEx) 

CFirstDialog::CFirstDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFirstDialog::IDD, pParent)
	, xValue(_T(""))
	, yValue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CFirstDialog::~CFirstDialog()
{
	//delete pBottomAxis;
	//delete pLeftAxis;
	//delete pSeries;
	//delete child;
}

void CFirstDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_First);
	DDX_Control(pDX, IDC_COMBO2, m_Second);
	DDX_Control(pDX, IDC_CUSTOM1, m_ChartCtrl);
	DDX_CBString(pDX, IDC_COMBO1, xValue);
	DDX_CBString(pDX, IDC_COMBO2, yValue);
}


BEGIN_MESSAGE_MAP(CFirstDialog, CDialogEx)
	
	ON_BN_CLICKED(IDC_ExportGraphBtn, &CFirstDialog::OnBnClickedExportgraphbtn)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CFirstDialog::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CFirstDialog::OnCbnSelchangeCombo2)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EXPORTDATA_EXPORTGRAPH, &CFirstDialog::OnExportdataExportgraph)
END_MESSAGE_MAP()

CFirstDialog* CFirstDialog::child = NULL;


BOOL CFirstDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	__super::OnInitDialog();
	child = this;

		//For chart control
		//CChartCtrl ref;
		
	m_ChartCtrl.RemoveAllSeries();
	m_ChartCtrl.EnableRefresh(true);
	pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);

		//Setting the axes
	

	pBottomAxis->SetMinMax(-2, 30); //Can be changed dynamically for the first appeared graph 
	pLeftAxis->SetMinMax(-2,30);

	pBottomAxis->SetTickIncrement(false,20.0);
	pBottomAxis->EnableScrollBar(true);

	
	 return true;
}
void CFirstDialog::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//Context menu
void CFirstDialog::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//Load the desired menu
	CMenu mnuPopupSubmit;

	mnuPopupSubmit.LoadMenu(IDR_MENU1);


	//Get a pointer to the button
	CButton* pButton;
	pButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_CUSTOM1));
	CRect rectSubmitButton;

	pButton->GetWindowRect(&rectSubmitButton);


	//Get a pointer to the first item of the menu
	CMenu* mnuPopupMenu = mnuPopupSubmit.GetSubMenu(0); //0 means first menu

	ASSERT(mnuPopupMenu);


	//Find out if the user right-clicked the button
	//becasue we are interested only the button
	if (rectSubmitButton.PtInRect(point))
		mnuPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTALIGN, point.x, point.y, this);
}

void CFirstDialog::OnCbnSelchangeCombo1()
{
	int comboBox1SelectedItem = m_First.GetCurSel(); //GetCurSel() return the index
	if(comboBox1SelectedItem != LB_ERR) //LB_ERR means index is -1
	{
		
		m_First.GetLBText(comboBox1SelectedItem, xValue); //GetLBText is stroing the text in str
		xValFlag = true;
		//m_latestComboSelection = _T("CB1 ")+m_latestComboSelection;
		UpdateData(false);

	}
		
}


void CFirstDialog::OnCbnSelchangeCombo2()
{
	int comboBox1SelectedItem = m_Second.GetCurSel(); //GetCurSel() return the index
	if(comboBox1SelectedItem != LB_ERR) //LB_ERR means index is -1
	{

		m_Second.GetLBText(comboBox1SelectedItem, yValue); //GetLBText is stroing the text in str
		yValFlag = true;
		//m_latestComboSelection = _T("CB1 ")+m_latestComboSelection;
		UpdateData(false);

	}
	if (xValFlag == true && yValFlag == true)
	{
		generateGraph(); //Generating graph dynamically
	}
		
}

void CFirstDialog::generateGraph()
{
	//ref
	m_ChartCtrl.RemoveAllSeries();
	m_ChartCtrl.EnableRefresh(true);

	//CDemoProjectDlg* baseObj = CDemoProjectDlg::basePointer;
	//int x = baseObj->minValInMap;
	//int y = baseObj->maxValInMap;

	//pBottomAxis->SetMinMax(x, y); //Can be changed dynamically for the first appeared graph 
	//pLeftAxis->SetMinMax(x, y);


	pLeftAxis->GetLabel()->SetText(xValue.GetString());
	pBottomAxis->GetLabel()->SetText(yValue.GetString());

	pBottomAxis->SetTickIncrement(false, 20.0);
	pBottomAxis->SetDiscrete(false);
	pBottomAxis->EnableScrollBar(true);

	pSeries = m_ChartCtrl.CreateLineSerie();
	pSeries->ClearSerie();
	pSeries->SetWidth(5); //line width
	pSeries->SetColor(RGB(0, 0, 255)); //color of line

	int Xsize = m_dataMap[xValue].size();
	int Ysize = m_dataMap[yValue].size();

	double *Xval = new double[Xsize];
	double *Yval = new double[Ysize];
	
	for (int i = 0; i < Xsize; i++)
	{
		Xval[i] = m_dataMap[xValue][i];
		Yval[i] = m_dataMap[yValue][i];
	}

	//double Xval[5] = { 100.02, 110.50, 120.3, 130.6 };
	//double Yval[5] = { 0.81, 0.91, 1.02, 1.10, 1.2033};
	pSeries->SetPoints(Xval, Yval, Xsize); //5 cz taking total 5 co-ordinates
	m_ChartCtrl.EnableRefresh(true);

	free(Xval);
	free(Yval);
}

void CFirstDialog::OnBnClickedExportgraphbtn()
{
	std::ofstream outputFile("graphData.csv");
	if (outputFile.is_open())
	{
		// Write the headers
		outputFile << CT2A(xValue) << "," << CT2A(yValue) << endl;

		// Determine the maximum size of the vectors
		//size_t maxSize = std::max(xvec.size(), yvec.size());

		// Iterate over the vectors
		for (size_t i = 0; i < m_dataMap[xValue].size(); i++)
		{
			// Write vector1 value if available
			outputFile << m_dataMap[xValue][i];

			outputFile << ",";

			// Write vector2 value if available
			outputFile << m_dataMap[yValue][i];

			outputFile << endl;
		}
		outputFile.close();
		// Close the file
	}
}

void CFirstDialog::insertInCombo() {
	CString strItem;
	m_First.ResetContent();
	m_Second.ResetContent();

	for (auto i : m_dataMap) //Inserting items into comboBox from the map
	{
		//strItem = (it->first.c_str());
		strItem = i.first;
		m_First.AddString(strItem);
		m_Second.AddString(strItem);
	}
}

void CFirstDialog::CopyValues() {
	CDemoProjectDlg* baseObj = CDemoProjectDlg::basePointer;
	m_dataMap = baseObj->m_dataMap;

	insertInCombo();
	generateGraph();
}

void CFirstDialog::OnExportdataExportgraph()
{
	// TODO: Add your command handler code here
	LPCTSTR pszFilter = _T("JPEG (*.jpg)|*.jpg|")
		_T("CSV (*.csv)|*.csv|")
		_T("Text (*.txt)|*.txt");

	CFileDialog dlgFile(FALSE, _T("jpg"), _T("Untitled"), OFN_HIDEREADONLY | OFN_FILEMUSTEXIST| OFN_OVERWRITEPROMPT, pszFilter, AfxGetMainWnd());
	try {
		if (IDOK == dlgFile.DoModal()) {
			string filepathAndName = string(CT2A(dlgFile.GetPathName()));
			std::wstring path(filepathAndName.begin(), filepathAndName.end());
			string fileExt = string(CT2A(dlgFile.GetFileExt()));
			CRect rect;
			if (fileExt == "jpg") {
				m_ChartCtrl.SaveAsImage(path, rect, 32, Gdiplus::ImageFormatJPEG);
				AfxMessageBox(L"File Saved Sucessfully!");
			}

		}
	}
	catch(CFileException * E){
		CString error;
		error.Format(_T("File could not be saved, cause = %d\n"), E->m_cause);
		AfxMessageBox(error);
		E->Delete();
	}
}
