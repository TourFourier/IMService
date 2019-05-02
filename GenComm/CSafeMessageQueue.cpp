#include "stdafx.h"
#include "IMessage.h"
#include <queue>
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
	IMessage* retVal;
	EnterCriticalSection(&m_cs);
	retVal = m_qMessageQueue.front();
	m_qMessageQueue.pop();
	LeaveCriticalSection(&m_cs);
	return retVal;
}
