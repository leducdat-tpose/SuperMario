#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Coin.h"
#include "Mushroom.h"
#include "SuperLeaf.h"
#include "PlayScene.h"

#define ID_ANI_LUCKYBOX 13000
#define ID_ANI_LUCKYBOX_COLLECTED 13001
#define LUCKYBOX_WIDTH 16
#define LUCKYBOX_BBOX_WIDTH 16
#define LUCKYBOX_BBOX_HEIGHT 16

#define LUCKYBOX_COLLECTED_STATE_UP 100
#define LUCKYBOX_COLLECTED_STATE_DOWN 200
#define LUCKYBOX_NORNMAL_STATE 300

#define LUCKYBOX_MOVING_Y 5.0f
#define TIME_TO_UP_DOWN 500


class CLuckyBox : public CGameObject {
private:
	float upDown_start;
	bool isCollected;
	int objectSpawned;
public:
	CLuckyBox(float x, float y, int objectSpawned = OBJECT_TYPE_COIN) : CGameObject(x, y) {
		this->upDown_start = 0;
		this->isCollected = false;
		this->objectSpawned = objectSpawned;
		CGameObject::SetState(LUCKYBOX_NORNMAL_STATE);
	}
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnCollisionWith(LPCOLLISIONEVENT e) {};
	void SpawnObject();
	void SetIsCollected(bool isCollected);
	void SetState(int state);
	bool GetIsCollected();
	void SetTypeObjectSpawned(int objectSpawned) { this->objectSpawned = objectSpawned; }
	int GetTypeObjectSpawned() { return objectSpawned; }
};