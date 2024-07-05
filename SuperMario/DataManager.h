#pragma once
#include <string>
#include <iostream>
#include <vector>

#include "debug.h"
#include "PlayScene.h"

#define GADGET_NONE 0
#define GADGET_MUSHROOM 10
#define GADGET_FLOWER 20
#define GADGET_STAR 30

class CDataManager
{
private:
	bool isInit;
	static CDataManager* instance;
	vector<int> gadgets;
	int id_world;
	int coin;
	int life;
	int point;
	int time;

	CDataManager();
	~CDataManager()
	{
	}
public:
	static CDataManager* getInstance()
	{
		if (instance == NULL)
		{
			DebugOut(L"[INFO]Creating DataManager.\n");
			instance = new CDataManager;
		}
		return instance;
	}

	static void Release()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void startInit()
	{
		if (isInit == true) return;
		isInit = true;
	}

	void Unload()
	{
		isInit = false;
	}

	void GetData(int& id_world, int& coin, int& life, int& point, vector<int>& gadgets);
	void SaveData(int coin, int life, int point, int time);
	void UpdateIdWorld(int id_world) { this->id_world = id_world; }
	void AddPoint(int point) { this->point += point; }
	void AddCoin(int coin) { this->coin += coin; }
	void AddLife(int life) { this->life += life; }
	void UpdatePlayTime(int time) { this->time = time; }

};
typedef CDataManager* LPDATAMANAGER;