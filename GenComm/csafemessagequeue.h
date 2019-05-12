#pragma once
#include <queue>
#include "IMessage.h"
using namespace std;

class  CSafeMessageQueue
{
public:
	CRITICAL_SECTION m_cs;
	queue<IMessage*> m_qMessageQueue;
	CSafeMessageQueue();
	~CSafeMessageQueue();

	void Push(IMessage* message);
	IMessage* Pop();
};

