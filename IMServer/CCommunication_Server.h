#pragma once
#include <map>


 class CCommunication_Server 
	 : public CAsyncSocket
 {
private:

	CCommunication_Server();
	static CCommunication_Server* s_pCommunicationServer; //SINGLETON
	std::string m_sSocketName = "SERVER";


	class CServerSocket : public CAsyncSocket
	{
	public:
		CServerSocket(std::string name) :m_sSocketName(name)
		{}

		std::string m_sSocketName;

		void OnReceive(int nErrorCode);

	};


	// For server side usage only:
	static std::list<CServerSocket*> m_listSocketsToClient;
	std::map<EMessageType, void*> m_hashCallbacks;// Used to perform task(callback) related to specific mssg type
	//IMessageFactory* m_pMessageFactory;





public:
	~CCommunication_Server();

	void OnTextMessageReceived(TTextMessage message);
	

	/*void OnGroupCreateUpdateReceived(MGroupCreateUpdate message);
	{
		CGroupsManager_Server::GetInstance()->CreateUpdateGroup(message.m_group);
	}
	void OnACKNOWLEDGEReceived(MAcknowledgeMessage message);
	{
		CTextMessageManager::GetInstance()->OnAckReceived(message);
	}*/

	void Register();

	static CCommunication_Server* GetInstance()
	{
		if (s_pCommunicationServer == NULL)
		{
			s_pCommunicationServer = new CCommunication_Server();
		}
		return s_pCommunicationServer;
	}

	void RegisterCallback(EMessageType eMessageType, void* pfnCallback);// (*pfnCallback)(IMessage*))
	void RemoveCallback(EMessageType eMessageType);
	//void OnMessageReceived(char pBuffer[]);
	void OnAccept(int nErrorCode);
	void OnClose(int nErrorCode);




	void SendTextMessage(TTextMessage text);
	
	void OnReceiveTextMessage();
};

