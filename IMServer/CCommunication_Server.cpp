#include "stdafx.h"
#include <atlstr.h>
#include <string>
#include <list>
#include "../GenComm/constants.h"
#include "../GenComm/IMessageFactory.h"
#include "../IMComm/CMessageFactory_WhatsApp.h"
#include "../IMComm/structsAndConstants.h"
#include "../GenComm/IMessage.h"
#include "../IMComm/MTextMessage.h"
#include "../IMComm/MGroupCreateUpdate.h"
#include "../IMComm/MAcknowledgeMessage.h"
#include "CTextMessageManager.h"
#include "CCommunication_Server.h"

class CServerSocket;

CCommunication_Server* CCommunication_Server::s_pCommunicationServer = NULL;

std::list <CCommunication_Server::CServerSocket*> CCommunication_Server::m_listSocketsToClient;


CCommunication_Server::CCommunication_Server()
{
	//Register();
}


CCommunication_Server::~CCommunication_Server()
{
	this->Close();
	for (std::list<CServerSocket*>::iterator itr = m_listSocketsToClient.begin(); itr != m_listSocketsToClient.end(); itr++)
	{
		delete *itr;
		*itr = nullptr;
	}
}

//This method would be called in the on received method. after extracting the text struct (which also contains destination), we would call this callback
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


void CCommunication_Server::RegisterCallback(EMessageType eMessageType, void* pfnCallback)// (*pfnCallback)(IMessage*))
{
	//m_hashCallbacks.insert({ eMessageType, pfnCallback });
	m_hashCallbacks[eMessageType] = pfnCallback;
	//m_hashCallbacks.insert(std::pair<EMessageType, void*>/*(*)(IMessage*)>*/(eMessageType, pfnCallback));
}

void CCommunication_Server::RemoveCallback(EMessageType eMessageType)
{
	m_hashCallbacks.erase(eMessageType);
}

/*void CCommunication_Server::OnMessageReceived(char pBuffer[])
{
	// Get message type from buffer (notice that in all messsages, first two
	// members are the GUID (in this implementation its an int and SIZE_GUID=sizeof(int)) and then type (see IMessage class) 
	//ie. this will move pointer over to point at type variable in buffer array. 
	//This explains the folowing line:
	EMessageType type = *(EMessageType*)(pBuffer + SIZE_GUID);//move pointer over till reach type;cast to pointer to enum;get content of pointer
	// 1. Create Message object by the type.
	IMessage* pMessage = m_pMessageFactory->CreateMessage(type); // 'pMessage' : Message obj
	pMessage->FromBuffer(pBuffer);// Calling mssg obj.'s FromBuffer method which Fills the message obj.'s fields 
	// 2. Call callback
	void* callbacks = m_hashCallbacks[type]; // returns a pointer to a function
	((void(*)(IMessage*))callbacks)(pMessage);
}*/

// This function is called when the server receives a connection request (V):
void CCommunication_Server::OnAccept(int nErrorCode)
{
	//::AfxMessageBox(L"received connection request");
// Create new socket for the connection to requesting client:
	CServerSocket* pNewSocket = new CServerSocket(/*m_pMessageFactory,*/ "Server Socket " + std::to_string(++SOCKET_NUMBER));
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


//Called by the framework to notify this socket that there is data in 
//the buffer that can be retrieved by calling the Receive() member function.
void CCommunication_Server::CServerSocket::OnReceive(int nErrorCode)
{
	//CString Ca(this->m_sSocketName.c_str());
	//AfxMessageBox(Ca);
	//::AfxMessageBox(L"text message received by " + Ca);

// Create a buffer to received the message:
	const int RECEIVE_BUFFER_SIZE = 100;
	char arrBuffer[RECEIVE_BUFFER_SIZE] = { 0 };
	// Receive the message:
	int nNumBytesReceived = CAsyncSocket::Receive(arrBuffer, RECEIVE_BUFFER_SIZE);
	// - If error code returned, do not continue:
	if (nNumBytesReceived == SOCKET_ERROR || nNumBytesReceived == 0)
	{
		return;
	}
	// When a message comes in the matching socket, in the list, receives it and runs over the list of
	// all sockets and for each socket, other then itself, calls the inherited (from CAsyncSocket) Send()
	//for (auto it : m_listSocketsToClient)
	//{
		//if ((it->m_sSocketName.compare(this->m_sSocketName)) != 0)
		//{
			/*it*/this->Send(arrBuffer, RECEIVE_BUFFER_SIZE);
		//}
	//}
}



void CCommunication_Server::OnClose(int nErrorCode)
{
	AfxMessageBox(L"Wow - connection closed...");
	SOCKET_NUMBER--;
}


/*void CCommunication_Server::OnMessageReceived(char pBuffer[])
{
	// Get message type from buffer (notice that in all messsages, first two
	// members are the GUID (in this implementation its an int and SIZE_GUID=sizeof(int)) and then type (see IMessage class) 
	//ie. this will move pointer over to point at type variable in buffer array. 
	//This explains the folowing line:
	EMessageType type = *(EMessageType*)(pBuffer + SIZE_GUID);//move pointer over till reach type;cast to pointer to enum;get content of pointer
	// 1. Create Message object by the type.
	IMessage* pMessage = m_pMessageFactory->CreateMessage(type); // 'pMessage' : Message obj
	pMessage->FromBuffer(pBuffer);// Calling mssg obj.'s FromBuffer method which Fills the message obj.'s fields 
	// 2. Call callback
	void* callbacks = m_hashCallbacks[type]; // returns a pointer to a function
	((void(*)(IMessage*))callbacks)(pMessage);
}*/