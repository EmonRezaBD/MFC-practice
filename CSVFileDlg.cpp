
// CSVFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSVFile.h"
#include "CSVFileDlg.h"
#include "afxdialogex.h"
#include "ShellAPI.h" //To automatic opening of csv file
#include "fstream"
#include "atlstr.h" // Include the necessary header for CStringA
#include "iostream"
#include <string>
#include <sstream>
#include <vector>
using namespace std;



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCSVFileDlg dialog



CCSVFileDlg::CCSVFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCSVFileDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCSVFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ID, m_editID);
	DDX_Control(pDX, IDC_Value, m_editValue);
	DDX_Control(pDX, IDC_Submit, m_btnSubmit);
}

BEGIN_MESSAGE_MAP(CCSVFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_Value, &CCSVFileDlg::OnEnChangeValue)
	ON_BN_CLICKED(IDC_Submit, &CCSVFileDlg::OnBnClickedSubmit)
END_MESSAGE_MAP()


// CCSVFileDlg message handlers

BOOL CCSVFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCSVFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCSVFileDlg::OnPaint()
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCSVFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCSVFileDlg::OnEnChangeValue()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.


	// TODO:  Add your control notification handler code here
}

std::vector<std::vector<std::string>> ReadCSVFile(const std::string& filePath)
{
    std::vector<std::vector<std::string>> rows;

    std::ifstream file(filePath);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<std::string> row;
            std::stringstream ss(line);
            std::string field;

            while (std::getline(ss, field, ','))
            {
                row.push_back(field);
            }

            rows.push_back(row);
        }

        file.close();
    }

    return rows;
}

void CCSVFileDlg::OnBnClickedSubmit()
{
	// TODO: Add your control notification handler code here
	//ASSERT(m_nMode==modeRead);
	CString strID, strValue;
	m_editID.GetWindowText(strID);
	m_editValue.GetWindowText(strValue);
	
	//int id = _tstoi(strID);
	string id = CW2A(strID.GetString());

	string value = CW2A(strValue.GetString());

    ofstream file("data.txt", ofstream::app); // Open the file in append mode
	vector<vector<string>> vec = ReadCSVFile("data.txt");
	int sz = vec.size();
    if (file.is_open())
    {
		for(int i=0; i<sz; i++)
		{
			if(id==vec[i][0])
			{
				id = vec[i][0];
				value = vec[i][1];
				 
				//file << id << "," << value << "\n"; // Insert the values into the file
			}
			else
			{
				vector<string> temp;
				temp.push_back(id);
				temp.push_back(value);
				vec.push_back(temp);

			}

		   //file << id << "," << value << "\n"; // Insert the values into the file
		}
        file.close(); // Close the file
    }
    else
    {
        // Handle file open error
		AfxMessageBox(_T("File is not exists!\n"));
    }
	
	//std::ofstream file1("data.csv", std::ios::app); // Open the file in append mode
	ofstream file1("data1.txt", ios::app); // Open the file in append mode


	for(unsigned int i=0; i<vec.size(); i++)
	{
	   file1 << vec[i][0] << "," << vec[i][1] << "\n"; // Insert the values into the file
	  // file1.seekp(-1, std::ios_base::cur); // Remove the trailing comma


	}
	file1.close(); // Close the file*/





	
	//CStringArray values;
	//values.Add(_T("Value 1"));

	//Open csv file for writing
	/*CString strFilePath("UserData.csv");
	CStdioFile file;

	
	if(file.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		CString strLine;
		//strLine.Format(_T("%s,%s\n"), strID, strValue);

		//Append a row
		file.SeekToEnd();//move to the end of the file
		strLine.Format(_T("%s,%s\n"), strID, strValue);
		file.WriteString(strLine+_T("\n"));

		file.Close();*/

		//ShellExecute(NULL, _T("open"), strFilePath, NULL, NULL, SW_SHOWNORMAL);
}


	

