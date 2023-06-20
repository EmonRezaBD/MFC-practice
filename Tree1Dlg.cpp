
// Tree1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tree1.h"
#include "Tree1Dlg.h"
#include "afxdialogex.h"

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


// CTree1Dlg dialog



CTree1Dlg::CTree1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTree1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	TreeSoft = new CTreeCtrl;
}

void CTree1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTree1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTree1Dlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CTree1Dlg message handlers

BOOL CTree1Dlg::OnInitDialog()
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
	TreeSoft->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP |
		             TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
			 TVS_SINGLEEXPAND | TVS_SHOWSELALWAYS |  
			 TVS_TRACKSELECT,
		             CRect(10, 10, 200, 240), this, 0x1221);
	//Converting to multibyte or use L, otherwise it shows error
	/*TreeSoft->InsertItem("Office Production");
	TreeSoft->InsertItem("Company Management");
	TreeSoft->InsertItem("Software Development");
	TreeSoft->InsertItem("Human Interaction");*/
	HTREEITEM hTree, hCompany, h1;

	hTree = TreeSoft->InsertItem("Software Production", TVI_ROOT);

	hCompany = TreeSoft->InsertItem("Microsoft", hTree); //1 Tree
	TreeSoft->InsertItem("Office",hCompany);
	TreeSoft->InsertItem("Visual Studio", hCompany);
	TreeSoft->InsertItem("Servers", hCompany, TVI_FIRST); //TVI_FIRST and TVI_LAST argument for the first and last element of the tree node
	//h1 = TreeSoft->InsertItem("Reza", hCompany); //More child node
    //TreeSoft->InsertItem("Dhaka", h1);

	
	hCompany = TreeSoft->InsertItem("Jasc", hTree); //2 Tree
	TreeSoft->InsertItem("Paint Shop Pro", hCompany);
	TreeSoft->InsertItem("Animation Shop", hCompany);
	
	hCompany = TreeSoft->InsertItem("Lotus", hTree);
	TreeSoft->InsertItem("Notes", hCompany);
	TreeSoft->InsertItem("Smart Office", hCompany);

	hCompany = TreeSoft->InsertItem("Macromedia", hTree);
	TreeSoft->InsertItem("Flash", hCompany);



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTree1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTree1Dlg::OnPaint()
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

/*CTree1Dlg::~CTree1Dlg() //destructor code
{
	delete TreeSoft;
}*/

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTree1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTree1Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	//@TN
		*pResult = 0;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
