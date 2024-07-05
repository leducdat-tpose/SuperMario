#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Coin.h"
#include "Mushroom.h"
#include "SuperLeaf.h"
#include "PlayScene.h"

#define LUCKYBOX_DEFLECT_GRAVITY 0.0005f
#define LUCKYBOX_DEFLECT_SPEED 0.07f

#define ID_ANI_LUCKYBOX 13000
#define ID_ANI_LUCKYBOX_COLLECTED 13001
#define LUCKYBOX_WIDTH 16
#define LUCKYBOX_BBOX_WIDTH 16
#define LUCKYBOX_BBOX_HEIGHT 16

#define LUCKYBOX_STATE_NORMAL 100
#define LUCKYBOX_STATE_DEFLECT 200

#define LUCKYBOX_MOVING_Y 5.0f
#define TIME_TO_UP_DOWN 500




class CLuckyBox : public CGameObject {
private:
	float ay;
	float initY;
	ULONGLONG fall_start;
	bool isCollected;
	int objectSpawned;
public:
	CLuckyBox(float x, float y, int objectSpawned = OBJECT_TYPE_COIN) : CGameObject(x, y) {
		this->fall_start = -1;
		this->initY = y;
		this->isCollected = false;
		this->objectSpawned = objectSpawned;
		this->ay = 0;
		SetState(LUCKYBOX_STATE_NORMAL);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e) {};
	void SpawnObject();
	void SetIsCollected(bool isCollected);
	void SetState(int state);
	bool GetIsCollected();
	void SetTypeObjectSpawned(int objectSpawned) { this->objectSpawned = objectSpawned; }
	int GetTypeObjectSpawned() const { return objectSpawned; }
};