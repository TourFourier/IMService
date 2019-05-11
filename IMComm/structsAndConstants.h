#pragma once

#include <atlstr.h>
#include <rpc.h>
#include <vector>

/* //Had linking problems with STringToBuffer()

char* StringToBuffer(char* pBuffer, CString str)
{
	memcpy(pBuffer, str.GetBuffer(), str.GetLength() * 2);
	pBuffer = pBuffer + (str.GetLength() * 2);
	return pBuffer;
}


// Represents one user
struct TUser 
{
	int guid; // "Global unique id"  a unique id that identifies this user globally
	CString sName;
	CString sPhoneNumber;
	char* ToBuffer(char* pBuffer)
	{
		//char* temp;

		*(int*)pBuffer = guid;
		pBuffer = StringToBuffer((pBuffer + sizeof(int)), sName);
		pBuffer = StringToBuffer(pBuffer, sPhoneNumber);

		return pBuffer;

		//memcpy((pBuffer + sizeof(int)), sName.GetBuffer(), sName.GetLength() * 2);
		//memcpy((pBuffer + sizeof(int)+(sName.GetLength() * 2)), sPhoneNumber.GetBuffer(), sPhoneNumber.GetLength() * 2);
		//pBuffer = (pBuffer + sizeof(int) + (sName.GetLength() * 2) + (sPhoneNumber.GetLength() * 2));

		//*(CString*)(pBuffer + sizeof(int)) = sName;
		//*(CString*)(pBuffer + sizeof(int) + sizeof(sName)) = sPhoneNumber;
		//pBuffer = (pBuffer + sizeof(int) + sizeof(sName) + sizeof(sPhoneNumber));
	}
};


// Represents a list of users
struct TGroup 
{
	int guid;
	// Simple implementation: For every change in group we send all numbers.
	std::vector<TUser> nlistUsers;
	char* ToBuffer(char* pBuffer)
	{
		//char* p_temp = pBuffer;
		*(int*)pBuffer = guid;
		pBuffer = (pBuffer + sizeof(int));
		for (auto it = nlistUsers.begin(); it != nlistUsers.end(); ++it)
		{
			pBuffer = (it->ToBuffer(pBuffer));
		}
		return pBuffer;
	}
};


// Represents one message
struct TTextMessage 
{
	CString m_sText; // message to send
	TUser m_userDestination; // to which user we are sending, in event we are sending to individual user/s
	TGroup m_groupDestination; // to which group, in event where sending to whole group 
	void ToBuffer(char* pBuffer)
	{

		// CString is not a primitive type and therefor we can't typecast and simply copy, rather we must access the 
		//buffer containing the CString; the string is in unicode and therefor is alloted 2 bytes for each letter;
		// GetBuffer() returns the number of letters and therfor we must multi by 2 to get the bytes.
		pBuffer = StringToBuffer(pBuffer , m_sText);
		pBuffer = m_userDestination.ToBuffer(pBuffer);
		m_groupDestination.ToBuffer(pBuffer);

		//memcpy(pBuffer,m_sText.GetBuffer(), m_sText.GetLength()*2);
		//pBuffer = pBuffer + (m_sText.GetLength() * 2);
	}
};
*/
struct TUser
{
	int guid; // "Global unique id"  a unique id that identifies this user globally
	CString sName;
	CString sPhoneNumber;
	char* ToBuffer(char* pBuffer)
	{
		*(int*)pBuffer = guid;
		//pBuffer = StringToBuffer((pBuffer + sizeof(int)), sName);
		//pBuffer = StringToBuffer(pBuffer, sPhoneNumber);

		memcpy((pBuffer + sizeof(int)), sName.GetBuffer(), sName.GetLength() * 2);
		memcpy((pBuffer + sizeof(int) + (sName.GetLength() * 2)), sPhoneNumber.GetBuffer(), sPhoneNumber.GetLength() * 2);
		pBuffer = (pBuffer + sizeof(int) + (sName.GetLength() * 2) + (sPhoneNumber.GetLength() * 2));

		return pBuffer;
	}
};


// Represents a list of users
struct TGroup
{
	int guid;
	// Simple implementation: For every change in group we send all numbers.
	std::vector<TUser> nlistUsers;
	char* ToBuffer(char* pBuffer)
	{
		//char* p_temp = pBuffer;
		*(int*)pBuffer = guid;
		pBuffer = (pBuffer + sizeof(int));
		for (auto it = nlistUsers.begin(); it != nlistUsers.end(); ++it)
		{
			pBuffer = (it->ToBuffer(pBuffer));
		}
		return pBuffer;
	}
};


// Represents one message
struct TTextMessage
{
	CString m_sText; // message to send
	TUser m_userDestination; // to which user we are sending, in event we are sending to individual user/s
	TGroup m_groupDestination; // to which group, in event where sending to whole group 
	void ToBuffer(char* pBuffer)
	{
		// CString is not a primitive type and therefor we can't typecast and simply copy, rather we must access the 
		//buffer containing the CString; the string is in unicode and therefor is alloted 2 bytes for each letter;
		// GetBuffer() returns the number of letters and therfor we must multi by 2 to get the bytes.
		//pBuffer = StringToBuffer(pBuffer, m_sText);
		memcpy(pBuffer, m_sText.GetBuffer(), m_sText.GetLength() * 2);
		pBuffer = pBuffer + (m_sText.GetLength() * 2);
		pBuffer = m_userDestination.ToBuffer(pBuffer);
		pBuffer = m_groupDestination.ToBuffer(pBuffer);
	}
};

enum EMessageType
{
	TEXT_MESSAGE,
	CREATE_UPDATE_GROUP,
	ACKNOWLEDGE 
};


