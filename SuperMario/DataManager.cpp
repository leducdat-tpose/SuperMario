#include "DataManager.h"

CDataManager* CDataManager::instance = NULL;

CDataManager::CDataManager()
{
	isInit = false;
	id_scene = 1;
	coin = 1;
	life = 4;
	point = 78;
	time = 157;
}

void CDataManager::GetData(int& id_scene, int& coin, int& life, int& point, int& time)
{
	id_scene = this->id_scene;
	coin = this->coin;
	life = this->life;
	point = this->point;
	time = this->time;
}