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

//static const int SIZE_GUID = sizeof(int);
//static const int SIZE_INT = sizeof(int);


struct TUser
{
	int guid; // "Global unique id"  a unique id that identifies this user globally
	CString sName;
	CString sPhoneNumber;
	char* ToBuffer(char* pBuffer)
	{
		int guidLength = sizeof(guid);
		int nameLength = sName.GetLength() * 2;
		int phoneNumberLength = sPhoneNumber.GetLength() * 2;

		*(int*)pBuffer = guidLength;
		*(int*)(pBuffer + SIZE_INT) = guid;
		*(int*)(pBuffer + SIZE_INT + SIZE_GUID) = nameLength;
		memcpy((pBuffer + SIZE_INT + SIZE_GUID + SIZE_INT), sName.GetBuffer(), nameLength);
		*(int*)(pBuffer + SIZE_INT + SIZE_GUID + SIZE_INT + nameLength) = phoneNumberLength;
		memcpy((pBuffer + SIZE_INT + SIZE_GUID + SIZE_INT + nameLength + SIZE_INT), sPhoneNumber.GetBuffer(), phoneNumberLength);
		pBuffer = (pBuffer + SIZE_INT + SIZE_GUID + SIZE_INT + nameLength + SIZE_INT + phoneNumberLength);

		return pBuffer;
	}

	char* FromBuffer(char* pBuffer)
	{
		int sizeOfNext;// the size of this variable itself is SIZE_INT

		sizeOfNext = *(int*)pBuffer;
		guid = *(int*)pBuffer + sizeOfNext;
		sizeOfNext = *(int*)pBuffer + sizeOfNext + SIZE_GUID;
		// sizeOfNext's value is probably no longer same size as an int therefor move pointer SIZE_INT instead of sizeOfNext
		pBuffer = (pBuffer + SIZE_INT + SIZE_GUID + SIZE_INT);
		for (int i = 0; i < sizeOfNext; i++)
		{
			sName += *(CString*)(pBuffer + i);
		}
		// Move pointer over to end of sName
		pBuffer = (pBuffer + sizeOfNext);
		// Get size of phone number
		sizeOfNext = *(int*)pBuffer;
		// Move pointer over to point at ohone number so loop can be kept simple
		pBuffer = (pBuffer + SIZE_INT);
		for (int i = 0; i < sizeOfNext; i++)
		{
			sPhoneNumber += *(CString*)(pBuffer + i);
		}
		pBuffer = (pBuffer + sizeOfNext);

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
		pBuffer = (pBuffer + SIZE_GUID);
		for (auto it = nlistUsers.begin(); it != nlistUsers.end(); ++it)
		{
			pBuffer = (it->ToBuffer(pBuffer));
		}
		return pBuffer;
	}

	void FromBuffer(char* pBuffer)
	{
		int sizeOfNext;// the size of this variable itself is SIZE_INT

		sizeOfNext = *(int*)pBuffer;
		guid = *(int*)pBuffer + sizeOfNext;
		pBuffer = pBuffer + SIZE_INT + SIZE_GUID;
		// sizeOfNext's value is probably no longer same size as an int therefor move pointer SIZE_INT instead of sizeOfNext
		for (auto it = nlistUsers.begin(); it != nlistUsers.end(); ++it)
		{
			pBuffer = (it->FromBuffer(pBuffer));
		}

		return;
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
		
		int textLength = m_sText.GetLength() * 2;
		*(int*)pBuffer = textLength;
		// Add text message(CString) to the buffer
		memcpy((pBuffer + SIZE_INT), m_sText.GetBuffer(), textLength);
		// Move buffer pointer over and pass on the buffer to TUser struct to deal with
		pBuffer = pBuffer + SIZE_INT + textLength;
		pBuffer = m_userDestination.ToBuffer(pBuffer);
		pBuffer = m_groupDestination.ToBuffer(pBuffer);
	}

	void FromBuffer(char* pBuffer)
	{
		int sizeOfNext;// the size of this variable itself is SIZE_INT
		
		sizeOfNext = *(int*)pBuffer;
		//m_sText = *(CString*)(pBuffer + sizeOfNext);
		pBuffer = (pBuffer + SIZE_INT);
		for (int i = 0; i < sizeOfNext; i++)
		{
			m_sText += *(CString*)(pBuffer + i);
		}
		pBuffer = (pBuffer + sizeOfNext);
		pBuffer = m_userDestination.FromBuffer(pBuffer);
		m_groupDestination.FromBuffer(pBuffer);
	}

};

enum EMessageType
{
	TEXT_MESSAGE,
	CREATE_UPDATE_GROUP,
	ACKNOWLEDGE 
};


