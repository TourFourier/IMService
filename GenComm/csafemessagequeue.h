#pragma once
#include <queue>
#include "IMessage.h"
using namespace std;

class  CSafeMessageQueue
{
	CRITICAL_SECTION m_cs;
	queue<IMessage*> m_qMessageQueue;
public:
	CSafeMessageQueue();
	~CSafeMessageQueue();

	void Push(IMessage* message);
	IMessage* Pop();
	bool Empty();
};

