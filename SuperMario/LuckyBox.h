#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LUCKYBOX 13000
#define ID_ANI_LUCKYBOX_COLLECTED 13001
#define LUCKYBOX_WIDTH 16
#define LUCKYBOX_BBOX_WIDTH 16
#define LUCKYBOX_BBOX_HEIGHT 16

class CLuckyBox : public CGameObject {
private:
	bool isCollected;
public:
	CLuckyBox(float x, float y) : CGameObject(x, y) {
		this->isCollected = false;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetIsCollected(bool isCollected);
};