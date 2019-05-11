#pragma once
#include "IMessage.h"


class IMessageFactory
{
public:
	IMessageFactory();
	~IMessageFactory();

	virtual IMessage* CreateMessage(EMessageType type) = 0;
};

