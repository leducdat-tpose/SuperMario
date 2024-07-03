#pragma once

#include <vector>
#include <string>

#include "Game.h"
#include "GameObject.h"

using namespace std;

class CDataManager: public CGameObject
{
private:
	CGame* game = CGame::GetInstance();

	string information;

	int id_scene;
	int coin;
	int life;
	int point;
	int time;

public:
	CDataManager(){}
	~CDataManager(){}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Init(){}
	void Render();
};