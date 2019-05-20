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
#include "CTextMessageManager.h"
#include "CCommunication_Server.h"

 CCommunication_Server* CCommunication_Server::s_pCommunicationServer = NULL; 

CCommunication_Server::CCommunication_Server() : CMefathimSocket(new CMessageFactory_WhatsApp, "Server")
{
	Register();
}


CCommunication_Server::~CCommunication_Server()
{
	this->Close();
}

void CCommunication_Server::OnTextMessageReceived(TTextMessage message)
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
	//<<<<<<<<<RegisterCallback(EMessageType::TEXT_MESSAGE, CCommunication_Server::GetInstance()->OnTextMessageReceived);>>>>>>>>>>>>>
	//this->RegisterCallback(EMessageType::CREATE_UPDATE_GROUP, OnGroupCreateUpdateReceived);
	//this->RegisterCallback(EMessageType::ACKNOWLEDGE, OnAcknowledgeReceived);
}

void CCommunication_Server::SendTextMessage(TTextMessage text) // sends to other client-side  ??????????????????????????????????????????????????????????????????
{
	CTextMessageManager::GetInstance()->PublishTextMessage(text);
}

void CCommunication_Server::OnReceive(int nErrorCode)
{
	//CString Ca(this->m_sSocketName.c_str());
	//AfxMessageBox(Ca);
	//::AfxMessageBox(L"text message received by " + Ca);

// Create a buffer to received the message:
	const int RECEIVE_BUFFER_SIZE = 300;
	char arrBuffer[RECEIVE_BUFFER_SIZE] = { 0 };
	// Receive the message:
	int nNumBytesReceived = CAsyncSocket::Receive(arrBuffer, RECEIVE_BUFFER_SIZE);
	// - If error code returned, do not continue:
	if (nNumBytesReceived == SOCKET_ERROR || nNumBytesReceived == 0)
	{
		return;
	}

	
		for (auto it : m_listSocketsToClient)
		{
			if ((it->m_sSocketName.compare(this->m_sSocketName)) != 0)
			{
				it->Send(arrBuffer, RECEIVE_BUFFER_SIZE);
			}
		}
}

void CMefathimSocket::OnAccept(int nErrorCode)
{
	//::AfxMessageBox(L"received connection request");
// Create new socket for the connection to requesting client:
	CMefathimSocket* pNewSocket = new CMefathimSocket(m_pMessageFactory, m_sSocketName + " Socket " + std::to_string(++SOCKET_NUMBER));
	this->m_listSocketsToClient.push_back(pNewSocket);
	CString sName(pNewSocket->m_sSocketName.c_str());
	::AfxMessageBox(sName + L" is added to the server socket list");
	// Accept client request by binding new socket to the clients ip and port
	BOOL bAccepted = CAsyncSocket::Accept(*pNewSocket);

	// Error handling; return value is non zero if the function was succesful
	if (bAccepted)
	{
		return;
	}
	else
	{
		throw GetLastError();
	}
}