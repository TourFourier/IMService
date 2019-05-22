#include "stdafx.h"
//#include <rpc.h>
#include <string>
#include "../GenComm/constants.h"

#include "structsAndConstants.h"
#include "structsAndConstants.cpp"

#include "../GenComm/IMessage.h"
#include "MTextMessage.h"


MTextMessage::MTextMessage()
{
}

MTextMessage::MTextMessage(int guid,const TTextMessage& message) : IMessage( guid , TEXT_MESSAGE)
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
/*char a[sizeof(int)];
*((int *)a) = 0x01010101;
printf("%d\n", *((int *)a));*/
bool MTextMessage::ToBuffer(char cBuffer[])
{
	// 1) Fill  buffer with basic fields of the MTextMessage object
	// Casting the buffer pointer to what it is pointing to ie. int, int, int
	*((int*)cBuffer) = m_guid;
	int ea = *((int*)cBuffer);

	*((int*)(cBuffer + SIZE_GUID)) = static_cast<int>(TEXT_MESSAGE);
	
	// Moving buffer pointer over by the amount of bytes that were allocated values in the buffer
	cBuffer = (cBuffer + SIZE_GUID + SIZE_INT);
	// 2) Fill rest of buffer with TTextMessage by calling its ToBuffer() method
	this->m_msgText.ToBuffer(cBuffer);
	//*(TTextMessage*)(cBuffer + IMessage::SIZE_GUID + IMessage::SIZE_INT + IMessage::SIZE_INT) = m_msgText;

	return 0;
}

 bool MTextMessage::FromBuffer(char* pBuffer)
{
	//char* sync = *(char*)pBuffer;
	//int totalSize;
	//TTextMessage temp;

	this->m_guid = *((int*)pBuffer);
	this->m_nMessageType = *((int*)(pBuffer + SIZE_GUID));
	//totalSize = *(int*)(pBuffer + SIZE_GUID + SIZE_INT);
	//sizeWithoutMessage = (SIZE_GUID + SIZE_INT + SIZE_INT);
	//sizeOfMessage = totalSize - sizeWithoutMessage;
	//temp.FromBuffer((pBuffer + SIZE_INT + SIZE_GUID));
	pBuffer = (pBuffer + SIZE_INT + SIZE_GUID);

	this->m_msgText.FromBuffer(pBuffer);
	// Note: the size of the text struct will differ depends on the text message and recipients...
	//...therefor must adjust to read that much of buffer or have a sync word/#       
	
	return 0;
}
