#pragma once
class CGroupsManager_Client :
	public IGroupsManager
{
public:
	CGroupsManager_Client();
	~CGroupsManager_Client();

	virtual void CreateUpdateGroup(TGroup& group);
	//virtual const TGroup& FindGroup(int guid);
	virtual void DeleteGroup(TGroup& group);
};

