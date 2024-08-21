#include "DataManager.h"

CDataManager* CDataManager::instance = NULL;

CDataManager::CDataManager()
{
	isInit = false;
	id_world = 1;
	ResetData();
}

void CDataManager::ResetData()
{
	coin = DEFAULT_COIN;
	life = DEFAULT_LIFE;
	point = DEFAULT_POINT;
	time = DEFAULT_TIME;
	gadgets.clear();
	gadgets.push_back(GADGET_NONE);
	gadgets.push_back(GADGET_NONE);
	gadgets.push_back(GADGET_NONE);
	changeAlert = 0;
	finishStageOverWorld_1[1] = false;
}

void CDataManager::GetData(int& id_world, int& coin, int& life, int& point, vector<int>& gadgets)
{
	id_world = this->id_world;
	coin = this->coin;
	life = this->life;
	point = this->point;
	gadgets = this->gadgets;
}

void CDataManager::SaveData(int coin, int life, int point, int time)
{
	this->coin = coin;
	this->life = life;
	this->point = point;
	this->time = time;
}

void CDataManager::UpdateGadget(int index)
{
	for (int i = 0; i < gadgets.size(); i++)
	{
		if (gadgets[i] == GADGET_NONE)
		{
			gadgets[i] = index;
			changeAlert = 1;
			return;
		}
	}
}