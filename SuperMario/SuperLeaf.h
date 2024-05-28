#pragma once
#include "GameObject.h"

#define SUPERLEAF_BBOX_WIDTH 16
#define SUPERLEAF_BBOX_HEIGHT 16

#define ID_ANI_SUPERLEAF 18000

class CSuperLeaf : public CGameObject
{
protected:
	float ax;
	float ay;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CSuperLeaf(float x, float y);
	virtual void SetState(int state);
};