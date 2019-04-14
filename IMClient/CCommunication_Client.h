#pragma once
#include <atlstr.h>
#include "../IMComm/CMessageFactory_WhatsApp.h"
#include "../GenComm/CCommunication_TCP.h"
#include "../GenComm/csafemessagequeue.h"


class CCommunication_Client :
	public CCommunication_TCP
{

//protected:

	//CHashTable<EMessageType, CList<void*>> m_hashCallbacks;

	//IMessageFactory* m_pMessageFactory;

//public:
	
	
	/*void RegisterCallback(EMessageType eMessageType, void* pfnCallback)
	{
		m_hashCallbacks.Insert(eMessageType, pfnCallback);
	}*/
	
	/*void RemoveCallback(EMessageType eMessageType, void* pfnCallback)
	{
		m_hashCallbacks.Remove(eMessageType, pfnCallback);
	}*/	
	
	
	//Constructor
	/*ICommunication(IMessageFactory* pMessageFactory)
	{
		m_pMessageFactory = pMessageFactory;
	}
};*/


private:
	static CCommunication_Client* s_pCCommunicationClient; // SINGLETON; 

	//Constructor; constructor of CCommunication_Client calls constructor of 'abba' ie. CCommunication_TCP, and passes in as an argument to the abba constructor a CMessageFactory_WhatsApp object

	// Creating queues of objects (text message, acknowledge and group) for INCOMING messages
	CSafeMessageQueue m_queueTextMessages;
	CSafeMessageQueue m_queueGroupCreateUpdateMessages;
	CSafeMessageQueue m_queueAcknowledge;

public:
	CCommunication_Client(/*CString sConnectionDetails*/);
	// This method fills a hash table(declared in  'IComm', the sabba)with message type and corresponding callback function    [5]*****************************************************************
	void Register();


	// These are the callback functions ie. for when a new message or ack or group  occur
	static void OnTextMessageReceived(IMessage* pMessage);
	static void OnGroupCreateUpdateReceived(IMessage* pMessage);
	static void OnAcknowledgeReceived(IMessage* pMessage);
	~CCommunication_Client();

	static CCommunication_Client* GetInstance()  // SINGLETON              
	{
		if (s_pCCommunicationClient == NULL)
		{
			s_pCCommunicationClient = new CCommunication_Client;
		}
		return s_pCCommunicationClient;
	}

	// Getters for the queues 
	const CSafeMessageQueue& GetTextMessagesQueue() { return m_queueTextMessages; }
    const CSafeMessageQueue& GetGroupCreateUpdateMessagesQueue() { return m_queueGroupCreateUpdateMessages; }
	const CSafeMessageQueue& GetAcknowledgeMessagesQueue() { return m_queueAcknowledge; }

	// methods for OUTGOING messages; must IMPLEMENT
	void SendTextMessage(const TTextMessage& text); // argument: struct (3) // IMPLEMENTATION WILL INC CREATING A TEXT MSSG OBJ(using factory) AND CALLING TObUFFER AND THEN SENDMESSAGE()
	void SendGroupCreateUpdate(const TGroup& group); // argument: struct (2)
	void SendAck(const TTextMessage& textMessageToAck); // argument: struct (3)
};

