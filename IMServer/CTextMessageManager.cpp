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
#include "CTextMessageManager.h"

 CTextMessageManager* CTextMessageManager::s_pTextMessagesManager = NULL; 

CTextMessageManager::CTextMessageManager()
{
}


CTextMessageManager::~CTextMessageManager()
{
}

void CTextMessageManager::PublishTextMessage(TTextMessage text)
{
	
}