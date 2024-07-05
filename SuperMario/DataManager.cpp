#include "DataManager.h"

CDataManager* CDataManager::instance = NULL;

CDataManager::CDataManager()
{
	isInit = false;
	id_world = 1;
	coin = 0;
	life = 4;
	point = 0;
	time = 157;
}

void CDataManager::GetData(int& id_world, int& coin, int& life, int& point, int& time)
{
	id_world = this->id_world;
	coin = this->coin;
	life = this->life;
	point = this->point;
	time = this->time;
}

void CDataManager::SaveData(int coin, int life, int point, int time)
{
	this->coin = coin;
	this->life = life;
	this->point = point;
	this->time = time;
}