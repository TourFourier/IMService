#include "stdafx.h"
#include <rpc.h> 
#include "structsAndConstants.h"
#include "../GenericComm/IMessage.h"

#include "MGroupCreateUpdate.h"


MGroupCreateUpdate::MGroupCreateUpdate()
{
}

MGroupCreateUpdate::MGroupCreateUpdate(TGroup group)
{
	m_group = group;
}


MGroupCreateUpdate::~MGroupCreateUpdate()
{
}


int MGroupCreateUpdate::Size()
{
	int size;

	size += IMessage::SIZE_GUID;// 16
	size += IMessage::SIZE_INT;// 4
	size += sizeof(m_group);// Variant

	return size;
}

bool MGroupCreateUpdate::ToBuffer()
{
	char* cBuffer = new char[this->Size()];
	*(GUID*)cBuffer = m_guid;
	*(int*)(cBuffer + IMessage::SIZE_GUID) = (int)EMessageType::CREATE_UPDATE_GROUP;
	*(TGroup*)(cBuffer + IMessage::SIZE_GUID + IMessage::SIZE_INT) = m_group;

	return cBuffer;
}

bool MGroupCreateUpdate::FromBuffer(char* pBuffer, int nLength)
{
	m_guid = *(GUID*)pBuffer;
	m_nMessageType = *(int*)(pBuffer + IMessage::SIZE_GUID);
	m_group = *(TGroup*)(pBuffer + IMessage::SIZE_GUID + IMessage::SIZE_INT);
	// Note: the size of the group struct will differ depends on the number of users the group... 
	//...therefor must adjust to read that much of buffer or have a sync word/#                     
}
