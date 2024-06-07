#pragma once
#include "GameObject.h"

#define SUPERLEAF_GRAVITY 0.001f
#define SUPERLEAF_SPEED 0.04f
#define SUPERLEAF_TIME_TURN_STATE 500

#define SUPERLEAF_BBOX_WIDTH 16
#define SUPERLEAF_BBOX_HEIGHT 16

#define ID_ANI_SUPERLEAF 18000

#define SUPERLEAF_STATE_FALL_LEFT 100
#define SUPERLEAF_STATE_FALL_RIGHT 200


class CSuperLeaf : public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG fall_start;
	bool isCollidable = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return !isCollidable; };
	virtual int IsBlocking() { return 0; };
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CSuperLeaf(float x, float y);
	void SetState(int state);
};