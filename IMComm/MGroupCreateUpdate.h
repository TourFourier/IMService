#pragma once
class MGroupCreateUpdate :
	public IMessage
{
private:
	TGroup m_group;
public:
	MGroupCreateUpdate();
	MGroupCreateUpdate(TGroup group);
   ~MGroupCreateUpdate();
	const TGroup& GetGroup() { return m_group; }

	// Implement IMessage functions.
   virtual int Size();
   virtual bool ToBuffer();
   virtual bool FromBuffer(char* pBuffer, int nLength);
};

