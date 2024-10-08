#pragma once
#include "GameObject.h"
//This will use if the hit box has animations
#include "Animation.h"
#include "Animations.h"

#include "Goomba.h"
#include "Koopas.h"
#include "Brick.h"

//E.g: When Mario is raccoon, he can attack goomba by click A
class CHitBox : public CGameObject {
protected:
	//hitbox will follow this object
	LPGAMEOBJECT GameObject;
	float bboxWidth;
	float bboxHeight;
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
public:
	CHitBox(LPGAMEOBJECT GameObject, float x, float y,float bboxWidth, float bboxHeight, bool enable = false) : CGameObject(x, y)
	{
		this->GameObject = GameObject;
		this->bboxWidth = bboxWidth;
		this->bboxHeight = bboxHeight;
		this->enable = enable;
	}
};