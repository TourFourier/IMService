#pragma once
#include "ICommunication.h"
#include "afxsock.h"
#include <atlstr.h>
#include "CMefathimSocket.h"

class CCommunication_TCP :
	public ICommunication
{
protected:
	CMefathimSocket *m_socket;
public:
	CCommunication_TCP(IMessageFactory* pMessageFactory, CString sSocketName);
	~CCommunication_TCP();


	// <<<<<<<<<<<Implement ICommunication functions.
	//virtual bool Connect(CString sConnectionDetails);//put in constructor of 
	//virtual bool Disconnect();
	//virtual bool SendingMessage(IMessage* pMessage);


	// This function is to be called by network card. 
	// It looks for the synch-word, then build up the buffer by the length field, 
	// and eventually calls correct handler by the message type, delivering it the message buffer:
	void OnMessageReceived(char* pBuffer);

};

