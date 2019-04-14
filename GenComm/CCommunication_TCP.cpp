#include "stdafx.h"
#include "afxsock.h"
#include <atlstr.h>
//xxxxxxxxxxxxxxx#include "constants.h"
#include "IMessage.h"
#include "IMessageFactory.h"
#include "ICommunication.h"
#include "CMefathimSocket.h"

#include "CCommunication_TCP.h"


CCommunication_TCP::CCommunication_TCP(IMessageFactory* pMessageFactory, CString sSocketName) :ICommunication(pMessageFactory)
{
	m_socket = new CMefathimSocket(sSocketName);
}


CCommunication_TCP::~CCommunication_TCP()
{
	delete m_socket;
}

void CCommunication_TCP::OnMessageReceived(char* pBuffer)
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


// methods that belong to ASyncSocket and are deffined. I have only to call them
//bool CCommunication_TCP::Connect(CString sConnectionDetails) {}
//bool CCommunication_TCP::Disconnect() {}
//bool CCommunication_TCP::SendingMessage(IMessage* pMessage) {}