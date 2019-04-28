#pragma once
class CTextMessageManager
{
private:
	static CTextMessageManager* s_pTextMessagesManager; //Singleton
	CTextMessageManager();
public:
	~CTextMessageManager();


	static CTextMessageManager* GetInstance()
	{
		if (s_pTextMessagesManager == NULL)
		{
			s_pTextMessagesManager = new CTextMessageManager();
		}
		return s_pTextMessagesManager;
	}

	// This function publishes a text message, and writes it to local m_acks for tracking when it finished.
	void PublishTextMessage(TTextMessage text);
};
