
// ListControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListControl.h"
#include "ListControlDlg.h"
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


// CListControlDlg dialog



CListControlDlg::CListControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CListControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}

BEGIN_MESSAGE_MAP(CListControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST1, &CListControlDlg::OnLvnEndlabeleditList1)
	ON_BN_CLICKED(IDC_BUTTON_Delete, &CListControlDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CListControlDlg message handlers

BOOL CListControlDlg::OnInitDialog()
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
	//DWORD dwExStyle = m_List.GetExtendedStyle();
	//m_List.SetExtendedStyle(dwExStyle | LVS_EX_CHECKBOXES | LVS_EX_BORDERSELECT);
	static CImageList imgList;
	imgList.Create(16,16,ILC_COLOR32,4,0);
	//imgList.Add(AfxGetApp()->LoadIconW(IDR_MAINFRAME));
	CString strItem = _T("");
	/*for(int i=0; i<4; i++) //Adding icons to list control
	{
	    //imgList.Add(AfxGetApp()->LoadIconW(IDI_ICON1+i));
		//strItem.Format(_T("%d th Item"), i);
		//m_List.InsertItem(i,strItem,i);

	}*/
	/*m_List.SetImageList(&imgList, LVSIL_SMALL);
	LVITEM item;
	::ZeroMemory(&item, sizeof(item));
	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	item.pszText = _T("Test Item");	
	item.iImage = 1;
 
	item.state = LVIS_SELECTED | LVIS_FOCUSED; */

	//m_List.InsertItem(&item);

	m_List.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(1, _T("Description"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, _T("Weed"), LVCFMT_LEFT, 100);

	//m_List.InsertColumn(0, _T("Test"), LVCFMT_LEFT, 400);


	m_List.ModifyStyle(LVS_TYPEMASK,LVS_REPORT);

	m_List.SetItemText(0,0,_T("New Name"));
	m_List.SetItemText(0,1,_T("Test String!"));

	//m_List.SetItemText(0,2,_T("Test String!...."));



	//m_List.InsertItem(0, _T("1th Test item"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListControlDlg::OnPaint()
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
HCURSOR CListControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CListControlDlg::OnLvnEndlabeleditList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	//@TN
		*pResult = 0;
	// TODO: Add your control notification handler code here
	
	CString strText = _T("");
	CEdit* pEdit = m_List.GetEditControl();
	pEdit->GetWindowTextW(strText);
	m_List.SetItemText(pDispInfo->item.iItem,0,strText);

	*pResult = 0;
}

void CListControlDlg::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	int nCount = m_List.GetItemCount();
	for(int i=nCount; i>=0; i-- )
	{
		if(m_List.GetCheck(i)) //if Checked then delete 
		{
			m_List.DeleteItem(i);
		}
	}
}
