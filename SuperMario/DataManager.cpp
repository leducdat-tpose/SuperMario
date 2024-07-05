#include "DataManager.h"

CDataManager* CDataManager::instance = NULL;

CDataManager::CDataManager()
{
	isInit = false;
	id_world = 1;
	coin = 0;
	life = 3;
	point = 0;
	time = 300;
	gadgets.push_back(GADGET_MUSHROOM);
	gadgets.push_back(GADGET_FLOWER);
	gadgets.push_back(GADGET_STAR);
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