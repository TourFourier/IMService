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
	::AfxMessageBox(L"received connection request");
	// Create new socket for the connection to this client:
	CMefathimSocket* pNewSocket = new CMefathimSocket(m_pMessageFactory,m_sSocketName + "Socket" + std::to_string(++SOCKET_NUMBER));
	this->m_listSocketsToClient.push_back(pNewSocket);

		CString Cp(pNewSocket->m_sSocketName.c_str());
		::AfxMessageBox(Cp);

	BOOL bAccepted = CAsyncSocket::Accept(*pNewSocket);

	// Transform string to CString for use with AFXMessageBox
	CString sName((pNewSocket->m_sSocketName).c_str());
	::AfxMessageBox(_T("Accepted request and created socket ") +  sName );
}

// This function is called when the client is connected (V):
void CMefathimSocket::OnConnect(int nErrorCode)
{
	CString sName(this->m_sSocketName.c_str());
	::AfxMessageBox(L"OnConnect called by !!!!" + sName);

	TTextMessage text;
	text.m_sText = _T("test text");
	text.m_userDestination.guid = 17;
	text.m_userDestination.sName =_T("dave");
	text.m_userDestination.sPhoneNumber = _T(" 058 ");
	text.m_groupDestination.guid = 12;

	int n_RetVal = SendTextMessage(/*"hello5"*/text);

		// Printing returned value from call to sendtextmessage()
		auto s = std::to_string(n_RetVal);
		CString Cs(s.c_str());
		::AfxMessageBox(Cs);

		//int nRet = CAsyncSocket::Send(carrMessage, sizeof(carrMessage));
}

//Called by the framework to notify this socket that there is data in 
//the buffer that can be retrieved by calling the Receive() member function.
void CMefathimSocket::OnReceive(int nErrorCode)
{
	CString Ca(this->m_sSocketName.c_str());
	AfxMessageBox(Ca);

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
	
	if (!(this->m_sSocketName.compare( "ServerSocket 1" )))
	{
		static int nMessageNumber = 51;
		char carrSendBack[100];
		sprintf_s(carrSendBack, "Test-message number... %d", nMessageNumber);
		Send(carrSendBack, sizeof(carrSendBack));
	}
	else
	{
		::AfxMessageBox(L" not sending back anything yet");

	}

	//::AfxMessageBox(L"about to call onMessageReceived");

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//OnMessageReceived(arrBuffer);
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		// Now send a message back:
	// - Use a local static counter of messages, this is just for debugging:
	/*static int nMessageNumber = 0;
	if (nMessageNumber < 2)
	{
		nMessageNumber++;
		char carrSendBack[100];
		sprintf_s(carrSendBack, "Test-message number... %d", nMessageNumber);
		char carrMessageBox[BUFFER_LENGTH];
		sprintf_s(carrMessageBox, BUFFER_LENGTH, "%s %s", "Now sending...", carrSendBack);
		::MessageBoxA(AfxGetMainWnd()->m_hWnd, carrMessageBox, "OnReceive()", 0);
		Send(carrSendBack, sizeof(carrSendBack));
	}*/
}


void CMefathimSocket::OnMessageReceived(char pBuffer[])
{
		AfxMessageBox(L"entered OnMessageReceived");
		std::string a(pBuffer);
		CString Ca(a.c_str());
		AfxMessageBox(Ca);


	// 0. Get message type from buffer (notice that in all messsages, first two
	//    members are the GUID and then type (see IMessage class) ie. this will move pointer over to point at type variable in buffer array. 
	//This explains the folowing line:
	/*int type = *(int*)(pBuffer + sizeof(int));//move pointer over till reach type;cast to pointer to enum;get content of pointer

		auto s = std::to_string(type);
		CString Cs(s.c_str());
		::AfxMessageBox(L"type" +Cs);
	// 1. Create Message object by the type.
	IMessage* pMessage = m_pMessageFactory->CreateMessage(type); // 'pMessage' : Message obj

		AfxMessageBox(L"created messg object with factory");
		AfxMessageBox(L"about to call frombuffer ");


	pMessage->FromBuffer(pBuffer);// Calling mssg obj.'s FromBuffer method which Fills the message obj.'s fields 

		AfxMessageBox(L"exited frombuffer ");

		int z = pMessage->GetGuid();
		int x = pMessage->GetType();
		int c = pMessage->Size();

		auto sz = std::to_string(z);
		auto sx = std::to_string(x);
		auto sc = std::to_string(c);
		CString Cz(sz.c_str());
		CString Cx(sx.c_str());
		CString Cc(sc.c_str());

		::AfxMessageBox(L"type  " + Cz + L" " + Cx + L" " + Cc);

	// 2. Call callback
	void* callbacks = m_hashCallbacks[type]; // 'callbacks' : specific callback func

		AfxMessageBox(L"exited callbacks ");

		//>>>>>>>>> PROGRAM CRASHES HERE...SERVER DOS NOT HAVE A MAP OF CALLBACKS YET
	((void(*)(IMessage*))callbacks)(pMessage);
	/*for (int i = 0; i < callbacks.GetSize(); i++)
	{
		void* pfnCallback = callbacks[i];
		(*pfnCallback)(pMessage);// Calling the callback func and passing in message obj. as an argument; the callbacks simply push the message into a queue to be handled by main thread
	}*/
		AfxMessageBox(L"called callback ");

}
	
int CMefathimSocket::SendTextMessage(/*std::string s*/const TTextMessage& text)
{
		// Buffer to hold message details which are being sent 
		char cBuffer[100];
		//Create a message object to fill and call its ToBuffer() method
		MTextMessage* pMTextmessage = new MTextMessage(33, text);
		
			AfxMessageBox(pMTextmessage->GetTextMessage().m_sText);
			AfxMessageBox(pMTextmessage->GetTextMessage().m_userDestination.sName);

			//strcpy_s(cBuffer, s.c_str());
	    // Filling the Buffer with the message objects details
		pMTextmessage->ToBuffer(cBuffer);
		//Sending the Buffer to server
		int nRet = CAsyncSocket::Send(cBuffer, sizeof(cBuffer));
		//TODO: define meaninful values for return values
		return nRet;
};

	
void CMefathimSocket::OnClose(int nErrorCode)
{
	AfxMessageBox(L"Wow - connection closed...");
}