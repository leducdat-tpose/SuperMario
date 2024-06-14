#pragma once
#include "GameObject.h"

#define TRIGGER_BUTTON_BBOX_WIDTH 16
#define TRIGGER_BUTTON_BBOX_HEIGHT 16
#define TRIGGER_BUTTON_GRAVITY 0.001f

#define ID_ANI_TRIGGER_BUTTON 19000
#define ID_ANI_TRIGGER_BUTTON_CLICKED 19001

class CTriggerButton : public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG fall_start;
	bool isClicked = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; };
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CTriggerButton(float x, float y): CGameObject(x,y)
	{}
};