#include "stdafx.h"
#include "afxsock.h"
#include <rpc.h>
#include <atlstr.h>
#include "../GenComm/IMessageFactory.h"
#include "../IMComm/CMessageFactory_WhatsApp.h"
#include "../GenComm/CMefathimSocket.h"
#include "../GenComm/ICommunication.h"
#include "../GenComm/CCommunication_TCP.h"
#include "../GenComm/CSafeMessageQueue.h"
#include "../IMComm/structsAndConstants.h"
#include "../GenComm/IMessage.h"
#include "../IMComm/MTextMessage.h"
#include "../IMComm/MGroupCreateUpdate.h"
#include "../IMComm/MAcknowledgeMessage.h"

#include "CCommunication_Client.h"


//CCommunication_Client::CCommunication_Client(){}
CCommunication_Client* CCommunication_Client::s_pCCommunicationClient = NULL;

CCommunication_Client::CCommunication_Client() : CCommunication_TCP(new CMessageFactory_WhatsApp, _T("This is a test"))     //[2]***************************************************************************************
{
	Register();
	m_socket->Connect(need address...sConnectionDetails);
}

CCommunication_Client::~CCommunication_Client()
{
	m_socket->Close();
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

// IMPLEMENTATION WILL INC CREATING A TEXT MSSG OBJ(using factory) AND CALLING TObUFFER AND THEN SENDMESSAGE()
void CCommunication_Client::SendTextMessage(const TTextMessage& text) 
{
	MTextMessage* pMTextmessage = new MTextMessage(1,text);
	char* cBuffer = new char[pMTextmessage->Size()];
	pMTextmessage->ToBuffer(cBuffer);
	m_socket->Send(cBuffer, sizeof(cBuffer));
};
void CCommunication_Client::SendGroupCreateUpdate(const TGroup& group) {};
void CCommunication_Client::SendAck(const TTextMessage& textMessageToAck) {};