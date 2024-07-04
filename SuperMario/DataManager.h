#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "debug.h"

class CDataManager
{
	static CDataManager* instance;
	/*int id_scene;
	int coin;
	int life;
	int point;
	int time;*/

	CDataManager() {}
	~CDataManager() {}
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
};
typedef CDataManager* LPDATAMANAGER;