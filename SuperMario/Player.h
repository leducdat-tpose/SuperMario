#pragma once
#include <vector>
#include <string>
#include <list>

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
	LPSPRITE pauseGameSprite;
	string information;
	float marioSpeed_sub;
	float posHudX;
	float posHudY;

	int id_world;
	int coin;
	int life;
	int point;
	int time;
	int changeAlert;
	vector<int> gadgetsList;
	vector<LPSPRITE> marioSpeed;
	vector<LPSPRITE> gadgetsSprite;

public:
	CPlayer(float x, float y);
	~CPlayer();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void UpdateIndex();
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom){}
};