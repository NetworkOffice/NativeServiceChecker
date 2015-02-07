// NativeServiceCheckerDlg.h : header file
//

#if !defined(AFX_NATIVESERVICECHECKERDLG_H__907DF015_9A0B_480A_93ED_BA3DB4640168__INCLUDED_)
#define AFX_NATIVESERVICECHECKERDLG_H__907DF015_9A0B_480A_93ED_BA3DB4640168__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNativeServiceCheckerDlg dialog
class CNativeServiceCheckerDlg : public CDialog
{
// Construction
public:
	int ServiceIndex;
	CNativeServiceCheckerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNativeServiceCheckerDlg)
	enum { IDD = IDD_NATIVESERVICECHECKER_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNativeServiceCheckerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNativeServiceCheckerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnServiceRefresh();
	afx_msg void OnServiceStart();
	afx_msg void OnServiceStop();
	afx_msg void OnServiceDelete();
	afx_msg void OnServiceCreate();
	afx_msg void OnStartmodeAuto();
	afx_msg void OnStartmodeManual();
	afx_msg void OnStartmodeDisabled();
	virtual void OnOK();
	afx_msg void OnServiceRestore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NATIVESERVICECHECKERDLG_H__907DF015_9A0B_480A_93ED_BA3DB4640168__INCLUDED_)
