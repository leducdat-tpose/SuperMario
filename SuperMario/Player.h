#pragma once
#include <vector>
#include <string>

#include "Game.h"
#include "PlayScene.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

using namespace std;

class CPlayer: public CGameObject
{
	CGame* game = CGame::GetInstance();
	CPlayScene* playScene = (LPPLAYSCENE)game->GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)playScene->GetPlayer();
	CSprites* sprites = CSprites::GetInstance();
	LPSPRITE sprite;
	string information;
	float marioSpeed_sub;
	float posHudX;
	float posHudY;

	int id_world;
	int coin;
	int life;
	int point;
	int time;

	vector<LPSPRITE> marioSpeed;
	vector<LPSPRITE> gadget;

public:
	CPlayer(float x, float y);
	~CPlayer();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void UpdateIndex();
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom){}
};