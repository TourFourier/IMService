#pragma once
#include <map>
#include <list>
#include "../IMComm/structsAndConstants.h"
#include "IMessageFactory.h"
#include "IMessage.h"


#ifdef DLL_IMPORT
#define DLL __declspec(dllimport)
#else
#define DLL __declspec(dllexport)
#endif


class CMefathimSocket : public CAsyncSocket
{
	// For server side usage only:
	static std::list<CMefathimSocket*> m_listSocketsToClient;
	std::string m_sSocketName;
protected:
	IMessageFactory* m_pMessageFactory;// This is to create a message of specific type upon receipt of buffer
	std::map<EMessageType, void*> m_hashCallbacks;// Used to perform task(callback) related to specific mssg type
	// In this implementation we are going to simply push the mssg object into a queue
	// TODO: Change value to vector/list of function pointers
public:
	CMefathimSocket(IMessageFactory* pMessageFactory, std::string sSocketName);
	~CMefathimSocket();


	void RegisterCallback(EMessageType eMessageType, void* pfnCallback);//(*pfnCallback)(IMessage*));
	void RemoveCallback(EMessageType eMessageType);
	void OnMessageReceived(char pBuffer[]);// Called in OnReceive()

	virtual void OnConnect(int nErrorCode);
	virtual void OnAccept(int nErrorCode)=0;
	virtual void OnReceive(int nErrorCode)=0;
	virtual void OnClose(int nErrorCode);
};