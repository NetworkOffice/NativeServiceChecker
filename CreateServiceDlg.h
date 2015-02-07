#if !defined(AFX_CREATESERVICEDLG_H__BEEC9852_CFF2_45FA_981B_370094E84DC6__INCLUDED_)
#define AFX_CREATESERVICEDLG_H__BEEC9852_CFF2_45FA_981B_370094E84DC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreateServiceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateServiceDlg dialog

class CCreateServiceDlg : public CDialog
{
// Construction
public:
	BOOL EnableProvi();
	CCreateServiceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateServiceDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_service_name;
	CString	m_service_des;
	CString	m_service_path;
	int		m_service_startmode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateServiceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreateServiceDlg)
	afx_msg void OnBtnSelectfile();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATESERVICEDLG_H__BEEC9852_CFF2_45FA_981B_370094E84DC6__INCLUDED_)
