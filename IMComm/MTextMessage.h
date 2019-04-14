#pragma once
#include "structsAndConstants.h"
#include "structsAndConstants.cpp"
#include "../GenComm/IMessage.h"


class MTextMessage :
	public IMessage
{
private:
		TTextMessage m_msgText;  
public:
	MTextMessage();
	MTextMessage(int messageType, const TTextMessage& message);
   ~MTextMessage();
	const TTextMessage& GetTextMessage() { return m_msgText; }

	// Returns absolute size of message object in bytes
	virtual int Size();
	// Logic for extracting from a buffer
	virtual bool ToBuffer(char* cBuffer);
	// Logic for creating a buffer
	virtual bool FromBuffer(char* pBuffer);	
};


