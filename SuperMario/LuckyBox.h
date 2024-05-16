#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LUCKYBOX 13000
#define LUCKYBOX_WIDTH 16
#define LUCKYBOX_BBOX_WIDTH 16
#define LUCKYBOX_BBOX_HEIGHT 16

class CLuckyBox : public CGameObject {
public:
	CLuckyBox(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};