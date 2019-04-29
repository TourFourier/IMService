#pragma once

#include <synchapi.h>
#include<queue>
using namespace std;

class  CSafeMessageQueue
{
public:
	CRITICAL_SECTION m_cs;
	std::queue<IMessage*> m_qMessageQueue;
	CSafeMessageQueue();
	~CSafeMessageQueue();

	void Push(IMessage* message);
	IMessage* Pop();
};

