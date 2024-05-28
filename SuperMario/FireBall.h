#pragma once
#include "GameObject.h"

#define FIREBALL_TIME_ENABLE 7000

#define FIREBALL_BBOX_WIDTH 8
#define FIREBALL_BBOX_HEIGHT 8

#define ID_ANI_FIREBALL 17000

class CFireBall: public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG disable_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CFireBall(float x, float y);
	virtual void SetState(int state);
};