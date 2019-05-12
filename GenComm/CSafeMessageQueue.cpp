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
		EnterCriticalSection(&m_cs);
	if (!m_qMessageQueue.empty())
	{
		retVal = m_qMessageQueue.front();
		m_qMessageQueue.pop();
		LeaveCriticalSection(&m_cs);
		return retVal;
	}
	return retVal;
}

bool CSafeMessageQueue::Empty()
{
	EnterCriticalSection(&m_cs);
	if (!m_qMessageQueue.empty())
	{
		return false;
	}
	return true;
	LeaveCriticalSection(&m_cs);
}