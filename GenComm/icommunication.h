#pragma once
#include <map>
#include "IMessageFactory.h"


class ICommunication
{
protected:
	std::map<int, void*> m_hashCallbacks; // TODO: Change value to vector of function pointers
	IMessageFactory* m_pMessageFactory;
public:
	//virtual bool Connect(CString sConnectionDetails) = 0;
	//virtual bool Disconnect() = 0;
	//virtual bool SendMessage(IMessage* pMessage) = 0;

	void RegisterCallback(int eMessageType, void(*pfnCallback)(IMessage*));

	void RemoveCallback(int eMessageType);


	//Constructor
	ICommunication(IMessageFactory* pMessageFactory);

	~ICommunication();
};


