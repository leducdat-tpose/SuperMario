#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "LuckyBox.h"

#define ID_ANI_COIN 11000

#define COIN_GRAVITY	0.002f
#define COIN_SPEED		0.002f
#define TIME_FLY_UP		750

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

class CCoin : public CGameObject {
	
protected:
	float ax;
	float ay;
	float fly_start;
	bool fromLuckyBox;
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithLuckybox(LPCOLLISIONEVENT e);
public:
	CCoin(float x, float y, bool fromLuckyBox = false);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};