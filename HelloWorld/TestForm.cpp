// TestForm.cpp : implementation file
//

#include "stdafx.h"
#include "HelloWorld.h"
#include "TestForm.h"


// CTestForm

IMPLEMENT_DYNCREATE(CTestForm, CFormView)

CTestForm::CTestForm()
	: CFormView(CTestForm::IDD)
{

}

CTestForm::~CTestForm()
{
}

void CTestForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestForm, CFormView)
END_MESSAGE_MAP()


// CTestForm diagnostics

#ifdef _DEBUG
void CTestForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTestForm message handlers
