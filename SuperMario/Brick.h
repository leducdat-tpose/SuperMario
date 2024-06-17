#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "HiddenButton.h"
#include "PlayScene.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_GOLD_BRICK 10100
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define TYPE_NORMAL_BRICK 0
#define TYPE_GOLD_BRICK 100

class CBrick : public CGameObject {
	int type;
public:
	CBrick(float x, float y, int type = TYPE_NORMAL_BRICK) : CGameObject(x, y)
	{
		this->type = type;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};