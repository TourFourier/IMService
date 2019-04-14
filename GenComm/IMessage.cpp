#include "stdafx.h"
#include "constants.h"
#include "IMessage.h"
//#include <rpc.h>

static const int SIZE_GUID = sizeof(int);
static const int SIZE_INT = sizeof(int);

IMessage::IMessage()
{

}

IMessage::IMessage(int guid, int messageType)
{
	m_guid = guid;
	m_nMessageType = messageType;
}


IMessage::~IMessage()
{
}
