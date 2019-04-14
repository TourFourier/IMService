#include "stdafx.h"
#include "CMefathimSocket.h"
#include <list>

static const int BUFFER_LENGTH = 100;

CMefathimSocket::CMefathimSocket(CString sSocketName) :CAsyncSocket()
{
	m_sSocketName = sSocketName;
}


CMefathimSocket::~CMefathimSocket()
{
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

// This function is called when the server receives a connection request (V):
void CMefathimSocket::OnAccept(int nErrorCode)
{
	// Create new socket for the connection to this client:
	CMefathimSocket* pNewSocket = new CMefathimSocket(m_sSocketName);
	this->m_listSocketsToClient.push_back(pNewSocket);
	BOOL bAccepted = CAsyncSocket::Accept(*pNewSocket);

	// Now send a message back:
	/*CString sStringToMessageBox = m_sSocketName + L" accepted connection request!";
	::AfxMessageBox(sStringToMessageBox);
	char carrSendBack[BUFFER_LENGTH] = "Hey, server accepted connection!";
	::AfxMessageBox(L"Now sending... ' Hey, server accepted connection! '");
	pNewSocket->Send(carrSendBack, sizeof(carrSendBack));*/
}

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
	arrBuffer[nNumBytesReceived - 1] = 0;

	// Plot it to message-box, for debugging:
	char carrReceived[BUFFER_LENGTH];
	sprintf_s(carrReceived, BUFFER_LENGTH, "%s %s", "Received message: ", arrBuffer);
	::MessageBoxA(AfxGetMainWnd()->m_hWnd, carrReceived, "OnReceive()", 0);

	// Now send a message back:
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
	Send(carrSendBack, sizeof(carrSendBack));
}

void CMefathimSocket::OnClose(int nErrorCode)
{
	AfxMessageBox(L"Wow - connection closed...");
}
