#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.03f

#pragma region BBOX
#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 16
#pragma endregion

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200

#pragma region ANIMATION_ID
#define KOOPAS_ANI_WALKING_LEFT 10000
#define KOOPAS_ANI_WALKING_RIGHT 10001
#define KOOPAS_ANI_DIE 10002
#pragma endregion

class CKoopas : public CGameObject
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
	CKoopas(float x, float y);
	virtual void SetState(int state);
};