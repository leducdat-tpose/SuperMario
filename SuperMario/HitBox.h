#pragma once
#include "GameObject.h"
//This will use if the hit box has animations
#include "Animation.h"
#include "Animations.h"

#define HITBOX_SPEED 0.1f


//E.g: When Mario is raccoon he can attack goomba by click A
class CHitBox : public CGameObject {
	float bboxWidth;
	float bboxHeight;
	bool active;
public:
	CHitBox(float x, float y, float bboxWidth, float bboxHeight, bool active = false) : CGameObject(x, y)
	{
		this->bboxWidth = bboxWidth;
		this->bboxHeight = bboxHeight;
		this->active = active;
	}
	void Render() {
		//Common is not has any render
		//Can has some animation such as in Dead Cells
	}
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetActive(bool active) { this->active = active; }
};