#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "HiddenButton.h"
#include "PlayScene.h"
#include "Coin.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_GOLD_BRICK 10100
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16
#define BRICK_CHANGE_TO_COIN_TIME 10000

#define TYPE_NORMAL_BRICK 0
#define TYPE_GOLD_BRICK 100

class CBrick : public CGameObject {
	int type;
	bool isChangeToCoin;
	ULONGLONG change_to_coin_start;
	LPGAMEOBJECT coin;
public:
	CBrick(float x, float y, int type = TYPE_NORMAL_BRICK) : CGameObject(x, y)
	{
		this->type = type;
		this->change_to_coin_start = -1;
		this->isChangeToCoin = false;
		this->coin = NULL;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void ChangeToCoin();
	void ChangeBackToBrick();
	int GetType() const{
		return this->type;
	}
};