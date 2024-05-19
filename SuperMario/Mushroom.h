#pragma once
#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.002f 
#define MUSHROOM_WALKING_SPEED 0.03f

#define MUSHROOM_BBOX_WIDTH 15
#define MUSHROOM_BBOX_HEIGHT 15


#define MUSHROOM_STATE_IDLE 100
#define MUSHROOM_STATE_WALKING 200
#define MUSHROOM_STATE_DIE 300

#define ID_ANI_MUSHROOM 15000

class CMushroom : public CGameObject
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
	CMushroom(float x, float y);
	virtual void SetState(int state);
};