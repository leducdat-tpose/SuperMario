#pragma once
#include "GameObject.h"
#include "FireBall.h"
#include "PlayScene.h"
#define PIRANHAPLANT_BBOX_WIDTH 16
#define PIRANHAPLANT_BBOX_HEIGHT 32


#define PIRANHAPLANT_SHOOT_DELAY_TIME 5000

#define PIRANHAPLANT_STATE_HEAD_UP 100
#define PIRANHAPLANT_STATE_HEAD_DOWN 200

#define ID_ANI_PIRANHAPLANT_HEAD_UP 16000
#define ID_ANI_PIRANHAPLANT_HEAD_DOWN 16001

#define ID_ANI_PIRANHAPLANT_HEAD_UP_FLIP 16002
#define ID_ANI_PIRANHAPLANT_HEAD_DOWN_FLIP 16003

#define ID_ANI_PIRANHAPLANT_NOT_SHOOT 16004

#define PIRANHAPLANT_TYPE_SHOOT 1
#define PIRANHAPLANT_TYPE_NOT_SHOOT 2

class CPiranhaPlant : public CGameObject
{
protected:
	float ax;
	float ay;
	float disXToPlayer;
	float disYToPlayer;
	int isFlip;
	int type;
	ULONGLONG shoot_start;
	LPGAMEOBJECT player;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CPiranhaPlant(float x, float y, LPGAMEOBJECT player, int type = PIRANHAPLANT_TYPE_SHOOT);
	virtual void SetState(int state);
	void CalPosPlayer();
	void Shoot();
};