// NativeService.h: interface for the CNativeService class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NATIVESERVICE_H__CBAA8B2A_6095_457C_98C7_87EEE33D36CC__INCLUDED_)
#define AFX_NATIVESERVICE_H__CBAA8B2A_6095_457C_98C7_87EEE33D36CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNativeService  
{
public:
	CNativeService();
	virtual ~CNativeService();
	char ServiceName[100];
	char ServiceDisplayName[100];
	char ServicePath[100];
};

#endif // !defined(AFX_NATIVESERVICE_H__CBAA8B2A_6095_457C_98C7_87EEE33D36CC__INCLUDED_)
