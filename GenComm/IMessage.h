#pragma once


class  IMessage
{
protected:
	int m_guid; // Simple implementation uses int instead of GUID
	int m_nMessageType;// define the EMessageType in the implementations and 
	//upon receipt of buffer, typecast this member into an EMessageType to get message type as enum(see from buffer definition)

public:
	IMessage(int guid=0, int messageType=0);
	virtual ~IMessage();

	
	const int GetGuid() { return m_guid; }
	int GetType() { return m_nMessageType; }
	virtual int Size() = 0;
	virtual bool ToBuffer(char* cBuffer)=0;
	virtual bool FromBuffer(char* pBuffer)=0;
};

