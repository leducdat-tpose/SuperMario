#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.03f
#define PARAKOOPAS_FLY_SPEED 0.5f
#define PARAKOOPAS_FLY_DELAY_TIME 5000

#pragma region BBOX
#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_HIDE_BBOX_WIDTH 16
#define KOOPAS_HIDE_BBOX_HEIGHT 16
#define KOOPAS_BBOX_HEIGHT_DIE 16
#pragma endregion

#define KOOPAS_STATE_WALKING_RIGHT 100
#define KOOPAS_STATE_WALKING_LEFT 200
#define KOOPAS_STATE_HIDE 300
#define KOOPAS_STATE_HIDE_FLIP 400
#define KOOPAS_STATE_DIE 500
#define PARAKOOPAS_STATE_WALKING_RIGHT 600
#define PARAKOOPAS_STATE_WALKING_LEFT 700
#define PARAKOOPAS_STATE_FLY_LEFT 800
#define KOOPAS_STATE_HIDE_MOVING 900
#define PARAKOOPAS_STATE_FLY_RIGHT 1000


#pragma region ANIMATION_ID
#define KOOPAS_ANI_WALKING_LEFT 12000
#define KOOPAS_ANI_WALKING_RIGHT 12001
#define KOOPAS_ANI_HIDE 12002
#define KOOPAS_ANI_HIDE_MOVING 12003
#define KOOPAS_ANI_DIE 12004
#define PARAKOOPAS_ANI_WALKING_LEFT 12005
#define PARAKOOPAS_ANI_WALKING_RIGHT 12006
#define PARAKOOPAS_ANI_FLY_LEFT 12007
#define KOOPAS_ANI_HIDE_FLIP 12008
#define PARAKOOPAS_ANI_FLY_RIGHT 12009

#pragma endregion

class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;
	bool specialAbility;
	bool isFly;
	ULONGLONG fly_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CKoopas(float x, float y, bool specialAbility);
	virtual void SetState(int state);
	virtual void SetSpecialAbility(bool specialAbility);
	void StartFly() { isFly = true; fly_start = GetTickCount64(); }
};