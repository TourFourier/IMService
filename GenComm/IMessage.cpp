#include "stdafx.h"
#include "constants.h"
#include "IMessage.h"
//#include <rpc.h>


IMessage::IMessage(int guid, EMessageType messageType):
m_guid(guid),
m_nMessageType(static_cast<int>(messageType))
{}


IMessage::~IMessage()
{
}
