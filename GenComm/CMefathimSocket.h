#pragma once

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
protected:
	std::map<int, void*> m_hashCallbacks; // TODO: Change value to vector of function pointers
	IMessageFactory* m_pMessageFactory;
public:
	CMefathimSocket(IMessageFactory* pMessageFactory, CString sSocketName);
	~CMefathimSocket();

	virtual void OnConnect(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	void RegisterCallback(int eMessageType, void(*pfnCallback)(IMessage*));

	void RemoveCallback(int eMessageType);
};