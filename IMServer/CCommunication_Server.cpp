#include "stdafx.h"
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
#include "CCommunication_Server.h"

 CCommunication_Server* CCommunication_Server::s_pCommunicaionServer = NULL; 

CCommunication_Server::CCommunication_Server() : CMefathimSocket(new CMessageFactory_WhatsApp, "Server")
{
	Register();
}


CCommunication_Server::~CCommunication_Server()
{
	this->Close();
}

void CCommunication_Server::OnTextMessageReceived(MTextMessage message)
{
	CTextMessageManager::GetInstance()->PublishTextMessage(message);
}

/*void CCommunication_Server::OnGroupCreateUpdateReceived(MGroupCreateUpdate message)
{
	CGroupsManager_Server::GetInstance()->CreateUpdateGroup(message.m_group);
}
void CCommunication_Server::OnACKNOWLEDGEReceived(MAcknowledgeMessage message)
{
	CTextMessageManager::GetInstance()->OnAckReceived(message);
}*/

void CCommunication_Server::Register()
{
	RegisterCallback(EMessageType::TEXT_MESSAGE, OnTextMessageReceived);
	//this->RegisterCallback(EMessageType::CREATE_UPDATE_GROUP, OnGroupCreateUpdateReceived);
	//this->RegisterCallback(EMessageType::ACKNOWLEDGE, OnAcknowledgeReceived);
}

void CCommunication_Server::SendTextMessage(TTextMessage text) // sends to other client-side  ??????????????????????????????????????????????????????????????????
{
	CTextMessageManager::GetInstance()->PublishTextMessage(text);
}