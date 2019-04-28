#pragma once
#include "../GenComm/CMefathimSocket.h"
#include "../GenComm/CSafeMessageQueue.h"
#include "../IMComm/structsAndConstants.h"


class CCommunication_Client :
	public  CMefathimSocket
{

private:
	static CCommunication_Client* s_pCCommunicationClient; // SINGLETON; 

	// Creating queues of objects (text message, acknowledge and group) for INCOMING messages
	CSafeMessageQueue m_queueTextMessages;
	CSafeMessageQueue m_queueGroupCreateUpdateMessages;
	CSafeMessageQueue m_queueAcknowledge;

	CCommunication_Client(/*CString sConnectionDetails*/);
public:
	// This method fills a hash tablewith message type and corresponding callback function    
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
	 CSafeMessageQueue& GetTextMessagesQueue() { return m_queueTextMessages; }
     CSafeMessageQueue& GetGroupCreateUpdateMessagesQueue() { return m_queueGroupCreateUpdateMessages; }
	 CSafeMessageQueue& GetAcknowledgeMessagesQueue() { return m_queueAcknowledge; }

	// methods for OUTGOING messages; must IMPLEMENT

	//void SendTextMessage(const TTextMessage& text); // argument: struct (3) // IMPLEMENTATION WILL INC CREATING A TEXT MSSG OBJ(using factory) AND CALLING TObUFFER AND THEN SENDMESSAGE()
	void SendTextMessage(const TTextMessage& text);
	void SendGroupCreateUpdate(const TGroup& group); // argument: struct (2)
	void SendAck(const TTextMessage& textMessageToAck); // argument: struct (3)

	void HandleIncomingMessages(); 
	void Tick();
};

