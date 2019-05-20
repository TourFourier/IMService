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




CMefathimSocket::CMefathimSocket(IMessageFactory* pMessageFactory, std::string sSocketName) :CAsyncSocket()
{
	m_pMessageFactory = pMessageFactory;
	m_sSocketName = sSocketName;
}


CMefathimSocket::~CMefathimSocket()
{
}







// This function is called when the client is connected (V):
void CMefathimSocket::OnConnect(int nErrorCode)
{
		CString sName(this->m_sSocketName.c_str());
		::AfxMessageBox(sName + L" is connected to the server" );
		
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