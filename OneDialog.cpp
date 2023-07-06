// OneDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TabControl.h"
#include "OneDialog.h"
#include "afxdialogex.h"



// COneDialog dialog

IMPLEMENT_DYNAMIC(COneDialog, CDialogEx)

COneDialog::COneDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(COneDialog::IDD, pParent)
{

}

COneDialog::~COneDialog()
{
}

void COneDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COneDialog, CDialogEx)
END_MESSAGE_MAP()


// COneDialog message handlers
