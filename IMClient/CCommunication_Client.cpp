#include "stdafx.h"
#include "afxsock.h"
#include <rpc.h>
#include <atlstr.h>
#include <string>
#include "../GenComm/constants.h"
#include "../GenComm/IMessageFactory.h"
#include "../IMComm/CMessageFactory_WhatsApp.h"
#include "../GenComm/CMefathimSocket.h"
#include "../IMComm/structsAndConstants.h"
#include "../GenComm/IMessage.h"
#include "../IMComm/MTextMessage.h"
#include "../IMComm/MGroupCreateUpdate.h"
#include "../IMComm/MAcknowledgeMessage.h"

#include "CCommunication_Client.h"


//CCommunication_Client::CCommunication_Client(){}
CCommunication_Client* CCommunication_Client::s_pCCommunicationClient = NULL;

// Hard coded cient number but should be dynamic
CCommunication_Client::CCommunication_Client() : CMefathimSocket(new CMessageFactory_WhatsApp, "Client")// + std::to_string(1))//++SOCKET_NUMBER))   
{
	Register();
}

CCommunication_Client::~CCommunication_Client()
{
	this->Close();
}

void CCommunication_Client::OnTextMessageReceived(IMessage* pMessage)
{
	CCommunication_Client::GetInstance()->m_queueTextMessages.Push((MTextMessage*)pMessage);
}

void CCommunication_Client::OnGroupCreateUpdateReceived(IMessage* pMessage)
{
	CCommunication_Client::GetInstance()->m_queueGroupCreateUpdateMessages.Push((MGroupCreateUpdate*)pMessage);
}

void CCommunication_Client::OnAcknowledgeReceived( IMessage* pMessage)
{
	CCommunication_Client::GetInstance()->m_queueAcknowledge.Push((MAcknowledgeMessage*)pMessage);
}

void CCommunication_Client::Register()
{
	//since RegisterCallback is an inherited method, using "this->" makes it clear that this method exists in this object(even though it is technically unnecessary)
	this->RegisterCallback(EMessageType::TEXT_MESSAGE, CCommunication_Client::GetInstance()->OnTextMessageReceived);
	this->RegisterCallback(EMessageType::CREATE_UPDATE_GROUP, CCommunication_Client::GetInstance()->OnGroupCreateUpdateReceived);
	this->RegisterCallback(EMessageType::ACKNOWLEDGE, CCommunication_Client::GetInstance()->OnAcknowledgeReceived);
}

// IMPLEMENTATION INC CREATING A TEXT MSSG OBJ(using factory) AND CALLING TObUFFER AND THEN SENDMESSAGE()
void CCommunication_Client::SendTextMessage(const TTextMessage& text) 
{
	MTextMessage* pMTextmessage = new MTextMessage(1,text);
	char* cBuffer = new char[pMTextmessage->Size()];
	pMTextmessage->ToBuffer(cBuffer);
	this->Send(cBuffer, sizeof(cBuffer));
};
void CCommunication_Client::SendGroupCreateUpdate(const TGroup& group) {};
void CCommunication_Client::SendAck(const TTextMessage& textMessageToAck) {};

void CCommunication_Client::HandleIncomingMessages()
{
	MTextMessage* pMessageToHandle = NULL;  // pointer to text message obj
	// while runs if test is not 0 even if value is negative; a pointer holds a number ie. address, and so long as it is not null it evals to true
	// This leaves me with an Imessage obj (if the queue wasn't empty). We then dynamic cast it to a text message
	while (pMessageToHandle = dynamic_cast<MTextMessage*>(CCommunication_Client::GetInstance()->GetTextMessagesQueue().Pop()))
	{
		// Update window (and DB)
		OnTextMessageReceived((dynamic_cast<MTextMessage*>(pMessageToHandle)->GetTextMessage()));
	}
}

// Tick function for main to call
void CCommunication_Client::Tick()
{
	this->HandleIncomingMessages();
}