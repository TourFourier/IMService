#include "stdafx.h"
#include <synchapi.h>
#include <queue>
#include "IMessage.h"
#include "CSafeMessageQueue.h"
//#include <Windows.h>


CSafeMessageQueue::CSafeMessageQueue()
{
	InitializeCriticalSection(&m_cs);
}


CSafeMessageQueue::~CSafeMessageQueue()
{
	DeleteCriticalSection(&m_cs);
}


void CSafeMessageQueue::Push(IMessage* message)
{
	EnterCriticalSection(&m_cs);
	m_qMessageQueue.push(message);
	LeaveCriticalSection(&m_cs);
}

IMessage* CSafeMessageQueue::Pop()
{
		IMessage* retVal = nullptr;
	if (!m_qMessageQueue.empty())
	{
		EnterCriticalSection(&m_cs);
		retVal = m_qMessageQueue.front();
		m_qMessageQueue.pop();
		LeaveCriticalSection(&m_cs);
		return retVal;
	}
	return retVal;
}
