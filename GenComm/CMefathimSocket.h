#pragma once
#include <afxsock.h>
#include <list>

#ifdef DLL_IMPORT
#define DLL __declspec(dllimport)
#else
#define DLL __declspec(dllexport)
#endif

class CMefathimSocket : public CAsyncSocket
{
	// For server side usage only:
	CString m_sSocketName;
	std::list<CMefathimSocket*> m_listSocketsToClient;
public:
	CMefathimSocket(CString sSocketName);
	~CMefathimSocket();

	virtual void OnConnect(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};