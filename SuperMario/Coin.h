#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "LuckyBox.h"

#define ID_ANI_COIN 11000

#define COIN_GRAVITY	0.014f
#define COIN_SPEED		0.02f
#define TIME_FLY_UP		200

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

class CCoin : public CGameObject {
private:
	void OnCollisionWithLuckybox(LPCOLLISIONEVENT e);
protected:
	float ax;
	float ay;
	ULONGLONG fly_start;
	bool fromLuckyBox;
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual int IsCollidable() { return 1; };
public:
	CCoin(float x, float y, bool fromLuckyBox = false);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; };
};