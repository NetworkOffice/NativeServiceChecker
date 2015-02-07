// CreateServiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NativeServiceChecker.h"
#include "CreateServiceDlg.h"
#include "NativeServiceCheckerDlg.h"
#include <winsvc.h>
#include <windows.h>
#include <Afxdlgs.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateServiceDlg dialog


CCreateServiceDlg::CCreateServiceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateServiceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateServiceDlg)
	m_service_name = _T("");
	m_service_des = _T("");
	m_service_path = _T("");
	m_service_startmode = -1;
	//}}AFX_DATA_INIT
}


void CCreateServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateServiceDlg)
	DDX_Text(pDX, IDC_EDIT1, m_service_name);
	DDX_Text(pDX, IDC_EDIT2, m_service_des);
	DDX_Text(pDX, IDC_EDIT3, m_service_path);
	DDX_Radio(pDX, IDC_RADIO1, m_service_startmode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateServiceDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateServiceDlg)
	ON_BN_CLICKED(IDC_BTN_SELECTFILE, OnBtnSelectfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateServiceDlg message handlers

void CCreateServiceDlg::OnBtnSelectfile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog * fDlg=new CFileDialog(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL,NULL);
	fDlg->DoModal();
	if(IDOK==fDlg->DoModal())
	{
		CString FilePath;
		FilePath=fDlg->GetPathName();
		SetDlgItemText(IDC_EDIT3,(LPCTSTR)FilePath);
	}
}
BOOL CCreateServiceDlg::EnableProvi()
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
void CCreateServiceDlg::OnOK() 
{
	// TODO: Add extra validation here
	SC_HANDLE scm=NULL;
	SC_HANDLE service=NULL;
	if((scm=OpenSCManager(NULL,NULL,SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE))==NULL)
	{
		MessageBox("OpenSCManager Error!\n");
	}
	DWORD dwStartType;
	int nSelectMode=GetCheckedRadioButton(IDC_RADIO1,IDC_RADIO2);
	switch(nSelectMode)
	{
	case IDC_RADIO1:
		//MessageBox("自动");
		dwStartType=SERVICE_AUTO_START;
		break;
	case IDC_RADIO2:
		//MessageBox("手动");
		dwStartType=SERVICE_DEMAND_START;
		break;
	}

	LPCTSTR name,des,path;
	char ch1[50],ch2[100],ch3[100];

	GetDlgItemText(IDC_EDIT1,ch1,100);
	GetDlgItemText(IDC_EDIT2,ch2,100);
	GetDlgItemText(IDC_EDIT3,ch3,100);

	name=(LPCTSTR)ch1;
	des=(LPCTSTR)ch2;
	path=(LPCTSTR)ch3;
	service=CreateService(scm,
		                 name,
						 des,
						 SERVICE_QUERY_STATUS,
						 SERVICE_WIN32_OWN_PROCESS,
						 dwStartType,
						 SERVICE_ERROR_NORMAL,
						 path,
						 NULL,
						 NULL,
						 0,
						 NULL,
						 NULL);
	UpdateData(true);
	if(service==NULL)
	{
		MessageBox("创建服务失败!\n");
		//CNativeServiceCheckerDlg::OnServiceRefresh();
	}
	else
	{
		MessageBox("创建服务成功!\n");
		//CNativeServiceCheckerDlg::OnServiceRefresh();
	}
	//CDialog::OnOK();
}
