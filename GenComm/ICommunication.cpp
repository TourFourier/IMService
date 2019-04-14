#include "stdafx.h"
#include <atlstr.h>
#include <map>
//#include "constants.h"
#include "IMessage.h"
#include "IMessageFactory.h"
#include "ICommunication.h"


ICommunication::ICommunication(IMessageFactory* pMessageFactory)
{
	m_pMessageFactory = pMessageFactory;
}


ICommunication::~ICommunication()
{
}

void ICommunication::RegisterCallback(int eMessageType, void(*pfnCallback)(IMessage*))
{
	m_hashCallbacks.insert(std::pair<int, void*>(eMessageType, pfnCallback));
	//m_hashCallbacks[eMessageType] = pfnCallback;
}

void ICommunication::RemoveCallback(int eMessageType)
{
	m_hashCallbacks.erase(eMessageType);
}