#pragma once
#include "../GenComm/CMefathimSocket.h"
#include "../IMComm/CMessageFactory_WhatsApp.h"
#include "../GenComm/CSafeMessageQueue.h"
#include "../IMComm/structsAndConstants.h"


class CCommunication_Client :
	public  CMefathimSocket
{
private:
	static CCommunication_Client* s_pCCommunicationClient; // SINGLETON; 
	char a = 'a';
	char c = 'c';
	char* b = new char('b');
	int v = 100;
	int w = 200;
	enum ENUM{A,B,C};
	//void (*fptr)()=HandleIncomingMessages;
	std::map<ENUM, int(*)()/*void(*)()*/> testmap;


	std::map<EMessageType, void*> m_hashCallbacks;// Used to perform task(callback) related to specific mssg type

	// Creating queues of objects (text message, acknowledge and group) for INCOMING messages
	CSafeMessageQueue m_queueTextMessages;
	CSafeMessageQueue m_queueGroupCreateUpdateMessages;
	CSafeMessageQueue m_queueAcknowledge;
	int(*fptr)() = add;

	CCommunication_Client(CMessageFactory_WhatsApp* p);
public:
	static int add()
	{
		::AfxMessageBox(L"called add");
		Sleep(5000);
		return 0;
	}
	~CCommunication_Client();
	static CCommunication_Client* GetInstance()  // SINGLETON              
	{
		if (s_pCCommunicationClient == NULL)
		{
			CMessageFactory_WhatsApp* p_MessageFac = new CMessageFactory_WhatsApp();
			s_pCCommunicationClient = new CCommunication_Client(p_MessageFac);
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
	void OnMessageReceived(char pBuffer[]);
	void OnReceive(int nErrorCode);



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

