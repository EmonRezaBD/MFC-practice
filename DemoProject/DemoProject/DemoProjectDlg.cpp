
// DemoProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DemoProject.h"
#include "DemoProjectDlg.h"
#include "afxdialogex.h"
//Added
#include "atlstr.h" // Include the necessary header for CStringA
#include "iostream"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
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
public:
	afx_msg void OnExportdataContextMenu();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_EXPORTDATA_EXPORTDATA, &CAboutDlg::OnExportdataContextMenu)
END_MESSAGE_MAP()


// CDemoProjectDlg dialog

//int CDemoProjectDlg::X = 10;

CDemoProjectDlg::CDemoProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDemoProjectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	TreeSoft = new CTreeCtrl;
}

void CDemoProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOAD_FILE, m_btnLoadFile);
	DDX_Control(pDX, IDC_Main_Tab, m_Tab);
	DDX_Control(pDX, IDC_LIST1, m_List);
}

BEGIN_MESSAGE_MAP(CDemoProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_LOAD_FILE, &CDemoProjectDlg::OnBnClickedLoadFile)
	ON_NOTIFY(TCN_SELCHANGE, IDC_Main_Tab, &CDemoProjectDlg::OnTcnSelchangeMainTab)
	ON_BN_CLICKED(IDOK, &CDemoProjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()

//CDemoProjectDlg* CDemoProjectDlg::CtrlDlg = NULL;
	CDemoProjectDlg* CDemoProjectDlg::basePointer = NULL; //Declaring NULL
// CDemoProjectDlg message handlers

BOOL CDemoProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	basePointer = this;
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
	//Create Tree Control
	TreeSoft->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP |
		             TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
			 TVS_SINGLEEXPAND | TVS_SHOWSELALWAYS |  
			 TVS_TRACKSELECT,
		             CRect(30, 80, 150, 290), this, 0x1221);
	//For Tab Control
	CString TabName= _T(""); //initializing an empty string
	for(int i=0; i<2; i++)
	{
		TabName.Format(_T("Tab-%d"), i+1);
		m_Tab.InsertItem(i,TabName,i);
	} //Tab creation
	CRect rect;
	m_Tab.GetClientRect(&rect);

	m_secondDialog.Create(IDD_DIALOG2, &m_Tab);
	m_secondDialog.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_SHOWWINDOW | SWP_NOZORDER);

	m_firstDialog.Create(IDD_DIALOG1, &m_Tab);
	m_firstDialog.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pwndShow = &m_firstDialog;

	m_firstDialog.ShowWindow(SW_SHOW);
	m_secondDialog.ShowWindow(SW_HIDE);
	m_pwndShow = &m_firstDialog;

	vector<int> v;
	v.push_back(1);
	v.push_back(3);
	v.push_back(5);

	//CFirstDialog * fstDlg = NULL;
	//int sz = fstDlg->vec.size();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoProjectDlg::OnPaint()
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
HCURSOR CDemoProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//List control code




void CDemoProjectDlg::buildTree()
{
	//Adding item to tree control
	HTREEITEM fileHeader;
	/*int n = m_dataMap.size();
	it = m_dataMap.begin();
	CStringA cstrA(it->first.c_str());
	CStringW cstrW(cstrA);*/
	
	fileHeader = TreeSoft->InsertItem(L"Used Variable", TVI_ROOT);


	for(auto it = m_dataMap.begin(); it!= m_dataMap.end();it++ )
	{
		// Convert std::string to CStringA
		//CStringA cstrA(it->first.c_str());
		// Convert CStringA to CStringW
		//CStringW cstrW(cstrA);
		//TreeSoft->InsertItem(cstrW,fileHeader);
		TreeSoft->InsertItem(it->first,fileHeader);
	}

}
void CDemoProjectDlg::LoadCSVFile(CString& filePath, map<CString, vector<double>>& m_dataMap)
{
    ifstream file(filePath);
	//m_dataMap.clear();
	//DeleteListControl(m_List); //It causes MFC can't run error, check whether m_List contains anything.
    if (!file)
    {
        cout << "Failed to open the file: " << filePath << endl;
        return;
    }

    string line;
    getline(file, line); // Read the first line (header)

    istringstream headerStream(line);
    string headerItem;
	int i=0;

    while (getline(headerStream, headerItem, ','))
    {
		// Convert std::string to CStringA
		

		CStringA cstrA(headerItem.c_str());
		// Convert CStringA to CStringW
		CStringW cstrW(cstrA);
        
		//m_dataMap[headerItem]; // Add the header item as a key in the map
		m_dataMap[cstrW]; // Add the header item as a key in the map

		//m_List.InsertColumn(i, CA2T(headerItem.c_str()), LVCFMT_LEFT, 150);
		//CString theCStr;
		//std::string STDStr(CW2A(headerItem.GetString()));
		m_List.InsertColumn(i, cstrW, LVCFMT_LEFT, 150);

		i++;

    }

	int rowNo = 0, item;
	vector<vector<CString>>values;
    while (getline(file, line))
    {
        istringstream rowStream(line);
        string value;
        int columnIndex = 0;
		bool flag = false;
		vector<CString>vec;
		map<CString,vector<double>>::iterator it1 = m_dataMap.begin();


        while (getline(rowStream, value, ','))
        {
			 double numericValue = stod(value);
             it1->second.push_back(numericValue); 

			 // Convert std::string to CStringA
			 CStringA cstrA(value.c_str());
			 // Convert CStringA to CStringW
			 CStringW cstrW(cstrA);
			 vec.push_back(cstrW);

			/*if(flag==false)
			 {
				 flag=true;
				 item = m_List.InsertItem(columnIndex, CA2T(value.c_str()));
			 }
			 else
			 {
				 m_List.SetItemText(item,columnIndex, CA2T(value.c_str()));
			 }*/
			 it1++; 
			// columnIndex++;
        }
		values.push_back(vec);
    }

	//passMapFunc(m_dataMap); //Passing Map

	for(int row = values.size()-1; row>=0; row--)
	{
		bool flag= FALSE;
		int colNo=0;
		for(int col=0; col<(int)values[row].size(); col++)
		{
			CString val = values[row][col];
			if(flag==FALSE)
			{
				item = m_List.InsertItem(colNo, val);
				flag = TRUE;
			}
			else m_List.SetItemText(item, colNo, val);
			colNo++;
		}
	}

	/*int f=1;
	for(auto key : dataMap)
	{
		int sz = key.second.size();
		//TRACE("%d",f); 
		f++;
		for(int i=0; i<sz; i++)
		{
			TRACE("%d ",key.second[i]);
		}
		//TRACE("\n");
	}*/		
	buildTree(); 
	file.close();

}


void CDemoProjectDlg::OnBnClickedLoadFile()
{
	// TODO: Add your control notification handler code here
	//int val = 100;
	//TRACE("%d\n", val); //To print the value in output like a console
	m_List.DeleteAllItems();
	TreeSoft->DeleteAllItems();

	//CFileDialog::m_data



	CString filePath;
    CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("CSV Files (*.csv)|*.csv||"), this);
    if (dlg.DoModal() == IDOK)
    {
        filePath = dlg.GetPathName();
        LoadCSVFile(filePath, m_dataMap);

		CFirstDialog* obj = CFirstDialog::child;
		obj->CopyValues();

    }

}

void CDemoProjectDlg::OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if(m_pwndShow !=NULL)
	{
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}
	int nIndex = m_Tab.GetCurSel();
	switch(nIndex)
	{
		case 0:
			m_firstDialog.ShowWindow(SW_SHOW);
			m_secondDialog.ShowWindow(SW_HIDE);
			m_pwndShow = &m_firstDialog;
			break;
		case 1:
			m_secondDialog.ShowWindow(SW_SHOW);
			m_firstDialog.ShowWindow(SW_HIDE);
			m_pwndShow = &m_secondDialog;
			break;
		default:
			m_firstDialog.ShowWindow(SW_SHOW);
			m_secondDialog.ShowWindow(SW_HIDE);
			m_pwndShow = &m_firstDialog;
   }
	*pResult = 0;

}

void CDemoProjectDlg:: DeleteListControl(CListCtrl & listCtrl)
{
	int nColumncnt = listCtrl.GetHeaderCtrl()->GetItemCount();
	for(int i=0; i<nColumncnt; ++i)
	{
		listCtrl.DeleteColumn(0);
	}
	listCtrl.DeleteAllItems();
}

void CDemoProjectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

void CAboutDlg::OnExportdataContextMenu()
{
	// TODO: Add your command handler code here
}
