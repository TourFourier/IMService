#include "stdafx.h"
#include <afxsock.h>
#include "IMessageFactory.h"
#include "IMessage.h"
#include "constants.h"
#include <atlstr.h>
#include <map>
#include <list>
#include <string>
#include "CMefathimSocket.h"

static const int BUFFER_LENGTH = 100;

CMefathimSocket::CMefathimSocket(IMessageFactory* pMessageFactory, std::string sSocketName) :CAsyncSocket()
{
	m_pMessageFactory = pMessageFactory;
	m_sSocketName = sSocketName;
}


CMefathimSocket::~CMefathimSocket()
{
}


void CMefathimSocket::RegisterCallback(int eMessageType, void(*pfnCallback)(IMessage*))
{
	m_hashCallbacks.insert(std::pair<int, void*>(eMessageType, pfnCallback));
}

void CMefathimSocket::RemoveCallback(int eMessageType)
{
	m_hashCallbacks.erase(eMessageType);
}



// This function is called when the server receives a connection request (V):
void CMefathimSocket::OnAccept(int nErrorCode)
{
	// Create new socket for the connection to this client:
	CMefathimSocket* pNewSocket = new CMefathimSocket(m_pMessageFactory,m_sSocketName + std::to_string(++CLIENT_NUMBER));
	this->m_listSocketsToClient.push_back(pNewSocket);
	BOOL bAccepted = CAsyncSocket::Accept(*pNewSocket);

	// Now send a message back:
	/*CString sStringToMessageBox = m_sSocketName + L" accepted connection request!";
	::AfxMessageBox(sStringToMessageBox);
	char carrSendBack[BUFFER_LENGTH] = "Hey, server accepted connection!";
	::AfxMessageBox(L"Now sending... ' Hey, server accepted connection! '");
	pNewSocket->Send(carrSendBack, sizeof(carrSendBack));*/
}

// This function is called when the client is connected (V):
void CMefathimSocket::OnConnect(int nErrorCode)
{
	::AfxMessageBox(L"OnConnect!!!!");

	// Connected. Now send a message:
	::AfxMessageBox(L"Now sending Boker Tov");
	char carrMessage[BUFFER_LENGTH] = "Boker tov";
	int nRet = CAsyncSocket::Send(carrMessage, sizeof(carrMessage));
}

//Called by the framework to notify this socket that there is data in 
//the buffer that can be retrieved by calling the Receive() member function.
void CMefathimSocket::OnReceive(int nErrorCode)
{
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
	// - In this practice we send text, so we must put a 
	//   null-terminating character to the buffer in order to 
	//   be able to work with it as a string:
	//arrBuffer[nNumBytesReceived - 1] = 0;

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	OnMessageReceived(arrBuffer);
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	// Plot it to message-box, for debugging:
	char carrReceived[BUFFER_LENGTH];
	sprintf_s(carrReceived, BUFFER_LENGTH, "%s %s", "Received message: ", arrBuffer);
	::MessageBoxA(AfxGetMainWnd()->m_hWnd, carrReceived, "OnReceive()", 0);

	/*/ Now send a message back:
	// - Use a local static counter of messages, this is just for debugging:
	static int nMessageNumber = 0;
	// - Create the buffer to send:
	char carrSendBack[BUFFER_LENGTH];
	sprintf_s(carrSendBack, "Test-message number... %d", nMessageNumber);
	nMessageNumber++;
	// - Plot it to message box for debugging:
	char carrMessageBox[BUFFER_LENGTH];
	sprintf_s(carrMessageBox, BUFFER_LENGTH, "%s %s", "Now sending...", carrSendBack);
	::MessageBoxA(AfxGetMainWnd()->m_hWnd, carrMessageBox, "OnReceive()", 0);
	// - Now send it:
	Send(carrSendBack, sizeof(carrSendBack));*/
}

void CMefathimSocket::OnClose(int nErrorCode)
{
	AfxMessageBox(L"Wow - connection closed...");
}

void CMefathimSocket::OnMessageReceived(char* pBuffer)
{
	// Notice this function is called on seprate thread then the main thread.
	// 0. Get message type from buffer (notice that in all messsages, first two
	//    members are the GUID and then type (see IMessage class) ie. this will move pointer over to point at type variable in buffer array. 
	//This explains the folowing line:
	int type = *(int*)(pBuffer + sizeof(int));//move pointer over till reach type;cast to pointer to enum;get content of pointer
	// 1. Create Message object by the type.
	IMessage* pMessage = m_pMessageFactory->CreateMessage(type); // 'pMessage' : Message obj
	pMessage->FromBuffer(pBuffer);// /Calling mssg obj.'s FromBuffer method which Fills the message obj.'s fields 
	// 2. Call callback
	void* callbacks = m_hashCallbacks[type]; // 'callbacks' : specific callback func
	((void(*)(IMessage*))callbacks)(pMessage);
	/*for (int i = 0; i < callbacks.GetSize(); i++)
	{
		void* pfnCallback = callbacks[i];
		(*pfnCallback)(pMessage);// Calling the callback func and passing in message obj. as an argument; the callbacks simply push the message into a queue to be handled by main thread
	}*/
}