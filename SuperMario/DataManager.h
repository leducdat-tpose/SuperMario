#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "debug.h"
#include "PlayScene.h"

#define GADGET_NONE 0
#define GADGET_MUSHROOM 10
#define GADGET_FLOWER 20
#define GADGET_STAR 30

#define DEFAULT_LIFE 1
#define DEFAULT_COIN 0
#define DEFAULT_TIME 300
#define DEFAULT_POINT 0


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
	unordered_map<int, bool> finishStageOverWorld_1;

	CDataManager();
	~CDataManager()
	{
	}
public:
	int changeAlert;
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
	void ResetData();
	void UpdateIdWorld(int id_world) { this->id_world = id_world; }
	void AddPoint(int point) { this->point += point; }
	void AddCoin(int coin) { this->coin += coin; }
	void AddLife(int life) { 
		this->life += life;
		if (this->life < 0)
		{
			CGame::GetInstance()->SetIsGameOver(1);
			this->life = 0;
		}
	}
	void UpdatePlayTime(int time) { this->time = time; }
	void UpdateGadget(int index);
	bool getIsFinishStage(int idScene)
	{
		return finishStageOverWorld_1[idScene];
	}
	int getLifeIndex() const
	{
		return this->life;
	}
	void SetIsFinishStage(int idScene, bool isFinish)
	{
		finishStageOverWorld_1[idScene] = isFinish;
	}
};
typedef CDataManager* LPDATAMANAGER;