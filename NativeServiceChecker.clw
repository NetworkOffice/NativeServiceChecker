; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNativeServiceCheckerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NativeServiceChecker.h"

ClassCount=4
Class1=CNativeServiceCheckerApp
Class2=CNativeServiceCheckerDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_DIALOG1
Resource2=IDR_MAINFRAME
Resource3=IDD_NATIVESERVICECHECKER_DIALOG
Resource4=IDD_ABOUTBOX
Class4=CCreateServiceDlg
Resource5=CG_IDR_POPUP_NATIVE_SERVICE_CHECKER_DLG

[CLS:CNativeServiceCheckerApp]
Type=0
HeaderFile=NativeServiceChecker.h
ImplementationFile=NativeServiceChecker.cpp
Filter=N

[CLS:CNativeServiceCheckerDlg]
Type=0
HeaderFile=NativeServiceCheckerDlg.h
ImplementationFile=NativeServiceCheckerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_SERVICE_DELETE

[CLS:CAboutDlg]
Type=0
HeaderFile=NativeServiceCheckerDlg.h
ImplementationFile=NativeServiceCheckerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_NATIVESERVICECHECKER_DIALOG]
Type=1
Class=CNativeServiceCheckerDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,SysListView32,1350631424

[MNU:CG_IDR_POPUP_NATIVE_SERVICE_CHECKER_DLG]
Type=1
Class=CNativeServiceCheckerDlg
Command1=ID_SERVICE_REFRESH
Command2=ID_SERVICE_START
Command3=ID_SERVICE_STOP
Command4=ID_SERVICE_CREATE
Command5=ID_SERVICE_DELETE
Command6=ID_STARTMODE_AUTO
Command7=ID_STARTMODE_MANUAL
Command8=ID_STARTMODE_DISABLED
Command9=ID_SERVICE_ABOUT
CommandCount=9

[DLG:IDD_DIALOG1]
Type=1
Class=CCreateServiceDlg
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT1,edit,1350631552
Control7=IDC_EDIT2,edit,1350631552
Control8=IDC_EDIT3,edit,1350631552
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_RADIO1,button,1342373897
Control12=IDC_RADIO2,button,1342242825
Control13=IDC_BTN_SELECTFILE,button,1342242816

[CLS:CCreateServiceDlg]
Type=0
HeaderFile=CreateServiceDlg.h
ImplementationFile=CreateServiceDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

