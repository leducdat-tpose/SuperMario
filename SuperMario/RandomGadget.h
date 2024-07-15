#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define RANDOMGADGET_BBOX_WIDTH 16
#define RANDOMGADGET_BBOX_HEIGHT 16

#define ID_ANI_RANDOMGADGET 21000

class CRandomGadget : public CGameObject
{
private:

public:
	CRandomGadget(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return 0; }
	void CollectGadget();
};