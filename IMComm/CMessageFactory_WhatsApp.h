#pragma once
#include "../GenComm/IMessageFactory.h"

class CMessageFactory_WhatsApp :
	public IMessageFactory
{
public:
	CMessageFactory_WhatsApp();
   ~CMessageFactory_WhatsApp();

public:
	IMessage* CreateMessage(EMessageType type);
};

