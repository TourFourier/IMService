#pragma once
#include<map>
#include "../IMComm/CMessageFactory_WhatsApp.h"
#include "../GenComm/CSafeMessageQueue.h"
#include "../IMComm/structsAndConstants.h"


class CCommunication_Client :
	public  CAsyncSocket
{
private:
	static CCommunication_Client* s_pCCommunicationClient; // SINGLETON; 
	std::string m_sSocketName;

	//void (*fptr)()=HandleIncomingMessages;


	std::map<EMessageType, void*> m_hashCallbacks;// Used to perform task(callback) related to specific mssg type

	// Creating queues of objects (text message, acknowledge and group) for INCOMING messages
	CSafeMessageQueue m_queueTextMessages;
	CSafeMessageQueue m_queueGroupCreateUpdateMessages;
	CSafeMessageQueue m_queueAcknowledge;
	// Initialized in the constructor
	IMessageFactory* m_pMessageFactory;

	CCommunication_Client();
public:
	~CCommunication_Client();
	static CCommunication_Client* GetInstance()  // SINGLETON              
	{
		if (s_pCCommunicationClient == NULL)
		{
			s_pCCommunicationClient = new CCommunication_Client();
		}
		return s_pCCommunicationClient;
	}

	// This method fills a hash tablewith message type and corresponding callback function and is called in CComm's constructor  
	void Register();

	// These are the callback functions ie. for when a new message or ack or group  occur
	static void OnTextMessageReceived(IMessage* pMessage);
	static void OnGroupCreateUpdateReceived(IMessage* pMessage);
	static void OnAcknowledgeReceived(IMessage* pMessage);

	void RegisterCallback(EMessageType eMessageType, void* pfnCallback);// (*pfnCallback)(IMessage*))
	void RemoveCallback(EMessageType eMessageType);
	void OnConnect(int nErrorCode);
	void OnMessageReceived(char pBuffer[]);
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);



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

