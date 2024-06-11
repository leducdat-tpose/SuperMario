#pragma once
#include "GameObject.h"

#define CHECKFALL_GRAVITY 0.001f

class CCheckFall :CGameObject
{
protected:
	LPGAMEOBJECT GameObject;
	float bboxWidth;
	float bboxHeight;
	float ay;
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
public:
	CCheckFall(LPGAMEOBJECT GameObject, float x, float y, float bboxWidth, float bboxHeight) :CGameObject(x, y)
	{
		this->ay = CHECKFALL_GRAVITY;
		this->GameObject = GameObject;
		this->bboxWidth = bboxWidth;
		this->bboxHeight = bboxHeight;
	}
};