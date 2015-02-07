// NativeServiceCheckerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NativeServiceChecker.h"
#include "NativeServiceCheckerDlg.h"
#include "resource.h"
#include <winsvc.h>
#include "CreateServiceDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNativeServiceCheckerDlg dialog

CNativeServiceCheckerDlg::CNativeServiceCheckerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNativeServiceCheckerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNativeServiceCheckerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNativeServiceCheckerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNativeServiceCheckerDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNativeServiceCheckerDlg, CDialog)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CNativeServiceCheckerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_SERVICE_REFRESH, OnServiceRefresh)
	ON_COMMAND(ID_SERVICE_START, OnServiceStart)
	ON_COMMAND(ID_SERVICE_STOP, OnServiceStop)
	ON_COMMAND(ID_SERVICE_DELETE, OnServiceDelete)
	ON_COMMAND(ID_SERVICE_CREATE, OnServiceCreate)
	ON_COMMAND(ID_STARTMODE_AUTO, OnStartmodeAuto)
	ON_COMMAND(ID_STARTMODE_MANUAL, OnStartmodeManual)
	ON_COMMAND(ID_STARTMODE_DISABLED, OnStartmodeDisabled)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNativeServiceCheckerDlg message handlers

BOOL CNativeServiceCheckerDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	DWORD dwStyle=::GetWindowLong(m_list.m_hWnd,GWL_STYLE);
	dwStyle &= ~(LVS_TYPEMASK);
	dwStyle &= ~(LVS_EDITLABELS);
	SetWindowLong(m_list.m_hWnd,GWL_STYLE,dwStyle | LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS);
	DWORD styles=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	ListView_SetExtendedListViewStyleEx(m_list.m_hWnd,styles,styles);
	m_list.InsertColumn(0,"服务名称",LVCFMT_LEFT,300,-1);
	m_list.InsertColumn(1,"显示名称",LVCFMT_LEFT,400,-1);
	m_list.InsertColumn(2,"启动状态",LVCFMT_LEFT,100,-1);
	m_list.InsertColumn(3,"启动类别",LVCFMT_LEFT,100,-1);
	m_list.InsertColumn(4,"程序路径",LVCFMT_LEFT,800,-1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNativeServiceCheckerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNativeServiceCheckerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNativeServiceCheckerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNativeServiceCheckerDlg::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_NATIVE_SERVICE_CHECKER_DLG));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CNativeServiceCheckerDlg::OnServiceRefresh() 
{
	// TODO: Add your command handler code here
		m_list.DeleteAllItems();
//	UpdateData(false);
	LPQUERY_SERVICE_CONFIG ServicesInfo=NULL;
	LPENUM_SERVICE_STATUS lpServices=NULL;
	DWORD nSize=0;
	DWORD n;
	DWORD nResumeHandle=0;
	DWORD dwServiceType=SERVICE_WIN32;
	SC_HANDLE schSCManager=NULL;
	BOOL flag=FALSE;
	if((schSCManager=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS))==NULL)
	{
		AfxMessageBox("OpenSCManager Error!\n");
	}
	lpServices=(LPENUM_SERVICE_STATUS)LocalAlloc(LPTR,64*1024);
	EnumServicesStatus(schSCManager,dwServiceType,SERVICE_STATE_ALL,(LPENUM_SERVICE_STATUS)lpServices,64*1024,&nSize,&n,&nResumeHandle);
	//int n=157;
	for(unsigned int i=0;i < n;i++)
	{
		SC_HANDLE service=NULL;
		DWORD nResumeHandle=0;
		service=OpenService(schSCManager,lpServices[i].lpServiceName,SERVICE_ALL_ACCESS);
		ServicesInfo=(LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR,4*1024);
		QueryServiceConfig(service,ServicesInfo,4*1024,&nResumeHandle);
		int nitem=m_list.InsertItem(0,lpServices[i].lpServiceName,0);
		m_list.SetItemText(nitem,1,lpServices[i].lpDisplayName);
		if(lpServices[i].ServiceStatus.dwCurrentState!=SERVICE_STOPPED)
		{
			m_list.SetItemText(nitem,2,"已启动");
		}else{
			m_list.SetItemText(nitem,2,"停止");
		}
		if(2==ServicesInfo->dwStartType)
		{
			m_list.SetItemText(nitem,3,"自动");
		}
		if(3==ServicesInfo->dwStartType)
		{
			m_list.SetItemText(nitem,3,"手动");
		}
		if(4==ServicesInfo->dwStartType)
		{
			m_list.SetItemText(nitem,3,"禁止");
		}
		m_list.SetItemText(nitem,4,ServicesInfo->lpBinaryPathName);
		UpdateData(false);
	}
}
BOOL EnableProvi()
{
	HANDLE hToken;
	if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken))
	{
		TOKEN_PRIVILEGES tkp;
		LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&tkp.Privileges[0].Luid);
		tkp.PrivilegeCount=1;
		tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken,FALSE,&tkp,sizeof(tkp),NULL,NULL);
		return ((GetLastError()==ERROR_SUCCESS));
	}
}
void CNativeServiceCheckerDlg::OnServiceStart() 
{
	// TODO: Add your command handler code here
	EnableProvi();
	char ServerName[100]=" ";
	int x=m_list.GetSelectionMark();
	m_list.GetItemText(x,0,ServerName,100);
	SC_HANDLE scm;
	SC_HANDLE service;
	SERVICE_STATUS status;
	if((scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE))==NULL)
	{
		MessageBox("OpenSCManager Error!\n");
	}
	service=OpenService(scm,ServerName,SERVICE_ALL_ACCESS);
	if(!service)
	{
		MessageBox("OpenService Error!\n");
	}
	BOOL isSuccess=QueryServiceStatus(service,&status);
	if(!isSuccess)
	{
		MessageBox("QueryServiceStatus Error!\n");
	}
	if(status.dwCurrentState==SERVICE_STOPPED)
	{
		isSuccess=StartService(service,0,NULL);
		if(!isSuccess)
		{
			MessageBox("启动服务失败!\n");
			OnServiceRefresh();
		}
		else
		{
			MessageBox("启动服务成功!\n");
			OnServiceRefresh();
		}
	}
}

void CNativeServiceCheckerDlg::OnServiceStop() 
{
	// TODO: Add your command handler code here
	EnableProvi();
	char ServerName[100]=" ";
	int x=m_list.GetSelectionMark();
	m_list.GetItemText(x,0,ServerName,100);
	SC_HANDLE scm;
	SC_HANDLE service;
	SERVICE_STATUS status;
	if((scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE))==NULL)
	{
		MessageBox("OpenSCManager Error!\n");
	}
	service=OpenService(scm,ServerName,SERVICE_ALL_ACCESS);
	if(!service)
	{
		MessageBox("OpenService Error!\n");
	}
	BOOL isSuccess=QueryServiceStatus(service,&status);
	if(!isSuccess)
	{
		MessageBox("QueryServiceStatus Error!\n");
	}
	else
	{
		if(status.dwCurrentState!=SERVICE_STOPPED)
		{
			isSuccess=ControlService(service,SERVICE_CONTROL_STOP,&status);
			if(!isSuccess)
			{
				MessageBox("停止服务失败!\n");
				OnServiceRefresh();
			}
		}
		else
		{
			MessageBox("停止服务成功!\n");
			OnServiceRefresh();
		}
	}
}

void CNativeServiceCheckerDlg::OnServiceDelete() 
{
	// TODO: Add your command handler code here
	EnableProvi();
	char ServerName[100]=" ";
	int x=m_list.GetSelectionMark();
	m_list.GetItemText(x,0,ServerName,100);
	SC_HANDLE scm;
	SC_HANDLE service;
	if((scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE))==NULL)
	{
		MessageBox("OpenSCManager Error!\n");
	}
	service=OpenService(scm,ServerName,SERVICE_ALL_ACCESS);
	if(!service)
	{
		MessageBox("OpenService Error!\n");
	}
	else
	{
		if(1==MessageBox("你确定要删除这个服务吗？服务删除后将不可恢复!","警告",MB_OKCANCEL | MB_ICONQUESTION))
		{
			BOOL isSuccess=DeleteService(service);
			if(!isSuccess)
			{
				MessageBox("删除服务失败!");
				OnServiceRefresh();
			}
			else
			{
				MessageBox("删除服务成功!");
				OnServiceRefresh();
			}
		}
	}
}

void CNativeServiceCheckerDlg::OnServiceCreate() 
{
	// TODO: Add your command handler code here
	CCreateServiceDlg * dlg=new CCreateServiceDlg;
	dlg->Create(IDD_DIALOG1,NULL);
	dlg->ShowWindow(SW_SHOW);
}

void CNativeServiceCheckerDlg::OnStartmodeAuto() 
{
	// TODO: Add your command handler code here
		EnableProvi();
	char ServerName[100]=" ";
	int x=m_list.GetSelectionMark();
	m_list.GetItemText(x,0,ServerName,100);
	SC_HANDLE scm;
	SC_HANDLE service;
	SC_LOCK scLock;
	if((scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE))==NULL)
	{
		MessageBox("OpenSCManager Error!\n");
	}
	service=OpenService(scm,ServerName,SERVICE_ALL_ACCESS);
	if(!service)
	{
		MessageBox("OpenService Error!\n");
	}
	scLock=LockServiceDatabase(scm);
	if(scLock==NULL)
	{
		if(GetLastError()!=ERROR_SERVICE_DATABASE_LOCKED)
		{
			//MessageBox("LockServiceDatabase Error!");
		}
	}
	BOOL isSuccess=ChangeServiceConfig(service,SERVICE_NO_CHANGE,SERVICE_AUTO_START,SERVICE_NO_CHANGE,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
	if(!isSuccess)
	{
		MessageBox("更改服务启动方式失败!\n");
		OnServiceRefresh();
	}
	else
	{
		MessageBox("更改服务启动方式成功!\n");
		OnServiceRefresh();
	}
	UnlockServiceDatabase(scLock);

}

void CNativeServiceCheckerDlg::OnStartmodeManual() 
{
	// TODO: Add your command handler code here
	EnableProvi();
	char ServerName[100]=" ";
	int x=m_list.GetSelectionMark();
	m_list.GetItemText(x,0,ServerName,100);
	SC_HANDLE scm;
	SC_HANDLE service;
	SC_LOCK scLock;
	if((scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE))==NULL)
	{
		MessageBox("OpenSCManager Error!\n");
	}
	service=OpenService(scm,ServerName,SERVICE_ALL_ACCESS);
	if(!service)
	{
		MessageBox("OpenService Error!\n");
	}
	scLock=LockServiceDatabase(scm);
	if(scLock==NULL)
	{
		if(GetLastError()!=ERROR_SERVICE_DATABASE_LOCKED)
		{
			//MessageBox("LockServiceDatabase Error!");
		}
	}
	BOOL isSuccess=ChangeServiceConfig(service,SERVICE_NO_CHANGE,SERVICE_DEMAND_START,SERVICE_NO_CHANGE,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
	if(!isSuccess)
	{
		MessageBox("更改服务启动方式失败!\n");
		OnServiceRefresh();
	}
	else
	{
		MessageBox("更改服务启动方式成功!\n");
		OnServiceRefresh();
	}
	UnlockServiceDatabase(scLock);
}

void CNativeServiceCheckerDlg::OnStartmodeDisabled() 
{
	// TODO: Add your command handler code here
	EnableProvi();
	char ServerName[100]=" ";
	int x=m_list.GetSelectionMark();
	m_list.GetItemText(x,0,ServerName,100);
	SC_HANDLE scm;
	SC_HANDLE service;
	SC_LOCK scLock;
	if((scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE))==NULL)
	{
		MessageBox("OpenSCManager Error!\n");
	}
	service=OpenService(scm,ServerName,SERVICE_ALL_ACCESS);
	if(!service)
	{
		MessageBox("OpenService Error!\n");
	}
	scLock=LockServiceDatabase(scm);
	if(scLock==NULL)
	{
		if(GetLastError()!=ERROR_SERVICE_DATABASE_LOCKED)
		{
			//MessageBox("LockServiceDatabase Error!");
		}
	}
	BOOL isSuccess=ChangeServiceConfig(service,SERVICE_NO_CHANGE,SERVICE_DISABLED,SERVICE_NO_CHANGE,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
	if(!isSuccess)
	{
		MessageBox("更改服务启动方式失败!\n");
		OnServiceRefresh();
	}
	else
	{
		MessageBox("更改服务启动方式成功!\n");
		OnServiceRefresh();
	}
	UnlockServiceDatabase(scLock);
}

void CNativeServiceCheckerDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
	m_list.DeleteAllItems();
	UpdateData(false);
	LPQUERY_SERVICE_CONFIG ServicesInfo=NULL;
	LPENUM_SERVICE_STATUS lpServices=NULL;
	DWORD nSize=0;
	DWORD n;
	DWORD nResumeHandle=0;
	DWORD dwServiceType=SERVICE_WIN32;
	SC_HANDLE schSCManager=NULL;
	BOOL flag=FALSE;
	if((schSCManager=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS))==NULL)
	{
		AfxMessageBox("OpenSCManager Error!\n");
	}
	lpServices=(LPENUM_SERVICE_STATUS)LocalAlloc(LPTR,64*1024);
	EnumServicesStatus(schSCManager,dwServiceType,SERVICE_STATE_ALL,(LPENUM_SERVICE_STATUS)lpServices,64*1024,&nSize,&n,&nResumeHandle);
	for(unsigned int i=0;i < n;i++)
	{
		SC_HANDLE service=NULL;
		DWORD nResumeHandle=0;
		service=OpenService(schSCManager,lpServices[i].lpServiceName,SERVICE_ALL_ACCESS);
		ServicesInfo=(LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR,4*1024);
		QueryServiceConfig(service,ServicesInfo,4*1024,&nResumeHandle);
		int nitem=m_list.InsertItem(0,lpServices[i].lpServiceName,0);
		m_list.SetItemText(nitem,1,lpServices[i].lpDisplayName);
		if(lpServices[i].ServiceStatus.dwCurrentState!=SERVICE_STOPPED)
		{
			m_list.SetItemText(nitem,2,"已启动");
		}else{
			m_list.SetItemText(nitem,2,"停止");
		}
		if(2==ServicesInfo->dwStartType)
		{
			m_list.SetItemText(nitem,3,"自动");
		}
		if(3==ServicesInfo->dwStartType)
		{
			m_list.SetItemText(nitem,3,"手动");
		}
		if(4==ServicesInfo->dwStartType)
		{
			m_list.SetItemText(nitem,3,"禁止");
		}
		m_list.SetItemText(nitem,4,ServicesInfo->lpBinaryPathName);
		UpdateData(false);
	}
}
