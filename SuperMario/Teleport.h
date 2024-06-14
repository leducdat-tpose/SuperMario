#pragma once

#include "GameObject.h"

#define TELEPORT_BBOX_WIDTH 32
#define TELEPORT_BBOX_HEIGHT 16

class CTeleport :public CGameObject
{
protected:
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
public:
	CTeleport(float x, float y):CGameObject(x,y){}
};
