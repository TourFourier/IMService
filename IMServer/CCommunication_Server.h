#pragma once


 class CCommunication_Server :
	public CMefathimSocket
{
private:
	CCommunication_Server();
	static CCommunication_Server* s_pCommunicationServer; //SINGLETON

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



	void SendTextMessage(TTextMessage text);
	
	void OnReceiveTextMessage();
};

