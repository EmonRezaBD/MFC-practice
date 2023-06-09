#pragma once



// CTestForm form view

class CTestForm : public CFormView
{
	DECLARE_DYNCREATE(CTestForm)

protected:
	CTestForm();           // protected constructor used by dynamic creation
	virtual ~CTestForm();

public:
	enum { IDD = IDD_TESTFORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};


