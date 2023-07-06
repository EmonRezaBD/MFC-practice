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
	ON_COMMAND(ID_EXPORTDATA, &CFirstDialog::OnExportContextMenu)

END_MESSAGE_MAP()

CFirstDialog* CFirstDialog::child = NULL;


BOOL CFirstDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	__super::OnInitDialog();
	child = this;

		//For chart control
		CChartCtrl ref;
		ref.RemoveAllSeries();
		m_ChartCtrl.EnableRefresh(true);
		pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
		pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);

		//Setting the axes
		pBottomAxis->SetMinMax(-2, 30); //Can be changed dynamically for the first appeared graph 
		pLeftAxis->SetMinMax(-2,30);

		pBottomAxis->SetTickIncrement(false,20.0);
		//pBottomAxis->SetDiscrete(false);
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

void CFirstDialog::OnExportContextMenu()
{
	CStdioFile file;
	file.Open(_T("graphData.csv"), CFile::modeCreate | CFile::modeWrite | CFile::typeText);

	CString strLine;
	//strLine.Format(_T("%s,%s\n"), _T("Column 1"), _T("Column 2"));
	strLine.Format(_T("%s,%s\n"), xValue, yValue);
	file.WriteString(strLine);

	int Size = m_dataMap[xValue].size();
	for (int i = 0; i < Size; i++)
	{
		strLine.Format(_T("%f, %f\n"), m_dataMap[xValue][i], m_dataMap[yValue][i]); //Inserting each row in new csv file
		file.WriteString(strLine);
	}

	file.Close();

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
	

	//Creating CSV file
	/*CStdioFile file;
	file.Open(_T("graphData.csv"), CFile::modeCreate | CFile::modeWrite | CFile::typeText);


	CString strLine;
	//strLine.Format(_T("%s,%s\n"), _T("Column 1"), _T("Column 2"));
	strLine.Format(_T("%s,%s\n"), xValue, yValue);
	file.WriteString(strLine);

	int Size = m_dataMap[xValue].size();
	for (int i = 0; i < Size; i++)
	{
		strLine.Format(_T("%f, %f\n"), m_dataMap[xValue][i], m_dataMap[yValue][i]); //Inserting each row in new csv file
		file.WriteString(strLine);
	}

	file.Close();*/

	//CString filePath = _T("chart.jpeg"); //Code for exporting as jpeg image
	//ExportChartToJpg(m_ChartCtrl, filePath);

	/*CImage image;
	image.Create(120, 480, 32);
	CDC* pDC = CDC::FromHandle(image.GetDC());
	m_ChartCtrl.SendMessage(WM_PRINTCLIENT, (WPARAM)pDC->m_hDC, PRF_CLIENT);
	image.Save(_T("chart.jpg"), Gdiplus::ImageFormatJPEG);
	CRect rect;
	m_ChartCtrl.GetWindowRect(rect);
	pDC = m_ChartCtrl.GetDC();*/


}

// CFirstDialog message handlers
/*void CFirstDialog::ExportChartToJpg(CChartCtrl& chartCtrl, CString filePath) //Exporting to jpg, came only white image
{
	
    CBitmap bmp;
    bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

    CDC memDC;
    memDC.CreateCompatibleDC(pDC);

    CBitmap* pOldBmp = memDC.SelectObject(&bmp);

    memDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));

    chartCtrl.SendMessage(WM_PRINT, (WPARAM)memDC.GetSafeHdc(), PRF_CLIENT | PRF_CHILDREN | PRF_NONCLIENT);

    CImage image;
    image.Attach((HBITMAP)bmp.Detach());

    CStringW strFilePath(filePath);
    HRESULT hr = image.Save(strFilePath.GetString(), Gdiplus::ImageFormatJPEG);

    memDC.SelectObject(pOldBmp);
    chartCtrl.ReleaseDC(pDC);
}*/

void CFirstDialog::insertInCombo() {
	CString strItem;
	m_First.ResetContent();
	m_Second.ResetContent();

	//for(it = m_dataMap.begin(); it!=m_dataMap.end(); it++)
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

