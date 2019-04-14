#pragma once
#include "IMessage.h"


class IMessageFactory
{
public:
	IMessageFactory();
	~IMessageFactory();

	virtual IMessage* CreateMessage(int type) = 0;
};

