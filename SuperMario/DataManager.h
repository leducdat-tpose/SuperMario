#pragma once
#include <string>
#include <iostream>

#include "debug.h"
#include "PlayScene.h"

class CDataManager
{
private:
	bool isInit;
	static CDataManager* instance;

	int id_scene;
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

	void GetData(int& id_scene, int& coin, int& life, int& point, int& time);
};
typedef CDataManager* LPDATAMANAGER;