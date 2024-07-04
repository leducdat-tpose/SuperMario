#pragma once
#include <vector>
#include <string>

#include "Game.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

using namespace std;

class CPlayer: public CGameObject
{
	CGame* game = CGame::GetInstance();
	LPSPRITE sprite;
	string information;

	int id_scene;
	int coin;
	int life;
	int point;
	int time;
public:
	CPlayer(float x, float y);
	~CPlayer();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom){}
};