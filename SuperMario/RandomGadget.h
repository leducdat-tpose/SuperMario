#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define RANDOMGADGET_GRAVITY -0.00017f
#define RANDOMGADGET_EXIST_TIME 3200

#define RANDOMGADGET_BBOX_WIDTH 16
#define RANDOMGADGET_BBOX_HEIGHT 16

#define ID_ANI_RANDOMGADGET 21000
#define ID_ANI_MUSHROOM_GADGET 21010
#define ID_ANI_FLOWER_GADGET 21020
#define ID_ANI_STAR_GADGET 21030

class CRandomGadget : public CGameObject
{
private:
	int isCollected;
	float ay;
	ULONGLONG delete_start;
public:
	CRandomGadget(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return 0; }
	void CollectGadget();
};