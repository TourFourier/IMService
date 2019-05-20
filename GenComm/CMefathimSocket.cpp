#include "stdafx.h"
#include <afxsock.h>
#include "../IMComm/MTextMessage.h"
#include "../IMComm/structsAndConstants.h"
#include "IMessageFactory.h"
#include "IMessage.h"
#include "constants.h"
#include <atlstr.h>
#include <map>
#include <list>
#include <string>
#include <iostream>
#include "CMefathimSocket.h"

//static const int BUFFER_LENGTH = 100;
std::list <CMefathimSocket*> CMefathimSocket::m_listSocketsToClient;


CMefathimSocket::CMefathimSocket(IMessageFactory* pMessageFactory, std::string sSocketName) :CAsyncSocket()
{
	m_pMessageFactory = pMessageFactory;
	m_sSocketName = sSocketName;
}


CMefathimSocket::~CMefathimSocket()
{
}


void CMefathimSocket::RegisterCallback(int eMessageType, int pfnCallback)// (*pfnCallback)(IMessage*))
{
	//m_hashCallbacks.insert({ eMessageType, pfnCallback });
	m_hashCallbacks[eMessageType] = pfnCallback;
	//m_hashCallbacks.insert(std::pair<EMessageType, void*>/*(*)(IMessage*)>*/(eMessageType, pfnCallback));
}

void CMefathimSocket::RemoveCallback(int eMessageType)
{
	m_hashCallbacks.erase(eMessageType);
}



// This function is called when the server receives a connection request (V):
void CMefathimSocket::OnAccept(int nErrorCode)
{
		//::AfxMessageBox(L"received connection request");
	// Create new socket for the connection to requesting client:
	CMefathimSocket* pNewSocket = new CMefathimSocket(m_pMessageFactory,m_sSocketName + " Socket " + std::to_string(++SOCKET_NUMBER));
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

// This function is called when the client is connected (V):
void CMefathimSocket::OnConnect(int nErrorCode)
{
		CString sName(this->m_sSocketName.c_str());
		::AfxMessageBox(sName + L" is connected to the server" );
		
}

//Called by the framework to notify this socket that there is data in 
//the buffer that can be retrieved by calling the Receive() member function.
void CMefathimSocket::OnReceive(int nErrorCode)
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

	// If recipient is a client: call onMessageReceived() to get the message object and call its callback
	if (this->m_sSocketName == "Client")
	{
		OnMessageReceived(arrBuffer);
	}
	// If recipient is the Server: receive buffer, accesses all sockets except receiving socket and sends buffer out to all other clients
	else
	{
		for (auto it : m_listSocketsToClient)
		{
			if ((it->m_sSocketName.compare(this->m_sSocketName)) != 0)
			{
				it->Send(arrBuffer, RECEIVE_BUFFER_SIZE);
			}
		}
	}	
}


void CMefathimSocket::OnMessageReceived(char pBuffer[])
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
	//void* callbacks = m_hashCallbacks[type]; // returns a pointer to a function
	//((void(*)(IMessage*))callbacks)(pMessage);
}
	


	
void CMefathimSocket::OnClose(int nErrorCode)
{
	AfxMessageBox(L"Wow - connection closed...");
}



/*
		TTextMessage text;
		text.m_sText = _T("test text");
		text.m_userDestination.guid = 17;
		text.m_userDestination.sName =_T("dave");
		text.m_userDestination.sPhoneNumber = _T(" 058 ");
		text.m_groupDestination.guid = 12;*/
		//::AfxMessageBox(L"SendTextMessage going to be called by" + sName);
		//int n_RetVal = SendTextMessage(/*"hello5"*/text);

		// Printing to message box returned int value from call to sendtextmessage(); need to convert to string and then to CString
		//auto s = std::to_string(n_RetVal);
		//CString Cs(s.c_str());
		//::AfxMessageBox(Cs);

		//int nRet = CAsyncSocket::Send(carrMessage, sizeof(carrMessage));
		/*if (!(this->m_sSocketName.compare("Client1")))
		{
			::AfxMessageBox(L"about to send from " + sName + L"to Client 2");
			static int nMessageNumber = 1;
			char carrSendBack[100];
			sprintf_s(carrSendBack, "Test-message  from client 1 to client 2  # %d", nMessageNumber);
			this->Send(carrSendBack, sizeof(carrSendBack));
		}*/


/*TAKEN OUT OF onReceived()*/
/*//need to access the list in the ServerSocket which holds sockets 1 and 2 ; using this gives me ServerSocket1 whos list is empty
	if (!(this->m_sSocketName.compare( "ServerSocket1" )))
	{
		//create new buffer to hold old message with additional text
		char carrReceived[BUFFER_LENGTH];
		sprintf_s(carrReceived, BUFFER_LENGTH, "%s %s", (this->m_sSocketName) + " Received message to send to client2: ", arrBuffer);
		::MessageBoxA(AfxGetMainWnd()->m_hWnd, carrReceived, "OnReceive()", 0);
			//::AfxMessageBox(L"entered ss1 if");
		 CMefathimSocket* t = *(++(CMefathimSocket::m_listSocketsToClient.begin()));
			
		 
			//std::string s = t->m_sSocketName;
			//std::list<CMefathimSocket*>::iterator it
			//int t = this->m_listSocketsToClient.size();
			//auto s = std::to_string(t);
			//CString Cs(s.c_str());
			//::AfxMessageBox(Cs + L"# of elements in this list");
		
			std::string s = t->m_sSocketName;
			CString Cs(s.c_str());
			//CString a = L"accessed list element";
			//::AfxMessageBox(Cs );
			//t = t + 1;
			::AfxMessageBox(L"about to send from " + Cs + L" to Client2");
		//static int nMessageNumber = 1;
		//char carrSendBack[100];
		//sprintf_s(carrSendBack, "Test-message  from client 1 to client 2  # %d", nMessageNumber);
		t->Send(arrBuffer, sizeof(arrBuffer));
	}
	if (!(this->m_sSocketName.compare("Client2")))
	{
		::AfxMessageBox(L"entered cl2 if");

		//  plot buffer
		arrBuffer[nNumBytesReceived - 1] = 0;
		char carrReceived[BUFFER_LENGTH];
		sprintf_s(carrReceived, BUFFER_LENGTH, "%s %s", /*(this->m_sSocketName) +*///"Received message: ", arrBuffer);
		//::MessageBoxA(AfxGetMainWnd()->m_hWnd, carrReceived, "OnReceive()", 0);}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//OnMessageReceived(arrBuffer);
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/