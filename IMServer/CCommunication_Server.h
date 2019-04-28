#pragma once


 class CCommunication_Server :
	public CMefathimSocket
{
private:
	CCommunication_Server();
	static CCommunication_Server* s_pCommunicaionServer; //SINGLETON

public:
	~CCommunication_Server();

	void OnTextMessageReceived(MTextMessage message)
	{
		CTextMessageManager::GetInstance()->PublishTextMessage(message);
	}

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
		if (s_pCommunicaionServer == NULL)
		{
			s_pCommunicaionServer = new CCommunication_Server();
		}
		return s_pCommunicaionServer;
	}



	void SendTextMessage(TTextMessage text);
	
	void OnReceiveTextMessage();
};

