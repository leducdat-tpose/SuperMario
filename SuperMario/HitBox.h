#pragma once
#include "GameObject.h"
//This will use if the hit box has animations
#include "Animation.h"
#include "Animations.h"

#define HITBOX_SPEED 0.1f


//E.g: When Mario is raccoon, he can attack goomba by click A
class CHitBox : public CGameObject {
protected:
	//hitbox will follow this object
	LPGAMEOBJECT GameObject;
	float bboxWidth;
	float bboxHeight;
	bool active;
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render() {
		//Common is not has any render
		//Can has some animation such as in Dead Cells
	}
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
public:
	CHitBox(LPGAMEOBJECT GameObject, float x, float y, float bboxWidth, float bboxHeight, bool active = false) : CGameObject(x, y)
	{
		this->GameObject = GameObject;
		this->bboxWidth = bboxWidth;
		this->bboxHeight = bboxHeight;
		this->active = active;
	}
	void SetActive(bool active) { this->active = active; }
	void UpdatePos()
	{
		GameObject->GetPosition(x, y);
	}
};