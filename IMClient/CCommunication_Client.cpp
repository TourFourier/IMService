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
CCommunication_Client::CCommunication_Client(CMessageFactory_WhatsApp* p) : CMefathimSocket(p, "Client")// +std::to_string(++SOCKET_NUMBER))
{
	n = 2;
	Register();
}

CCommunication_Client::~CCommunication_Client()
{
	this->Close();
	delete s_pCCommunicationClient;
}

void CCommunication_Client::OnTextMessageReceived(IMessage* pMessage)
{
	CCommunication_Client::GetInstance()->m_queueTextMessages.Push((MTextMessage*)pMessage);
}

/*void CCommunication_Client::OnGroupCreateUpdateReceived(IMessage* pMessage)
{
	CCommunication_Client::GetInstance()->m_queueGroupCreateUpdateMessages.Push((MGroupCreateUpdate*)pMessage);
}

void CCommunication_Client::OnAcknowledgeReceived( IMessage* pMessage)
{
	CCommunication_Client::GetInstance()->m_queueAcknowledge.Push((MAcknowledgeMessage*)pMessage);
}*/

/*void CMefathimSocket::RegisterCallback(EMessageType eMessageType, void* pfnCallback)
{
	m_hashCallbacks.insert(std::pair<EMessageType, void*>(eMessageType, pfnCallback));
}*/

/*std::map<EMessageType, void*> m_hashCallbacks;
void CMefathimSocket::RegisterCallback(EMessageType eMessageType, void(*pfnCallback)(IMessage*))
{
	m_hashCallbacks.insert(std::pair<EMessageType, void(*)(IMessage*)>(eMessageType, pfnCallback));
}*/
void CCommunication_Client::Register()
{
	//void(*fptr)(IMessage*) = this->OnTextMessageReceived;
	//since RegisterCallback is an inherited method, using "this->" makes it clear that this method exists in this object(even though it is technically unnecessary)
	this->RegisterCallback(TEXT_MESSAGE, OnTextMessageReceived);// &(this->OnTextMessageReceived));
	//this->RegisterCallback(EMessageType::CREATE_UPDATE_GROUP, CCommunication_Client::GetInstance()->OnGroupCreateUpdateReceived);
	//this->RegisterCallback(EMessageType::ACKNOWLEDGE, CCommunication_Client::GetInstance()->OnAcknowledgeReceived);
}

void CCommunication_Client::SendTextMessage(const TTextMessage& text) 
{	
	//Create a message object to fill and call its ToBuffer() method
	MTextMessage* pMTextmessage = new MTextMessage(613,text);
	// Buffer to hold message object details which are being sent 
	char* cBuffer = new char[pMTextmessage->Size()];
	// Filling the Buffer with the message objects details
	pMTextmessage->ToBuffer(cBuffer);
	//Sending the Buffer to server
	this->Send(cBuffer, pMTextmessage->Size());
};


void CCommunication_Client::HandleIncomingMessages()
{
	if (!(GetTextMessagesQueue().Empty()))
	{
		MTextMessage* pMessageToHandle = NULL;  // pointer to text message obj
		pMessageToHandle = dynamic_cast<MTextMessage*>(GetTextMessagesQueue().Pop());
		CString text = pMessageToHandle->GetTextMessage().m_sText;
		::AfxMessageBox(text);
		Sleep(5000);
		// while runs if test is not 0 even if value is negative; a pointer holds a number ie. address, and so long as it is not null it evals to true
		// This leaves me with an Imessage obj (if the queue wasn't empty). We then dynamic cast it to a text message
		//while (!(GetTextMessagesQueue().Empty()))
		//while (pMessageToHandle = dynamic_cast<MTextMessage*>(CCommunication_Client::GetInstance()->GetTextMessagesQueue().Pop()))
		//{
			// Update window (and DB); In Primitive version just post a message box with the text received
			//OnTextMessageReceived((dynamic_cast<MTextMessage*>pMessageToHandle)->GetTextMessage()));
	}
}

// Tick function for main to call
void CCommunication_Client::Tick()
{
	this->HandleIncomingMessages();
}



//void CCommunication_Client::SendGroupCreateUpdate(const TGroup& group) {};
//void CCommunication_Client::SendAck(const TTextMessage& textMessageToAck) {};
/*int CCommunication_Client::SendTextMessage(const TTextMessage& text)
{
	// Buffer to hold message details which are being sent 
	char cBuffer[100];
	//Create a message object to fill and call its ToBuffer() method
	MTextMessage* pMTextmessage = new MTextMessage(1, text);
	// Filling the Buffer with the message objects details
	pMTextmessage->ToBuffer(cBuffer);
	//Sending the Buffer to server
	int nRet = CAsyncSocket::Send(cBuffer, sizeof(cBuffer));
	//TODO: define meaninful values for return values
	return nRet;
}*/
