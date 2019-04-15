#include "stdafx.h"
//#include <rpc.h>
#include "../GenComm/constants.h"

#include "structsAndConstants.h"
#include "structsAndConstants.cpp"

#include "../GenComm/IMessage.h"
#include "MTextMessage.h"


MTextMessage::MTextMessage()
{
}

MTextMessage::MTextMessage(int guid,const TTextMessage& message) : IMessage( guid , (int)EMessageType::TEXT_MESSAGE)
{
	m_msgText.m_sText = message.m_sText;
	m_msgText.m_userDestination = message.m_userDestination;
	m_msgText.m_groupDestination = message.m_groupDestination;
}


MTextMessage::~MTextMessage()
{
}


int MTextMessage::Size()
{
	int size=0;

	size += SIZE_GUID;// 4; simple implementation uses int for GUID
	size += SIZE_INT;// 4
	size += SIZE_INT;// 4; this is the int that represents the size of the message
	size += sizeof(m_msgText);// Variant

	return size;
}

bool MTextMessage::ToBuffer(char* cBuffer)
{
	
	*(int*)cBuffer = m_guid;
	*(int*)(cBuffer + ::SIZE_GUID) = (int)EMessageType::TEXT_MESSAGE;
	*(int*)(cBuffer + ::SIZE_GUID + ::SIZE_INT) = this->Size();
	cBuffer = cBuffer + ::SIZE_GUID + ::SIZE_INT + ::SIZE_INT;
	this->m_msgText.ToBuffer(cBuffer);
	//*(TTextMessage*)(cBuffer + IMessage::SIZE_GUID + IMessage::SIZE_INT + IMessage::SIZE_INT) = m_msgText;

	return 0;
}

 bool MTextMessage::FromBuffer(char* pBuffer)
{
	//char* sync = *(char*)pBuffer;
	/*int totalSize;
	int sizeWithoutMessage;
	int sizeOfMessage;


	m_guid = *(int*)pBuffer;
	m_nMessageType = *(int*)(pBuffer + IMessage::SIZE_GUID);
	totalSize = *(int*)(pBuffer + IMessage::SIZE_GUID + IMessage::SIZE_INT);
	sizeWithoutMessage = (IMessage::SIZE_GUID + IMessage::SIZE_INT + IMessage::SIZE_INT);
	sizeOfMessage = totalSize - sizeWithoutMessage;

	for (int i = sizeWithoutMessage; i < sizeOfMessage;i++)
	{
		pBuffer + i;
	}

	m_msgText = *(TTextMessage*)(pBuffer + sizeWithoutMessage);
	// Note: the size of the text struct will differ depends on the text message and recipients...
	//...therefor must adjust to read that much of buffer or have a sync word/#       
	*/
	return 0;
}
