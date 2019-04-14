#include "stdafx.h"
#include <rpc.h>
#include "structsAndConstants.h"
#include "../GenericComm/IMessage.h"

#include "MAcknowledgeMessage.h"


MAcknowledgeMessage::MAcknowledgeMessage()
{
}

MAcknowledgeMessage::MAcknowledgeMessage(int guidOriginalMessage)
{
	m_guidOriginalMessage = guidOriginalMessage;
}


MAcknowledgeMessage::~MAcknowledgeMessage()
{
}


int MAcknowledgeMessage::Size()
{
	int size;

	size += (2 * IMessage::SIZE_GUID);// GUId of this message and of text message that is being acknowledged
	size += IMessage::SIZE_INT;

	return size;
}

bool MAcknowledgeMessage::ToBuffer()
{
	char* cBuffer = new char[this->Size()];
	*(int*)cBuffer = m_guid;
	*(int*)(cBuffer + IMessage::SIZE_GUID) = (int)EMessageType::ACKNOWLEDGE;
	*(int*)(cBuffer + IMessage::SIZE_GUID + IMessage::SIZE_INT) = m_guidOriginalMessage;

	return cBuffer;
}

bool MAcknowledgeMessage::FromBuffer(char* pBuffer, int nLength)
{
	m_guid = *(int*)pBuffer;
	m_nMessageType = *(int*)(pBuffer + IMessage::SIZE_GUID);
	m_guidOriginalMessage = *(int*)(pBuffer + IMessage::SIZE_GUID + IMessage::SIZE_INT);
}
