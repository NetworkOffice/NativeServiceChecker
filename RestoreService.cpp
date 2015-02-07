// RestoreService.cpp : implementation file
//

#include "stdafx.h"
#include "NativeServiceChecker.h"
#include "NativeServiceCheckerDlg.h"
#include "RestoreService.h"
#include "NativeService.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRestoreService dialog


CRestoreService::CRestoreService(CWnd* pParent /*=NULL*/)
	: CDialog(CRestoreService::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRestoreService)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRestoreService::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRestoreService)
	DDX_Control(pDX, IDC_LIST2, m_list2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRestoreService, CDialog)
	//{{AFX_MSG_MAP(CRestoreService)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRestoreService message handlers



BOOL CRestoreService::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	DWORD dwStyle=::GetWindowLong(m_list2.m_hWnd,GWL_STYLE);
	dwStyle &= ~(LVS_TYPEMASK);
	dwStyle &= ~(LVS_EDITLABELS);
	SetWindowLong(m_list2.m_hWnd,GWL_STYLE,dwStyle | LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS);
	DWORD styles=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	ListView_SetExtendedListViewStyleEx(m_list2.m_hWnd,styles,styles);
	m_list2.InsertColumn(0,"服务名称",LVCFMT_LEFT,300,-1);
	m_list2.InsertColumn(1,"显示名称",LVCFMT_LEFT,400,-1);
//	m_list2.InsertColumn(2,"启动状态",LVCFMT_LEFT,100,-1);
	m_list2.InsertColumn(3,"启动类别",LVCFMT_LEFT,100,-1);
	m_list2.InsertColumn(4,"程序路径",LVCFMT_LEFT,800,-1);
	CNativeService DeletedServiceInfo2[100];
	for(int i=0;i<100;i++)
	{
		int nitem=m_list2.InsertItem(0,DeletedServiceInfo2[i].ServiceName,0);
		m_list2.SetItemText(nitem,1,DeletedServiceInfo2[i].ServiceDisplayName);
		m_list2.SetItemText(nitem,4,DeletedServiceInfo2[i].ServicePath);
	}

	return TRUE;
}

void CRestoreService::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}
