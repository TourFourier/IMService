#pragma once


class  IMessage
{
protected:
	int m_guid; // Simple implementation uses int instead of GUID
	int m_nMessageType;// define the EMessageType in the implementations and, typecast this into an enum EMessageType in the inheritances

public:
	IMessage();
	IMessage(int guid, int messageType);
	virtual ~IMessage();

	
	const int GetGuid() { return m_guid; }
	virtual int GetType() { return m_nMessageType; }
	virtual int Size() = 0;
	virtual bool ToBuffer(char* cBuffer)=0;
	virtual bool FromBuffer(char* pBuffer)=0;
};

