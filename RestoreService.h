#if !defined(AFX_RESTORESERVICE_H__182D1C7A_9295_4D30_B856_7E0A9C64E1A8__INCLUDED_)
#define AFX_RESTORESERVICE_H__182D1C7A_9295_4D30_B856_7E0A9C64E1A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RestoreService.h : header file
//
#include "NativeDeletedService.h"
/////////////////////////////////////////////////////////////////////////////
// CRestoreService dialog

class CRestoreService : public CDialog
{
// Construction
public:
	BOOL OnInitDialog();
	CRestoreService(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRestoreService)
	enum { IDD = IDD_DIALOG2 };
	CListCtrl	m_list2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRestoreService)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRestoreService)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESTORESERVICE_H__182D1C7A_9295_4D30_B856_7E0A9C64E1A8__INCLUDED_)
