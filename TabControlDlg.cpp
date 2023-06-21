
// TabControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TabControl.h"
#include "TabControlDlg.h"
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


// CTabControlDlg dialog



CTabControlDlg::CTabControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabControlDlg::IDD, pParent)
	, m_pwndShow(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTabControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CTabControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTabControlDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CTabControlDlg message handlers

BOOL CTabControlDlg::OnInitDialog()
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
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP6);
	static CImageList imgList;
	imgList.Create(16,16,ILC_COLOR24|ILC_MASK, 5,0);
	imgList.Add(&bmp, RGB(192,192,192));
	m_Tab.SetImageList(&imgList);
	CString strTmp = _T(""); //initializing an empty string
	for(int i=0; i<5; i++)
	{
		strTmp.Format(_T("%dth Tab"), i+1);
		m_Tab.InsertItem(i,strTmp,i);
	} //Tab
	CRect rect;
	m_Tab.GetClientRect(&rect);

	m_one.Create(IDD_One_Dialog, &m_Tab);
	m_one.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pwndShow = &m_one;

	m_second.Create(IDD_Second_Dialog, &m_Tab);
	m_second.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_SHOWWINDOW | SWP_NOZORDER);

	m_third.Create(IDD_Third_Dialog, &m_Tab);
	m_third.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_SHOWWINDOW | SWP_NOZORDER);

	m_fourth.Create(IDD_Fourth_Dialog, &m_Tab);
	m_fourth.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_SHOWWINDOW | SWP_NOZORDER);

	m_fifth.Create(IDD_Fifth_Dialog, &m_Tab);
	m_fifth.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_SHOWWINDOW | SWP_NOZORDER);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTabControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTabControlDlg::OnPaint()
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
HCURSOR CTabControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTabControlDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
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
			m_one.ShowWindow(SW_SHOW);
			m_second.ShowWindow(SW_HIDE);
			m_third.ShowWindow(SW_HIDE);
			m_fourth.ShowWindow(SW_HIDE);
			m_fifth.ShowWindow(SW_HIDE);
			m_pwndShow = &m_one;
			break;
		case 1:
			m_one.ShowWindow(SW_HIDE);
			m_second.ShowWindow(SW_SHOW);
			m_third.ShowWindow(SW_HIDE);
			m_fourth.ShowWindow(SW_HIDE);
			m_fifth.ShowWindow(SW_HIDE);
			m_pwndShow = &m_second;
			break;
		case 2:
			m_one.ShowWindow(SW_HIDE);
			m_second.ShowWindow(SW_HIDE);
			m_third.ShowWindow(SW_SHOW);
			m_fourth.ShowWindow(SW_HIDE);
			m_fifth.ShowWindow(SW_HIDE);			
			m_pwndShow = &m_third;
			break;
		case 3:
			m_one.ShowWindow(SW_HIDE);
			m_second.ShowWindow(SW_HIDE);
			m_third.ShowWindow(SW_HIDE);
			m_fourth.ShowWindow(SW_SHOW);
			m_fifth.ShowWindow(SW_HIDE);
			m_pwndShow = &m_fourth;
			break;
		case 4:
			m_one.ShowWindow(SW_HIDE);
			m_second.ShowWindow(SW_HIDE);
			m_third.ShowWindow(SW_HIDE);
			m_fourth.ShowWindow(SW_HIDE);
			m_fifth.ShowWindow(SW_SHOW);
			m_pwndShow = &m_fifth;
			break;


	}

	*pResult = 0;
}
