#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LUCKYBOX 13000
#define ID_ANI_LUCKYBOX_COLLECTED 13001
#define LUCKYBOX_WIDTH 16
#define LUCKYBOX_BBOX_WIDTH 16
#define LUCKYBOX_BBOX_HEIGHT 16

#define LUCKYBOX_COLLECTED_STATE_UP 100
#define LUCKYBOX_COLLECTED_STATE_DOWN 200
#define LUCKYBOX_NORNMAL_STATE 300

#define LUCKYBOX_MOVING_Y 5.0f
#define TIME_TO_UP_DOWN 500


class CLuckyBox : public CGameObject {
private:
	float upDown_start;
	bool isCollected;
public:
	CLuckyBox(float x, float y) : CGameObject(x, y) {
		this->upDown_start = 0;
		this->isCollected = false;
		CGameObject::SetState(LUCKYBOX_NORNMAL_STATE);
	}
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetIsCollected(bool isCollected);
	bool GetIsCollected();
	void SetState(int state);
};