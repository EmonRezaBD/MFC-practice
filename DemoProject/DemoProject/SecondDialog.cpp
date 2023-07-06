// SecondDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DemoProject.h"
#include "SecondDialog.h"
#include "afxdialogex.h"


// CSecondDialog dialog

IMPLEMENT_DYNAMIC(CSecondDialog, CDialogEx)

CSecondDialog::CSecondDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSecondDialog::IDD, pParent)
{

}

CSecondDialog::~CSecondDialog()
{
}

void CSecondDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSecondDialog, CDialogEx)
END_MESSAGE_MAP()


// CSecondDialog message handlers
