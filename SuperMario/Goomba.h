#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f
#define PARAGOOMBA_FLY_SPEED 0.5f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7
#define PARAGOOMBA_BBOX_WIDTH 19
#define PARAGOOMBA_BBOX_HEIGHT 18
#define PARAGOOMBA_BBOX_WIDTH_FLY 19
#define PARAGOOMBA_BBOX_HEIGHT_FLY 23

#define GOOMBA_DIE_TIMEOUT 500
#define PARAGOOMBA_FLY_DELAY_TIME 2500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define PARAGOOMBA_STATE_WALKING 300
#define PARAGOOMBA_STATE_FLY 400


#pragma region ID_ANIMATION
//Normal
#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
//Special
#define ID_ANI_PARAGOOMBA_WALKING 14000
#define ID_ANI_PARAGOOMBA_FLY 14001
#pragma endregion

class CGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	bool specialAbility;
	bool isFly;
	ULONGLONG die_start;
	ULONGLONG fly_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	
public:
	CGoomba(float x, float y, bool specialAbility);
	virtual void SetState(int state);
	virtual void SetSpecialAbility(bool specialAbility);
	void StartFly() { isFly = true; fly_start = GetTickCount64(); }
};